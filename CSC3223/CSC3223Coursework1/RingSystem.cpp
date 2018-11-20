#include "RingSystem.h"

RingSystem::RingSystem(OGLMesh* mesh) {
	renderObject = new RenderObject(mesh, Matrix4::Scale(Vector3(10, 10, 10)));
}

RingSystem::~RingSystem() {
	delete renderObject;
}

void RingSystem::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}

void RingSystem::update(float delta) {
	totalTime += delta;
	totalTime = fmod(totalTime * ROTATION_SPEED, 2.0f * PI);
}

void RingSystem::render(Renderer& renderer) {
	Matrix4 newTranslation = renderObject->GetTransform();
	newTranslation = newTranslation * Matrix4::Rotation(ROTATION_SPEED, Vector3(0, 1, 0));
	newTranslation = newTranslation * Matrix4::Rotation(OFFSET_ANGLE, Vector3(1, 0, 0));

	renderObject->SetTransform(newTranslation);
} 