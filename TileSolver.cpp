// TileSolver.cpp
// Implements the backtracking solver for the hexagonal calendar puzzle.
//
// All geometry helpers required by the solver are duplicated here as
// file-local functions so this translation unit is fully self-contained
// and does not reach into the anonymous namespace of Hexa3DApp.cpp.

#include "TileSolver.h"

// ── file-local geometry helpers ──────────────────────────────────────────

static bool topLeftLess(const std::pair<float,float>& a,
						const std::pair<float,float>& b)
{
	if (fabsf(a.second - b.second) > 0.001f) return a.second > b.second;
	return a.first < b.first;
}

static void cleanTiny(float& v)
{
	if (fabsf(v) < 0.00001f) v = 0.0f;
}

static void normalizeToUpperLeft(Offsets& offsets)
{
	if (offsets.empty()) return;
	auto anchor = offsets[0];
	for (const auto& c : offsets)
		if (topLeftLess(c, anchor)) anchor = c;
	for (auto& c : offsets) {
		c.first  -= anchor.first;
		c.second -= anchor.second;
		cleanTiny(c.first);
		cleanTiny(c.second);
	}
	std::sort(offsets.begin(), offsets.end(),
			  [](const auto& a, const auto& b){ return topLeftLess(a,b); });
}

// Rotate or mirror a single point (same formula as applyPieceTransform in
// Hexa3DApp.cpp so orientations are consistent with manual transforms).
static std::pair<float,float> transformedPoint(std::pair<float,float> c, bool rotateCW, bool mirror)
{
	if (mirror) { c.first = -c.first; cleanTiny(c.first); cleanTiny(c.second); return c; }
	const float cs =  0.5f;
	const float sn = rotateCW ? -0.86602540378443864676f : 0.86602540378443864676f;
	float rx = cs * c.first - sn * c.second;
	float ry = sn * c.first + cs * c.second;
	cleanTiny(rx); cleanTiny(ry);
	return { rx, ry };
}

// Find the index of the tile whose centre is within maxDist of (x,y).
// Returns -1 when nothing is close enough.
static int nearestCell(const std::vector<HexTile>& tiles,
					   float x, float y, float maxDist)
{
	int   best  = -1;
	float best2 = maxDist * maxDist;
	for (int i = 0; i < (int)tiles.size(); ++i) {
		float dx = tiles[i].x - x;
		float dy = tiles[i].y - y;
		float d2 = dx*dx + dy*dy;
		if (d2 <= best2) { best2 = d2; best = i; }
	}
	return best;
}

// Compute world-space hex centres for a piece.
static std::vector<std::pair<float,float>> pieceCenters(const PieceState& p)
{
	std::vector<std::pair<float,float>> c;
	c.reserve(p.offsets.size());
	for (const auto& o : p.offsets)
		c.push_back({ p.x + o.first, p.y + o.second });
	return c;
}

// Reset piece occupancy bookkeeping.
static void clearPieceOccupancy(AppState& app, int pi)
{
	for (int c : app.pieces[pi].occupiedCells)
		if (c >= 0 && c < (int)app.occupancy.size() && app.occupancy[c] == pi)
			app.occupancy[c] = -1;
	app.pieces[pi].occupiedCells.clear();
	app.pieces[pi].placed = false;
}

// Send a piece back to its home position.
static void restorePieceToHome(AppState& app, int pi)
{
	clearPieceOccupancy(app, pi);
	PieceState& p = app.pieces[pi];
	p.x       = p.homeX;
	p.y       = p.homeY;
	p.offsets = p.homeOffsets;
	p.placed  = false;
	p.occupiedCells.clear();
}

// Returns true when every non-protected cell is occupied and all pieces placed.
static bool checkSolved(const AppState& app)
{
	if (app.tiles == nullptr) return false;
	for (const auto& p : app.pieces)
		if (!p.placed) return false;
	int freeCells = 0;
	for (int i = 0; i < (int)app.occupancy.size(); ++i) {
		if (app.occupancy[i] == -1) {
			++freeCells;
			if (!(*app.tiles)[i].protectedDate) return false;
		}
	}
	return freeCells == app.protectedCellCount;
}

// ── orientation generation ───────────────────────────────────────────────

static std::string orientationKey(const Offsets& o)
{
	Offsets s = o;
	normalizeToUpperLeft(s);
	char buf[512] = {};
	int  pos = 0;
	for (const auto& p : s)
		pos += snprintf(buf + pos, (int)sizeof(buf) - pos, "%d,%d;",
						(int)lroundf(p.first  * 1000.0f),
						(int)lroundf(p.second * 1000.0f));
	return std::string(buf);
}

