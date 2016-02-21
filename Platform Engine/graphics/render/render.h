// render.h

#ifndef _RENDER_H_
#define _RENDER_H_

#include "..\shader\shader.h"
#include "..\sprite\sprite.h"
#include "..\vbo\vbo.h"

namespace PlatformEngine
{
	// Render class
	class CRender
	{
	public:
		// primitives
		void RenderLines(CVbo *vbo, CShader *shader, color4 color);
		void RenderLines(CVbo *vbo, CShader *shader, glm::mat4 mat, color4 color);

		//
		void RenderTriangles(CVbo *vbo, CShader *shader);
		void RenderTriangles(CVbo *vbo, CShader *shader, color4 color);
		void RenderTriangles(CVbo *vbo, CShader *shader, unsigned int texid, glm::mat4 mat);
		void RenderTriangles(CVbo *vbo, CShader *shader, unsigned int texid, glm::mat4 mat, color4 cmul);
	};
};

#endif /*_RENDER_H_*/