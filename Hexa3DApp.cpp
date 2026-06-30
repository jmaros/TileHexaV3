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

// Cell descriptor -------------------------------------------------------
struct Cell { int type, value; };
// type: -1=base, 0=empty,  1=month(1-12),  2=weekday(0=Sun..6=Sat),  3=date(1-31)
enum { CT_BASE = -1, CT_EMPTY = 0, CT_MONTH = 1, CT_WDAY = 2, CT_DATE = 3 };
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

struct HexTile {
	float x, y, z;
	bool highlight;
	Cell content;
};

// -----------------------------------------------------------------------
// Puzzle-piece preview data (Solution 1)
// -----------------------------------------------------------------------
struct PieceDefinition {
	char                               label;
	std::vector<std::pair<float, float>> offsets; // final local offsets in world units
	float                              r, g, b;
};

const std::vector<PieceDefinition> PieceDefinitions = {
	{ 'A', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{3.0f*sx,0.0f},{4.0f*sx,0.0f}}, 1.0f,1.0f,0.3f },
	{ 'B', {{0.0f,0.0f},{1.0f*sx,0.0f},{0.5f*sx,-1.0f*sy},{1.5f*sx,-1.0f*sy},{2.5f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'C', {{-1.0f*sx,0.0f},{0.0f,0.0f},{0.5f*sx,-1.0f*sy},{1.5f*sx,-1.0f*sy},{2.5f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'D', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{3.0f*sx,0.0f},{3.5f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'E', {{-1.5f*sx,0.0f},{-0.5f*sx,0.0f},{0.5f*sx,0.0f},{0.0f*sx,-1.0f*sy},{1.0f*sx,-1.0f*sy},{2.0f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'F', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{0.5f*sx,-1.0f*sy},{1.5f*sx,-1.0f*sy},{2.5f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'G', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{3.0f*sx,0.0f},{1.5f*sx,-1.0f*sy},{2.5f*sx,-1.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'H', {{0.0f,0.0f},{0.5f*sx,-1.0f*sy},{1.5f*sx,-1.0f*sy},{2.5f*sx,-1.0f*sy},{3.0f*sx,-2.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'I', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{2.5f*sx,-1.0f*sy},{3.0f*sx,-2.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'J', {{0.5f*sx,0.0f},{1.5f*sx,0.0f},{1.0f*sx,-1.0f*sy},{0.5f*sx,-2.0f*sy},{1.5f*sx,-2.0f*sy}}, 1.0f,1.0f,0.3f },
	{ 'K', {{0.0f,0.0f},{1.0f*sx,0.0f},{2.0f*sx,0.0f},{0.5f*sx,-1.0f*sy},{1.5f*sx,-1.0f*sy},{1.0f*sx,-2.0f*sy}}, 1.0f,1.0f,0.3f },
};

void setPerspective(float fovy, float aspect, float zNear, float zFar)
{
    float fH = tan(fovy / 360.0f * PI) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void glText(const std::array<char, 4>& text)
{
    if (FONT_BASE == 0) return;
    glRasterPos3f(0.0f, 0.0f, 0.01f);
    int len = (int)strlen(text.data());
    glListBase(FONT_BASE - 32);
    glCallLists(len, GL_UNSIGNED_BYTE, text.data());
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
				 Cell const&	content)
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
			case CT_WDAY:  { r *= 0.6f; g *= 0.6f; b *= 0.6f; text = weekNames[content.value]; } break;
			case CT_DATE:  { r *= 0.4f; g *= 0.4f; b *= 0.4f; snprintf(text.data(), text.size(), "%d", content.value); } break;
			case CT_EMPTY: { r *= 0.6f; g *= 0.6f; b *= 0.0f; } break;
			case CT_BASE:  { r  = 1.0f; g  = 1.0f; b  = 0.0f; } break;
		}
		// Filled polygon – pushed back slightly so the border line renders on top
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glColor3f(r, g, b);
		if (content.type == CT_BASE) {
			CreateHexVertices(GL_POLYGON, radius, 0.0f);
		} else if (content.type != CT_EMPTY) {
			CreateHexVertices(GL_POLYGON, radius);
		}
		glDisable(GL_POLYGON_OFFSET_FILL);

		if (content.type != CT_BASE && content.type != CT_EMPTY) {
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
	static void drawPieceOuterOutline(const std::vector<std::pair<float, float>>& centers, float radius);

	static void drawPieceOuterOutline(const std::vector<std::pair<float, float>>& centers, float radius)
{
    struct QPoint {
        int x;
        int y;
        bool operator==(const QPoint& o) const noexcept { return x == o.x && y == o.y; }
    };
    struct QPointHash {
        size_t operator()(const QPoint& p) const noexcept {
            return (static_cast<size_t>(static_cast<unsigned int>(p.x)) << 1) ^
                   static_cast<size_t>(static_cast<unsigned int>(p.y));
        }
    };
    struct EdgeKey {
        QPoint a;
        QPoint b;
        bool operator==(const EdgeKey& o) const noexcept { return a == o.a && b == o.b; }
    };
    struct EdgeKeyHash {
        size_t operator()(const EdgeKey& e) const noexcept {
            return QPointHash{}(e.a) * 1315423911u ^ QPointHash{}(e.b);
        }
    };

    auto quantizePoint = [](float x, float y) -> QPoint {
        constexpr float Q = 10000.0f;
        return { static_cast<int>(lroundf(x * Q)), static_cast<int>(lroundf(y * Q)) };
    };
    auto makeEdgeKey = [](QPoint p1, QPoint p2) -> EdgeKey {
        if (p2.y < p1.y || (p2.y == p1.y && p2.x < p1.x)) {
            QPoint t = p1; p1 = p2; p2 = t;
        }
        return { p1, p2 };
    };

    std::unordered_map<EdgeKey, int, EdgeKeyHash> edgeUseCount;

    for (const auto& c : centers) {
        for (int i = 0; i < 6; ++i) {
            float a1 = PI / 3.0f * (i + 0.5f);
            float a2 = PI / 3.0f * ((i + 1) % 6 + 0.5f);
            QPoint p1 = quantizePoint(c.first + radius * cosf(a1), c.second + radius * sinf(a1));
            QPoint p2 = quantizePoint(c.first + radius * cosf(a2), c.second + radius * sinf(a2));
            edgeUseCount[makeEdgeKey(p1, p2)]++;
        }
    }

    std::unordered_map<QPoint, std::vector<QPoint>, QPointHash> adjacency;
    for (const auto& kv : edgeUseCount) {
        if (kv.second == 1) {
            adjacency[kv.first.a].push_back(kv.first.b);
            adjacency[kv.first.b].push_back(kv.first.a);
        }
    }
    if (adjacency.empty()) return;

    QPoint start = adjacency.begin()->first;
    for (const auto& kv : adjacency) {
        const QPoint& p = kv.first;
        if (p.y < start.y || (p.y == start.y && p.x < start.x)) start = p;
    }

    std::vector<QPoint> loop;
    loop.reserve(adjacency.size() + 1);
    QPoint prev{ 0x7fffffff, 0x7fffffff };
    QPoint cur = start;

    for (size_t guard = 0; guard < adjacency.size() + 8; ++guard) {
        loop.push_back(cur);
        const auto& nbr = adjacency[cur];
        //if (nbr.empty()) break;
        QPoint next = nbr[0];
        if (nbr.size() > 1 && next == prev) next = nbr[1];
        prev = cur;
        cur = next;
        if (cur == start) {
            loop.push_back(start);
            break;
        }
    }

    constexpr float Q = 10000.0f;
    glLineWidth(1.4f);
    glBegin(GL_LINE_STRIP);
    for (const auto& p : loop) {
        glVertex3f(p.x / Q, p.y / Q, 0.0f);
    }
    glEnd();
}

	void drawPiecePreviews(const std::vector<PieceDefinition>& pieces)
	{
    const float pR = drawR;
    const float fillR = pR * 1.015f; // tiny overlap to hide internal raster seams

    auto pieceAnchor = [](char label) -> std::pair<float, float> {
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
            case 'G': return {  6.1f, -6.0f };
            case 'H': return {  6.1f, -2.6f };
            case 'I': return {  6.1f, -0.2f };
            case 'J': return {  6.1f,  3.2f };
            case 'K': return {  6.1f,  6.2f };
            default:  return {  6.0f,  0.0f };
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
            float px = rc.first  - tlX + ox;
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
        drawPieceOuterOutline(pieceCenters, R);

        std::array<char, 4> lbl{};
        lbl[0] = p.label;
        glPushMatrix();
        glTranslatef(ox - 0.9f, (minCY + maxCY) * 0.5f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glText(lbl);
        glPopMatrix();
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Hex Board", nullptr, nullptr);
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

    glViewport(0, 0, 800, 600);
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
    int wday  = now.tm_wday;     // 0=Sunday


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
            tiles.push_back({x, y, 0.0f, hl, c});
        }
    }

	// Set projection once before the loop
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
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
		drawPiecePreviews(PieceDefinitions);
        glfwSwapBuffers(window);
    }
#ifdef _WIN32
    glDeleteLists(FONT_BASE, 96);
#endif
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
