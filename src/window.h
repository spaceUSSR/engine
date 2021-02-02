/*
 *  Static window class
 *
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include "events.h"

struct GLFWwindow{};

class Window
{
private:
    static GLFWwindow* m_window;
    static int m_height;
    static int m_width;
	static Events m_events;

public:
    static int initialize(int w, int h, const char* title);
    static int finalize();

    static bool isSouldClose();
    static void swapBuffers();  // Swap front and back buffers

    static void clearColor(float r, float g, float b, float a = 1.0f);

    static int getKey(int key);

    static int getHeight();
    static void setHeight(int height);

    static int getWidth();
    static void setWidth(int width);

private:
    static void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height);

	friend class Events;
};

#endif //!WINDOW_H_
