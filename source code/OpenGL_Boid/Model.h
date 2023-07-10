#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <vector>

#include "ShaderClass.h"
#include "Mesh.h"
#include "Material.h"

class Model {
	std::vector<Shader*> shaders;
	std::vector<Shader*> meshes;
};

#endif