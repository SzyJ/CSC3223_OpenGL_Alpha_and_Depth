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

using namespace NCL;
using namespace CSC3223;

void generateStarfield(Renderer& renderer, const int sceneSize) {
	OGLMesh* stars = new OGLMesh();
	vector<Vector3> starPos;
	vector<Vector4> starCol;
	starPos.reserve(10000);
	starCol.reserve(10000);

	const int sceneHeight = 100;
	int diameter = sceneSize * 2 * PI;
	float x = rand() % diameter;
	float y = rand() % sceneHeight;

	for (int i = 0; i < 10000; i++) {
		starPos.emplace_back(rand() % 780, rand() % 600, (rand() % 300) - 150);
		starCol.emplace_back(1, 1, 1, 1);
	}

	stars->SetVertexPositions(starPos);
	stars->SetVertexColours(starCol);

	stars->SetPrimitiveType(GeometryPrimitive::Points);
	stars->UploadToGPU();

	renderer.AddRenderObject(new RenderObject(stars));
}

void createSkybox(Renderer& renderer) {
	OGLMesh * planet = new OGLMesh("Sphere.msh");

	planet->SetPrimitiveType(GeometryPrimitive::Triangles);
	planet->UploadToGPU();

	int scaleAmount = 7000;
	Matrix4 scale = Matrix4::Scale(
		Vector3(scaleAmount, scaleAmount, scaleAmount)
	);

	renderer.AddRenderObject(new RenderObject(planet, scale));
}

void generateSpaceship(Renderer& renderer, const int xPos, const int zPos) {
	const int shipWidth = 40;
	const int shipWingLength = 15;
	const int shipLength = 50;
	const int shipHeight = 10;

	Vector4 wingColour = Vector4(0.808f, 0.286f, 1, 1);
	Vector4 frontColour = Vector4(1, 0.0f, 0.914f, 1);
	Vector4 backColour = Vector4(0.906f, 0.22f, 1, 1);

	OGLMesh* ship = new OGLMesh();

	ship->SetVertexPositions({
		Vector3(xPos - (shipWidth / 2), shipHeight * -1, zPos),
		Vector3(xPos, 0, zPos - shipLength),
		Vector3(xPos, 0, zPos - shipWingLength),
		Vector3(xPos + (shipWidth / 2), shipHeight * -1, zPos)
		});
	ship->SetVertexColours({
		wingColour,
		frontColour,
		backColour,
		wingColour
		});

	ship->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	ship->UploadToGPU();

	renderer.AddRenderObject(new RenderObject(ship));
}

