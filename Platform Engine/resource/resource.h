// resource.h

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "../platform_engine.h"
#include <map>

#define RESOURCE_TYPE_SPRITE			(0x1)
#define RESOURCE_TYPE_FONT				(0x2)

namespace PlatformEngine
{
	class CSprite;
	class CFont;

	class ÑResource
	{
		friend class CResourceManager;
		friend class CSpriteManager;
		friend class CFontManager;

	private:
		std::string name;
		unsigned int type;
		const char *path;
	};

	typedef std::map<std::string, ÑResource*> resourceMap;
	typedef resourceMap::const_iterator resMapIter;

	class CResourceManager
	{
	protected:
		resourceMap resourcesList;		// Õðàíèëèùå ðåñóðñîâ

		void AddResourceToList(ÑResource *Res, int resource_type, std::string name);

	public:
		PLATFORMENGINE_API	CResourceManager();
		PLATFORMENGINE_API	~CResourceManager();

		PLATFORMENGINE_API  bool Delete(std::string name);
	};

	class CSpriteManager :public CResourceManager
	{
	public:
		PLATFORMENGINE_API	CSprite* Load(const char *path, std::string name);
		PLATFORMENGINE_API	CSprite* Get(std::string name);
	};

	class CFontManager :public CResourceManager
	{
	public:
		PLATFORMENGINE_API	CFont* Load(char *path, std::string name);
		PLATFORMENGINE_API	CFont* Get(std::string name);
	};
};

#endif /*_RESOURCE_H_*/