#include "config.h"

// Functions
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;

	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		GLFW_CLOSE(-1);
	}
}

void OnResize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

Camera* currentCamera;

void OnKeyDown(GLFWwindow* window, int key, int, int, int) {
	if (key == GLFW_KEY_W) {
		currentCamera->position.y += 12;
	}
	if (key == GLFW_KEY_A) {
		currentCamera->position.x -= 12;
	}
	if (key == GLFW_KEY_S) {
		currentCamera->position.y -= 12;
	}
	if (key == GLFW_KEY_D) {
		currentCamera->position.x += 12;
	}
	if (key == GLFW_KEY_R) {
		currentCamera->zoom += .2;
	}
	if (key == GLFW_KEY_T) {
		currentCamera->zoom -= .2;
	}
}

// Main
int main() {
	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(500, 400, "Glfw", NULL, NULL);
	if (!window) GLFW_CLOSE(-1);
	glfwMakeContextCurrent(window);
	if (!gladLoadGL()) GLFW_CLOSE(-1);

	// Config
	glViewport(0, 0, 500, 400);
	glfwSwapInterval(60);
	glfwSetFramebufferSizeCallback(window, OnResize);
	glfwSetKeyCallback(window, OnKeyDown);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	
	// IMGUI > Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	// Render
	Geometry geometry;
	GeometryHUD geometryHUD(&geometry);

	geometry.Resize(150, 150);
	geometry.Fill(1, 1, 150, 150, TileType::Solid);

	Camera cam;
	currentCamera = &cam;

	double currentTime = 0;

	while (!glfwWindowShouldClose(window)) {
		// Get any inputs
		glfwPollEvents();
		
		//Clear
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2, 0.3, 0.6, 1);
		
		// ImGui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Render
		geometry.Draw(cam, window);
		geometryHUD.Draw();

		// ImGUI Draw
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGui::EndFrame();

		// Update
		glfwSwapBuffers(window);
	}

	// Imgui Clear
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Clear
	GLFW_CLOSE(0);
}

