#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <filesystem>

#include <glad/glad.h>

#include <stb/stb_image.h>

#include "ShaderClass.h"

// Texture Base Class /////////////////////////////////////////////////////////
class TextureBase {
// variables
private:
	// maximum texture solts for shader
	static const int maximumSolts;
	// 
	static int currSolt;
	// Number of reserve solt for spical texture(ex: shadow map from Frame Buffer , ...)
	static int reserveSoltsNum;
protected:
public:
	// Texture ID
	GLuint ID;
	// currint bind solt
	int solt;
	
// functions
private:

protected:

public:

	// bind texture with perives solt
	virtual void Bind() {};
	// bind texture with given solt
	void Bind(int solt);
	// find an empty solt and bind texture
	void BindAnySolt();
};

// tradition 2d texture ///////////////////////////////////////////////////////
class Texture2D : public TextureBase {
// variables
private:
protected:
public:
	int width;
	int height;
	int nChannels;
	GLenum format;

// functions
private:

protected:

public:
	// Constructors
	Texture2D();
	Texture2D(const char* imageFile);
	// Copy constructor
	Texture2D(const Texture2D&);
	// Destructor
	~Texture2D();

	// load texture from file
	void Load(const char* file);
	// default initial process
	void Init();
	// read a block of pixels
	std::vector<float> Read(int x, int y, int w, int h);
	// write a block of pixels
	void Write(int x, int y, int w, int h, std::vector<float>& datas);
	// bind texture
	void Bind() override;
};

// Cubemap ////////////////////////////////////////////////////////////////////
class TextureCube : public TextureBase {
// variables
private:
protected:
public:
	int width;
	int height;
	int nChannels;
	GLenum format;

// functions
private:

protected:

public:
	// Constructors
	TextureCube();
	TextureCube(const char* folder);
	TextureCube(const char* imageRight, const char* imageLeft, const char* imageTop, const char* imageBottom, const char* imageBack, const char* imageFront);
	// Copy constructor
	TextureCube(const TextureCube&);
	// Destructor
	~TextureCube();

	// load texture from 6 images in same folder
	void Load(const char* folder);
	// load texture from 6 images
	void Load(const char* imageRight, const char* imageLeft, const char* imageTop, const char* imageBottom, const char* imageBack, const char* imageFront);
	// default initial process
	void Init();
	// read a block of pixels
	std::vector<float> Read(int target, int x, int y, int w, int h);
	// write a block of pixels
	void Write(int target, int x, int y, int w, int h, std::vector<float>& datas);
	// bind texture
	void Bind() override;
};

// choose a picture by given time as texture
class TextureAnimate {

};

// decode video to texture
class TextureVideo {

};
#endif