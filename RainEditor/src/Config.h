// Includes //
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Includes.Custom //
#include <main/Geometry.h>
#include <main/Camera.h>
#include <main/hud/GeometryHUD.h>

// Macros //
#define GLFW_CLOSE(x) { glfwTerminate(); exit(x); }