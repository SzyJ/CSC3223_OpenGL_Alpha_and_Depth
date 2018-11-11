#include "RandomMatrixUtils.h"

Matrix4 RandomMatrixUtils::randomDisplacementMatrix(const int sceneSize) {
	Matrix4 translate = Matrix4::Translation(
		Vector3(
			(rand() % (2 * sceneSize)) - sceneSize,
			(rand() % (2 * sceneSize)) - sceneSize,
			(rand() % (2 * sceneSize)) - sceneSize
		)
	);

	return translate;
}

Matrix4 RandomMatrixUtils::randomScaleMatrix(const unsigned minScale, const unsigned scaleVarience) {
	float scaleAmount = rand() % scaleVarience;
	scaleAmount += minScale;

	Matrix4 scale = Matrix4::Scale(
		Vector3(scaleAmount, scaleAmount, scaleAmount)
	);

	return scale;
}