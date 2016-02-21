// gui_manager.cpp

#include "gui_manager.h"


namespace Gui
{
	CGuiManager::CGuiManager(PE::CApplication *App)
	{
		this->app = App;

		clickedElement = nullptr;
		_OnElementClick = nullptr;
		_OnActionStop = nullptr;
	}

	CGuiManager::~CGuiManager()
	{

	}

	void CGuiManager::SetActionStopCallback(Gui::_OnActionStop _OnActionStop)
	{
		this->_OnActionStop = _OnActionStop;
	}

	void CGuiManager::SetElementClickCallback(::_OnElementClick func)
	{
		this->_OnElementClick = func;
	}

	void CGuiManager::SetElementReleaseCallback(::_OnElementRelease func)
	{
		this->_OnElementRelease = func;
	}

	void CGuiManager::ElementAddToList(CGuiElement *Element)
	{
		elementList.push_back(Element);
	}

	bool CGuiManager::ElementDeleteToList(CGuiElement *Element)
	{
		for(auto it = elementList.begin(); it != elementList.end(); it++)
		{
			if(*it == Element)
			{
				elementList.erase(it);
				return true;
			}
		}
		return false;
	}

	void CGuiManager::Show(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr) gelem->Show();
	}

	void CGuiManager::Hide(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr) gelem->Hide();
	}

	void CGuiManager::DrawElements()
	{
		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			if(elementList[i]->IsShowed())
			{
				elementList[i]->Render();
			}
		}
	}

	CText* CGuiManager::CreateText(TextSettings ts)
	{
		CText *t = new CText;
		t->Create(this, ts);
		return t;
	}

	bool CGuiManager::DestroyText(CText* text)
	{
		if(ElementDeleteToList(text))
		{
			delete text;
			return true;
		}
		return false;
	}

	bool CGuiManager::DestroyText(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr)
		{
			delete gelem;
			return true;
		}
		return false;
	}

	CImage* CGuiManager::CreateImage(GuiElementSettings ges)
	{
		CImage *img = new CImage;
		img->Create(this, ges);
		return img;
	}

	CButton* CGuiManager::CreateButton(GuiElementSettings ges)
	{
		CButton *b = new CButton;
		b->Create(this, ges);
		return b;
	}

	CBox* CGuiManager::CreateBox(GuiElementSettings ges)
	{
		CBox *b = new CBox;
		b->Create(this, ges);
		return b;
	}

	bool CGuiManager::DestroyBox(CBox* box)
	{
		if(ElementDeleteToList(box))
		{
			delete box;
			return true;
		}
		return false;
	}

	bool CGuiManager::DestroyBox(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr)
		{
			delete gelem;
			return true;
		}
		return false;
	}

	CGuiElement* CGuiManager::FindElement(std::string name)
	{
		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			if(name == elementList[i]->GetName()) return elementList[i];
		}
		return nullptr;
	}

	bool CGuiManager::DestroyImage(CImage* img)
	{
		if(ElementDeleteToList(img))
		{
			delete img;
			return true;
		}
		return false;
	}

	bool CGuiManager::DestroyImage(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr)
		{
			delete gelem;
			return true;
		}
		return false;
	}

	bool CGuiManager::DestroyButton(CButton* button)
	{
		if(ElementDeleteToList(button))
		{
			delete button;
			return true;
		}
		return false;
	}

	bool CGuiManager::DestroyButton(std::string name)
	{
		CGuiElement *gelem = FindElement(name);
		if(gelem != nullptr)
		{
			delete gelem;
			return true;
		}
		return false;
	}

	void CGuiManager::CheckElementCick(int button, int mposx, int mposy)
	{
		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			if(elementList[i]->IsShowed())
			{
				float pos[2];
				float size[2];
				int ws[2];
				elementList[i]->GetPosition(pos[0], pos[1]);
				elementList[i]->GetSize(size[0], size[1]);
				app->GetWindowSize(ws[0], ws[1]);
				pos[1] = (pos[1] - ws[1])*-1;
				/*if(mposx >= pos[0] - size[0] / 2 && mposx <= pos[0] + size[0] / 2 &&
					mposy >= pos[1] - size[1] / 2 && mposy <= pos[1] + size[1] / 2)*/
				if(POINT_IN_SQUARE(pos[0] - size[0] / 2, pos[0] + size[0] / 2, pos[1] - size[1] / 2, pos[1] + size[1] / 2, mposx, mposy))
				{
					OnElementClick(button, elementList[i]);
				}
			}
		}
	}

	void CGuiManager::CheckElementRelease(int button, int mposx, int mposy)
	{
		if(clickedElement != nullptr) OnElementRelease(clickedElement);
	}

	void CGuiManager::UpdateMoving(int i, float dt)
	{
		if(elementList[i]->moving)
		{
			elementList[i]->posX += elementList[i]->posStep[0] * dt;
			elementList[i]->posY += elementList[i]->posStep[1] * dt;
			elementList[i]->mcurtime += dt;
			if(elementList[i]->mcurtime >= elementList[i]->mtime)
			{
				elementList[i]->moving = false;
				elementList[i]->posX = elementList[i]->gpos[0];
				elementList[i]->posY = elementList[i]->gpos[1];

				elementList[i]->posStep[0] = 0, elementList[i]->posStep[1] = 0;

				if(_OnActionStop != nullptr) _OnActionStop(elementList[i], GUI_ACTION_TYPE_MOVE);
			}
		}
	}

	void CGuiManager::UpdateAlpha(int i, float dt)
	{
		if(elementList[i]->alphaSset)
		{
			elementList[i]->color.a += elementList[i]->alphaStep*dt;
			elementList[i]->acurtime += dt;
			if(elementList[i]->acurtime >= elementList[i]->atime)
			{
				elementList[i]->color.a = elementList[i]->galpha;
				elementList[i]->alphaSset = false;
				elementList[i]->galpha = 0.0f;
				elementList[i]->alphaStep = 0.0f;
				elementList[i]->acurtime = 0.0f;
				elementList[i]->atime = 0.0f;

				if(_OnActionStop != nullptr) _OnActionStop(elementList[i], GUI_ACTION_TYPE_ALPHA);
			}
		}
	}

	void CGuiManager::UpdateScaling(int i, float dt)
	{
		if(elementList[i]->scaling)
		{
			elementList[i]->sizeX += elementList[i]->scaleStep[0]*dt;
			elementList[i]->sizeY += elementList[i]->scaleStep[1]*dt;
			elementList[i]->scurtime += dt;
			if(elementList[i]->scurtime >= elementList[i]->stime)
			{
				elementList[i]->scaling = false;
				elementList[i]->sizeX = elementList[i]->gscale[0];
				elementList[i]->sizeY = elementList[i]->gscale[1];

				if(_OnActionStop != nullptr) _OnActionStop(elementList[i], GUI_ACTION_TYPE_SCALE);
			}
		}
	}

	void CGuiManager::Update(float dt)
	{
		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			UpdateAlpha(i, dt);
			UpdateMoving(i, dt);
			UpdateScaling(i, dt);
		}
	}

	//CALLBACKS
	void CGuiManager::OnElementClick(int button, CGuiElement* Element)
	{
		Element->clicked = true;
		Element->clickedKey = button;
		clickedElement = Element;
		if(_OnElementClick != nullptr) _OnElementClick(button, Element);
	}

	void CGuiManager::OnElementRelease(CGuiElement* Element)
	{
		if(_OnElementRelease != nullptr) _OnElementRelease(Element);
		Element->clicked = false;
		clickedElement = nullptr;
	}
};