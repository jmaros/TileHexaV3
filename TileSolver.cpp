// TileSolver.cpp
// Implements the backtracking solver for the hexagonal calendar puzzle.
//
// All geometry helpers required by the solver are duplicated here as
// file-local functions so this translation unit is fully self-contained
// and does not reach into the anonymous namespace of Hexa3DApp.cpp.

#include "TileSolver.h"
#include <numeric>
#include <random>

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

// Capture a per-piece snapshot of the entire board so the user can
// restore after a solver run with Esc.
static void savePresolveState(AppState& app)
{
	const int n = (int)app.pieces.size();
	app.presolveState.resize(n);
	for (int i = 0; i < n; ++i) {
		const PieceState& p = app.pieces[i];
		PieceSnapshot& s    = app.presolveState[i];
		s.x             = p.x;
		s.y             = p.y;
		s.placed        = p.placed;
		s.offsets       = p.offsets;
		s.occupiedCells = p.occupiedCells;
		s.ghostCenters  = p.ghostCenters;
	}
	app.presolveUndoStack = app.undoStack;
	app.presolveRedoStack = app.redoStack;
}

// Restore the board to the snapshot saved by savePresolveState.
void restorePresolveState(AppState& app)
{
	if (app.presolveState.empty()) return;
	// Clear all occupancy first.
	app.occupancy.assign(app.occupancy.size(), -1);
	const int n = (int)app.pieces.size();
	for (int i = 0; i < n && i < (int)app.presolveState.size(); ++i) {
		const PieceSnapshot& s = app.presolveState[i];
		PieceState& p          = app.pieces[i];
		p.x             = s.x;
		p.y             = s.y;
		p.placed        = s.placed;
		p.offsets       = s.offsets;
		p.occupiedCells = s.occupiedCells;
		p.ghostCenters  = s.ghostCenters;
		if (p.placed) {
			for (int c : p.occupiedCells)
				if (c >= 0 && c < (int)app.occupancy.size())
					app.occupancy[c] = i;
		}
	}
	app.undoStack = app.presolveUndoStack;
	app.redoStack = app.presolveRedoStack;
	app.solved = checkSolved(app);
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

// solveBacktrack places pieces in the order given by pieceOrder[].
// When a full solution is found it decrements *skipRemaining; if the
// counter reaches 0 the solution is accepted and the function returns true.
// This lets the caller enumerate solutions by passing skip=0 (first),
// skip=1 (second), etc.
static bool solveBacktrack(AppState& app,
							const std::vector<std::vector<Offsets>>& orientations,
							const std::vector<int>& pieceOrder,
							std::vector<bool>& placed,
							int& skipRemaining)
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
	if (target == -1) {
		// All free cells covered — this is a complete solution.
		if (skipRemaining > 0) { --skipRemaining; return false; }
		return true;
	}

	const float tx = tiles[target].x;
	const float ty = tiles[target].y;

	for (int pi : pieceOrder) {
		if (placed[pi]) continue;
		for (const auto& ori : orientations[pi]) {
			for (int k = 0; k < (int)ori.size(); ++k) {
				int anchorTile = nearestCell(tiles,
											 tx - ori[k].first,
											 ty - ori[k].second,
											 R * 0.5f);
				if (anchorTile < 0) continue;

				const float snapX = tiles[anchorTile].x;
				const float snapY = tiles[anchorTile].y;

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
				placed[pi]                   = true;
				app.pieces[pi].x             = snapX;
				app.pieces[pi].y             = snapY;
				app.pieces[pi].offsets       = ori;
				app.pieces[pi].occupiedCells = cells;
				app.pieces[pi].placed        = true;

				if (solveBacktrack(app, orientations, pieceOrder, placed, skipRemaining))
					return true;

				// Unplace.
				for (int c : cells) app.occupancy[c] = -1;
				placed[pi]                   = false;
				app.pieces[pi].placed        = false;
				app.pieces[pi].occupiedCells.clear();
			}
		}
	}
	return false;
}

// ── shared setup / teardown ──────────────────────────────────────────────

static void resetAllPieces(AppState& app)
{
	app.occupancy.assign(app.occupancy.size(), -1);
	for (int i = 0; i < (int)app.pieces.size(); ++i) {
		// Preserve ghostCenters — they hold the permanent home silhouette.
		const auto savedGhost = app.pieces[i].ghostCenters;
		app.pieces[i].placed = false;
		app.pieces[i].occupiedCells.clear();
		restorePieceToHome(app, i);
		app.pieces[i].ghostCenters = savedGhost;
	}
	app.undoStack.clear();
	app.redoStack.clear();
	app.solved = false;
}

static bool runSolver(AppState& app,
					  const std::vector<std::vector<Offsets>>& orientations,
					  const std::vector<int>& pieceOrder)
{
	std::vector<bool> placed(app.pieces.size(), false);
	const bool found = solveBacktrack(app, orientations, pieceOrder, placed,
									  app.solverSkipCount);
	if (found) {
		for (auto& p : app.pieces)
			p.ghostCenters = pieceCenters(p);
		app.solved = checkSolved(app);
	} else {
		resetAllPieces(app);
	}
	return found;
}

// ── public entry points ──────────────────────────────────────────────────

// Phase 1: called from the key handler.
// Picks a random label, arms the pending flag, sets solverRunning so the
// banner is visible during the very next rendered frame.
void prepareSolve(AppState& app, bool randomize)
{
	if (app.solverRunning || app.solverPending || app.dragging) return;

	static std::mt19937 rng{ std::random_device{}() };
	static const char* labels[] = { "Searching...", "Thinking...", "Solving..." };
	app.solverLabel    = labels[std::uniform_int_distribution<int>(0, 2)(rng)];
	app.solverRandomize = randomize;
	app.solverRunning  = true;   // banner becomes visible immediately
	app.solverPending  = true;   // executePendingSolve will run after the swap
}

// Phase 2: called from the render loop AFTER glfwSwapBuffers.
// The user has already seen one frame with the label; now we actually solve.
void executePendingSolve(AppState& app)
{
	if (!app.solverPending) return;
	app.solverPending = false;

	// Snapshot only on the very first call in a sequence.
	if (app.presolveState.empty())
		savePresolveState(app);

	resetAllPieces(app);

	std::vector<std::vector<Offsets>> orientations(app.pieces.size());
	for (int i = 0; i < (int)app.pieces.size(); ++i)
		generateOrientations(app.pieces[i].homeOffsets, orientations[i]);

	std::vector<int> order((int)app.pieces.size());
	std::iota(order.begin(), order.end(), 0);

	if (app.solverRandomize) {
		static std::mt19937 rng2{ std::random_device{}() };
		std::shuffle(order.begin(), order.end(), rng2);
		for (auto& oriList : orientations)
			std::shuffle(oriList.begin(), oriList.end(), rng2);
		app.solverSkipCount = 0;
	}

	const bool found = runSolver(app, orientations, order);
	if (found)
		++app.solverSkipCount;
	else
		app.solverSkipCount = 0;

	app.solverRunning = false;   // banner switches from label to SUCCESS / nothing
}
