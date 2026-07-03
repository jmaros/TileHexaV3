#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "GLFW/glfw3.h"
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "TileSolver.h"

constexpr float PI = 3.14159265358979323846f;

// -----------------------------------------------------------------------
	// Hexagonal grid geometry
	//   Side-5 hexagon: 9 rows, widths 5-6-7-8-9-8-7-6-5
	//   Pointy-top orientation:
	//     horizontal spacing  sx = sqrt(3) * R  (adjacent centres, same row)
	//     vertical   spacing  sy = 1.5    * R  (adjacent row centres)
	//   1% gap: draw each tile at 99 % of its spacing radius
	// -----------------------------------------------------------------------
const float R = 0.5f;
const float baseR = R * 8.5f;     // The total radius of the whole board (from centre to outer edge)
const float drawR = R * 0.99f;    // 1% gap
const float sx = sqrtf(3.0f) * R;
const float sy = 1.5f * R;
constexpr int WINDOW_W = 800;
constexpr int WINDOW_H = 600;

// Cell descriptor and enums are defined in TileSolver.h
GLuint FONT_BASE = 0;   // bitmap-font display-list base; set after GL context is created

// 9-row layout (row 4 = centre, y = 0)
//
//  Row 0 (5): - ***  ***  May  Jun  ---  Jul  Aug
//  Row 1 (6): ***  ***  Apr  Sun  Mon  Tue  Wed  Sep
//  Row 2 (7): - ***  Mar  ---  Thu  Fri  Sat  ---  Oct
//  Row 3 (8): ***  Feb  1   2    3    4    5    6   Nov
//  Row 4 (9): - Jan  7    8    9   10   11   12   13  Dec
//  Row 5 (8): *** ---  14   15   16   17   18   19  ---
//  Row 6 (7): - ***  --- 20   21   22   23   24  ---
//  Row 7 (6): *** *** ---  25   26   27   28  ---
//  Row 8 (5): - *** ***  ---  29   30   31  ---

// Show the three letters and the numbers in white on the tiles!

std::array<std::array<char, 4>, 12> monthNames = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

std::array<std::array<char, 4>, 7> weekNames = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

const std::vector<std::vector<Cell>> grid = {
	{{CT_MONTH,5},{CT_MONTH,6},{CT_EMPTY,0},{CT_MONTH,7},{CT_MONTH,8}},
	{{CT_MONTH,4},{CT_WDAY,0},{CT_WDAY,1},{CT_WDAY,2},{CT_WDAY,3},{CT_MONTH,9}},
	{{CT_MONTH,3},{CT_EMPTY,0},{CT_WDAY,4},{CT_WDAY,5},{CT_WDAY,6},{CT_EMPTY,0},{CT_MONTH,10}},
	{{CT_MONTH,2},{CT_DATE,1},{CT_DATE,2},{CT_DATE,3},{CT_DATE,4},{CT_DATE,5},{CT_DATE,6},{CT_MONTH,11}},
	{{CT_MONTH,1},{CT_DATE,7},{CT_DATE,8},{CT_DATE,9},{CT_DATE,10},{CT_DATE,11},{CT_DATE,12},{CT_DATE,13},{CT_MONTH,12}},
	{{CT_EMPTY,0},{CT_DATE,14},{CT_DATE,15},{CT_DATE,16},{CT_DATE,17},{CT_DATE,18},{CT_DATE,19},{CT_EMPTY,0}},
	{{CT_EMPTY,0},{CT_DATE,20},{CT_DATE,21},{CT_DATE,22},{CT_DATE,23},{CT_DATE,24},{CT_EMPTY,0}},
	{{CT_EMPTY,0},{CT_DATE,25},{CT_DATE,26},{CT_DATE,27},{CT_DATE,28},{CT_EMPTY,0}},
	{{CT_EMPTY,0},{CT_DATE,29},{CT_DATE,30},{CT_DATE,31},{CT_EMPTY,0}},
};

//  Row 0 (5): - ***  ***  May  Jun  ---  Jul  Aug
//  Row 1 (6): ***  ***  Apr  Sun  Mon  Tue  Wed  Sep
//  Row 2 (7): - ***  Mar  ---  Thu  Fri  Sat  ---  Oct
//  Row 3 (8): ***  Feb  1   2    3    4    5    6   Nov
//  Row 4 (9): - Jan  7    8    9   10   11   12   13  Dec

// HexTile is defined in TileSolver.h

// PieceDefinition is defined in TileSolver.h

