//resource.cpp

#include "resource.h"
#include "../graphics/sprite/sprite.h"
#include "../font/font.h"

namespace PlatformEngine
{
	CResourceManager::CResourceManager()
	{

	}

	CResourceManager::~CResourceManager()
	{

	}

	void CResourceManager::AddResourceToList(ÑResource *Res, int resource_type, std::string name)
	{
		Res->name = name;
		Res->type = resource_type;

		resourcesList[name] = Res;
	}

	bool CResourceManager::Delete(std::string name)
	{
		resMapIter i;
		i = resourcesList.find(name);

		if(i != resourcesList.end())
		{
			delete i->second;
			resourcesList.erase(name);
			return true;
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////

	CSprite* CSpriteManager::Load(const char *path, std::string name)
	{
		CSprite *tempSprite = Get(name);

		if(tempSprite == nullptr)
		{
			tempSprite = new CSprite;
			tempSprite->LoadFromFile(path);
			AddResourceToList(tempSprite, RESOURCE_TYPE_SPRITE, name);
			tempSprite->path = path;
		}

		return tempSprite;
	}

	CSprite* CSpriteManager::Get(std::string name)
	{
		resMapIter i;
		i = resourcesList.find(name);

		if(i != resourcesList.end()) return (CSprite*)i->second;
		else return nullptr;
	}

	//////////////////////////////////////////////////////////////////////////////////

	CFont* CFontManager::Load(char *path, std::string name)
	{
		CFont *tempFont = Get(name);

		if(tempFont == nullptr)
		{
			CFont *tempFont = new CFont;
			tempFont->Load(path);
			AddResourceToList(tempFont, RESOURCE_TYPE_FONT, name);
			tempFont->path = path;
		}

		return tempFont;
	}

	CFont* CFontManager::Get(std::string name)
	{
		resMapIter i;
		i = resourcesList.find(name);

		if(i != resourcesList.end()) return (CFont*)i->second;
		else return nullptr;
	}
};