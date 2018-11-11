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
#include "GPUName.h"

using namespace NCL;
using namespace CSC3223;

class NameScene {
private:
	const float LETTER_SPACING = 10.0f;

	GPUName MESHES;

	RenderObject* sObject;
	RenderObject* zObject;
	RenderObject* yObject;
	RenderObject* mObject;
	RenderObject* oObject;
	RenderObject* nObject;

public:
	NameScene();

	void performInitialRender(Renderer& renderer);
};