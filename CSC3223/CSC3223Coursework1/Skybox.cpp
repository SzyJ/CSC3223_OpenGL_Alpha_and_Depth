#include "Skybox.h"

Skybox::Skybox(OGLMesh* backgroundMesh, OGLMesh* starfieldMesh) {
	background = new RenderObject(backgroundMesh, Matrix4::Scale(Vector3(SCENE_RADIUS, SCENE_RADIUS, SCENE_RADIUS)));
	starfield.reserve(STARFIELD_DENSITY);
	for (int i = 0; i < STARFIELD_DENSITY; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += SCENE_RADIUS - 500;
		Matrix4 scale = Matrix4::Scale(
			Vector3(scaleAmount, scaleAmount, scaleAmount)
		);
		Matrix4 yRotation = Matrix4::Rotation(
			rand() % 360, Vector3(0, 1, 0)
		);
		Matrix4 xRotation = Matrix4::Rotation(
			rand() % 360, Vector3(1, 0, 0)
		);
		Matrix4 zRotation = Matrix4::Rotation(
			rand() % 360, Vector3(0, 0, 1)
		);

		starfield.push_back(new RenderObject(starfieldMesh, zRotation * xRotation * yRotation * scale));
	}
}

Skybox::~Skybox() {
	delete background;
	for (RenderObject* stars : starfield) {
		delete stars;
	}
}

void Skybox::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(background);

	for (RenderObject* stars : starfield) {
		renderer.AddRenderObject(stars);
	}
}