const std::vector<PieceDefinition> PieceDefinitions = {
	{ 'A', {{0.0f,0.0f},{1.0f * sx,0.0f},{2.0f * sx,0.0f},{3.0f * sx,0.0f},{4.0f * sx,0.0f}}, 1.0f,1.0f,0.3f },
	{ 'B', {{0.0f,0.0f},{1.0f * sx,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{2.5f * sx,-1.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'C', {{-1.0f * sx,0.0f},{0.0f,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{2.5f * sx,-1.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'D', {{0.0f,0.0f},{1.0f * sx,0.0f},{2.0f * sx,0.0f},{3.0f * sx,0.0f},{3.5f * sx,-1.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'E', {{-1.5f * sx,0.0f},{-0.5f * sx,0.0f},{0.5f * sx,0.0f},{0.0f * sx,-1.0f * sy},{1.0f * sx,-1.0f * sy},{2.0f * sx,-1.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'F', {{0.0f,0.0f},{1.0f * sx,0.0f},{2.0f * sx,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{2.5f * sx,-1.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'G', {{0.0f,0.0f},{1.0f * sx,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{1.0f * sx,-2.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'H', {{0.0f,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{2.5f * sx,-1.0f * sy},{3.0f * sx,-2.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'I', {{0.0f,0.0f},{1.0f * sx,0.0f},{2.0f * sx,0.0f},{2.5f * sx,-1.0f * sy},{3.0f * sx,-2.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'J', {{0.5f * sx,0.0f},{1.5f * sx,0.0f},{1.0f * sx,-1.0f * sy},{0.5f * sx,-2.0f * sy},{1.5f * sx,-2.0f * sy}}, 1.0f,1.0f,0.3f },
	{ 'K', {{0.0f,0.0f},{1.0f * sx,0.0f},{2.0f * sx,0.0f},{0.5f * sx,-1.0f * sy},{1.5f * sx,-1.0f * sy},{1.0f * sx,-2.0f * sy}}, 1.0f,1.0f,0.3f },
};

void setPerspective(float fovy, float aspect, float zNear, float zFar)
{
	float fH = tan(fovy / 360.0f * PI) * zNear;
	float fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void glText(const char* text)
{
	if (FONT_BASE == 0 || text == nullptr) return;
	glRasterPos3f(0.0f, 0.0f, 0.01f);
	int len = (int)strlen(text);
	glListBase(FONT_BASE - 32);
	glCallLists(len, GL_UNSIGNED_BYTE, text);
}

void glText(const std::array<char, 4>& text)
{
	glText(text.data());
}

namespace {
	void CreateHexVertices(GLenum cap, double radius, double rotation = PI / 6.0f)
	{
		glBegin(cap);
		for (int i = 0; i < 6; ++i) {
			float angle = PI / 3.0f * i + rotation;
			glVertex3f(radius * cosf(angle), radius * sinf(angle), 0.0f);
		}
		glEnd();
	}

	void drawHex(float			cx,
				 float			cy,
				 float			cz,
				 float			radius,
				 bool			highlight,
				 Cell const& content)
	{
		glPushMatrix();
		glTranslatef(cx, cy, cz);

		float r, g, b;
		if (highlight) {
			r = 1.0f; g = 0.7f; b = 0.2f;
		} else {
			r = 0.3f; g = 0.6f; b = 0.8f;
		}
		std::array<char, 4> text{};
		switch (content.type) {
			case CT_MONTH: { r *= 0.8f; g *= 0.8f; b *= 0.8f; text = monthNames[content.value - 1]; } break;
			case CT_WDAY: { r *= 0.6f; g *= 0.6f; b *= 0.6f; text = weekNames[content.value]; } break;
			case CT_DATE: { r *= 0.4f; g *= 0.4f; b *= 0.4f; snprintf(text.data(), text.size(), "%d", content.value); } break;
			case CT_EMPTY: { r = 0.82f; g = 0.74f; b = 0.18f; } break; // empty playable cell: no text, yellow-brown shade
			case CT_BASE: { r = 1.0f; g = 1.0f; b = 0.0f; } break;
		}
		// Filled polygon – pushed back slightly so the border line renders on top
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glColor3f(r, g, b);
		if (content.type == CT_BASE) {
			CreateHexVertices(GL_POLYGON, radius, 0.0f);
		} else {
			CreateHexVertices(GL_POLYGON, radius);
		}
		glDisable(GL_POLYGON_OFFSET_FILL);

		if (content.type == CT_EMPTY) {
			// Empty cells are visible hexagons, but without text.
			glColor3f(0.95f, 0.88f, 0.25f);
			glLineWidth(1.1f);
			CreateHexVertices(GL_LINE_LOOP, radius);
		} else if (content.type != CT_BASE) {
			// Text in white
			glColor3f(1.0f, 1.0f, 1.0f);
			glPushMatrix();
			double x1 = (strlen(text.data()) > 1 ? -0.18f : 0.0f);
			double x2 = (strlen(text.data()) > 2 ? -0.28f : x1);
			glTranslatef(x2, 0.0, 0.0f);
			glText(text);
			glPopMatrix();

			// Border 2.0 times brighter, but not exceeding 1.0
			glColor3f(r * 2.0f, g * 2.0f, b * 2.0f);
			glLineWidth(1.5f);
			CreateHexVertices(GL_LINE_LOOP, radius);
		}
		glPopMatrix();
	}

	// Forward declaration so drawPiecePreviews can always resolve this helper.
	void drawPieceOuterOutline(const std::vector<std::pair<float, float>>& centers, float radius, float z = 0.0f);

	void drawPieceOuterOutline(const std::vector<std::pair<float, float>>& centers, float radius, float z)
	{
		if (centers.empty()) return;

		const std::array<std::pair<float, float>, 6> vertexDir = { {
			{ cosf(PI / 6.0f),  sinf(PI / 6.0f)  },
			{ cosf(PI / 2.0f),  sinf(PI / 2.0f)  },
			{ cosf(5.0f * PI / 6.0f),  sinf(5.0f * PI / 6.0f)  },
			{ cosf(7.0f * PI / 6.0f),  sinf(7.0f * PI / 6.0f)  },
			{ cosf(3.0f * PI / 2.0f),  sinf(3.0f * PI / 2.0f)  },
			{ cosf(11.0f * PI / 6.0f), sinf(11.0f * PI / 6.0f) }
		} };

		const std::array<std::pair<float, float>, 6> neighbourDir = { {
			{ 0.5f * sx,  sy },
			{ -0.5f * sx, sy },
			{ -sx,        0.0f },
			{ -0.5f * sx, -sy },
			{ 0.5f * sx,  -sy },
			{ sx,         0.0f }
		} };

		auto hasNeighbour = [&](const std::pair<float, float>& c, const std::pair<float, float>& d) -> bool
			{
				const float tx = c.first + d.first;
				const float ty = c.second + d.second;
				const float eps = 0.01f;

				for (const auto& o : centers) {
					if (fabsf(o.first - tx) < eps && fabsf(o.second - ty) < eps) {
						return true;
					}
				}
				return false;
			};

		// Draw only exterior edges.  Shared edges are detected from neighbouring
		// hex centres, rather than by comparing rounded vertex coordinates.  This
		// removes the initial B/C/E internal outline artefacts caused by tiny float
		// differences between nominally identical edge vertices.
		const float halfWidth = radius * 0.045f;
		glBegin(GL_QUADS);
		for (const auto& c : centers) {
			for (int i = 0; i < 6; ++i) {
				if (hasNeighbour(c, neighbourDir[i])) continue;

				const auto& v1 = vertexDir[i];
				const auto& v2 = vertexDir[(i + 1) % 6];
				float ax = c.first + radius * v1.first;
				float ay = c.second + radius * v1.second;
				float bx = c.first + radius * v2.first;
				float by = c.second + radius * v2.second;

				float dx = bx - ax;
				float dy = by - ay;
				float len = sqrtf(dx * dx + dy * dy);
				if (len <= 0.000001f) continue;

				float ux = dx / len;
				float uy = dy / len;
				float nx = -uy * halfWidth;
				float ny = ux * halfWidth;

				ax -= ux * halfWidth;
				ay -= uy * halfWidth;
				bx += ux * halfWidth;
				by += uy * halfWidth;

				glVertex3f(ax + nx, ay + ny, z);
				glVertex3f(bx + nx, by + ny, z);
				glVertex3f(bx - nx, by - ny, z);
				glVertex3f(ax - nx, ay - ny, z);
			}
		}
		glEnd();
	}

	[[maybe_unused]]
	void drawPiecePreviews(const std::vector<PieceDefinition>& pieces)
	{
		const float pR = drawR;
		const float fillR = pR * 1.015f; // tiny overlap to hide internal raster seams

		auto pieceAnchor = [](char label) -> std::pair<float, float>
			{
				switch (label) {
					// left side: A..E top -> down
					case 'A': return { -9.6f,  5.6f };
					case 'B': return { -9.6f,  2.9f };
					case 'C': return { -9.6f,  0.0f };
					case 'D': return { -9.6f, -3.5f };
					case 'E': return { -9.6f, -5.7f };

					// bottom middle: F
					case 'F': return { -0.2f, -5.5f };

					// right side: G..K bottom -> up
					case 'G': return { 6.1f, -6.0f };
					case 'H': return { 6.1f, -2.6f };
					case 'I': return { 6.1f, -0.2f };
					case 'J': return { 6.1f,  3.2f };
					case 'K': return { 6.1f,  6.2f };
					default:  return { 6.0f,  0.0f };
				}
			};

		for (const auto& p : pieces) {
			float tlX = p.offsets[0].first, tlY = p.offsets[0].second;
			for (const auto& rc : p.offsets) {
				if (rc.second > tlY || (rc.second == tlY && rc.first < tlX)) {
					tlX = rc.first; tlY = rc.second;
				}
			}

			auto anc = pieceAnchor(p.label);
			const float ox = anc.first;
			const float oy = anc.second;

			std::vector<std::pair<float, float>> pieceCenters;
			pieceCenters.reserve(p.offsets.size());

			float minCY = 1e9f, maxCY = -1e9f;

			for (const auto& rc : p.offsets) {
				float px = rc.first - tlX + ox;
				float py = rc.second - tlY + oy;
				pieceCenters.push_back({ px, py });
				minCY = fminf(minCY, py);
				maxCY = fmaxf(maxCY, py);

				glPushMatrix();
				glTranslatef(px, py, 0.0f);

				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset(1.0f, 1.0f);
				glColor3f(p.r * 0.7f, p.g * 0.7f, p.b * 0.7f);
				CreateHexVertices(GL_POLYGON, fillR);
				glDisable(GL_POLYGON_OFFSET_FILL);

				glPopMatrix();
			}

			glColor3f(p.r, p.g, p.b);
			drawPieceOuterOutline(pieceCenters, R, 0.07f);

			std::array<char, 4> lbl{};
			lbl[0] = p.label;
			glPushMatrix();
			glTranslatef(ox - 0.9f, (minCY + maxCY) * 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glText(lbl);
			glPopMatrix();
		}
	}


	// PlacementCandidate, PieceState, PieceSnapshot, MoveHistoryEntry and AppState
	// are defined in TileSolver.h

	AppState* gApp = nullptr;

	bool checkSolved(const AppState& app);

	std::pair<float, float> pieceHomeAnchor(char label)
	{
		switch (label) {
			case 'A': return { -9.6f,  5.6f };
			case 'B': return { -9.6f,  2.9f };
			case 'C': return { -9.6f,  0.0f };
			case 'D': return { -9.6f, -3.5f };
			case 'E': return { -9.6f, -5.7f };
			case 'F': return { -0.2f, -5.5f };
			case 'G': return { 6.1f, -6.0f };
			case 'H': return { 6.1f, -2.6f };
			case 'I': return { 6.1f, -0.2f };
			case 'J': return { 6.1f,  3.2f };
			case 'K': return { 6.1f,  6.2f };
			default:  return { 6.0f,  0.0f };
		}
	}

	bool topLeftLess(const std::pair<float, float>& a, const std::pair<float, float>& b)
	{
		if (fabsf(a.second - b.second) > 0.001f) return a.second > b.second;
		return a.first < b.first;
	}

	void cleanTiny(float& v)
	{
		if (fabsf(v) < 0.00001f) v = 0.0f;
	}

	void normalizeToUpperLeft(std::vector<std::pair<float, float>>& offsets)
	{
		if (offsets.empty()) return;
		auto anchor = offsets[0];
		for (const auto& c : offsets) {
			if (topLeftLess(c, anchor)) anchor = c;
		}
		for (auto& c : offsets) {
			c.first -= anchor.first;
			c.second -= anchor.second;
			cleanTiny(c.first);
			cleanTiny(c.second);
		}
		std::sort(offsets.begin(), offsets.end(), [](const auto& a, const auto& b)
				  {
					  return topLeftLess(a, b);
				  });
	}

	std::vector<std::pair<float, float>> makeLocalOffsets(const PieceDefinition& p)
	{
		auto result = p.offsets;
		normalizeToUpperLeft(result);
		return result;
	}

	enum class PieceTransform { RotateCW, RotateCCW, MirrorX };

	std::pair<float, float> transformedPoint(const std::pair<float, float>& c, PieceTransform tr)
	{
		float x = c.first;
		float y = c.second;
		if (tr == PieceTransform::RotateCW || tr == PieceTransform::RotateCCW) {
			// Pure geometric 60-degree rotation around the held hex.
			const float cs = 0.5f;
			const float sn = (tr == PieceTransform::RotateCW)
				? -0.86602540378443864676f   // sin(-60 deg)
				: 0.86602540378443864676f;  // sin(+60 deg)
			return { cs * x - sn * y, sn * x + cs * y };
		}
		// Left-right mirror.  On this pointy-top hex grid x -> -x keeps all
		// hex centres on valid half-step rows.
		return { -x, y };
	}

	std::pair<float, float> applyPieceTransform(PieceState& p,
													   PieceTransform tr,
													   std::pair<float, float> keepLocal = { 0.0f, 0.0f },
													   bool keepHexInPlace = false)
	{
		const std::pair<float, float> keepWorld{ p.x + keepLocal.first, p.y + keepLocal.second };

		std::vector<std::pair<float, float>> transformed;
		transformed.reserve(p.offsets.size());
		for (const auto& c : p.offsets) {
			auto t = transformedPoint(c, tr);
			cleanTiny(t.first);
			cleanTiny(t.second);
			transformed.push_back(t);
		}
		auto newKeep = transformedPoint(keepLocal, tr);
		cleanTiny(newKeep.first);
		cleanTiny(newKeep.second);

		if (!transformed.empty()) {
			auto anchor = transformed[0];
			for (const auto& c : transformed) {
				if (topLeftLess(c, anchor)) anchor = c;
			}
			for (auto& c : transformed) {
				c.first -= anchor.first;
				c.second -= anchor.second;
				cleanTiny(c.first);
				cleanTiny(c.second);
			}
			newKeep.first -= anchor.first;
			newKeep.second -= anchor.second;
			cleanTiny(newKeep.first);
			cleanTiny(newKeep.second);
		}

		std::sort(transformed.begin(), transformed.end(), [](const auto& a, const auto& b)
				  {
					  return topLeftLess(a, b);
				  });
		p.offsets = transformed;

		if (keepHexInPlace) {
			p.x = keepWorld.first - newKeep.first;
			p.y = keepWorld.second - newKeep.second;
		}
		return newKeep;
	}

	[[maybe_unused]]
	void rotatePieceClockwise(PieceState& p)
	{
		applyPieceTransform(p, PieceTransform::RotateCW);
	}

	[[maybe_unused]]
	void rotatePieceCounterClockwise(PieceState& p)
	{
		applyPieceTransform(p, PieceTransform::RotateCCW);
	}

	[[maybe_unused]]
	void mirrorPiece(PieceState& p)
	{
		applyPieceTransform(p, PieceTransform::MirrorX);
	}

	std::vector<std::pair<float, float>> pieceCenters(const PieceState& p)
	{
		std::vector<std::pair<float, float>> centers;
		centers.reserve(p.offsets.size());
		for (const auto& c : p.offsets) {
			centers.push_back({ p.x + c.first, p.y + c.second });
		}
		return centers;
	}

	PieceSnapshot makeSnapshot(const PieceState& p)
	{
		PieceSnapshot s;
		s.x = p.x;
		s.y = p.y;
		s.placed = p.placed;
		s.offsets = p.offsets;
		s.occupiedCells = p.occupiedCells;
		s.ghostCenters = p.ghostCenters;
		return s;
	}

	std::pair<float, float> screenToWorld(double sxPos, double syPos)
	{
		const float nx = static_cast<float>(2.0 * sxPos / WINDOW_W - 1.0);
		const float ny = static_cast<float>(1.0 - 2.0 * syPos / WINDOW_H);
		const float halfH = 20.0f * tanf(45.0f * PI / 360.0f);
		const float halfW = halfH * (static_cast<float>(WINDOW_W) / static_cast<float>(WINDOW_H));
		return { nx * halfW, ny * halfH };
	}

	int nearestCell(const std::vector<HexTile>& tiles, float x, float y, float maxDist)
	{
		int best = -1;
		float bestD2 = maxDist * maxDist;
		for (int i = 0; i < static_cast<int>(tiles.size()); ++i) {
			float dx = tiles[i].x - x;
			float dy = tiles[i].y - y;
			float d2 = dx * dx + dy * dy;
			if (d2 <= bestD2) {
				bestD2 = d2;
				best = i;
			}
		}
		return best;
	}

	void clearPieceOccupancy(AppState& app, int pieceIndex)
	{
		if (pieceIndex < 0 || pieceIndex >= static_cast<int>(app.pieces.size())) return;
		for (int c : app.pieces[pieceIndex].occupiedCells) {
			if (c >= 0 && c < static_cast<int>(app.occupancy.size()) && app.occupancy[c] == pieceIndex) {
				app.occupancy[c] = -1;
			}
		}
		app.pieces[pieceIndex].occupiedCells.clear();
		app.pieces[pieceIndex].placed = false;
	}

	void applySnapshot(AppState& app, int pieceIndex, const PieceSnapshot& s)
	{
		if (pieceIndex < 0 || pieceIndex >= static_cast<int>(app.pieces.size())) return;
		clearPieceOccupancy(app, pieceIndex);
		PieceState& p = app.pieces[pieceIndex];
		p.x = s.x;
		p.y = s.y;
		p.offsets = s.offsets;
		p.placed = s.placed;
		p.occupiedCells = s.occupiedCells;
		p.ghostCenters = s.ghostCenters;
		if (p.placed) {
			for (int c : p.occupiedCells) {
				if (c >= 0 && c < static_cast<int>(app.occupancy.size())) {
					app.occupancy[c] = pieceIndex;
				}
			}
		}
		app.selectedPiece = pieceIndex;
		app.solved = checkSolved(app);
	}

	PlacementCandidate computePlacementCandidate(const AppState& app, const PieceState& p)
	{
		PlacementCandidate result;
		if (app.tiles == nullptr) return result;
		const auto& tiles = *app.tiles;

		int anchorCell = nearestCell(tiles, p.x, p.y, R * 0.90f);
		if (anchorCell < 0) {
			result.outsideBoard = true;
			return result;
		}

		result.snapX = tiles[anchorCell].x;
		result.snapY = tiles[anchorCell].y;
		result.cells.reserve(p.offsets.size());

		for (const auto& w : p.offsets) {
			float cx = result.snapX + w.first;
			float cy = result.snapY + w.second;
			int ci = nearestCell(tiles, cx, cy, R * 0.25f);
			if (ci < 0) {
				result.valid = false;
				result.outsideBoard = true;
				return result;
			}
			if (std::find(result.cells.begin(), result.cells.end(), ci) != result.cells.end()) {
				result.valid = false;
				return result;
			}
			if (tiles[ci].protectedDate) {
				result.cells.push_back(ci);
				result.valid = false;
				return result;
			}
			if (ci < static_cast<int>(app.occupancy.size()) && app.occupancy[ci] != -1) {
				result.cells.push_back(ci);
				result.valid = false;
				return result;
			}
			result.cells.push_back(ci);
		}
		result.valid = true;
		return result;
	}

	void updateDragTarget(AppState& app)
	{
		app.target = PlacementCandidate{};
		if (!app.dragging || app.dragPiece < 0) return;
		app.target = computePlacementCandidate(app, app.pieces[app.dragPiece]);
	}

	bool placePiece(AppState& app, int pieceIndex, const PlacementCandidate& placement)
	{
		if (!placement.valid) return false;
		PieceState& p = app.pieces[pieceIndex];
		p.x = placement.snapX;
		p.y = placement.snapY;
		p.occupiedCells = placement.cells;
		p.placed = true;
		for (int c : p.occupiedCells) {
			if (c >= 0 && c < static_cast<int>(app.occupancy.size())) {
				app.occupancy[c] = pieceIndex;
			}
		}
		return true;
	}

	bool snapshotsEqual(const PieceSnapshot& a, const PieceSnapshot& b)
	{
		return a.x == b.x &&
			a.y == b.y &&
			a.placed == b.placed &&
			a.offsets == b.offsets &&
			a.occupiedCells == b.occupiedCells &&
			a.ghostCenters == b.ghostCenters;
	}

	void restorePieceToHome(AppState& app, int pieceIndex)
	{
		if (pieceIndex < 0 || pieceIndex >= static_cast<int>(app.pieces.size())) return;
		clearPieceOccupancy(app, pieceIndex);
		PieceState& p = app.pieces[pieceIndex];
		p.x = p.homeX;
		p.y = p.homeY;
		p.offsets = p.homeOffsets;
		p.placed = false;
		p.occupiedCells.clear();
		// p.ghostCenters intentionally remains the permanent original home silhouette.
	}

	void restoreDraggedPiece(AppState& app, int pieceIndex)
	{
		PieceState& p = app.pieces[pieceIndex];
		p.x = app.savedX;
		p.y = app.savedY;
		p.offsets = app.savedOffsets;
		p.placed = app.savedPlaced;
		p.occupiedCells = app.savedCells;
		// Keep the grey footprint created at drag start.  It should remain visible
		// after an invalid drop or after a successful move.
		if (p.placed) {
			for (int c : p.occupiedCells) {
				if (c >= 0 && c < static_cast<int>(app.occupancy.size())) {
					app.occupancy[c] = pieceIndex;
				}
			}
		}
	}

	bool checkSolved(const AppState& app)
	{
		if (app.tiles == nullptr) return false;
		for (const auto& p : app.pieces) {
			if (!p.placed) return false;
		}
		int freeCells = 0;
		for (int i = 0; i < static_cast<int>(app.occupancy.size()); ++i) {
			if (app.occupancy[i] == -1) {
				++freeCells;
				if (!(*app.tiles)[i].protectedDate) return false;
			}
		}
		return freeCells == app.protectedCellCount;
	}

	void undoLastMove(AppState& app)
	{
		if (app.dragging || app.undoStack.empty()) return;
		MoveHistoryEntry h = app.undoStack.back();
		app.undoStack.pop_back();
		applySnapshot(app, h.pieceIndex, h.before);
		app.redoStack.push_back(h);
	}

	void redoLastMove(AppState& app)
	{
		if (app.dragging || app.redoStack.empty()) return;
		MoveHistoryEntry h = app.redoStack.back();
		app.redoStack.pop_back();
		applySnapshot(app, h.pieceIndex, h.after);
		app.undoStack.push_back(h);
	}

	struct PieceHit {
		int pieceIndex = -1;
		int localIndex = -1;
	};

	PieceHit findPieceHitAt(AppState& app, float x, float y)
	{
		for (int i = static_cast<int>(app.pieces.size()) - 1; i >= 0; --i) {
			if (app.dragging && i == app.dragPiece) continue;
			const PieceState& p = app.pieces[i];
			for (int j = 0; j < static_cast<int>(p.offsets.size()); ++j) {
				float cx = p.x + p.offsets[j].first;
				float cy = p.y + p.offsets[j].second;
				float dx = x - cx;
				float dy = y - cy;
				if (dx * dx + dy * dy <= (drawR * 0.95f) * (drawR * 0.95f)) {
					return { i, j };
				}
			}
		}
		return {};
	}

	bool shouldDrawHomeGhost(const PieceState& p)
	{
		// Do not draw the permanent home silhouette while the piece itself is
		// still exactly at home.  Drawing the grey ghost and the yellow piece on
		// top of each other caused the apparent B/C outline instability.
		return fabsf(p.x - p.homeX) > 0.001f || fabsf(p.y - p.homeY) > 0.001f;
	}

	void drawGhostFootprint(const std::vector<std::pair<float, float>>& centers)
	{
		if (centers.empty()) return;

		// Draw the grey home ghost as two filled polygon layers.  First draw a
		// slightly larger light-grey silhouette, then draw the darker body on top.
		// This avoids all line/edge reconstruction for ghosts, so there are no
		// unstable internal strokes at concave joins or shared hex edges.
		const float outlineR = drawR * 1.085f;
		const float fillR = drawR * 1.018f;

		for (const auto& c : centers) {
			glPushMatrix();
			glTranslatef(c.first, c.second, 0.010f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1.0f);
			glColor3f(0.68f, 0.68f, 0.68f);
			CreateHexVertices(GL_POLYGON, outlineR);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPopMatrix();
		}

		for (const auto& c : centers) {
			glPushMatrix();
			glTranslatef(c.first, c.second, 0.014f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1.0f);
			glColor3f(0.38f, 0.38f, 0.38f);
			CreateHexVertices(GL_POLYGON, fillR);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPopMatrix();
		}
	}

	void drawCellOverlay(const std::vector<HexTile>& tiles, const std::vector<int>& cells,
								float r, float g, float b, bool filled)
	{
		for (int ci : cells) {
			if (ci < 0 || ci >= static_cast<int>(tiles.size())) continue;
			glPushMatrix();
			glTranslatef(tiles[ci].x, tiles[ci].y, 0.035f);
			glColor3f(r, g, b);
			if (filled) {
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset(1.0f, 1.0f);
				CreateHexVertices(GL_POLYGON, drawR * 0.96f);
				glDisable(GL_POLYGON_OFFSET_FILL);
			} else {
				glLineWidth(2.2f);
				CreateHexVertices(GL_LINE_LOOP, drawR * 1.03f);
			}
			glPopMatrix();
		}
	}

	void drawPieceState(const PieceState& p, bool selected, bool dragging)
	{
		const float fillR = drawR * 1.015f;
		auto centers = pieceCenters(p);
		for (const auto& c : centers) {
			glPushMatrix();
			glTranslatef(c.first, c.second, dragging ? 0.08f : 0.05f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1.0f);
			float scale = dragging ? 0.88f : 0.70f;
			glColor3f(p.def->r * scale, p.def->g * scale, p.def->b * scale);
			CreateHexVertices(GL_POLYGON, fillR);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPopMatrix();
		}

		if (selected)      glColor3f(1.0f, 1.0f, 1.0f);
		else if (p.placed) glColor3f(0.10f, 0.10f, 0.05f);
		else               glColor3f(p.def->r, p.def->g, p.def->b);
		drawPieceOuterOutline(centers, R, dragging ? 0.125f : 0.095f);

		// Keep the original preview style: no extra visible handle and no black
		// letter printed inside the piece.  Any hex can be used for dragging.
		if (!p.placed || dragging) {
			float minCY = 1e9f, maxCY = -1e9f;
			for (const auto& c : centers) {
				minCY = fminf(minCY, c.second);
				maxCY = fmaxf(maxCY, c.second);
			}
			std::array<char, 4> lbl{};
			lbl[0] = p.def->label;
			glPushMatrix();
			glTranslatef(p.x - 0.9f, (minCY + maxCY) * 0.5f, dragging ? 0.11f : 0.08f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glText(lbl);
			glPopMatrix();
		}
	}

	void drawPieces(const AppState& app)
	{
		for (int i = 0; i < static_cast<int>(app.pieces.size()); ++i) {
			if (app.dragging && i == app.dragPiece) continue;
			drawPieceState(app.pieces[i], i == app.selectedPiece, false);
		}
		if (app.dragging && app.dragPiece >= 0) {
			drawPieceState(app.pieces[app.dragPiece], true, true);
		}
	}

	void drawStatusBanner(const AppState& app)
	{
		const float pulse = 0.5f + 0.5f * sinf(static_cast<float>(glfwGetTime()) * 5.0f);
		glPushMatrix();
		glTranslatef(-2.8f, 4.95f, 0.20f);
		if (app.solverRunning && !app.solverLabel.empty()) {
			// Phase-1 frame: one rendered frame showing the searching label
			// before executePendingSolve runs the actual backtracking.
			glColor3f(0.4f + 0.6f * pulse, 0.85f, 1.0f);
			glText(app.solverLabel.c_str());
		} else if (app.solved) {
			// Both manual and solver-found solutions show SUCCESS.
			glColor3f(1.0f, 0.75f + 0.25f * pulse, 0.15f);
			glText("SUCCESS!");
		}
		glPopMatrix();
	}

	void drawHelpTooltip(bool showHelp)
	{
		if (!showHelp) {
			glPushMatrix();
			glTranslatef(-0.55f, 7.55f, 0.30f);
			glColor3f(0.75f, 0.75f, 0.75f);
			glText("H/F1: help");
			glPopMatrix();
			return;
		}

		glPushMatrix();
		glTranslatef(-3.75f, 7.75f, 0.28f);
		glColor3f(0.03f, 0.03f, 0.06f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f,  0.15f, 0.0f);
		glVertex3f(8.8f,  0.15f, 0.0f);
		glVertex3f(8.8f, -2.95f, 0.0f);
		glVertex3f(0.0f, -2.95f, 0.0f);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.15f, -0.15f, 0.02f);
		glText("Drag any hex to move");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("R/Space: rotate CW held piece");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("L: rotate CCW held piece");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("M: mirror held piece");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("Green=place, Red=blocked");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("Drop outside: return home");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("Ctrl+Z/Y: undo/redo");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("s: next deterministic solution");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("S: next randomized solution");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("Esc: cancel drag / restore pre-solve");
		glTranslatef(0.0f, -0.30f, 0.0f);
		glText("H/F1: hide help");
		glPopMatrix();
	}

	void cursorPosCallback(GLFWwindow*, double xpos, double ypos)
	{
		if (gApp == nullptr || !gApp->dragging || gApp->dragPiece < 0) return;
		auto w = screenToWorld(xpos, ypos);
		PieceState& p = gApp->pieces[gApp->dragPiece];
		p.x = w.first + gApp->dragDx;
		p.y = w.second + gApp->dragDy;
		updateDragTarget(*gApp);
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int)
	{
		if (gApp == nullptr || button != GLFW_MOUSE_BUTTON_LEFT) return;

		double mx = 0.0, my = 0.0;
		glfwGetCursorPos(window, &mx, &my);
		auto w = screenToWorld(mx, my);

		if (action == GLFW_PRESS) {
			PieceHit hit = findPieceHitAt(*gApp, w.first, w.second);
			int pieceIndex = hit.pieceIndex;
			if (pieceIndex < 0 || hit.localIndex < 0) return;

			gApp->selectedPiece = pieceIndex;
			PieceState& p = gApp->pieces[pieceIndex];
			gApp->beforeDragSnapshot = makeSnapshot(p);
			gApp->savedPlaced = p.placed;
			gApp->savedX = p.x;
			gApp->savedY = p.y;
			gApp->savedOffsets = p.offsets;
			gApp->savedCells = p.occupiedCells;
			gApp->savedGhostCenters = p.ghostCenters;
			// Keep the grey silhouette fixed at the original home position.
			gApp->dragLocal = p.offsets[hit.localIndex];

			if (p.placed) {
				clearPieceOccupancy(*gApp, pieceIndex);
			}

			gApp->dragDx = p.x - w.first;
			gApp->dragDy = p.y - w.second;
			gApp->dragPiece = pieceIndex;
			gApp->dragging = true;
			gApp->solved = false;
			updateDragTarget(*gApp);
		} else if (action == GLFW_RELEASE) {
			if (!gApp->dragging || gApp->dragPiece < 0) return;
			int pieceIndex = gApp->dragPiece;
			updateDragTarget(*gApp);
			bool ok = placePiece(*gApp, pieceIndex, gApp->target);
			if (ok) {
				MoveHistoryEntry h;
				h.pieceIndex = pieceIndex;
				h.before = gApp->beforeDragSnapshot;
				h.after = makeSnapshot(gApp->pieces[pieceIndex]);
				gApp->undoStack.push_back(h);
				gApp->redoStack.clear();
			} else if (gApp->target.outsideBoard) {
				// Dropping outside the board sends the piece back to its original
				// starting position outside the board, not to the previous attempt.
				restorePieceToHome(*gApp, pieceIndex);
				MoveHistoryEntry h;
				h.pieceIndex = pieceIndex;
				h.before = gApp->beforeDragSnapshot;
				h.after = makeSnapshot(gApp->pieces[pieceIndex]);
				if (!snapshotsEqual(h.before, h.after)) {
					gApp->undoStack.push_back(h);
					gApp->redoStack.clear();
				}
			} else {
				// Blocked board position: cancel this try and return to the drag-start state.
				restoreDraggedPiece(*gApp, pieceIndex);
			}
			gApp->dragging = false;
			gApp->dragPiece = -1;
			gApp->target = PlacementCandidate{};
			gApp->solved = checkSolved(*gApp);
		}
	}

	void transformSelectedPiece(GLFWwindow* window, PieceTransform tr)
	{
		if (gApp == nullptr || gApp->selectedPiece < 0) return;
		int pieceIndex = gApp->dragging ? gApp->dragPiece : gApp->selectedPiece;
		if (pieceIndex < 0) return;
		PieceState& p = gApp->pieces[pieceIndex];

		if (gApp->dragging && pieceIndex == gApp->dragPiece) {
			gApp->dragLocal = applyPieceTransform(p, tr, gApp->dragLocal, true);
			double mx = 0.0, my = 0.0;
			glfwGetCursorPos(window, &mx, &my);
			auto w = screenToWorld(mx, my);
			gApp->dragDx = p.x - w.first;
			gApp->dragDy = p.y - w.second;
			updateDragTarget(*gApp);
		} else if (!p.placed) {
			applyPieceTransform(p, tr);
		}
	}

	void keyCallback(GLFWwindow* window, int key, int, int action, int mods)
	{
		if (gApp == nullptr || action != GLFW_PRESS) return;
		const bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		const bool shift = (mods & GLFW_MOD_SHIFT)   != 0;
		if (ctrl && key == GLFW_KEY_Z) {
			undoLastMove(*gApp);
			return;
		}
		if (ctrl && key == GLFW_KEY_Y) {
			redoLastMove(*gApp);
			return;
		}
		if (key == GLFW_KEY_H || key == GLFW_KEY_F1) {
			gApp->showHelp = !gApp->showHelp;
			return;
		}
		if (key == GLFW_KEY_R || key == GLFW_KEY_SPACE) {
			transformSelectedPiece(window, PieceTransform::RotateCW);
			return;
		}
		if (key == GLFW_KEY_L) {
			transformSelectedPiece(window, PieceTransform::RotateCCW);
			return;
		}
		if (key == GLFW_KEY_M) {
			transformSelectedPiece(window, PieceTransform::MirrorX);
			return;
		}
		if (key == GLFW_KEY_S) {
			if (shift) {
				// S (uppercase) — randomized; each press finds a fresh random solution
				prepareSolve(*gApp, /*randomize=*/true);
			} else {
				// s (lowercase) — deterministic; repeated presses cycle through solutions
				prepareSolve(*gApp, /*randomize=*/false);
			}
			return;
		}
		if (key == GLFW_KEY_ESCAPE) {
			if (gApp->dragging && gApp->dragPiece >= 0) {
				// Cancel an in-progress drag.
				restoreDraggedPiece(*gApp, gApp->dragPiece);
				gApp->dragging  = false;
				gApp->dragPiece = -1;
				gApp->target    = PlacementCandidate{};
			} else if (!gApp->presolveState.empty()) {
					// Esc after a solver run — undo the solver placement.
					restorePresolveState(*gApp);
					gApp->presolveState.clear();
					gApp->solverSkipCount = 0;
					gApp->solverLabel.clear();
				}
		}
	}


} // namespace

int main()
{

	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "3D Hex Board", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable VSync
#ifdef _WIN32
	FONT_BASE = glGenLists(96);
	HFONT hFont = CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
							 ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
							 ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, TEXT("Courier New"));
	HDC hdc = wglGetCurrentDC();
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	wglUseFontBitmaps(hdc, 32, 96, FONT_BASE);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
#endif

	glViewport(0, 0, WINDOW_W, WINDOW_H);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

	// Get current date (thread-safe)
	std::time_t t = std::time(nullptr);
	std::tm now{};
#ifdef _WIN32
	if (localtime_s(&now, &t) != 0) {
#else
	if (!localtime_r(&t, &now)) {
#endif
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	int today = now.tm_mday;
	int month = now.tm_mon + 1;  // 1-12
	int wday = now.tm_wday;     // 0=Sunday


	// Build flat tile list from grid
	std::vector<HexTile> tiles;
	for (int row = 0; row < (int)grid.size(); ++row) {
		int w = (int)grid[row].size();
		float y = (4 - row) * sy;   // row 4 is the centre at y = 0
		for (int col = 0; col < w; ++col) {
			// Centre each row symmetrically; odd/even widths alternate
			// between integer and half-integer multiples of sx, which is
			// exactly what a regular pointy-top hex grid requires.
			float x = (col - (w - 1) * 0.5f) * sx;
			const Cell& c = grid[row][col];
			bool hl = false;
			switch (c.type) {
				case CT_MONTH: hl = (c.value == month); break;
				case CT_WDAY:  hl = (c.value == wday);  break;
				case CT_DATE:  hl = (c.value == today);  break;
			}
			bool protectedDate = hl && (c.type == CT_MONTH || c.type == CT_WDAY || c.type == CT_DATE);
			tiles.push_back({ row, col, x, y, 0.0f, hl, protectedDate, c });
		}
	}

	AppState app;
	app.tiles = &tiles;
	app.occupancy.assign(tiles.size(), -1);
	for (const auto& tile : tiles) {
		if (tile.protectedDate) ++app.protectedCellCount;
	}
	for (const auto& def : PieceDefinitions) {
		PieceState ps;
		ps.def = &def;
		ps.offsets = makeLocalOffsets(def);
		auto home = pieceHomeAnchor(def.label);
		ps.x = home.first;
		ps.y = home.second;
		ps.homeX = home.first;
		ps.homeY = home.second;
		ps.homeOffsets = ps.offsets;
		ps.ghostCenters = pieceCenters(ps); // permanent original silhouette
		app.pieces.push_back(ps);
	}
	gApp = &app;
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);

	char title[128];
	snprintf(title, sizeof(title), "3D Hex Board - %04d-%02d-%02d %s",
			 now.tm_year + 1900, month, today, weekNames[wday].data());
	glfwSetWindowTitle(window, title);

	// Set projection once before the loop
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective(45.0f, static_cast<float>(WINDOW_W) / static_cast<float>(WINDOW_H), 1.0f, 100.0f);
	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -20.0f);
		glRotatef(0.0f, 1.0f, 0.0f, 0.0f);

		drawHex(0.0f, 0.0f, -0.01f, baseR, false, { CT_BASE, 0 });
		for (const auto& tile : tiles) {
			drawHex(tile.x, tile.y, tile.z, drawR, tile.highlight, tile.content);
		}
		for (const auto& piece : app.pieces) {
			if (!piece.ghostCenters.empty() &&
				(app.solved || shouldDrawHomeGhost(piece))) {
				drawGhostFootprint(piece.ghostCenters);
			}
		}
		if (app.dragging && !app.target.cells.empty()) {
			if (app.target.valid) {
				drawCellOverlay(tiles, app.target.cells, 0.25f, 1.0f, 0.25f, false);
			} else {
				drawCellOverlay(tiles, app.target.cells, 1.0f, 0.25f, 0.25f, false);
			}
		}
		drawPieces(app);
		drawStatusBanner(app);
		drawHelpTooltip(app.showHelp);
		glfwSwapBuffers(window);
		executePendingSolve(app); // runs after the label frame is displayed
	}
#ifdef _WIN32
	glDeleteLists(FONT_BASE, 96);
#endif
	gApp = nullptr;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
