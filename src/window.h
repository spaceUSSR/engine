/*
 *  Static window class
 *
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "events.h"

struct GLFWwindow{};

class Window final
{
private:
    GLFWwindow* m_window;
    std::string m_title;
    int m_height, m_width;
private:
    Window(const std::string& title, int width, int height);
private:
    ~Window();
private:
    void init();
public:
    static Window& getInstance() { static Window instance("My window", 1280, 720);
                            return instance; }
public:
    bool isSouldClose();
    void swapBuffers();
    void clearColor(float r, float g, float b, float a = 1.0f);
    void pollEvents();
    inline int getHeight() const { return m_height; }
    inline int getWidth() const { return m_width; }
};

#endif //!WINDOW_H_
