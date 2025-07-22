#include "Window.hpp"

// Initialize static member
Window* Window::window = nullptr;

Window::Window() : width(800), height(600), title("Engine Window"), glfwWindow(nullptr) {
    
}

Window::~Window() {
    if (glfwWindow) {
        glfwDestroyWindow(glfwWindow);
    }
    glfwTerminate();
}

Window* Window::get() {
    if (Window::window == nullptr) {
        Window::window = new Window();
    }

    return Window::window;
}

void Window::errorCallback(int error, const char *description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Window::run() {
    std::cout << "GLFW Version: " << glfwGetVersionString() << "!" << std::endl;
    init();
    loop();
}

void Window::init() {
    // Setup an error callback
    glfwSetErrorCallback(errorCallback);

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Unable to initialize GLFW.");
    }

    // Configure GLFW
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (glfwWindow == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create the GLFW window.");
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(glfwWindow);

    // Initialize GLAD - This must be done after making the context current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    // Enable VSync
    glfwSwapInterval(1);

    // Make the window visible
    glfwShowWindow(glfwWindow);
}

void Window::loop() {
    while (!glfwWindowShouldClose(glfwWindow)) {
        // Poll for events
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(glfwWindow);
    }
}



