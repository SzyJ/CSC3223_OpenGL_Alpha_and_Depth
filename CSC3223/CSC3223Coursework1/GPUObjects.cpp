#include "GPUObjects.h"

GPUObjects::~GPUObjects() {
	delete sphere_white;
	delete sphere_black;
	delete sphere_alpha_blue;
	delete sphere_points_white;
	delete sphere_textured_red;
	delete sphere_textured_green;
	delete sphere_textured_blue;
	delete circle_yellow_gradient;
	delete ring_rainbow;
	delete spaceship;
}

GPUObjects::GPUObjects() {
	setUpSpheres();
	setUpGradientCircle();
	setUpRainbowRing();
	setUpSpaceship();
}

void GPUObjects::setUpSpheres() {
	OGLMesh sphereBase("Sphere.msh");
	int vertextCount = sphereBase.GetVertexCount();

	vector<Vector4> spherePointsBlack;
	vector<Vector4> spherePointsWhite;
	vector<Vector4> spherePointsAlphaBlue;
	vector<Vector4> spherePointsTextureRed;
	vector<Vector4> spherePointsTextureBlue;
	vector<Vector4> spherePointsTextureGreen;
	spherePointsBlack.reserve(vertextCount);
	spherePointsWhite.reserve(vertextCount);
	spherePointsTextureRed.reserve(vertextCount);
	spherePointsTextureGreen.reserve(vertextCount);
	spherePointsTextureBlue.reserve(vertextCount);

	for (int i = 0; i < vertextCount; i++) {
		spherePointsBlack.emplace_back(0.0f, 0.0f, 0.0f, 1.0f);
		spherePointsWhite.emplace_back(1.0f, 1.0f, 1.0f, 1.0f);
		spherePointsAlphaBlue.emplace_back(0.143f, 0.236f, 1.0f, 0.05f);
		spherePointsTextureRed.emplace_back(
			(float)(rand() % 255) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			1.0f);
		spherePointsTextureGreen.emplace_back(
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 255) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			1.0f);
		spherePointsTextureBlue.emplace_back(
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 255) / 255.0f,
			1.0f);
	}

	sphere_white = new OGLMesh("Sphere.msh");
	sphere_white->SetVertexColours(spherePointsWhite);
	sphere_white->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_white->UploadToGPU();

	sphere_black = new OGLMesh("Sphere.msh");;
	sphere_black->SetVertexColours(spherePointsBlack);
	sphere_black->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_black->UploadToGPU();

	sphere_alpha_blue = new OGLMesh("Sphere.msh");;
	sphere_alpha_blue->SetVertexColours(spherePointsAlphaBlue);
	sphere_alpha_blue->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_alpha_blue->UploadToGPU();

	sphere_points_white = new OGLMesh("Sphere.msh");;
	sphere_points_white->SetVertexColours(spherePointsWhite);
	sphere_points_white->SetPrimitiveType(GeometryPrimitive::Points);
	sphere_points_white->UploadToGPU();

	sphere_textured_red = new OGLMesh("Sphere.msh");;
	sphere_textured_red->SetVertexColours(spherePointsTextureRed);
	sphere_textured_red->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_textured_red->UploadToGPU();

	sphere_textured_green = new OGLMesh("Sphere.msh");;
	sphere_textured_green->SetVertexColours(spherePointsTextureGreen);
	sphere_textured_green->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_textured_green->UploadToGPU();

	sphere_textured_blue = new OGLMesh("Sphere.msh");;
	sphere_textured_blue->SetVertexColours(spherePointsTextureBlue);
	sphere_textured_blue->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere_textured_blue->UploadToGPU();
}

