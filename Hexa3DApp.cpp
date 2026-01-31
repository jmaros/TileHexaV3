#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "GLFW/glfw3.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <string>

constexpr float PI = 3.14159265359f;

struct HexTile {
    float x, y, z;
    bool highlight;
	// Removed: std::string label;
};

void setPerspective(float fovy, float aspect, float zNear, float zFar) {
    float fH = tan(fovy / 360.0f * PI) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void drawHex(float cx, float cy, float cz, float radius, bool highlight) {
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    if (highlight) {
        glColor3f(1.0f, 0.7f, 0.2f);
    } else {
        glColor3f(0.3f, 0.6f, 0.8f);
    }
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; ++i) {
        float angle = PI / 3.0f * i;
        glVertex3f(radius * cos(angle), radius * sin(angle), 0.0f);
    }
    glEnd();
    glPopMatrix();
}

int main() {

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

    // Get current date
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    if (!now) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    int today = now->tm_mday;
    int month = now->tm_mon + 1;
    int wday = now->tm_wday; // 0=Sunday

    // Prepare hex tiles (simple flat grid, 3 rows: day, month, date)
    std::vector<HexTile> tiles;
    float radius = 0.5f;
    // Days of week (0=Sunday)
    for (int i = 0; i < 7; ++i) {
        tiles.push_back({ (i - 3) * 1.1f, 1.2f, 0.0f, i == wday });
    }
    // Months (1-12)
    for (int i = 1; i <= 12; ++i) {
        tiles.push_back({ (i - 6.5f) * 0.7f, 0.0f, 0.0f, i == month });
    }
    // Dates (1-31)
    for (int i = 1; i <= 31; ++i) {
        tiles.push_back({ (i - 16) * 0.35f, -1.2f, 0.0f, i == today });
    }

    // Set projection once before the loop
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -10.0f);
        glRotatef(-30, 1, 0, 0);
        // Draw hex tiles
        for (const auto& tile : tiles) {
            drawHex(tile.x, tile.y, tile.z, radius, tile.highlight);
        }
        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
