#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

// include std libraries
#include <iostream>

// include gui libraries
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/FileBrowser/ImGuiFileBrowser.h>

// include objects
#include "ShaderClass.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//
#include "Boid.h"

// Scene base class ///////////////////////////////////////////////////////////////////////////////
class SceneBase {
private:
	// render states
	bool limitFrameRate;

public:
	int width, height;

private:
	// initialize VAO, VBO, EBO, Shader, Texture...
	virtual void InitObjects() {}
	// Delete VAO, VBO, EBO, Shader, Texture...
	virtual void DeleteObjects() {}
	// draw gui (Imgui for this project)
	virtual void drawGui() {}
	// draw 3d scene
	virtual void DrawView(float deltaTime = 0.016667f) {}

public:
	// Draw all, contains gui and 3d objects
	void Draw(float deltaTime = 0.016667f);
	// resize view port
	virtual void Resize(int width, int height) {}
	// update variables for animation and simulation
	virtual void UpdateParameter(float deltaTime = 0.016667f) {}
};



class BoidScene : public SceneBase {
private:
	// render states
	bool limitFrameRate;

	// Imgui objects
	imgui_addons::ImGuiFileBrowser file_dialog;

	// 3d objects (Meshs, Models)
	Mesh* planeMesh;
	Texture2D* uvTestTex;

	Boids* boids;
	Mesh* aBoidMesh;

	// Cameras
	Camera* directionalLight;
	float directionalLight_theta;
	float directionalLight_phi;

	// Shaders
	Shader* planeShader;
	Shader* boidShader;

private:
	// initialize VAO, VBO, EBO, Shader, Texture...
	void InitObjects() override;
	// Delete VAO, VBO, EBO, Shader, Texture...
	void DeleteObjects() override;
	// draw gui (Imgui for this project)
	void drawGui() override;
	// draw 3d scene
	void DrawView(float deltaTime = 0.016667f) override;

public:
	// Constructors
	BoidScene();
	// Destructor
	~BoidScene();
	// resize view port
	void Resize(int width, int height) override;
	// update variables for animation and simulation
	void UpdateParameter(float deltaTime = 0.016667f) override;
};

#endif SCENE_CLASS_H