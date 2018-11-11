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

class RingSystem {
private:
	const float OFFSET_ANGLE = 0.1f;
	const float ROTATION_SPEED = 0.001f;
	RenderObject* renderObject;
	float totalTime;
	float xPos;
	float zPos;

public:
	RingSystem(OGLMesh* mesh);
	~RingSystem();

	void performInitialRender(Renderer& renderer);
	void setNewLocation(float x, float z);
	void update(float delta);
	void render(Renderer& renderer);
};