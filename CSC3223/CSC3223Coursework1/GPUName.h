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

class GPUName {
private:
	const float LETTER_WIDTH = 50;
	const float LETTER_HEIGHT = 100;

	bool useBresenham = false;

	OGLMesh* s;
	OGLMesh* z;
	OGLMesh* y;
	OGLMesh* m;
	OGLMesh* o;
	OGLMesh* n;

	void setUpLetterMeshes();

public:
	GPUName();
	~GPUName();

	OGLMesh* get_s_mesh();
	OGLMesh* get_z_mesh();
	OGLMesh* get_y_mesh();
	OGLMesh* get_m_mesh();
	OGLMesh* get_o_mesh();
	OGLMesh* get_n_mesh();
};