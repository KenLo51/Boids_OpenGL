#pragma once

// C/C++ Libraries
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

// OpenGL Libreries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// User Defined Libreries
#include "ShaderClass.h"
#include "Camera.h"
#include "Mesh.h"

#include "InputHandler.h"

//#include "mainView.h"
//class MainView;
#include "Scene.h"

// call_back function while window size has been changed
static void windowResize_CB(GLFWwindow* window, int width, int height);

class MainWindow {
private:
	const char title[80] = {"Boid"};

public:
	InputHandler* inputHandler;
	GLFWwindow* window;
	SceneBase* currScene;
	int width;
	int height;

private:
	void initVariables();

	// initialize glfw window
	void initWindow();

	// initialize opengl
	void initOpneGL();

	// initialize imgui
	void initImgui();
public:
	// constructor. initialize window, opengl, imgui
	MainWindow();

	// run window
	void run();

	// get the width of the window
	int w();

	// get the height of the window
	int h();
};

static MainWindow* currWindow;