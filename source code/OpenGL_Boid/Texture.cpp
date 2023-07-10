#include "Texture.h"

// Texture Base Class /////////////////////////////////////////////////////////
const int TextureBase::maximumSolts = 16;
int TextureBase::currSolt = 0;
int TextureBase::reserveSoltsNum = 8;
// bind texture with given solt, -1 will find an unused solt and bind
void TextureBase::Bind(int solt) {
	if (solt < 0) {
		BindAnySolt();
		return;
	}
	TextureBase::solt = solt;
	Bind();
}
// find an empty solt and bind texture
void TextureBase::BindAnySolt() {
	int solt = currSolt + 1;
	if (solt >= maximumSolts) solt = reserveSoltsNum;
	currSolt = solt;
	solt = solt;
	Bind();
}

// tradition 2d texture ///////////////////////////////////////////////////////
// Constructors
Texture2D::Texture2D() {
	glGenTextures(1, &ID);
	width = 0;
	height = 0;
	nChannels = 0;
	format = 0;
}
Texture2D::Texture2D(const char* imageFile) {
	glGenTextures(1, &ID);
	width = 0;
	height = 0;
	nChannels = 0;
	format = 0;
	Load(imageFile);
	Init();
}
// Copy constructor
Texture2D::Texture2D(const Texture2D& srcTex) {
	// create frame buffer
	GLuint copyFbo;
	glCreateFramebuffers(1, &copyFbo);
	// bind source framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, copyFbo);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, srcTex.width, srcTex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// attach source texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTex.ID, 0);

	// copy texture parameter
	width = srcTex.width;
	height = srcTex.height;
	nChannels = srcTex.nChannels;
	format = srcTex.format;

	// create new texture
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + solt);
	// bind destination texture
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(ID, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// copy pixels from framebuffer to texture
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);

	// delete framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &copyFbo);
}
// Destructor
Texture2D::~Texture2D() {
	glDeleteTextures(1, &ID);
}

// load texture from file
void Texture2D::Load(const char* file) {
	std::cout << "[INFO::TEXTURE2D::LOAD] " << file << std::endl;
	stbi_set_flip_vertically_on_load(1);

	unsigned char* data;
	// read new data
	data = stbi_load(file, &(width), &(height), &(nChannels), 0);
	// check if load fail
	if (!data) {
		std::cout << "[ERROR::TEXTURE2D::LOAD] Failed to load texture \"" << file << "\"" << std::endl;
		exit(1);
	}

	GLenum dataFormat =	(nChannels == 4) ? GL_RGBA :
						(nChannels == 3) ? GL_RGB :
						(nChannels == 2) ? GL_RG :
						(nChannels == 1) ? GL_RED :
						GL_RGB;
	GLenum glFormat =	(nChannels == 4) ? GL_RGBA :
						(nChannels == 3) ? GL_RGB :
						(nChannels == 2) ? GL_RG :
						(nChannels == 1) ? GL_RED :
						GL_RGB;
	// bind texture to config
	Bind();
	// upload pixel datas to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	format = glFormat;
	// generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// free loaded data
	stbi_image_free(data);
}

// default initial process
void Texture2D::Init() {
	std::cout << "[INFO::TEXTURE2D::INIT] " << "Defaule initialize" << std::endl;
	// bind texture to config
	Bind();

	// setting up texture
	//		Texture Wrapping
	//			2d or 3d texture; s and t (and r)axis; repeat, mirror repeat, edge or border mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//		border mode setting
	float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//		Texture Filtering 
	//			2d or 3d texture; scaling up and scaling down; nearest or linear;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//			Mipmaps. use low resolution textures when objects are far away.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
// read a block of pixels
std::vector<float> Texture2D::Read(int x, int y, int w, int h) {
	// create frame buffer
	GLuint readFbo;
	glCreateFramebuffers(1, &readFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, readFbo);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// attach source texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);


	// read from framebuffer
	std::vector<float> returnData;
	returnData.resize(w*h);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, returnData.data());

	// delete framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &readFbo);

	return returnData;
}
// read a block of pixels
void Texture2D::Write(int x, int y, int w, int h, std::vector<float>& datas) {

}
// bind texture
void Texture2D::Bind() {
	glActiveTexture(GL_TEXTURE0 + solt); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, ID);
}

// Cubemap ////////////////////////////////////////////////////////////////////
// Constructors
TextureCube::TextureCube(){
	glGenTextures(1, &ID);
	width = 0;
	height = 0;
	nChannels = 0;
	format = 0;
}

// load texture from 6 images in same folder
void TextureCube::Load(const char* folder) {

}
// load texture from 6 images
void TextureCube::Load(const char* imageRight, const char* imageLeft, const char* imageTop, const char* imageBottom, const char* imageBack, const char* imageFront) {
	std::cout << "[INFO::TEXTURECUBE::LOAD] " << std::endl;
	
	const char* images[6] = { imageRight, imageLeft, imageTop, imageBottom, imageBack, imageFront };
	for (unsigned int i = 0; i < 6; i++) {
		unsigned char* data = NULL;
		// read new data
		data = stbi_load(images[i], &(width), &(height), &(nChannels), 0);
		// check if load fail
		if (!data) {
			std::cout << "[ERROR::TEXTURECUBE::LOAD] Failed to load cube texture \"" << images[i] << "\"" << std::endl;
			exit(1);
		}

		GLenum dataFormat = (nChannels == 4) ? GL_RGBA :
			(nChannels == 3) ? GL_RGB :
			(nChannels == 2) ? GL_RG :
			(nChannels == 1) ? GL_RED :
			GL_RGB;
		GLenum glFormat = (nChannels == 4) ? GL_RGBA :
			(nChannels == 3) ? GL_RGB :
			(nChannels == 2) ? GL_RG :
			(nChannels == 1) ? GL_RED :
			GL_RGB;
		// bind texture to config
		Bind();
		// upload pixel datas to opengl
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, glFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		format = glFormat;
		// generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		// free loaded data
		stbi_image_free(data);
	}
}
// default initial process
void TextureCube::Init() {
	std::cout << "[INFO::TEXTURECUBE::INIT] " << "Defaule initialize" << std::endl;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
// bind texture
void TextureCube::Bind() {
	glActiveTexture(GL_TEXTURE0 + solt); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}