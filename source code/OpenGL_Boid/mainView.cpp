#include "mainView.h"

MainView::MainView() {
	initViewObjects();
	directionalLight_theta = 29.0f;
	directionalLight_phi = 67.0f;
	limitFrameRate = true;
}


void MainView::drawImgui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// User Manual Halper
	ImGui::Begin("User Manual");
	ImGui::Text("left click        : Set a barrier in the maze.");
	ImGui::Text("right click       : Clear a barrier in the maze.");
	ImGui::Text("alt + left click  : Set the end point.");
	ImGui::Text("alt + right click : Set the starting point.");
	ImGui::End();

	ImGui::Render();
}

// initialize VAO, VBO, EBO, Shader, Texture...
void MainView::initViewObjects() {
	// init shader ////////////////////////////////////////////////////////////////////////////////
	planeShader = new Shader ("plane.vert", NULL, NULL, NULL, "plane.frag");

	// init camera ////////////////////////////////////////////////////////////////////////////////

	// init opengl render setting /////////////////////////////////////////////////////////////////
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// init models ////////////////////////////////////////////////////////////////////////////////
	glm::mat4 modelTransform;
	// Maze plane
	mazePlane = new Mesh();
	BasicMesh_Plane(mazePlane);
}

void MainView::resize(int width, int height) {
	glViewport(0, 0, width, height);
}

void MainView::drawView(float deltaTime) {
	planeShader->Activate();
	mazePlane->Draw();
}

void MainView::draw(float deltaTime) {
	// draw imgui
	drawImgui();

	// draw view
	drawView(deltaTime);
}

void MainView::updateParameter(float deltaTime) {
}