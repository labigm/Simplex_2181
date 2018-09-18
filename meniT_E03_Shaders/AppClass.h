/*----------------------------------------------
Programmer: Alberto Bobadilla(labigm@gmail.com)
Date : 2018 / 01
----------------------------------------------*/
#ifndef __APPCLASS_H_
#define __APPCLASS_H_

#include <stdio.h>
#include <stdlib.h>

#include "ShaderCompiler.h"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>

class AppClass 
{
	std::string m_sWindowName = ""; //window name
	sf::Window* m_pWindow = nullptr; //SFML window
	GLuint m_uShaderProgramID = 0; //Shader program
	GLuint m_uVAO = 0; //Vertex Array Object
	GLuint m_uVBO = 0; //Vertex Buffer Object
	
	glm::vec3 m_v3Color = glm::vec3(-1.0f); //Color of shape

	bool m_bRunning = true; //Running Flag
		
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	AppClass(std::string a_windowName);
	/*
	USAGE: Destroys instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void);
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Run(void);

private:
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	AppClass(AppClass const& input);
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	AppClass& operator=(AppClass const& input);

	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Initialize the window
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitWindow(void);
	/*
	USAGE: Initialize the OpenGL Context
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitOpenGL(void);
	/*
	USAGE: Initialize the OpenGL Shaders
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitShaders(void);
	/*
	USAGE: Initializes user specific variables, this is executed right after InitWindow,
	the purpose of this member function is to initialize member variables specific for this project.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitVariables(void);
	/*
	USAGE: Releases the application
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyboard(sf::Event a_event);
};

#endif //__SFMLAPPCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/