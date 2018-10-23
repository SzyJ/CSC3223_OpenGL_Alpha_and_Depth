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

void generateStarfield(Renderer& renderer) {
	OGLMesh* stars = new OGLMesh();
	vector<Vector3>* starPos = new vector<Vector3>;
	vector<Vector4>* starCol = new vector<Vector4>;
	starPos->reserve(5000);

	for (int i = 0; i < 5000; i++) {
		starPos->emplace_back(rand() % 780, rand() % 600, 0);
		starCol->emplace_back(1, 1, 1, (i / 5000.0f));
	}
	
	stars->SetVertexPositions(*starPos);
	stars->SetVertexColours(*starCol);

	stars->SetPrimitiveType(GeometryPrimitive::Points);
	stars->UploadToGPU();

	renderer.AddRenderObject(new RenderObject(stars));
	
}

void generateSpaceship(Renderer& renderer) {
	int xPos = 390;
	int yPos = 300;

	int shipWidth = 40;
	int shipWingLength = 15;
	int shipLength = 50;

	Vector4 wingColour = Vector4(0.808f, 0.286f, 1, 1);
	Vector4 frontColour = Vector4(1, 0.0f, 0.914f, 1);
	Vector4 backColour = Vector4(0.906f, 0.22f, 1, 1);

	OGLMesh* ship = new OGLMesh();
	
	ship->SetVertexPositions({
		Vector3(xPos - (shipWidth / 2), yPos, 0),
		Vector3(xPos, yPos - shipLength, 0),
		Vector3(xPos, yPos - shipWingLength, 0),
		Vector3(xPos + (shipWidth /2), yPos, 0)
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

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}
	
	Renderer*	renderer = new Renderer(*w);

	generateStarfield(*renderer);
	generateSpaceship(*renderer);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		renderer->Update(time);

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		renderer->Render();

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