void GPUObjects::setUpGradientCircle() {
	float doublePI = PI * 2.0f;
	circle_yellow_gradient = new OGLMesh();
	float circleRadius = 100;
	int circleSmoothness = 20;
	int circleVertexCount = circleSmoothness + 2;
	
	vector<Vector3> circlePositions;
	vector<Vector4> circleColours;
	circlePositions.reserve(circleVertexCount);
	circleColours.reserve(circleVertexCount);

	circlePositions.emplace_back(0, 0, 0);
	circleColours.emplace_back(1.0f, 1.0f, 0.0f, 1.0f);

	for (int i = 0; i < circleVertexCount; i++) {
		circlePositions.emplace_back(
			circleRadius * cos(i * doublePI / circleSmoothness),
			circleRadius * sin(i * doublePI / circleSmoothness),
			0
		);

		circleColours.emplace_back(0.0f, 0.0f, 0.0f, 0.0f);
	}

	circle_yellow_gradient->SetVertexPositions(circlePositions);
	circle_yellow_gradient->SetVertexColours(circleColours);
	circle_yellow_gradient->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	circle_yellow_gradient->UploadToGPU();
}

void GPUObjects::setUpRainbowRing() {
	float doublePI = PI * 2.0f;
	ring_rainbow = new OGLMesh();
	float ringRadius = 75;
	int ringSmoothness = 20;
	int ringVertexCount = ringSmoothness + 2;
	float ringXPos = 0.0f;
	float ringYPos = 0.0f;
	float ringZPos = 0.0f;

	vector<Vector3> ringPositions;
	vector<Vector4> ringColours;
	ringPositions.reserve(ringVertexCount);
	ringColours.reserve(ringVertexCount);
	for (int i = 0; i < ringVertexCount; i++) {
		ringPositions.emplace_back(
			ringRadius * cos(i * doublePI / ringSmoothness),
			0,
			ringRadius * sin(i * doublePI / ringSmoothness)
		);

		ringColours.emplace_back(sin(i + 1), sin(i + 3), sin(i + 5), 0.1f);
	}

	ring_rainbow->SetVertexPositions(ringPositions);
	ring_rainbow->SetVertexColours(ringColours);
	ring_rainbow->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	ring_rainbow->UploadToGPU();
}

void GPUObjects::setUpSpaceship() {
	spaceship = new OGLMesh;
	const int shipWidth = 40;
	const int shipWingLength = 15;
	const int shipLength = 50;
	const int shipHeight = 10;

	Vector4 shipWingColour = Vector4(0.808f, 0.286f, 1, 1);
	Vector4 shipFrontColour = Vector4(1, 0.0f, 0.914f, 1);
	Vector4 shipBackColour = Vector4(0.906f, 0.22f, 1, 1);

	spaceship->SetVertexPositions({
		Vector3(0 - (shipWidth / 2), shipHeight * -1, 0),
		Vector3(0, 0, 0 - shipLength),
		Vector3(0, 0, 0 - shipWingLength),
		Vector3(0 + (shipWidth / 2), shipHeight * -1, 0)
		});
	spaceship->SetVertexColours({
		shipWingColour,
		shipFrontColour,
		shipBackColour,
		shipWingColour
		});
	spaceship->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	spaceship->UploadToGPU();
}

OGLMesh *GPUObjects::get_Sphere_white() {
	return sphere_white;
}
OGLMesh *GPUObjects::get_Sphere_black() {
	return sphere_black;
}
OGLMesh *GPUObjects::get_Sphere_alpha_blue() {
	return sphere_alpha_blue;
}
OGLMesh *GPUObjects::get_Sphere_points_white() {
	return sphere_points_white;
}
OGLMesh *GPUObjects::get_Sphere_textured_red() {
	return sphere_textured_red;
}
OGLMesh *GPUObjects::get_Sphere_textured_green() {
	return sphere_textured_green;
}
OGLMesh *GPUObjects::get_Sphere_textured_blue() {
	return sphere_textured_blue;
}
OGLMesh *GPUObjects::get_Circle_yellow_gradient() {
	return circle_yellow_gradient;
}
OGLMesh *GPUObjects::get_Ring_rainbow() {
	return ring_rainbow;
}
OGLMesh *GPUObjects::get_Spaceship() {
	return spaceship;
}