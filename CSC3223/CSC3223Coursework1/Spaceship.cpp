#include "Spaceship.h"

Spaceship::Spaceship(OGLMesh* mesh) {
	renderObject = new RenderObject(mesh, Matrix4::Translation(Vector3(0, 100, 500)));
}
Spaceship::~Spaceship() {
	delete renderObject;
}

void Spaceship::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}