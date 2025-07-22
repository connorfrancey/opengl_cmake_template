#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>

class Window {
private:
    int width, height;
    const char* title;
    GLFWwindow* glfwWindow;
    static Window* window;

    // Private constructor for singleton
    Window();

public:

    // Delete copy constructor and assignment operator
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Static method to get singleton instance
    static Window* get();

    // Main methods
    void run();
    void init();
    void loop();

    // Destructor
    ~Window();

private:
    // Error callback function
    static void errorCallback(int error, const char* description);
};
