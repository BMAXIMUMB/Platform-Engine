// shader.h

#ifndef _SHADER_H_
#define _SHADER_H_

#include "../../platform_engine.h"
#include "../../object/particles.h"
#include "../color/color.h"
#include <string>
#include <iostream>

//----------------------------------------------------------------------------------------------------------

namespace PlatformEngine
{
	class CShader
	{
	private:
		int linkOk;									// Cобрана ли программа

	public:
		GLuint programID;							// ID шейдерной программы
		GLuint vertexShaderID;						// Вершинный шейдер
		GLuint fragmentShaderID;					// Фрагментный шейдер

	public:
		PLATFORMENGINE_API CShader();
		PLATFORMENGINE_API ~CShader();

		PLATFORMENGINE_API bool LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

		GLuint	GetIDProgram(void);
		void	Use(void);
		int		IsLink(void);

		// Attribute
		GLuint getAttribLocation(const GLchar* name) const;

		// Uniform get
		GLuint getUniformLocation(const GLchar* name) const;

		// Uniform set
		void setUniform(GLint location, const glm::vec4& value);
		void setUniform(GLint location, const glm::vec3& value);
		void setUniform(GLint location, const glm::vec2& value);

		void setUniform(GLint location, const glm::mat4& value);
		void setUniform(GLint location, const GLint value);
		void setUniform(GLint location, const GLfloat value);
		void setUniform(GLint location, const color4 value);
		void setUniform(GLint location, const float value[4]);
	};
}

#endif //_SHADER_H_