#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include "Texture.h"

class PhongMaterial {
	Texture2D* diffuse;
	Texture2D* specular;	
};

class PBRMaterial {
	Texture2D* diffuse;
	Texture2D* specular;
	float roughness;
	float metalness;
};

#endif