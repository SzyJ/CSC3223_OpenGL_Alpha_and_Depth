#include "RingSystem.h"

RingSystem::RingSystem(OGLMesh* mesh) {
	renderObject = new RenderObject(mesh);
}

RingSystem::~RingSystem() {
	delete renderObject;
}

void RingSystem::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}

void RingSystem::setNewLocation(float x, float z) {
	xPos = x;
	zPos = z;
}

void RingSystem::update(float delta) {
	totalTime += delta;
	totalTime = fmod(totalTime * ROTATION_SPEED, 2.0f * PI);
}

void RingSystem::render(Renderer& renderer) {
	Matrix4 newTranslation;
	newTranslation = newTranslation * Matrix4::Rotation(totalTime * ROTATION_SPEED, Vector3(0, 1, 0));
	newTranslation = newTranslation * Matrix4::Rotation(OFFSET_ANGLE, Vector3(1, 0, 0));
	newTranslation = newTranslation * Matrix4::Translation(Vector3(xPos, 0, zPos));

	renderObject->SetTransform(newTranslation);
}