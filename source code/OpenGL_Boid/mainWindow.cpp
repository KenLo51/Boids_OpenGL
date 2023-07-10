#include "MainWindow.h"

// call_back function while window size has been changed
void windowResize_CB(GLFWwindow* window, int width, int height) {
	currWindow->width = width;
	currWindow->height = height;
	if (currWindow->width <= 0)currWindow->width = 1;
	if (currWindow->height <= 0)currWindow->height = 1;

	currWindow->currScene->Resize(width, height);
}


// constructor. initialize window, opengl, imgui
MainWindow::MainWindow() {
	initVariables();
	initWindow();
	initOpneGL();
	initImgui();

	currWindow = this;
	glfwSetFramebufferSizeCallback(window, windowResize_CB);
	std::cout << "[INFO] Initialize passed" << std::endl;

	//mainView = new MainView();
	currScene = new BoidScene();
	//inputHandler = new InputHandler(MainWindow::window, mainView->mainCamera);
}

void MainWindow::initVariables() {
	MainWindow::width = 1920;
	MainWindow::height = 1080;
}

// initialize glfw window
void MainWindow::initWindow() {
	std::cout << "[INFO::GLFW::INIT] Initializing GLFW" << std::endl;
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "[ERROR::GLFW::INIT] GLFW initialize failed" << std::endl;
		return;
	}

	// OpenGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// use OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW creating window /////////////////////////////////////////////
	MainWindow::window = glfwCreateWindow(MainWindow::width, MainWindow::height, title, NULL, NULL);
	if (MainWindow::window == NULL) {
		std::cout << "[ERROR::GLFW] Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(MainWindow::window);
}

// initialize opengl
void MainWindow::initOpneGL() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "[ERROR::GLAD] Failed to initialize GLAD" << std::endl;
		return;
	}

	// tell OpenGL the size of rendering
	glViewport(0, 0, MainWindow::width, MainWindow::height);
}

// initialize imgui
void MainWindow::initImgui() {
	std::cout << "[INFO::ImGUI::INIT] Initializing ImGUI" << std::endl;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(MainWindow::window, true);
	ImGui_ImplOpenGL3_Init("#version 150");
}

// run window
void MainWindow::run() {
	std::cout << "[INFO] Running" << std::endl;
	float prevTime = glfwGetTime();

	float counter_1s = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		float currTime = glfwGetTime();
		float deltaTime = currTime - prevTime;
		prevTime = currTime;

		counter_1s = counter_1s + deltaTime;
		if (counter_1s >= 1.0f) {
			counter_1s = fmod(counter_1s, 1.0f);
			char titleStr[80];
			sprintf(titleStr, "%s - FPS:%7.2f", title, 1.0f/ deltaTime);
			glfwSetWindowTitle(window, titleStr);
		}

		currScene->Draw(deltaTime);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	std::cout << "[INFO] Window closed" << std::endl;

	glfwTerminate();

}

// get the width of the window
int MainWindow::w() {
	return MainWindow::width;
}

// get the height of the window
int MainWindow::h() {
	return MainWindow::height;
}