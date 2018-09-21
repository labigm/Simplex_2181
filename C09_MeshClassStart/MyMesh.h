/*----------------------------------------------
Programmer: Alberto Bobadilla(labigm@rit.edu)
Date : 2018 / 09
----------------------------------------------*/
#ifndef __MYMESH_H_
#define __MYMESH_H_

#include "Definitions.h"

class MyMesh
{
public:
	GLuint m_uShaderProgramID = 0; //Shader program
	GLuint m_uVAO = 0; //Vertex Array Object
	GLuint m_uVBO = 0; //Vertex Buffer Object
	std::vector<glm::vec3> m_lVertex;
	MyMesh(float size);
	void InitShader(void);
	void InitTriangle(float size);
	void Draw(void);
	~MyMesh();
};

#endif