#pragma once
#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLMesh.h"

namespace NCL {
	namespace CSC3223 {
		class RasterisationMesh : public Rendering::OGLMesh {
		public:
			RasterisationMesh();
			~RasterisationMesh();

			static RasterisationMesh* CreateTriangleFromPoints(const std::vector<Vector3>& vertices, int type = 1);
			static RasterisationMesh* CreateLineFromPoints(const std::vector<Vector3>& vertices, bool bresenham = false);

		protected:
			void RasterLineEquasionTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2);
			void RasterSpanTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2);
			void RasterBasicLine(const Vector3& p0, const Vector3& p1);
			void RasterBresenhamLine(const Vector3& p0, const Vector3& p1);
		};
	}
}