void generateOrientations(const Offsets& base, std::vector<Offsets>& out)
{
	out.clear();
	std::set<std::string> seen;
	Offsets cur = base;
	normalizeToUpperLeft(cur);

	for (int mirror = 0; mirror < 2; ++mirror) {
		for (int rot = 0; rot < 6; ++rot) {
			// Add current orientation if unique
			Offsets tmp = cur;
			normalizeToUpperLeft(tmp);
			if (seen.insert(orientationKey(tmp)).second)
				out.push_back(tmp);
			// Rotate 60° CW
			for (auto& p : cur)
				p = transformedPoint(p, /*rotateCW=*/true, /*mirror=*/false);
		}
		// Mirror once, then do the next 6 rotations
		for (auto& p : cur)
			p = transformedPoint(p, /*rotateCW=*/false, /*mirror=*/true);
	}
}

// ── backtracking solver ──────────────────────────────────────────────────

static bool solveBacktrack(AppState& app,
							const std::vector<std::vector<Offsets>>& orientations,
							std::vector<bool>& placed)
{
	const auto& tiles = *app.tiles;

	// Find the first free, non-protected cell (exact-cover anchor).
	int target = -1;
	for (int i = 0; i < (int)app.occupancy.size(); ++i) {
		if (app.occupancy[i] == -1 && !tiles[i].protectedDate) {
			target = i;
			break;
		}
	}
	if (target == -1) return true; // all free cells covered → solved

	const float tx = tiles[target].x;
	const float ty = tiles[target].y;

	for (int pi = 0; pi < (int)app.pieces.size(); ++pi) {
		if (placed[pi]) continue;
		for (const auto& ori : orientations[pi]) {
			// Try covering the target cell with each hex k of this orientation.
			for (int k = 0; k < (int)ori.size(); ++k) {
				// Compute where the anchor tile would land.
				int anchorTile = nearestCell(tiles,
											 tx - ori[k].first,
											 ty - ori[k].second,
											 R * 0.5f);
				if (anchorTile < 0) continue;

				const float snapX = tiles[anchorTile].x;
				const float snapY = tiles[anchorTile].y;

				// Validate all hexes of the orientation.
				std::vector<int> cells;
				cells.reserve(ori.size());
				bool ok = true;
				for (const auto& off : ori) {
					int ci = nearestCell(tiles,
										 snapX + off.first,
										 snapY + off.second,
										 R * 0.4f);
					if (ci < 0 || tiles[ci].protectedDate) { ok = false; break; }
					if (app.occupancy[ci] != -1)            { ok = false; break; }
					if (std::find(cells.begin(), cells.end(), ci) != cells.end())
															{ ok = false; break; }
					cells.push_back(ci);
				}
				if (!ok) continue;

				// Place.
				for (int c : cells) app.occupancy[c] = pi;
				placed[pi]                  = true;
				app.pieces[pi].x            = snapX;
				app.pieces[pi].y            = snapY;
				app.pieces[pi].offsets      = ori;
				app.pieces[pi].occupiedCells = cells;
				app.pieces[pi].placed       = true;

				if (solveBacktrack(app, orientations, placed)) return true;

				// Unplace.
				for (int c : cells) app.occupancy[c] = -1;
				placed[pi]                  = false;
				app.pieces[pi].placed       = false;
				app.pieces[pi].occupiedCells.clear();
			}
		}
	}
	return false;
}

// ── public entry point ───────────────────────────────────────────────────

bool solvePuzzle(AppState& app)
{
	if (app.dragging) return false;

	// Reset every piece to home and clear occupancy.
	app.occupancy.assign(app.occupancy.size(), -1);
	for (int i = 0; i < (int)app.pieces.size(); ++i) {
		app.pieces[i].placed = false;
		app.pieces[i].occupiedCells.clear();
		restorePieceToHome(app, i);
	}
	app.undoStack.clear();
	app.redoStack.clear();
	app.solved = false;

	// Generate orientations from each piece's normalised home offsets.
	std::vector<std::vector<Offsets>> orientations(app.pieces.size());
	for (int i = 0; i < (int)app.pieces.size(); ++i)
		generateOrientations(app.pieces[i].homeOffsets, orientations[i]);

	std::vector<bool> placed(app.pieces.size(), false);
	const bool found = solveBacktrack(app, orientations, placed);

	if (found) {
		// Update ghost silhouettes to match the solution positions.
		for (auto& p : app.pieces)
			p.ghostCenters = pieceCenters(p);
		app.solved = checkSolved(app);
	} else {
		// No solution found — put everything back home.
		app.occupancy.assign(app.occupancy.size(), -1);
		for (int i = 0; i < (int)app.pieces.size(); ++i) {
			app.pieces[i].placed = false;
			app.pieces[i].occupiedCells.clear();
			restorePieceToHome(app, i);
		}
	}
	return found;
}
