// vbo.h

#ifndef _VBO_H_
#define _VBO_H_

#include "../vertex/vertex.h"

namespace PlatformEngine
{
	class CVbo
	{
	public:
		CVertex2f * vertex;											// Вершины

		unsigned int verticesID;									// ID вершинного буфера
		unsigned int textureCoordID;								// ID координатного буфера
		int vertexCount;											// Кол-во вершин

		CVbo();
		~CVbo();

		void Build(PlatformEngine::CTexCoord2f * Texcoord);		// Сборка буферов
	};
};

#endif //_VBO_H_