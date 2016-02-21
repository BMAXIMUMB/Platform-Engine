// sprite.cpp

#include "sprite.h"
#include "../../application/application.h"
#include <stdlib.h>
#include "../render/render.h"

extern void logprintf(std::string str);

namespace PlatformEngine
{
	CSprite::CSprite()
	{
		texture = new PlatformEngine::CTextureImage;
		vbo = new PlatformEngine::CVbo;
	}

	CSprite::~CSprite()
	{
		delete texCoord;
		delete vbo;
	}

	bool CSprite::LoadFromFile(const char * path)
	{
		PlatformEngine::CFile File;

		if(!File.Open(path))
		{
			logprintf("���������� ������� ����: " + (std::string)path);
			return false;
		}

		// ��������� ���������� ������
		vbo->vertexCount = File.GetInt("spr_info", "v_count");
		if(vbo->vertexCount == 0) return false;

		texCoord = new PlatformEngine::CTexCoord2f[vbo->vertexCount];
		vbo->vertex = new PlatformEngine::CVertex2f[vbo->vertexCount];

		char buff[10];

		// ��������� ������ � ��������
		for(int i = 0; i < vbo->vertexCount; i++)
		{
			// ������ ���������� � ���������� ����������� � ��������� ������
			sprintf(buff, "vt%du", i+1);										// ����������� ������ ��� ������
			texCoord[i].u = File.GetFloat("texcoord", buff);					// ���������� ������ � ���������� �������
			sprintf(buff, "vt%dv", i+1);
			texCoord[i].v = File.GetFloat("texcoord", buff);

			// ��������� ��������� ����� �������
			sprintf(buff, "v%dx", i + 1);
			vbo->vertex[i].x = File.GetFloat("vertex", buff);
			sprintf(buff, "v%dy", i + 1);
			vbo->vertex[i].y = File.GetFloat("vertex",  buff);
		}

		// ������, ��� �������� ��������
		std::string str_path = File.GetString("spr_info", "texpath");
		// ������ ��
		texture->LoadFromFileTGA(str_path.c_str());

		// �������� ����� 
		vbo->Build(texCoord);
		return true;
	}

	void CSprite::Draw(PlatformEngine::CApplication *app, SpriteDrawSettings sds)
	{
		// ��������� �������
#pragma warning(disable:4244)

		// ������ ������� ����
		int wsize[2];
		app->GetWindowSize(wsize[0], wsize[1]);
		float objsize[2] = {sds.sizeX, sds.sizeY};
		float objpos[2] = {sds.posX, sds.posY};

		// ������� ��� ���������� ���������
		// ������ ����� �� ��������)
		int px = (int)objpos[0] + 0.5;
		int py = (int)objpos[1] + 0.5;

		objpos[0] = px;
		objpos[1] = py;


		// ������ ������� ������� � ������� �����������
		float wndpos[2];
		float wwd[2] = {(float)wsize[0] / 2, (float)wsize[1] / 2};
		wndpos[0] = (1.0f / wwd[0])*objpos[0];
		wndpos[0] -= 1.0f;
		wndpos[1] = (1.0f / wwd[1])*objpos[1];
		wndpos[1] -= 1.0f;

		// ������� �������
		glm::mat4 Mat(1.0f);

		// ������ ������� ������
		if(sds.Cam != nullptr)
		{
			float coffset[2] = {sds.Cam->offsetX, sds.Cam->offsetY};
			float cpos[2] = {sds.Cam->posX - coffset[0], sds.Cam->posY - coffset[1]};

			// ����� �� �������� ������ ����������
			int __cpos[2];
			__cpos[0] = (int)cpos[0] + 0.5;
			__cpos[1] = (int)cpos[1] + 0.5;

			cpos[0] = (float)__cpos[0];
			cpos[1] = (float)__cpos[1];

			float cposwnd[2] = {((1.0f / wwd[0])*cpos[0]) - (sds.Cam->GetAttachedObject() != NULL ? 1 : 0), ((1.0f / wwd[1])*cpos[1]) - (sds.Cam->GetAttachedObject() != NULL ? 1 : 0)};
			
			// ����������� ������� ������� � ������ ������
			Mat = glm::translate(Mat, glm::vec3(-cposwnd[0], -cposwnd[1], 0.0f));
		}
		
		// �������������� ������� ������� � ������� �����������
		Mat = glm::translate(Mat, glm::vec3(wndpos[0], wndpos[1], 0.0f));

		// �������������� �������� �������
		Mat = glm::scale(Mat, glm::vec3((objsize[0] / (float)wsize[0]), (objsize[1] / (float)wsize[1]), 0.0f));

		// ������� �������
		float rotA = sds.rot * 3.14159265358979323846 / 180;
		Mat = glm::rotate(Mat, rotA, glm::vec3(0.0f, 0.0f, 1.0f));
		
		// �������� ������ �� ������
		color4 cm = {sds.cmultiple[0], sds.cmultiple[1], sds.cmultiple[2], sds.cmultiple[3]};
		app->render->RenderTriangles(vbo, app->shaderDefault, texture->textureID, Mat, cm);

#pragma warning(default:4244)
	}
}