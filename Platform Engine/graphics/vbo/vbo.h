// vbo.h

#ifndef _VBO_H_
#define _VBO_H_

#include "../vertex/vertex.h"

namespace PlatformEngine
{
	class CVbo
	{
	public:
		CVertex2f * vertex;											// �������

		unsigned int verticesID;									// ID ���������� ������
		unsigned int textureCoordID;								// ID ������������� ������
		int vertexCount;											// ���-�� ������

		CVbo();
		~CVbo();

		void Build(PlatformEngine::CTexCoord2f * Texcoord);		// ������ �������
	};
};

#endif //_VBO_H_