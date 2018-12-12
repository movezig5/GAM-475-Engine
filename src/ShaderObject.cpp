#include <sb7.h>
#include <math.h>
#include <assert.h>

#include "GameObject.h"
#include "MathEngine.h"
#include "File.h"
#include "ShaderObject.h"
#include "Game.h"

ShaderObject::ShaderObject(ShaderObject::Name shaderName, const char * const pShaderBaseFileName)
	: DLink(), name(shaderName)
{
	assert(pShaderBaseFileName != 0);
	this->privCreateShader(this->programObject, pShaderBaseFileName);
}

ShaderObject::~ShaderObject() {}

void ShaderObject::SetActive()
{
	glUseProgram(this->programObject);
}

GLint ShaderObject::GetLocation(const char * pUniformName)
{
	assert(pUniformName != 0);
	GLint loc = glGetUniformLocation(this->programObject, pUniformName);
	assert(loc != -1);

	return loc;
}
bool ShaderObject::privCreateShader(GLuint &inProgramObject, const char * const pShaderBaseFileName)
{
	bool status;
	char nameBuff[128];

	assert(pShaderBaseFileName);

	strcpy_s(nameBuff, 128, pShaderBaseFileName);
	strcat_s(nameBuff, 128, ".fs.glsl");

	GLuint fs;
	status = privLoadNCompile(fs, nameBuff, GL_FRAGMENT_SHADER);
	assert(status == true);

	strcpy_s(nameBuff, 128, pShaderBaseFileName);
	strcat_s(nameBuff, 128, ".vs.glsl");

	GLuint vs;
	status = privLoadNCompile(vs, nameBuff, GL_VERTEX_SHADER);
	assert(status == true);

	inProgramObject = glCreateProgram();
	glAttachShader(inProgramObject, vs);
	glAttachShader(inProgramObject, fs);
	glLinkProgram(inProgramObject);

	return true;
}

bool ShaderObject::privLoadNCompile(GLuint &shaderObject, const char * const pShaderFileName, GLenum shader_type)
{
	File::Handle fh;
	File::Error ferror;

	ferror = File::Open(fh, pShaderFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Location::END, 0);
	assert(ferror == File::Error::SUCCESS);

	DWORD numBytesInFile;
	ferror = File::Tell(fh, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	char *data = new char[numBytesInFile + 1];
	assert(data != 0);

	ferror = File::Read(fh, data, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	// null termination character
	data[numBytesInFile] = 0;

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	// create shader object
	shaderObject = glCreateShader(shader_type);
	assert(shaderObject != 0);

	// load shader
	glShaderSource(shaderObject, 1, &data, 0);
	delete[] data;

	glCompileShader(shaderObject);

	// check for errors
	GLint status = 0;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);

	// found one
	if (!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(shaderObject, 4096, NULL, buffer);

		printf("Error(ShaderObject.cpp %s: %s\n", pShaderFileName, buffer);

		glDeleteShader(shaderObject);

		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}