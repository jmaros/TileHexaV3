#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "GLFW/glfw3.h"
#include <cmath>
#include <ctime>
#include <array>
#include <vector>

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
const float drawR = R * 0.99f;               // 1% gap
const float sx = sqrtf(3.0f) * R;
const float sy = 1.5f * R;

// Cell descriptor -------------------------------------------------------
struct Cell { int type, value; };
// type: 0=empty  1=month(1-12)  2=weekday(0=Sun..6=Sat)  3=date(1-31)
enum { CT_EMPTY = 0, CT_MONTH = 1, CT_WDAY = 2, CT_DATE = 3 };

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
	bool empty;       // true = no content, skip rendering
};

void setPerspective(float fovy, float aspect, float zNear, float zFar)
{
    float fH = tan(fovy / 360.0f * PI) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void CreateHexVertices(GLenum cap, double radius)
{
	glBegin(cap);
	for (int i = 0; i < 6; ++i) {
		float angle = PI / 3.0f * (i + 0.5);
		glVertex3f(radius * cosf(angle), radius * sinf(angle), 0.0f);
	}
	glEnd();
}

void drawHex(float			cx,
			 float			cy,
			 float			cz,
			 float			radius,
			 bool			highlight,
			 Cell const &	content)
{
    glPushMatrix();
    glTranslatef(cx, cy, cz);

    float r, g, b;
	if (highlight) {
		{ r = 1.0f; g = 0.7f; b = 0.2f; }
	} else {
		{ r = 0.3f; g = 0.6f; b = 0.8f; }
	}
	std::array<char, 4> text {};
	switch (content.type) {
		case CT_MONTH: { r *= 0.8f; g *= 0.8f; b *= 0.8f; } break;
		case CT_WDAY:  { r *= 0.6f; g *= 0.6f; b *= 0.6f; } break;
		case CT_DATE:  { r *= 0.4f; g *= 0.4f; b *= 0.4f; } break;
	}
    // Filled polygon – pushed back slightly so the border line renders on top
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glColor3f(r, g, b);
	CreateHexVertices(GL_POLYGON, radius);
    glDisable(GL_POLYGON_OFFSET_FILL);

    // Border 2.0 times brighter than the fill colour.
    glColor3f(r * 2.0f, g * 2.0f, b * 2.0f);
    glLineWidth(1.5f);
	CreateHexVertices(GL_LINE_LOOP, radius);

    glPopMatrix();
}

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
            tiles.push_back({x, y, 0.0f, hl, c, c.type == CT_EMPTY});
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
        glTranslatef(0.0f, 0.0f, -10.0f);
        glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
        for (const auto& tile : tiles) {
			if (!tile.empty) {
				drawHex(tile.x, tile.y, tile.z, drawR, tile.highlight, tile.content);
			}
        }
        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
