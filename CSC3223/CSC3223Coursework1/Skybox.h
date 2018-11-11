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

#include "Skybox.h"

using namespace NCL;
using namespace CSC3223;

class Skybox {
private:
	const unsigned STARFIELD_DENSITY = 50;
	const unsigned SCENE_RADIUS = 7000;

	vector<RenderObject*> starfield;
	RenderObject* background;

public:
	Skybox(OGLMesh* backgroundMesh, OGLMesh* starfieldMesh);
	~Skybox();
	void performInitialRender(Renderer& renderer);
};