void generate3DPlanet(Renderer& renderer) {
	OGLMesh* bluePlanet = new OGLMesh("Sphere.msh");
	OGLMesh* greenPlanet = new OGLMesh("Sphere.msh");
	OGLMesh* redPlanet = new OGLMesh("Sphere.msh");

	const unsigned vertexCount = bluePlanet->GetVertexCount();
	vector<Vector4> blueVerts;
	vector<Vector4> greenVerts;
	vector<Vector4> redVerts;

	blueVerts.reserve(vertexCount);
	greenVerts.reserve(vertexCount);
	redVerts.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		blueVerts.emplace_back((float)(rand() % 30) / 255.0f, (float)(rand() % 30) / 255.0f, (float) (rand() % 255) / 255.0f, 1.0f);
		greenVerts.emplace_back((float)(rand() % 30) / 255.0f, (float)(rand() % 255) / 255.0f, (float)(rand() % 30) / 255.0f, 1.0f);
		redVerts.emplace_back((float)(rand() % 255) / 255.0f, (float)(rand() % 30) / 255.0f, (float)(rand() % 30) / 255.0f, 1.0f);
	}

	bluePlanet->SetVertexColours(blueVerts);
	greenPlanet->SetVertexColours(greenVerts);
	redPlanet->SetVertexColours(redVerts);

	bluePlanet->SetPrimitiveType(GeometryPrimitive::Triangles);
	greenPlanet->SetPrimitiveType(GeometryPrimitive::Triangles);
	redPlanet->SetPrimitiveType(GeometryPrimitive::Triangles);

	bluePlanet->UploadToGPU();
	greenPlanet->UploadToGPU();
	redPlanet->UploadToGPU();


	for (int i = 0; i < 10; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += 10;
		Matrix4 translate = Matrix4::Translation(
			Vector3(
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000
			)
		);
		Matrix4 scale = Matrix4::Scale(
			Vector3(scaleAmount, scaleAmount, scaleAmount)
		);
		renderer.AddRenderObject(
			new RenderObject(redPlanet, translate * scale)
		);
	}

	for (int i = 0; i < 10; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += 10;
		Matrix4 translate = Matrix4::Translation(
			Vector3(
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000
			)
		);
		Matrix4 scale = Matrix4::Scale(
			Vector3(scaleAmount, scaleAmount, scaleAmount)
		);
		renderer.AddRenderObject(
			new RenderObject(greenPlanet, translate * scale)
		);
	}

	for (int i = 0; i < 10; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += 10;
		Matrix4 translate = Matrix4::Translation(
			Vector3(
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000,
				((rand() % 2000) * -1) + 1000
			)
		);
		Matrix4 scale = Matrix4::Scale(
			Vector3(scaleAmount, scaleAmount, scaleAmount)
		);
		renderer.AddRenderObject(
			new RenderObject(bluePlanet, translate * scale)
		);
	}
}

void createPlanet(Renderer& renderer, const int x, const int y, const int radius, const int numberOfSides) {
	OGLMesh* planet = new OGLMesh();
	const int numberOfVertices = numberOfSides + 2;

	float doublePI = PI * 2.0f;

	vector<Vector3> positions;
	vector<Vector4> colours;

	positions.emplace_back(x, y, 1);
	colours.emplace_back(0.0f, 1.0f, 1.0f, 1.0f);

	positions.reserve(numberOfVertices);
	colours.reserve(numberOfVertices);

	for (int i = 0; i < numberOfVertices; i++) {
		positions.emplace_back(
			y + (radius * sin(i * doublePI / numberOfSides)),
			x + (radius * cos(i * doublePI / numberOfSides)),
			1
		);

		colours.emplace_back(0.0f, 0.0f, 1.0f, 1.0f);
	}

	planet->SetVertexPositions(positions);
	planet->SetVertexColours(colours);
	planet->SetPrimitiveType(GeometryPrimitive::TriangleFan);

	planet->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(planet));
}

void generateRingSystem(Renderer& renderer, int x, int y, int radius, int numberOfSides) {
	OGLMesh* planet = new OGLMesh();
	const int numberOfVertices = numberOfSides + 2;

	float doublePI = PI * 2.0f;

	vector<Vector3> positions;
	vector<Vector4> colours;


	//positions.emplace_back(x, y, 1);
	//colours.emplace_back(0.0f, 1.0f, 1.0f, 1.0f);


	positions.reserve(numberOfVertices);
	colours.reserve(numberOfVertices);


	for (int i = 0; i < numberOfVertices; i++) {
		positions.emplace_back(
			y + (radius * sin(i * doublePI / numberOfSides)),
			x + (radius * cos(i * doublePI / numberOfSides)),
			1
		);

		colours.emplace_back(1.0f, 1.0f, 1.0f, 1.0f);
	}

	planet->SetVertexPositions(positions);
	planet->SetVertexColours(colours);
	planet->SetPrimitiveType(GeometryPrimitive::TriangleStrip);

	planet->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(planet));
}

