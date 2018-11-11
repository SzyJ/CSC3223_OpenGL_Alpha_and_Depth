#pragma once
#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

class GPUObjects {
private:
	OGLMesh* sphere_white;
	OGLMesh* sphere_black;
	OGLMesh* sphere_alpha_blue;
	OGLMesh* sphere_points_white;
	OGLMesh* sphere_textured_red;
	OGLMesh* sphere_textured_green;
	OGLMesh* sphere_textured_blue;
	OGLMesh* circle_yellow_gradient;
	OGLMesh* ring_rainbow;
	OGLMesh* spaceship;

	void setUpSpheres();
	void setUpGradientCircle();
	void setUpRainbowRing();
	void setUpSpaceship();
public:
	GPUObjects();
	~GPUObjects();
	OGLMesh* get_Sphere_white();
	OGLMesh* get_Sphere_black();
	OGLMesh* get_Sphere_alpha_blue();
	OGLMesh* get_Sphere_points_white();
	OGLMesh* get_Sphere_textured_red();
	OGLMesh* get_Sphere_textured_green();
	OGLMesh* get_Sphere_textured_blue();
	OGLMesh* get_Circle_yellow_gradient();
	OGLMesh* get_Ring_rainbow();
	OGLMesh* get_Spaceship();

};