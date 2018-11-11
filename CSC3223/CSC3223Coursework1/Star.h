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

#include "Star.h"

using namespace NCL;
using namespace CSC3223;

class Star {
private:
	TextureBase* starTexture;
	RenderObject* renderObject;

public:
	Star(OGLMesh* mesh);
	~Star();
	void performInitialRender(Renderer& renderer);
};