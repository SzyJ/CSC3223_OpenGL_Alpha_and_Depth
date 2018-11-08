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
		}, false);

	renderer.AddRenderObject(new RenderObject(rasterLine));

	OGLMesh* rasterTri = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({
		Vector3(550, 400, 0),
		Vector3(750, 380, 0),
		Vector3(650, 300, 0)
		}, false);

	renderer.AddRenderObject(new RenderObject(rasterTri));
}

void Tutorial4(Renderer& renderer) {
	OGLMesh * tri = new OGLMesh();
	tri->SetVertexPositions({
		Vector3(-1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
		});
	tri->SetVertexColours({
		Vector4(1, 0, 0, 1),
		Vector4(0, 1, 0, 1),
		Vector4(0, 0, 1, 1)
		});
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			Matrix4 translate = Matrix4::Translation(
				Vector3((x + 1) * 130, (y + 1) * 120, 0));
			Matrix4 rotate = Matrix4::Rotation(
				((y * 5) + x) * 10, Vector3(0, 0, 1));
			Matrix4 scale = Matrix4::Scale(Vector3(50, 50, 50) / (1 + y));
			Matrix4 modelMat = translate * rotate * scale;
			renderer.AddRenderObject(new RenderObject(tri, modelMat));
		}
	}
}

void Tutorial5(Renderer & renderer) {
	OGLMesh * tri = new OGLMesh("Sphere.msh");
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for (int y = -4; y < 3; ++y) {
		for (int x = -4; x < 3; ++x) {
			float zAmount = rand() % 30;
			float scaleAmount = ((rand() % 3) + 1);

			Matrix4 translate = Matrix4::Translation(
				Vector3((x + 1) * 10, (y + 1) * 10, -50 - zAmount)
			);
			Matrix4 rotate = Matrix4::Rotation(
				((y * 5) + x) * 10, Vector3(0, 0, 1)
			);
			Matrix4 scale = Matrix4::Scale(
				Vector3(scaleAmount, scaleAmount, scaleAmount)
			);
			renderer.AddRenderObject(
				new RenderObject(tri, translate * rotate * scale)
			);
		}
	}
}

void Tutorial6(Renderer& renderer) {
	std::vector <Vector4> red = {
		Vector4(1, 0, 0, 1),
		Vector4(1, 0, 0, 1),
		Vector4(1, 0, 0, 1)
	};
	std::vector <Vector4> blue = {
		Vector4(0, 0, 1, 1),
		Vector4(0, 0, 1, 1),
		Vector4(0, 0, 1, 1)
	};
	std::vector <Vector3> verts = {
		Vector3(-1, -1, 0),
		Vector3(1, -1, 0),
		Vector3(0, 1, 0)
	};

	OGLMesh * redTri = new OGLMesh();
	redTri->SetVertexPositions(verts);
	redTri->SetVertexColours(red);
	redTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri->UploadToGPU();

	OGLMesh * blueTri = new OGLMesh();
	blueTri->SetVertexPositions(verts);
	blueTri->SetVertexColours(blue);
	blueTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri->UploadToGPU();

	Matrix4 redModelMat = Matrix4::Translation(Vector3(0, 0, -30)) * Matrix4::Scale(Vector3(5, 5, 5));
	Matrix4 blueModelMat = Matrix4::Translation(Vector3(0, 0, -70)) * Matrix4::Scale(Vector3(15, 15, 15));

	renderer.AddRenderObject(new RenderObject(redTri, redModelMat));
	renderer.AddRenderObject(new RenderObject(blueTri, blueModelMat));
}

void Tutorial7(Renderer& renderer) {
	std::vector<Vector3> verts = {
		Vector3(-1, -1, 0), Vector3(1, -1, 0), Vector3(0, 1, 0)
	};
	std::vector<Vector4> white = {
		Vector4(1, 1, 1, 1), Vector4(1, 1, 1, 1), Vector4(1, 1, 1, 1)
	};
	std::vector <Vector2> texCoords = {
		Vector2(0, 0), Vector2(10, 0), Vector2(5, 10)
	};

	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(white);
	tri->SetVertexTextureCoords(texCoords);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	Matrix4 modelMat =
		Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Rotation(45.0f, Vector3(1, 0, 0)) *
		Matrix4::Scale(Vector3(15, 15, 15));

	RenderObject* renderObj = new RenderObject(tri, modelMat);

	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");
	//renderer.EnableBilinearFiltering(*(OGLTexture*)newTex);
	renderObj->SetBaseTexture(newTex);
	renderer.EnableTextureRepeating(*(OGLTexture*)newTex, false, false);

	renderer.AddRenderObject(renderObj);
}

RenderObject* Tutorial13(Renderer& renderer) {
	OGLShader * lightingShader = new OGLShader("LightingVertex.glsl", "LightingFragment.glsl");

	// Simple demo case , load a cube with normals precalculated !
	OGLMesh* cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject* cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(lightingShader);

	TextureBase* tex = OGLTexture::RGBATextureFromFilename("doge.PNG");
	cubeObject->SetBaseTexture(tex);
	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(
		Vector3(0, 25, 0),
		Vector3(1.0f, 0.3f, 0.2f),
		200.0f
	);

	return cubeObject;
}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	//Tutorial2(*renderer);
	//Tutorial4(*renderer);
	//Tutorial5(*renderer);
	Tutorial6(*renderer);
	//Tutorial7(*renderer);
	//RenderObject* litCube = Tutorial13(*renderer);



	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 1000.0f, aspect, 45.0f);
	renderer->SetProjectionMatrix(proj);
	renderer->EnableDepthBuffer(true);

	const float speed = 0.1f;
	Vector3 viewPosition(0, 0, 0);

	float rotation = 0.0f;

	float pitch = 0;
	float yaw = 0;
	bool depthBuffer = true;
	bool alphaBlending = true;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		/* Tutorial 13 code
		rotation += time * 0.1f;
		litCube->SetTransform(
			Matrix4::Translation(Vector3(-25, 0, -70)) *
			Matrix4::Rotation(rotation, Vector3(1, 1, 1)) *
			Matrix4::Scale(Vector3(6, 6, 6))
		);*/

		renderer->Update(time);

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		renderer->Render();

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.z += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition.x += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.z -= speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x -= speed;
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
			yaw -= 0.1f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			yaw += 0.1f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {
			pitch += 0.1f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
			pitch -= 0.1f;
		}
		renderer->SetViewMatrix(
			Matrix4::Rotation(pitch, Vector3(1, 0, 0)) *
			Matrix4::Rotation(yaw, Vector3(0, 1, 0)) *
			Matrix4::Translation(viewPosition)
		);

		// Toggle depth buffer
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			depthBuffer = !depthBuffer;
			renderer->EnableDepthBuffer(depthBuffer);
		}


		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F11)) {
			renderer->WriteDepthBuffer("Depth.png");
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