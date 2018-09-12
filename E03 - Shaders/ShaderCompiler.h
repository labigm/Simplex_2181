/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2018/01
----------------------------------------------*/
#ifndef __SHADERCOMPILER_H_
#define __SHADERCOMPILER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL\glew.h>
#include <GL\wglew.h>

/*
USAGE: Compiles a new shader based on a vertex file and a fragment file
ARGUMENTS:
	const char * vertex_file_path -> Path to the vertex shader file
	const char * fragment_file_path -> Path to the fragment shader file
OUTPUT:
	Shader Program ID
*/
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);


#endif //__SHADER_H__
