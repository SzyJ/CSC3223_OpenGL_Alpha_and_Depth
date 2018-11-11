#include "NameScene.h"

NameScene::NameScene() {
	float letterCounter = -2.5f;
	sObject = new RenderObject(MESHES.get_s_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
	letterCounter += 1.0f;
	zObject = new RenderObject(MESHES.get_z_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
	letterCounter += 1.0f;
	yObject = new RenderObject(MESHES.get_y_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
	letterCounter += 1.0f;
	mObject = new RenderObject(MESHES.get_m_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
	letterCounter += 1.0f;
	oObject = new RenderObject(MESHES.get_o_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
	letterCounter += 1.0f;
	nObject = new RenderObject(MESHES.get_n_mesh(), Matrix4::Translation(Vector3(letterCounter * LETTER_SPACING, 0, 0)));
}

void NameScene::performInitialRender(Renderer& renderer) {
	renderer.AddRenderObject(sObject);
	renderer.AddRenderObject(zObject);
	renderer.AddRenderObject(yObject);
	renderer.AddRenderObject(mObject);
	renderer.AddRenderObject(oObject);
	renderer.AddRenderObject(nObject);
}