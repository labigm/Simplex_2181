/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __MYCAMERACLASS_H_
#define __MYCAMERACLASS_H_

#include "Definitions.h"

namespace Simplex
{

class MyCamera
{
	vector3 m_v3Position = vector3(0.0f, 0.0f, 10.0f); //Where my camera is located
	vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What I'm looking at
	vector3 m_v3Up = vector3(0.0f, 1.0f, 0.0f); //What is up

	vector3 m_v3Forward = vector3(0.0f, 0.0f,-1.0f); //View vector
	vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //where my head is pointing up
	vector3 m_v3Rightwart = vector3(0.0f, 1.0f, 0.0f); //What is to my right
	
	matrix4 m_m4View; //View matrix
	matrix4 m_m4Projection; //Projection Matrix
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: the class object
	*/
	MyCamera();

	/*
	USAGE: constructor
	ARGUMENTS:
	-	vector3 a_v3Position -> Where my camera is located
	-	vector3 a_v3Target -> What I'm looking at
	-	vector3 a_v3Upward -> What is up
	OUTPUT: ---
	*/
	MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

	/*
	USAGE: Copy constructor
	ARGUMENTS: MyCamera const& other -> object to copy
	OUTPUT: ---
	*/
	MyCamera(MyCamera const& other);

	/*
	USAGE: Copy Assignment operator
	ARGUMENTS: MyCamera const& other -> object to copy
	OUTPUT: ---
	*/
	MyCamera& operator=(MyCamera const& other);

	/*
	USAGE: Initialize the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/*
	USAGE: Release pointers in the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: swap the content with an incoming object
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Swap(MyCamera& other);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyCamera(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Position -> Position where we want the camera to be
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetPosition(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Target -> What we want the camera to look at
	OUTPUT: ---
	*/
	void SetTarget(vector3 a_v3Target);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetTarget(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Up -> What up means in the world
	OUTPUT: ---
	*/
	void SetUp(vector3 a_v3Up);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetUp(void);

	/*
	USAGE: Gets the projection matrix of the camera
	ARGUMENTS: ---
	OUTPUT: projection matrix of the camera
	*/
	matrix4 GetProjectionMatrix(void);

	/*
	USAGE: Gets the view matrix of the camera
	ARGUMENTS: ---
	OUTPUT: view matrix of the camera
	*/
	matrix4 GetViewMatrix(void);

	/*
	USAGE: Resets the camera to default values
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ResetCamera(void);

	/*
	USAGE: Set the position target and up of the camera at once
	ARGUMENTS:
	-	vector3 a_v3Position -> Where my camera is located
	-	vector3 a_v3Target -> What I'm looking at
	-	vector3 a_v3Upward -> What is up
	OUTPUT: ---
	*/
	void SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward = AXIS_Y);

	/*
	USAGE: Calculate what the camera should be looking at with the values of position target and up
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateViewMatrix(void);

	/*
	USAGE: Calculate how the camera sees the world
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateProjectionMatrix(void);

};

} //namespace Simplex

#endif //__MYCAMERACLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */