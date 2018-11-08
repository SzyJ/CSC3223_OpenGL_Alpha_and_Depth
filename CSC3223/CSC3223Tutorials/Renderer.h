#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {
		struct Light {
			Vector3 position;
			float radius;
			Vector3 colour;
		};

		class Renderer : public OGLRenderer {
		public:
			Renderer(Window& w);
			~Renderer();

			void EnableDepthBuffer(bool state);
			void WriteDepthBuffer(const string& filepath) const;

			void EnableBilinearFiltering(OGLTexture& t);
			void EnableMipMapFiltering(OGLTexture& t);
			void EnableTextureRepeating(OGLTexture& t, bool uRepeat, bool vRepeat);


			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}

			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}

			void SetLightProperties(Vector3 pos, Vector3 colour, float radius);

		protected:
			void RenderNode(RenderObject* root);

			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;

			Light activeLight;
			void ApplyLightToShader(const Light& light, const OGLShader* shader);

			GameTimer frameTimer;
		};
	}
}