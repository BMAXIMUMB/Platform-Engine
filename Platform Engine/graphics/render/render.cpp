// render.cpp

#include "render.h"

namespace PlatformEngine
{
	// Lines
	////////////////////////////////////////////////////////////////////////////////////
	void CRender::RenderLines(CVbo *vbo, CShader *shader, color4 color)
	{
		// enable shader program
		shader->Use();
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");
		GLuint cmul = shader->getUniformLocation("color_multiple");

		shader->setUniform(cmul, color);
		// enable arrays
		glEnableVertexAttribArray(vertexPos);
		// bind buffers
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);

		// draw
		glDrawArrays(GL_LINE_LOOP, 0, vbo->vertexCount);
		// disable arrays and shaders
		glDisableVertexAttribArray(vertexPos);
		glUseProgram(0);
	}

	void CRender::RenderLines(CVbo *vbo, CShader *shader, glm::mat4 mat, color4 color)
	{
		shader->Use();
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");
		GLuint cmul = shader->getUniformLocation("color_multiple");
		GLuint matrix = shader->getUniformLocation("matrix");

		shader->setUniform(matrix, mat);
		shader->setUniform(cmul, color);
		// enable arrays
		glEnableVertexAttribArray(vertexPos);
		// bind buffers
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);

		// draw
		glDrawArrays(GL_LINE_LOOP, 0, vbo->vertexCount);
		// disable arrays and shaders
		glDisableVertexAttribArray(vertexPos);
		glUseProgram(0);
	}

	// Triangles
	////////////////////////////////////////////////////////////////////////////////////
	void CRender::RenderTriangles(CVbo *vbo, CShader *shader)
	{
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");

		shader->Use();
		glEnableVertexAttribArray(vertexPos);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);
		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);
		glDisableVertexAttribArray(vertexPos);
	}

	void CRender::RenderTriangles(CVbo *vbo, CShader *shader, color4 color)
	{
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");
		GLuint cmul = shader->getUniformLocation("color_multiple");

		shader->Use();
		shader->setUniform(cmul, color);
		glEnableVertexAttribArray(vertexPos);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);
		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);
		glDisableVertexAttribArray(vertexPos);
	}

	void CRender::RenderTriangles(CVbo *vbo, CShader *shader, unsigned int texid, glm::mat4 mat)
	{
		shader->Use();
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");
		GLuint vertexUV = shader->getAttribLocation("vertexUV");
		GLuint matrix = shader->getUniformLocation("matrix");

		// push matrix
		shader->setUniform(matrix, mat);
		glBindTexture(GL_TEXTURE_2D, texid);
		// enable arrays
		glEnableVertexAttribArray(vertexPos);
		glEnableVertexAttribArray(vertexUV);
		// bind buffers
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->textureCoordID);
		glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);
		// draw
		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);
		// disable arrays and shaders
		glDisableVertexAttribArray(vertexPos);
		glDisableVertexAttribArray(vertexUV);
		glUseProgram(0);
	}

	void CRender::RenderTriangles(CVbo *vbo, CShader *shader, unsigned int texid, glm::mat4 mat, color4 cmultiple)
	{
		shader->Use();
		GLuint vertexPos = shader->getAttribLocation("vertexPosition");
		GLuint vertexUV = shader->getAttribLocation("vertexUV");
		GLuint matrix = shader->getUniformLocation("matrix");
		GLuint cmul = shader->getUniformLocation("color_multiple");

		// push matrix
		shader->setUniform(matrix, mat);
		// push color
		shader->setUniform(cmul, cmultiple);
		glBindTexture(GL_TEXTURE_2D, texid);
		glEnableVertexAttribArray(vertexPos);
		glEnableVertexAttribArray(vertexUV);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->verticesID);
		glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo->textureCoordID);
		glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, NULL, (void*)NULL);

		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);
		glDisableVertexAttribArray(vertexPos);
		glDisableVertexAttribArray(vertexUV);
		glUseProgram(0);
	}
};