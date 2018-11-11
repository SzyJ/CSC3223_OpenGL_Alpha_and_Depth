#include "DistantStar.h"

DistantStar::DistantStar(OGLMesh* mesh) {
	renderObject = new RenderObject(mesh, Matrix4::Translation(Vector3(0, 0, -6000)));
}
DistantStar::~DistantStar() {
	delete renderObject;
}

void DistantStar::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}