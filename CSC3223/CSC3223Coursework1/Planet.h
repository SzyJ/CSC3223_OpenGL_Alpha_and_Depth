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

class Planet {
private:
	const float ROTATION_SPEED = 0.1f;
	const float ORBIT_SPEED = 0.001f;
	RenderObject* renderObject;
	Matrix4 scaleMatrix;
	unsigned orbitRadius;
	float circumferenceSize;
	float totalTime;
	float x;
	float z;

public:
	Planet(OGLMesh* mesh, const unsigned orbitRadius);
	~Planet();
	void performInitialRender(Renderer& renderer);
	void update(float delta);
	void render(Renderer& renderer);
	float getXPos();
	float getZPos();
};