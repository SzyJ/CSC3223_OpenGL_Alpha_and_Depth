#include "Cloud.h"
#include "RandomMatrixUtils.h"
#include "GPUObjects.h"

Cloud::Cloud(OGLMesh* mesh) {
	sphereObjects.reserve(NEBULA_DENSITY);
	sphereObjects.push_back(new RenderObject(mesh));
}

void Cloud::performInitialRender(Renderer& renderer) {
	int x = rand() % 2000;
	x -= 1000;
	int z = rand() % 2000;
	z -= 1000;
	int y = rand() % 2000;
	y -= 1000;
	for (RenderObject* sphere : sphereObjects) {
		sphere->SetTransform(
			Matrix4::Translation(Vector3(x, y, z)) *
			RandomMatrixUtils::randomDisplacementMatrix(60) *
			RandomMatrixUtils::randomScaleMatrix(20, 50));

		renderer.AddRenderObject(sphere);
	}
}

Cloud::~Cloud() {
	for (RenderObject* object : sphereObjects) {
		delete object;
	}
}