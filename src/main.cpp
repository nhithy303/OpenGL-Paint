#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "headers/Shader.h"
#include "headers/VAO.h"
#include "headers/VBO.h"
#include "components/Canvas.h"
#include "components/Point.h"
#include "components/Line.h"
#include "components/Circle.h"
#include "components/Ellipse.h"
using namespace std;

/**************************************/
/************* INITIALIZE *************/
/**************************************/
GLuint SCR_WIDTH = 800;
GLuint SCR_HEIGHT = 800;

const string colorNames[6] = { "White", "Black", "Red", "Green", "Blue", "Yellow" };
const vector<vector<GLfloat>> colors = {
    {1.0f, 1.0f, 1.0f}, // white
    {0.0f, 0.0f, 0.0f}, // black
    {1.0f, 0.0f, 0.0f}, // red
    {0.0f, 1.0f, 0.0f}, // green
    {0.0f, 0.0f, 1.0f}, // blue
    {1.0f, 1.0f, 0.0f}  // yellow
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
VAO setupVAO(GLfloat shape[], GLsizeiptr size);

void getVertices(GLfloat vertices[], int n, vector<Point> shape, int colorIndex);
GLfloat normalizeX(int x);
GLfloat normalizeY(int y);
vector<Point> floodFill(Canvas &canvas, int sx, int sy, int newColor);

/********************************/
/************* MAIN *************/
/********************************/
int main() {
    while (1) {
        // User input
        int shape, outlineColor, fillColor;
        bool isFilled = false;
        char opt;
        int drawAlgorithm;
        int x1, y1, x2, y2, r, a, b;

        cout << "~ Screen width: ";
        cin >> SCR_WIDTH;
        cout << "~ Screen height: ";
        cin >> SCR_HEIGHT;
        cout << "-------------------\n";
        cout << "------ Shape ------\n";
        cout << "1 - Line\n2 - Circle\n3 - Ellipse\n";
        cout << "=> Pick: ";
        cin >> shape;

        switch (shape) {
            case 1:
                cout << "+ Start point (x y): ";
                cin >> x1 >> y1;
                cout << "+ End point (x y): ";
                cin >> x2 >> y2;
                cout << "+ Drawing algorithms (0 - DDA, 1 - MidPoint): ";
                cin >> drawAlgorithm;
                break;
            case 2:
                cout << "+ Center (x y): ";
                cin >> x1 >> y1;
                cout << "+ Radius: ";
                cin >> r;
                break;
            case 3:
                cout << "+ Center (x y): ";
                cin >> x1 >> y1;
                cout << "+ Semi axes (a b): ";
                cin >> a >> b;
                break;
        }

        cout << "------ Outline color ------\n";
        for (int i = 1; i < colors.size(); i++) {
            cout << i << " - " << colorNames[i] << "\n";
        }
        // cout << "1 - Black\n2 - Red\n3 - Green\n4 - Blue\n5 - Yellow\n";
        cout << "=> Pick: ";
        cin >> outlineColor;

        if (shape != 1) {
            cout << "------ Fill color ------\n";
            cout << "+ Fill in (y/n): ";
            cin >> opt;
            isFilled = (opt == 'y');
            if (isFilled) {
                cout << "+ Color to fill in:\n";
                for (int i = 1; i < colors.size(); i++) {
                    cout << i << " - " << colorNames[i] << "\n";
                }
                // cout << "1 - Black\n2 - Red\n3 - Green\n4 - Blue\n5 - Yellow\n";
                cout << "=> Pick: ";
                cin >> fillColor;
            }
        }
        
        // Initialize canvas to store color value of integer coordinates
        Canvas canvas(SCR_WIDTH, SCR_HEIGHT);
        
        // GLFW: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // GLFW: create a window object
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Computer Graphics - Midterm Lab", NULL, NULL);
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // GLAD: load all OpenGL function pointers
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        
        // Generate Shader object using shaders default.vert and default.frag
        Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

        vector<Point> shapePoints;
        vector<Point> colorPoints;
        VAO VAO_shape;
        VAO VAO_color;

        // Get shape coordinates
        if (shape == 1) {
            Line l = Line(Point(x1, y1), Point(x2, y2));
            if (drawAlgorithm == 0) {
                shapePoints = l.drawDDA(SCR_WIDTH, SCR_HEIGHT);
            }
            else {
                shapePoints = l.drawMidPoint(SCR_WIDTH, SCR_HEIGHT);
            }
            int nLine = shapePoints.size() * 6;
            GLfloat ndcLine[nLine];
            getVertices(ndcLine, nLine, shapePoints, outlineColor);
            VAO_shape = setupVAO(ndcLine, sizeof(ndcLine));
        }
        else if (shape == 2) {
            shapePoints = Circle(Point(x1, y1), r).draw(SCR_WIDTH, SCR_HEIGHT);
            int nCircle = shapePoints.size() * 6;
            GLfloat ndcCircle[nCircle];
            getVertices(ndcCircle, nCircle, shapePoints, outlineColor);
            VAO_shape = setupVAO(ndcCircle, sizeof(ndcCircle));
        }
        else if (shape == 3) {
            shapePoints = Ellipse(Point(x1, y1), a, b).draw(SCR_WIDTH, SCR_HEIGHT);
            int nEllipse = shapePoints.size() * 6;
            GLfloat ndcEllipse[nEllipse];
            getVertices(ndcEllipse, nEllipse, shapePoints, outlineColor);
            VAO_shape = setupVAO(ndcEllipse, sizeof(ndcEllipse));
        }

        // Store color values of shape coordinates in canvas (for coloring purpose)
        canvas.updatePixels(shapePoints, outlineColor);

        // Color if picked
        if (isFilled) {
            colorPoints = floodFill(canvas, x1, y1, fillColor);
            int nColor = colorPoints.size() * 6;
            GLfloat ndcColor[nColor];
            getVertices(ndcColor, nColor, colorPoints, fillColor);
            VAO_color = setupVAO(ndcColor, sizeof(ndcColor));
        }

        // Display
        while(!glfwWindowShouldClose(window)) {
            // Keyboard input
            processInput(window);

            // Clear screen
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Tell OpenGL which Shader Program to use
            shaderProgram.Activate();

            // Bind VAO of shape and draw
            VAO_shape.Bind();
            glDrawArrays(GL_POINTS, 0, shapePoints.size());

            // Bind VAO of color and draw
            if (isFilled) {
                VAO_color.Bind();
                glDrawArrays(GL_POINTS, 0, colorPoints.size());
            }

            // GLFW: Swap buffers and poll I/O events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        VAO_shape.Delete();
        VAO_color.Delete();
        shaderProgram.Delete();
        
        // GLFW: Clear all previously allocated resources
        glfwDestroyWindow(window);
        glfwTerminate();

        // Quit program
        cout << "~ Do you want to quit? (y/n) ";
        cin >> opt;
        if (opt == 'y') {
            break;
        }
        cout << "\n=============================\n\n";
    }
    return 0;
}

/**************************************/
/************* PREPROCESS *************/
/**************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

VAO setupVAO(GLfloat shape[], GLsizeiptr size) {
    // Generate VAO (Vertex Array Object) and bind it
    VAO _VAO;
    _VAO.Bind();

    // Generate VBO (Vertex Buffer Object) and link it to vertices
    VBO _VBO(shape, size);

    // Link VBO to VAO
    _VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    _VAO.LinkAttrib(_VBO, 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    _VAO.Unbind();
    _VBO.Unbind();
    _VBO.Delete();
    
    return _VAO;
}

/*********************************/
/************* UTILS *************/
/*********************************/

// Generate vertices array of size 6
// ~ First 3 for coordinate in 3D space (x, y, z)
// ~ Last 3 for RGB color value (r, g, b)
void getVertices(GLfloat vertices[], int n, vector<Point> shape, int colorIndex) {
    int k = 0;
    for (int i = 0; i < n; i += 6) {
        // Coordinate
        vertices[i] = normalizeX(shape[k].getX());
        vertices[i + 1] = normalizeY(shape[k].getY());
        vertices[i + 2] = 0.0f;

        // Color
        vertices[i + 3] = colors[colorIndex][0];
        vertices[i + 4] = colors[colorIndex][1];
        vertices[i + 5] = colors[colorIndex][2];
        
        k++;
    }
}

// Convert Integer Coordinates into Normalized Device Coordinates in range [-1, 1]
GLfloat normalizeX(int x) {
    GLfloat ndcX = x * 2.0f / SCR_WIDTH - 1.0f;
    return ndcX;
}
GLfloat normalizeY(int y) {
    GLfloat ndcY = y * 2.0f / SCR_HEIGHT - 1.0f;
    return ndcY;
}

// Fill in color using FloodFill algorithm with Stack
vector<Point> floodFill(Canvas &canvas, int sx, int sy, int newColor) {
    vector<Point> colorPoint;
    Point pStart(sx, sy);
    int oldColor = canvas.getPixel(sx, sy);
    stack<Point> st;
    st.push(pStart);
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    while (!st.empty()) {
        Point pTemp = st.top();
        st.pop();
        sx = pTemp.getX();
        sy = pTemp.getY();
        if (canvas.getPixel(sx, sy) != newColor) {
            canvas.setPixel(sx, sy, newColor);
            colorPoint.push_back(Point(sx, sy));
            for (int i = 0; i < 4; i++) {
                int nx = sx + dx[i];
                int ny = sy + dy[i];
                if (nx >= 0 && nx < canvas.getWidth() && ny >= 0 && ny < canvas.getHeight() && canvas.getPixel(nx, ny) == oldColor) {
                    st.push(Point(nx, ny));
                }
            }
        }
    }
    return colorPoint;
}