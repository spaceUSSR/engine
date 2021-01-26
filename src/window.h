/*
 *  Static window class
 *
*/

#ifndef WINDOW_H_
#define WINDOW_H_

struct GLFWwindow{};

class Window
{
private:
    static GLFWwindow* m_window;
    static int m_height;
    static int m_width;

public:
    static int initialize(int w, int h, const char* title);
    static int finalize();
    static bool isSouldClose();
    static void swapBuffers();  // Swap front and back buffers
    static void pollEvents();   // Poll for and process events

    static void clearColor(float r, float g, float b, float a = 1.0f);

    static int getKey(int key);

private:
    static void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height);
    static void glfwWindowKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};

#endif //!WINDOW_H_
