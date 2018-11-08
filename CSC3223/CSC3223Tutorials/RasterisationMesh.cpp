#include "RasterisationMesh.h"

using namespace NCL;
using namespace CSC3223;


RasterisationMesh::RasterisationMesh() {}

RasterisationMesh::~RasterisationMesh() {}

RasterisationMesh* RasterisationMesh::CreateLineFromPoints(const std::vector<Vector3>& vertices, bool bresenham) {
	RasterisationMesh* line = new RasterisationMesh();

	for (int i = 0; i < vertices.size(); i += 2) {
		if (bresenham) {
			line->RasterBresenhamLine(vertices[i], vertices[i + 1]);
		}
		else {
			line->RasterBasicLine(vertices[i], vertices[i + 1]);
		}
	}

	line->SetPrimitiveType(GeometryPrimitive::Points);
	line->UploadToGPU();

	return line;
}

void RasterisationMesh::RasterBasicLine(const Vector3& v0, const Vector3& v1) {
	float lineLength = (v0 - v1).Length();
	int numPixels = (int)lineLength;

	float lerpAmount = 1.0f / (numPixels - 1);
	float t = 0.0f;

	for (int i = 0; i < numPixels; i++) {
		positions.emplace_back(Maths::Lerp<Vector3>(v0, v1, t));
		t += lerpAmount;
	}
}

void RasterisationMesh::RasterBresenhamLine(const Vector3& v0, const Vector3& v1) {
	Vector3 dir = v1 - v0;
	Vector3 currentPos = v0;
	int scanRange = 0;
	float slope = 0.0f;
	float* periodAxis = nullptr;
	float* scanAxis = nullptr;
	int scanDelta = 0;
	int targetDelta = 0;

	float absSlope = abs(slope);
	float error = 0.0f;

	if (abs(dir.y) > abs(dir.y)) {
		slope = (dir.x / dir.y);
		scanRange = (int)abs(dir.y);
		periodAxis = &currentPos.x;
		scanAxis = &currentPos.y;
		scanDelta = (dir.y < 0.0f) ? -1 : 1;
		targetDelta = (dir.x < 0.0f) ? -1 : 1;
	}
	else {
		slope = (dir.y / dir.x);
		scanRange = (int)abs(dir.x);
		periodAxis = &currentPos.y;
		scanAxis = &currentPos.x;
		scanDelta = (dir.x < 0.0f) ? -1 : 1;
		targetDelta = (dir.y < 0.0f) ? -1 : 1;
	}

	for (int i = 0; i < scanRange; i++) {
		positions.emplace_back(currentPos);

		error += absSlope;

		if (error > 0.5f) {
			error -= 1.0f;
			(*periodAxis) += targetDelta;
		}

		(*scanAxis) += scanDelta;
	}
}

RasterisationMesh* RasterisationMesh::CreateTriangleFromPoints(const std::vector<Vector3>& inVerts, int type) {
	RasterisationMesh* tri = new RasterisationMesh();

	for (size_t i = 0; i < inVerts.size() - 2; i += 3) {
		if (type) {
			tri->RasterSpanTriangle(inVerts[i], inVerts[i + 1], inVerts[i + 2]);
		}
		else {
			tri->RasterLineEquasionTriangle(inVerts[i], inVerts[i + 1], inVerts[i + 2]);
		}
	}

	tri->SetPrimitiveType(GeometryPrimitive::Points);
	tri->UploadToGPU();

	return tri;
}

void RasterisationMesh::RasterLineEquasionTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2) {
	Vector2 topLeft, bottomRight;

	Maths::ScreenBoxOfTri(p0, p1, p2, topLeft, bottomRight);

	Vector3 linev0v1 = Vector3::Cross(Vector3(p0.x, p0.y, 1), Vector3(p1.x, p1.y, 1));
	Vector3 linev1v2 = Vector3::Cross(Vector3(p1.x, p1.y, 1), Vector3(p2.x, p2.y, 1));
	Vector3 linev2v0 = Vector3::Cross(Vector3(p2.x, p2.y, 1), Vector3(p0.x, p0.y, 1));

	for (int y = (int)topLeft.y; y < bottomRight.y; y++) {
		for (int x = (int)topLeft.x; x < bottomRight.x; x++) {
			Vector3 screenPos((float)x, (float)y, 1.0f);

			float line01 = Vector3::Dot(linev0v1, screenPos);
			float line12 = Vector3::Dot(linev1v2, screenPos);
			float line20 = Vector3::Dot(linev2v0, screenPos);

			if (line01 <= 0 && line12 <= 0 && line20 <= 0) {
				positions.emplace_back(screenPos);
			}
		}
	}
}

void RasterisationMesh::RasterSpanTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
	const Vector3* vertices[3] = { &v0, &v1, &v2 };

	if (vertices[1]->y < vertices[0]->y) {
		std::swap(vertices[1], vertices[0]);
	}

	if (vertices[2]->y < vertices[0]->y) {
		std::swap(vertices[2], vertices[0]);
	}

	if (vertices[2]->y < vertices[1]->y) {
		std::swap(vertices[2], vertices[1]);
	}

	Vector3 longDir = *vertices[2] - *vertices[0];
	Vector3 longDelta = longDir / longDir.y;
	Vector3 shortDir = *vertices[1] - *vertices[0];
	Vector3 shortDelta = shortDir / shortDir.y;

	float longX = vertices[0]->x;
	float shortX = vertices[0]->x;

	for (int y = vertices[0]->y; y < vertices[1]->y; y++) {
		int startX = std::min(longX, shortX);
		int endX = std::max(longX, shortX);

		for (int x = startX; x < endX; x++) {
			positions.emplace_back(Vector3(x, y, 1));
		}

		longX += longDelta.x;
		shortX += shortDelta.x;
	}
}