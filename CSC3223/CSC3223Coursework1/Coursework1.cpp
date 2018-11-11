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

#include "Scene.h"
#include "NameScene.h"

#include "RasterisationMesh.h"
using namespace NCL;
using namespace CSC3223;
/*
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

Matrix4 randomDisplacementMatrix(const int sceneSize) {
	Matrix4 translate = Matrix4::Translation(
		Vector3(
			(rand() % (2 * sceneSize)) - sceneSize,
			(rand() % (2 * sceneSize)) - sceneSize,
			(rand() % (2 * sceneSize)) - sceneSize
		)
	);

	return translate;
}

Matrix4 randomScaleMatrix(const unsigned minScale, const unsigned scaleVarience) {
	float scaleAmount = rand() % scaleVarience;
	scaleAmount += minScale;

	Matrix4 scale = Matrix4::Scale(
		Vector3(scaleAmount, scaleAmount, scaleAmount)
	);

	return scale;
}

vector<Planet*>* generate3DPlanet(Renderer& renderer) {
	const unsigned PLANET_COUNT = 2;
	vector<Planet*>* planetList = new vector<Planet*>;
	planetList->reserve(PLANET_COUNT * 3);

	OGLMesh* bluePlanet = new OGLMesh("Sphere.msh");
	OGLMesh* greenPlanet = new OGLMesh("Sphere.msh");
	OGLMesh* redPlanet = new OGLMesh("Sphere.msh");

	// Define Random colour patterns
	const unsigned vertexCount = bluePlanet->GetVertexCount();
	vector<Vector4> blueVerts;
	vector<Vector4> greenVerts;
	vector<Vector4> redVerts;
	blueVerts.reserve(vertexCount);
	greenVerts.reserve(vertexCount);
	redVerts.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		blueVerts.emplace_back(
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 255) / 255.0f,
			1.0f);
		greenVerts.emplace_back(
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 255) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			1.0f);
		redVerts.emplace_back(
			(float)(rand() % 255) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			(float)(rand() % 30) / 255.0f,
			1.0f);
	}

	// Set Planet Colours
	bluePlanet->SetVertexColours(blueVerts);
	greenPlanet->SetVertexColours(greenVerts);
	redPlanet->SetVertexColours(redVerts);

	// Set Type
	bluePlanet->SetPrimitiveType(GeometryPrimitive::Triangles);
	greenPlanet->SetPrimitiveType(GeometryPrimitive::Triangles);
	redPlanet->SetPrimitiveType(GeometryPrimitive::Triangles);

	// Upload 3 types of planets to GPU
	bluePlanet->UploadToGPU();
	greenPlanet->UploadToGPU();
	redPlanet->UploadToGPU();

	for (int i = 1; i <= PLANET_COUNT * 3; i+=3) {
		// Red Planet
		Planet* thisRedPlanet = new Planet(redPlanet, randomScaleMatrix(5, 50), i * 10);
		renderer.AddRenderObject(thisRedPlanet->getRenderObject());
		planetList->push_back(thisRedPlanet);

		// Green Planet
		Planet* thisGreenPlanet = new Planet(greenPlanet, randomScaleMatrix(5, 50), (i + 1) * 10);
		//thisGreenPlanet->SetBaseTexture(nyanTexture);
		renderer.AddRenderObject(thisGreenPlanet->getRenderObject());
		planetList->push_back(thisGreenPlanet);

		// Blue Planet
		Planet* thisBluePlanet = new Planet(bluePlanet, randomScaleMatrix(5, 50), (i + 2) * 10);
		//thisBluePlanet->SetBaseTexture(brickTexture);
		renderer.AddRenderObject(thisBluePlanet->getRenderObject());
		planetList->push_back(thisBluePlanet);
	}

	return planetList;
}

void generateDistantStar(Renderer& renderer, const int radius, const int numberOfSides) {
	OGLMesh* planet = new OGLMesh();
	const int numberOfVertices = numberOfSides + 2;

	float doublePI = PI * 2.0f;

	vector<Vector3> positions;
	vector<Vector4> colours;
	int y = 0;
	int x = 0;
	positions.emplace_back(x, y, -6000);
	
	colours.emplace_back(1.0f, 1.0f, 0.0f, 1.0f);

	positions.reserve(numberOfVertices);
	colours.reserve(numberOfVertices);

	for (int i = 0; i < numberOfVertices; i++) {
		positions.emplace_back(
			x + (radius * cos(i * doublePI / numberOfSides)),
			y + (radius * sin(i * doublePI / numberOfSides)),
			-6000
		);

		colours.emplace_back(0.0f, 0.0f, 0.0f, 0.0f);
	}

	planet->SetVertexPositions(positions);
	planet->SetVertexColours(colours);
	planet->SetPrimitiveType(GeometryPrimitive::TriangleFan);

	planet->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(planet));
}

void generateRingSystem(Renderer& renderer, int radius, int numberOfSides) {
	OGLMesh* planet = new OGLMesh();
	const int numberOfVertices = numberOfSides + 2;

	float doublePI = PI * 2.0f;

	vector<Vector3> positions;
	vector<Vector4> colours;

	positions.reserve(numberOfVertices);
	colours.reserve(numberOfVertices);

	for (int i = 0; i < numberOfVertices; i++) {
		positions.emplace_back(
			radius * cos(i * doublePI / numberOfSides),
			0,
			radius * sin(i * doublePI / numberOfSides)
		);

		colours.emplace_back(sin(i + 1), sin(i + 3), sin(i + 5), 1.0f);
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
		colours.emplace_back(1.0f, 1.0f, 1.0f, (rand() % 100) + 150.0f / 255.0f);
	}
	
	starPoints->SetVertexColours(colours);
	starPoints->SetPrimitiveType(GeometryPrimitive::Points);
	starPoints->UploadToGPU();
	
	
	for (int i = 0; i < 50; i++) {
		float scaleAmount = rand() % 50;
		scaleAmount += 6000;
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

void generateNebula(Renderer& renderer) {
	OGLMesh* blueCloud = new OGLMesh("Sphere.msh");
	const unsigned vertexCount = blueCloud->GetVertexCount();

	vector<Vector4> colour;
	colour.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		colour.emplace_back(0.143f, 0.236f, 1.0f, 0.05f);
	}
	blueCloud->SetVertexColours(colour);
	blueCloud->UploadToGPU();
	
	const unsigned nebulaCount = 15;
	const unsigned nebulaDensity = 25;

	for (int eachNebula = 0; eachNebula < nebulaCount; eachNebula++) {
		int x = rand() % 2000;
		x -= 1000;
		int z = rand() % 2000;
		z -= 1000;
		int y = rand() % 2000;
		y -= 1000;
		for (int i = 0; i < nebulaDensity; i++) {
			renderer.AddRenderObject(new RenderObject(blueCloud, Matrix4::Translation(Vector3(x, y, z)) * randomDisplacementMatrix(60) * randomScaleMatrix(20, 50)));
		}
	}
}

void generateStar(Renderer& renderer, int scale) {
	OGLMesh* star = new OGLMesh("Sphere.msh");
	unsigned vertexCount = star->GetVertexCount();
	vector<Vector4> colourData;
	colourData.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		colourData.emplace_back(1, 1, 1, 1);
	}
	star->SetVertexColours(colourData);
	star->UploadToGPU();

	TextureBase* starTexture = OGLTexture::RGBATextureFromFilename("Doge.png");
	RenderObject* renderStar = new RenderObject(star, Matrix4::Scale(Vector3(scale, scale, scale)));
	renderStar->SetBaseTexture(starTexture);

	renderer.AddRenderObject(renderStar);
}

vector<Planet*>* drawObjects(Renderer& renderer) {
	createSkybox(renderer);
	generate3DStarfield(renderer);
	generateDistantStar(renderer, 100, 20);

	generateSpaceship(renderer, 0, 0);

	
	generateRingSystem(renderer, 75, 20);
	generateStar(renderer, 150);

	vector<Planet*>* planetList = generate3DPlanet(renderer);
	
	generateNebula(renderer);

	
	return planetList;
}
*/
void drawName(Renderer& renderer) {
	OGLMesh* lines = new OGLMesh();
	lines->SetVertexPositions({
		Vector3(150, 50, 0),
		Vector3(180, 80, 0),
		Vector3(100, 200, 0),
		Vector3(150, 150, 0)
		});
	lines->SetVertexColours({
		Vector4(1, 0, 0, 1),
		Vector4(0, 1, 0, 1),
		Vector4(0, 0, 1, 1),
		Vector4(1, 0, 1, 1)
		});
	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(lines));


	OGLMesh* tris = new OGLMesh();
	tris->SetVertexPositions({
		Vector3(550, 200, 0),
		Vector3(750, 200, 0),
		Vector3(650, 100, 0)
		});
	tris->SetVertexColours({
		Vector4(1, 0, 0, 1),
		Vector4(0, 1, 0, 1),
		Vector4(0, 0, 1, 1)
		});
	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(tris));

	OGLMesh* rasterLine = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({
		Vector3(150, 350, 0),
		Vector3(180, 380, 0),
		Vector3(100, 500, 0),
		Vector3(150, 450, 0)
		}, false);

	renderer.AddRenderObject(new RenderObject(rasterLine));

	OGLMesh* rasterTri = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({
		Vector3(550, 400, 0),
		Vector3(750, 380, 0),
		Vector3(650, 300, 0)
		}, false);

	renderer.AddRenderObject(new RenderObject(rasterTri));
}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	//vector<Planet*>* planetList = drawObjects(*renderer);

	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 12000.0f, aspect, 45.0f);
	renderer->SetProjectionMatrix(proj);

	Vector3 viewPosition(0, -210, -600);

	const float speed = 1.0f;
	const float rotationSpeed = 0.6f;
	bool mouseControls = true;


	bool objsDrawn = true;

	std::string blendingState = "Linear";
	short blendingMode = 0;
	std::string depthState = "Less-or-Equal";

	bool depthBuffer = true;
	bool alphaBlending = true;
	renderer->SetDepthBufferState(depthBuffer);
	renderer->SetAlphaBlendingState(alphaBlending);

	float pitch = 0.0f;
	float yaw = 0.0f;

	float totalTime = 0.0f;
	NameScene* nameScene = nullptr;
	Scene* scene = new Scene();
	scene->performInitialRender(*renderer);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();
		
		// Depth buffer
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			depthBuffer = !depthBuffer;
			renderer->SetDepthBufferState(depthBuffer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2)) {
			renderer->SetDepthFunctionTo(GL_EQUAL);
			depthState = "Equal";
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) {
			renderer->SetDepthFunctionTo(GL_ALWAYS);
			depthState = "Always";
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) {
			renderer->SetDepthFunctionTo(GL_LEQUAL);
			depthState = "Less-or-Equal";
		}

		// Alpha blending
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {
			alphaBlending = !alphaBlending;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {
			blendingMode = 0;
			blendingState = "Linear";
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			blendingMode = 1;
			blendingState = "Additive";
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F8)) {
			blendingMode = 2;
			blendingState = "Invert";
		}
		switch (blendingMode) {
		case 0:
			renderer->SetBlendToLinear();
			break;
		case 1:
			renderer->SetBlendToAdditive();
			break;
		case 2:
			renderer->SetBlendToInvert();
			break;
		}
		renderer->SetAlphaBlendingState(alphaBlending);

		if (objsDrawn) {
			scene->update(time);
		}
		renderer->Update(time);
		
		if (objsDrawn) {
			scene->render(*renderer);
		}
		renderer->Render();
		
		/*
		totalTime += time;
		
		for (Planet* planet : *planetList) {
			planet->update(time);
		}*/
		
		// Draw Render Info
		std::string alphaInfo = "Alpha: ";
		alphaInfo += alphaBlending ? "On [" + blendingState + "]" : "Off";
		std::string depthInfo = "Depth: ";
		depthInfo += depthBuffer ? "On [" + depthState + "]" : "Off";
		renderer->DrawString(alphaInfo, Vector2(10, 35));
		renderer->DrawString(depthInfo, Vector2(10, 10));

		// Movement keys
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.z += cos((yaw * PI) / 180) * speed;
			viewPosition.x -= sin((yaw * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition.x -= sin(((yaw - 90) * PI) / 180) * speed;
			viewPosition.z += cos(((yaw - 90) * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.z -= cos((yaw * PI) / 180) * speed;
			viewPosition.x += sin((yaw * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x += sin(((yaw - 90) * PI) / 180) * speed;
			viewPosition.z -= cos(((yaw - 90) * PI) / 180) * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			viewPosition.y += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			viewPosition.y -= speed;
		}

		// Rotation
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_T)) {
			mouseControls = !mouseControls;
		}
		if (mouseControls) {
			yaw += Window::GetMouse()->GetRelativePosition().x;
			pitch += Window::GetMouse()->GetRelativePosition().y;
			w->LockMouseToWindow(true);
			w->ShowOSPointer(false);
		} else {
			w->ShowOSPointer(true);
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			yaw -= rotationSpeed;
			if (yaw < 0) {
				yaw += 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			yaw += rotationSpeed;
			if (yaw > 360) {
				yaw -= 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {
			pitch += rotationSpeed;
			if (pitch > 360) {
				pitch-= 360;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
			pitch -= rotationSpeed;
			if (pitch < 0) {
				pitch += 360;
			}
		}
		renderer->SetViewMatrix(
			Matrix4::Rotation(pitch, Vector3(1, 0, 0)) *
			Matrix4::Rotation(yaw, Vector3(0, 1, 0)) *
			Matrix4::Translation(viewPosition)
		);

		// Toggle between name and planets
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
			
			renderer->DeleteAllRenderObjects();
			if (objsDrawn) {
				delete scene;
				nameScene = new NameScene();
				nameScene->performInitialRender(*renderer);
			} else {
				delete nameScene;
				scene = new Scene();
				scene->performInitialRender(*renderer);
			}
			objsDrawn = !objsDrawn;
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