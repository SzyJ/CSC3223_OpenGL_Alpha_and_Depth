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
#include "GPUObjects.h"

#include "Planet.h"
#include "Cloud.h"
#include "DistantStar.h"
#include "RingSystem.h"
#include "Spaceship.h"
#include "Skybox.h"
#include "Star.h"

using namespace NCL;
using namespace CSC3223;

class Scene {
private:
	const unsigned PLANET_COUNT = 2;
	const unsigned CLOUD_COUNT = 15;
	const unsigned ORBIT_SPACING = 10;

	GPUObjects MESHES;

	vector<Planet*> planets;
	vector<Cloud*> clouds;
	Skybox* starfield;
	Star* centralStar;
	DistantStar* distantStar;
	RingSystem* ringSystem;
	Spaceship* spaceship;

public:
	Scene();
	~Scene();

	void performInitialRender(Renderer& renderer);
	void update(float delta);
	void render(Renderer& renderer);
};