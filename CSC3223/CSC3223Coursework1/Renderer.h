#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {

		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

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

			// Depth Buffer States
			void SetDepthBufferState(bool state);
			void SetDepthFunctionTo(GLenum functionType);

			// Alpha States
			void SetAlphaBlendingState(bool state);
			void SetBlendToLinear();
			void SetBlendToAdditive();
			void SetBlendToInvert();
		protected:
			void RenderNode(RenderObject* root);
	
			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;
		};
	}
}

