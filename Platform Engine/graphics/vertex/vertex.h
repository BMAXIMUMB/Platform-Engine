// vertex.h

#ifndef _VERTEX_H_
#define _VERTEX_H_

namespace PlatformEngine
{
	// Классы вершин

	class CVertex2f
	{
	public:
		float x;
		float y;
	};
			
	class CVertex3f	
	{
	public:
		float x;
		float y;
		float z;
	};

	class CTexCoord2f
	{
	public:
		float u;
		float v;
	};
}

#endif //_VERTEX_H_