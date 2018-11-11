#include "GPUName.h"
#include "RasterisationMesh.h"

GPUName::GPUName() {
	setUpLetterMeshes();
}

GPUName::~GPUName() {
	delete s;
	delete z;
	delete y;
	delete m;
	delete o;
	delete n;
}

void GPUName::setUpLetterMeshes() {
	const float HALF_HEIGHT = LETTER_HEIGHT / 2.0f;
	const float QUART_HEIGHT = LETTER_HEIGHT / 4.0f;
	const float HALF_WIDTH = LETTER_WIDTH / 2.0f;

	s = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
		{
		Vector3(HALF_WIDTH  , QUART_HEIGHT  , 0),
		Vector3(0           , HALF_HEIGHT   , 0),
		Vector3(-HALF_WIDTH , QUART_HEIGHT  , 0),
		Vector3(HALF_WIDTH  , -QUART_HEIGHT , 0),
		Vector3(0           , HALF_HEIGHT   , 0),
		Vector3(-HALF_WIDTH , -QUART_HEIGHT , 0)
		}
	, useBresenham);
	s->UploadToGPU();
	
	z = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
		{
		Vector3(-HALF_WIDTH , HALF_HEIGHT  , 0),
		Vector3(HALF_WIDTH  , HALF_HEIGHT  , 0),
		Vector3(-HALF_WIDTH , -HALF_HEIGHT , 0),
		Vector3(HALF_WIDTH  , -HALF_HEIGHT , 0)
		}
	, useBresenham);
	z->UploadToGPU();
	
	y = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
		{
		Vector3(-HALF_WIDTH , HALF_HEIGHT  , 0),
		Vector3(0           , 0            , 0),
		Vector3(HALF_WIDTH  , HALF_HEIGHT  , 0),
		Vector3(0           , 0            , 0),
		Vector3(0           , -HALF_HEIGHT , 0)
		}
	, useBresenham);
	y->UploadToGPU();
	
	m = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
		{
		Vector3(-HALF_WIDTH , -HALF_HEIGHT , 0),
		Vector3(-HALF_WIDTH , HALF_HEIGHT  , 0),
		Vector3(0           , 0            , 0),
		Vector3(HALF_WIDTH  , HALF_HEIGHT  , 0),
		Vector3(HALF_WIDTH  , -HALF_HEIGHT  , 0)
		}
	, useBresenham);
	m->UploadToGPU();
	
	o = new OGLMesh();
	o->UploadToGPU();
	
	n = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
		{
		Vector3(-HALF_WIDTH , -HALF_HEIGHT , 0),
		Vector3(-HALF_WIDTH , HALF_HEIGHT  , 0),
		Vector3(HALF_WIDTH  , -HALF_HEIGHT , 0),
		Vector3(HALF_WIDTH  , HALF_HEIGHT  , 0)
		}
	, useBresenham);
	n->UploadToGPU();
}

OGLMesh* GPUName::get_s_mesh() {
	return s;
}
OGLMesh* GPUName::get_z_mesh() {
	return z;
}
OGLMesh* GPUName::get_y_mesh() {
	return y;
}
OGLMesh* GPUName::get_m_mesh() {
	return m;
}
OGLMesh* GPUName::get_o_mesh() {
	return o;
}
OGLMesh* GPUName::get_n_mesh() {
	return n;
}