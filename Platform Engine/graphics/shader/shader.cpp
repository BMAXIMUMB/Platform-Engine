// shader.cpp

#include "shader.h"
#include <fstream>
#include <vector>
#include "../../logprintf.h"

//----------------------------------------------------------------------------------------------------------

namespace PlatformEngine
{
	CShader::CShader()
	{
		linkOk = NULL;
	}

	CShader::~CShader()
	{
		// Удаляем шейдеры, они нам больше не нужны
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void CShader::setUniform(GLint location, const glm::vec4& value)
	{
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}

	void CShader::setUniform(GLint location, const float value[4])
	{
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}

	void CShader::setUniform(GLint location, const color4 value)
	{
		glUniform4f(location, value.r, value.g, value.b, value.a);
	}

	void CShader::setUniform(GLint location, const glm::vec3& value)
	{
		glUniform3f(location, value[0], value[1], value[2]);
	}

	void CShader::setUniform(GLint location, const glm::vec2& value)
	{
		glUniform2f(location, value[0], value[1]);
	}

	void CShader::setUniform(GLint location, const glm::mat4& value)
	{
		glUniformMatrix4fv(location, 1, GL_FLOAT, &value[0][0]);
	}

	void CShader::setUniform(GLint location, const GLint value)
	{
		glUniform1d(location, value);
	}

	void CShader::setUniform(GLint location, const GLfloat value)
	{
		glUniform1f(location, value);
	}

	GLuint CShader::getAttribLocation(const GLchar* name) const
	{
		GLuint location = -1;
		location = glGetAttribLocation(programID, name);
		return location;
	}

	GLuint CShader::getUniformLocation(const GLchar* name) const
	{
		GLuint location = -1;
		location = glGetUniformLocation(programID, name);
		return location;
	}

	void CShader::Use()
	{
		glUseProgram(programID);
		/*glUniform4fv(unif_color, 1, red);
		glEnableVertexAttribArray(attrib_vertex);*/
	}

	int CShader::IsLink()
	{
		return linkOk;
	}

	GLuint CShader::GetIDProgram()
	{
		return programID;
	}

	bool CShader::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
	{
		// создаем шейдеры
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		
		// читаем вершинный шейдер из файла
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if(VertexShaderStream.is_open())
		{
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}

		// читаем фрагментный шейдер из файла
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if(FragmentShaderStream.is_open()){
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		// Компилируем вершинный шейдер
		logprintf("Compiling shader : %s\n", vertex_file_path);
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(vertexShaderID);

		GLint Result = GL_FALSE;
		//int InfoLogLength;


		// Дебаг ошибок
		/*glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);*/

		// Компилируем фрагментный шейдер
		logprintf("Compiling shader : %s\n", fragment_file_path);
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(fragmentShaderID);

		// Дебаг ошибок
		/*glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FShaderErrorMessage[0]);
		printf("%s\n", &FShaderErrorMessage[0]);*/

		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		glGetProgramiv(programID, GL_LINK_STATUS, &linkOk);
		if(!linkOk)
		{
			logprintf("Ошибка шейдера");
			return false;
		}
		return true;
	}
}