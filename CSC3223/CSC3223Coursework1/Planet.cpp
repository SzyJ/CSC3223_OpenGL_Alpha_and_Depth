#include "Planet.h"
#include "RandomMatrixUtils.h"

Planet::Planet(OGLMesh* mesh, const unsigned orbitRadius) {
	totalTime = 0.0f;
	this->orbitRadius = orbitRadius;
	circumferenceSize = 2.0f * orbitRadius * PI;

	x = 0;
	z = orbitRadius;

	renderObject = new RenderObject(mesh);
	scaleMatrix = RandomMatrixUtils::randomScaleMatrix(5, 50);
}

Planet::~Planet() {
	delete renderObject;
}

void Planet::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(renderObject);
}

void Planet::update(float delta) {
	totalTime += delta;

	float distance = fmod(totalTime * ORBIT_SPEED, circumferenceSize);
	double theta = 2.0f * PI * ((double)distance / (double)circumferenceSize);
	x = (sin(theta) * orbitRadius);
	z = (cos(theta) * orbitRadius);
}

void Planet::render(Renderer& renderer) {
	Matrix4 newTransform = scaleMatrix;
	newTransform = newTransform * Matrix4::Translation(
		Vector3(x, 0, z)
	);
	newTransform = newTransform * Matrix4::Rotation(totalTime * ROTATION_SPEED, Vector3(0, 1, 0));

	renderObject->SetTransform(newTransform);
}

float Planet::getXPos() {
	return x;
}

float Planet::getZPos() {
	return z;
}