#include "Star.h"

Star::Star(OGLMesh* mesh) {

	const unsigned STAR_SIZE = 150;
	starTexture = OGLTexture::RGBATextureFromFilename("Doge.png");
	renderObject = new RenderObject(mesh, Matrix4::Scale(Vector3(STAR_SIZE, STAR_SIZE, STAR_SIZE)));
	renderObject->SetBaseTexture(starTexture);
}
Star::~Star() {
	delete renderObject;
	delete starTexture;
}

void Star::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}