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


int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

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

		// Alpha blendingsa
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
		}
		w->ShowOSPointer(!mouseControls);
		w->LockMouseToWindow(mouseControls);

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
				scene = nullptr;
				nameScene = new NameScene();
				nameScene->performInitialRender(*renderer);
			} else {
				delete nameScene;
				nameScene = nullptr;
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