void generate3DStarfield(Renderer& renderer) {
	OGLMesh * starPoints = new OGLMesh("Sphere.msh");

	const unsigned vertexCount = starPoints->GetVertexCount();
	vector<Vector4> colours;
	colours.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		colours.emplace_back(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	starPoints->SetVertexColours(colours);
	starPoints->SetPrimitiveType(GeometryPrimitive::Points);
	
	starPoints->UploadToGPU();
	
	
	for (int i = 0; i < 50; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += 2000;
		Matrix4 scale = Matrix4::Scale(
			Vector3(scaleAmount, scaleAmount, scaleAmount)
		);
		Matrix4 yRotation = Matrix4::Rotation(
			rand() % 360, Vector3(0, 1, 0)
		);
		Matrix4 xRotation = Matrix4::Rotation(
			rand() % 360, Vector3(1, 0, 0)
		);
		renderer.AddRenderObject(
			new RenderObject(starPoints, xRotation * yRotation * scale)
		);
	}
}

void drawObjects(Renderer& renderer) {
	createSkybox(renderer);
	//generateStarfield(renderer, 1000);
	generateSpaceship(renderer, 0, 0);
	createPlanet(renderer, 150, 150, 50, 20);
	generateRingSystem(renderer, 150, 150, 75, 20);

	generate3DPlanet(renderer);

	generate3DStarfield(renderer);
}

void drawName(Renderer& renderer) {

}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	drawObjects(*renderer);

	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 9000.0f, aspect, 45.0f);
	renderer->SetProjectionMatrix(proj);
	renderer->SetDepthBufferState(true);

	Vector3 viewPosition(0, 0, 0);

	const float speed = 0.5f;
	const float rotationSpeed = 0.1f;

	bool objsDrawn = true;
	bool depthBuffer = true;
	bool alphaBlending = true;

	float pitch = 0.0f;
	float yaw = 0.0f;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		renderer->Update(time);

		//renderer->DrawString("Yaw: " + std::to_string(yaw), Vector2(10, 30));
		//renderer->DrawString("Pitch: " + std::to_string(pitch), Vector2(10, 10));
		//renderer->DrawString("Cos(Yaw): " + std::to_string(cos((yaw * PI) / 180)), Vector2(10, 50));
		//renderer->DrawString("Sin(Yaw): " + std::to_string(sin((yaw * PI) / 180)), Vector2(10, 70));

		// Movement keys
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.z += cos((pitch * PI) / 180) * speed;
			viewPosition.x -= sin((pitch * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition.x -= sin(((pitch - 90) * PI) / 180) * speed;
			viewPosition.z += cos(((pitch - 90) * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.z -= cos((pitch * PI) / 180) * speed;
			viewPosition.x += sin((pitch * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x += sin(((pitch - 90) * PI) / 180) * speed;
			viewPosition.z -= cos(((pitch - 90) * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			viewPosition.y += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			viewPosition.y -= speed;
		}

		// Rotation
		//pitch += Window::GetMouse()->GetRelativePosition().x;
		//yaw += Window::GetMouse()->GetRelativePosition().y;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			pitch -= rotationSpeed;
			if (pitch < 0) {
				pitch += 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			pitch += rotationSpeed;
			if (pitch > 360) {
				pitch -= 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {
			yaw += rotationSpeed;
			if (yaw > 360) {
				yaw -= 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
			yaw -= rotationSpeed;
			if (yaw < 0) {
				yaw += 360;
			}
		}
		renderer->SetViewMatrix(
			Matrix4::Rotation(pitch, Vector3(0, 1, 0)) *
			Matrix4::Translation(viewPosition) *
			Matrix4::Rotation(yaw, Vector3(1, 0, 0))
		);

		renderer->Render();

		// Toggle between name and planets
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
			renderer->DeleteAllRenderObjects();
			if (objsDrawn) {
				drawName(*renderer);
			} else {
				drawObjects(*renderer);
			}
			objsDrawn = !objsDrawn;
		}

		// Toggle depth buffer
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			depthBuffer = !depthBuffer;
			renderer->SetDepthBufferState(depthBuffer);
		}

		// Toggle alpha blending
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {
			alphaBlending = !alphaBlending;
			renderer->SetAlphaBlendingState(alphaBlending);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}