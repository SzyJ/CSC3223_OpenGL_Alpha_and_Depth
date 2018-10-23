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

#include "RasterisationMesh.h"
#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

void bresenhams(Renderer& renderer) {
	OGLMesh* points = new OGLMesh();
	points->SetVertexPositions({
		Vector3(50, 50, 0),
		Vector3(200, 100, 0)
		});
	points->SetPrimitiveType(GeometryPrimitive::Lines);
	points->UploadToGPU();

	renderer.AddRenderObject(new RenderObject(points));
}

void Tutorial2(Renderer& renderer) {
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
		}, true);

	renderer.AddRenderObject(new RenderObject(rasterLine));

	OGLMesh* rasterTri = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({
		Vector3(550, 400, 0),
		Vector3(750, 380, 0),
		Vector3(650, 300, 0)
		}, true);

	renderer.AddRenderObject(new RenderObject(rasterTri));
}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	Tutorial2(*renderer);
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