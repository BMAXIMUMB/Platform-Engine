// object manager.h

#ifndef ___object_manager_h___
#define ___object_manager_h___

#include <vector>
#include "../object.h"
#include "../../world/camera/camera.h"

namespace PlatformEngine
{
	class ObjectManager
	{
		friend World;
	private:
		std::vector< PlatformEngine::Object*> DrawObject;				// ��� �������� ��� ������� �� ���������
		std::vector< PlatformEngine::Object*> ColObject;				// �������, ����������� �� ������������
	public:
		ObjectManager();
		~ObjectManager();
		void Draw(Application *app, Camera *Cam);						// ���������� ��� �������
		void Update(float dTime);										// �������� ��� ������� � ������
		//void CollisionUpdate(void);										// �������� ������������
		void ObjectAdd(Object *Object);
		void ObjectDelete(Object *Object);
		void Clear(void);												// �������� ������ ��������
	};
};

#endif //___oject_manager_h___