#pragma once
#include <string>

struct GLFWwindow{};

class MainWindow
{
private:
    GLFWwindow* m_pWindow;
    bool m_isCreated = false;

public:
    MainWindow(const std::string title);
    ~MainWindow();
    MainWindow() = delete;
    MainWindow(MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;

    void ClearColor(float r, float g, float b, float a = 1.0f);
    bool isCreated();

    int WindowHeight();
    int WindowWidth();

    GLFWwindow* getWindow();


    MainWindow& operator= (MainWindow&) = delete;
    MainWindow& operator= (MainWindow&&) = delete;
};
