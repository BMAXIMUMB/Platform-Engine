// vbo.cpp

#include <string>

#include "../../platform_engine.h"
#include "../sprite/texture/texture.h"

#include "vbo.h"

namespace PlatformEngine
{
	CVbo::CVbo()
	{
		// ������� ����� �� ����� �������� �������
		glGenBuffersARB(1, &verticesID);
		glGenBuffersARB(1, &textureCoordID);
	}

	CVbo::~CVbo()
	{
		// ������� ��� ������
		glDeleteBuffersARB(1, &verticesID);
		glDeleteBuffersARB(1, &textureCoordID);
	}

	void CVbo::Build(PlatformEngine::CTexCoord2f * Texcoord)
	{
		// ��������� �����
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, verticesID);					// ������ ������
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertexCount * 2 * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, vertexCount * 2 * sizeof(float), vertex);			// ��������� ������

		// ������������ �����
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, textureCoordID);					// ������ ������
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertexCount * 2 * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, vertexCount * 2 * sizeof(float), Texcoord);			// ��������� ������
	}
};