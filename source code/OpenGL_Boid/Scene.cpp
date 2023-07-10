#include "Scene.h"

// Scene base class ///////////////////////////////////////////////////////////////////////////////

// Draw all, contains gui and 3d objects
void SceneBase::Draw(float deltaTime) {
	DrawView();
	drawGui();
	UpdateParameter(deltaTime);
}

// Boid scene class ///////////////////////////////////////////////////////////////////////////////
// Constructors
BoidScene::BoidScene() {
	InitObjects();
}
// Destructor
BoidScene::~BoidScene() {
	DeleteObjects();
}
// initialize VAO, VBO, EBO, Shader, Texture...
void BoidScene::InitObjects() {
	std::cout << "[INFO::SCENE] BoidScene::InitObjects()" << std::endl;
	// init shader ////////////////////////////////////////////////////////////////////////////////
	planeShader = new Shader("plane.vert", NULL, NULL, NULL, "plane.frag");
	boidShader = new Shader("boid.vert", NULL, NULL, NULL, "boid.frag");
	// init camera ////////////////////////////////////////////////////////////////////////////////

	// init opengl render setting /////////////////////////////////////////////////////////////////
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	// init models ////////////////////////////////////////////////////////////////////////////////
	glm::mat4 modelTransform;
	// plane
	planeMesh = new Mesh();
	BasicMesh_Plane(planeMesh, glm::vec2(0.8, 0.8));

	uvTestTex = new Texture2D();
	uvTestTex->Load("E:\\Workspace\\Cpp\\OpenGL_Boid\\OpenGL_Boid\\Textures\\checker-map_tho.png");
	uvTestTex->Init();

	boids = new Boids(200, 0.3, 0.4, 0.4);
	aBoidMesh = new Mesh();
	BasicMesh_Dot(aBoidMesh);
}
// Delete VAO, VBO, EBO, Shader, Texture...
void BoidScene::DeleteObjects() {
	// delete shader //////////////////////////////////////////////////////////////////////////////
	delete planeShader;

	// delete camera //////////////////////////////////////////////////////////////////////////////

	// delete models //////////////////////////////////////////////////////////////////////////////
	delete planeMesh;
	delete uvTestTex;
	delete boids;
}

// draw gui (Imgui for this project)
void BoidScene::drawGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// User Manual Halper
	ImGui::Begin("Boid");
	ImGui::SliderFloat("Separation range", &(boids->separationR), 0.0f, 2.0f);
	ImGui::SliderFloat("sMul", &(boids->separationMul), 0.0f, 0.5f);
	ImGui::SliderFloat("Alignment range ", &(boids->alignmentR), 0.0f, 2.0f);
	ImGui::SliderFloat("aMul", &(boids->alignmentMul), 0.0f, 0.5f);
	ImGui::SliderFloat("Cohesion range  ", &(boids->cohesionR), 0.0f, 2.0f);
	ImGui::SliderFloat("cMul", &(boids->cohesionMul), 0.0f, 0.5f);
	ImGui::End();

	ImGui::Render();
}

// draw 3d scene
void BoidScene::DrawView(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//uvTestTex->Bind();
	//planeShader->Activate();
	//planeShader->setUniform("image", (int)uvTestTex->solt);
	//planeMesh->Draw();

	//boidShader->Activate();
	//glm::vec3 pos = glm::vec3(0.5, 0, 0);
	//boidShader->setUniform("pos", pos);
	//glPointSize(10);
	//aBoidMesh->Draw(GL_POINTS);

	boidShader->Activate();
	glPointSize(10);
	for (unsigned int i = 0; i < boids->birds.size(); i++) {
		boidShader->setUniform("pos", boids->birds[i].position);
		aBoidMesh->Draw(GL_POINTS);
	}
}

// resize view port
void BoidScene::Resize(int width, int height) {
	BoidScene::width = width;
	BoidScene::height = height;
	glViewport(0, 0, width, height);
}

// update variables for animation and simulation
void BoidScene::UpdateParameter(float deltaTime) {
	boids->Step(deltaTime);
}