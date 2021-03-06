#include "window.h"

namespace rokka { namespace graphics {

  void window_resize(GLFWwindow *window, int width, int height);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

  // bool Window::m_Keys[MAX_KEYS];
  // bool Window::m_MouseButtons[MAX_BUTTONS];
  // double Window::m_MouseX;
  // double Window::m_MouseY;

  Window::Window(const char *title, int width, int height) {
    m_Title = title;
    m_Width = width;
    m_Height = height;
    if(!Init()) glfwTerminate();

    for(int i = 0; i < MAX_KEYS; ++i) {
      m_Keys[i] = false;
    }

    for(int i = 0; i < MAX_BUTTONS; ++i) {
      m_MouseButtons[i] = false;
    }
  }

  Window::~Window() {
    glfwTerminate();
  }

  bool Window::Init() {
    if(!glfwInit()) {
      std::cout << "Failed to initialize GLFW!" << std::endl;
      return false;
    }
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
    if(!m_Window) {
      glfwTerminate();
      std::cout << "Failed to create GFLW window!" << std::endl;
      return false;
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, window_resize);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, cursor_position_callback);

    if(glewInit() != GLEW_OK) {
      std::cout << "Could not initialize GLEW!" << std::endl;
      return false;
    }

    return true;
  }

  bool Window::isKeyPressed(unsigned int keycode) const {
    if(keycode >= MAX_KEYS) {
      //log something
      return false;
    }
    return m_Keys[keycode];
  }

  bool Window::isMouseButtonPressed(unsigned int button) const {
    if(button >= MAX_BUTTONS) {
      //log something
      return false;
    }
    return m_MouseButtons[button];
  }

  void Window::getMousePosition(double &x, double &y) const {
    x = m_MouseX;
    y = m_MouseY;
  }

  void Window::Update() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  void Window::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  bool Window::closed() const {
    return glfwWindowShouldClose(m_Window) == 1;
  }

  void window_resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    win->m_Keys[key] = action != GLFW_RELEASE;
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    win->m_MouseButtons[button] = action != GLFW_RELEASE;
  }

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    win->m_MouseX = xpos;
    win->m_MouseY = xpos;
  }


} }
