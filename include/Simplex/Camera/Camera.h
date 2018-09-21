/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "Simplex\System\SystemSingleton.h"

namespace Simplex
{
//Camera Class
class SimplexDLL Camera
{
	bool m_bFPS = true; //If set to false will behave like a flight simulator camera

	BTO_CAMERAMODE m_nMode = BTO_CAMERAMODE::CAM_PERSP; //Sets the mode the camera will display

	float m_fFOV = 45.0f; //Field of View

	vector2 m_v2NearFar = vector2(0.001f, 1000.0f); //Near and Far planes

	vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f); //Where my camera is located
	vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What the camera is looking at
	vector3 m_v3Above = vector3(0.0f, 1.0f, 0.0f); //What is above the camera position

	vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f); //Line of sight
	vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //Up line
	vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f); //side line

	vector3 m_v3PitchYawRoll = vector3(0.0f); //Orientation in Euler

	matrix4 m_m4Projection = matrix4(1.0f); //Projection Matrix
	matrix4 m_m4View = matrix4(1.0f); //View matrix

	bool m_bInternalCalculation = true; //use of this flag to accept other matrices instead of calculating them

public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Camera(void);
	/*
	USAGE: Constructor with parameters
	ARGUMENTS:
	-	vector3 a_v3Position -> Where my camera is located
	-	vector3 a_v3Target -> What I'm looking at
	-	vector3 a_v3Upward -> What is up
	OUTPUT: ---
	*/
	Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: Camera const& other -> object to copy
	OUTPUT: ---
	*/
	Camera(Camera const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: Camera const& other -> object to copy
	OUTPUT: ---
	*/
	Camera& operator=(Camera const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Camera(void);
	/*
	USAGE: Gets the View matrix from the camera
	ARGUMENTS: ---
	OUTPUT: view matrix
	*/
	matrix4 GetViewMatrix(void);
	/*
	USAGE: Gets the Projection matrix from the camera
	ARGUMENTS: ---
	OUTPUT: projection matrix
	*/
	matrix4 GetProjectionMatrix(void);
	/*
	USAGE: Gets the ModelViewProjection matrix from the camera
	ARGUMENTS: matrix4 a_m4ModelToWorld -> model matrix to evaluate
	OUTPUT: ModelViewProjection matrix
	*/
	matrix4 GetMVP(matrix4 a_m4ModelToWorld);
	/*
	USAGE: Gets the ViewProjection matrix from the camera
	ARGUMENTS: ---
	OUTPUT: View projection matrix
	*/
	matrix4 GetVP(void);
	/*
	USAGE:  Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetPosition(void);
	/*
	USAGE:  Gets the forward vector of the camera
	ARGUMENTS: ---
	OUTPUT: forward vector of the camera
	*/
	vector3 GetForward(void);
	/*
	USAGE:  Gets the upward vector of the camera
	ARGUMENTS: ---
	OUTPUT: upward vector of the camera
	*/
	vector3 GetUpward(void);
	/*
	USAGE:  Gets the sidewards vector of the camera
	ARGUMENTS: ---
	OUTPUT: rightward vector of the camera
	*/
	vector3 GetRightward(void);
	/*
	USAGE:  Sets the Forward vector of the camera
	ARGUMENTS: vector3 a_v3Input -> input vector
	OUTPUT: ---
	*/
	void SetForward(vector3 a_v3Input);
	/*
	USAGE:  Sets the Upward vector of the camera
	ARGUMENTS: vector3 a_v3Input -> input vector
	OUTPUT: ---
	*/
	void SetUpward(vector3 a_v3Input);
	/*
	USAGE:  Sets the Forward vector of the camera
	ARGUMENTS: vector3 a_v3Input -> input vector
	OUTPUT: ---
	*/
	void SetRightward(vector3 a_v3Input);
	/*
	USAGE: Changes the near and far planes
	ARGUMENTS:
	-	float a_fNear -> near clipping plane
	-	float a_fFar -> far clipping plane
	OUTPUT:
	*/
	void SetNearFarPlanes(float a_fNear, float a_fFar);
	/*
	USAGE: Calculates the projection based on the camera values
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateProjection(void);
	/*
	USAGE: Calculates the view based on the camera values
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateView(void);
	/*
	USAGE: Set Field of View
	ARGUMENTS: input field of view
	OUTPUT: ---
	*/
	void SetFOV(float a_fFOV);
	/*
	USAGE: Sets the camera at the specified position
	ARGUMENTS: vector3 a_v3Position -> input
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Sets the target of the camera to the specified position
	ARGUMENTS: vector3 a_vTarget -> point to look at
	OUTPUT: ---
	*/
	void SetTarget(vector3 a_v3Target);
	/*
	USAGE: Sets the camera at the specified position and target
	ARGUMENTS:
	-	vector3 a_v3Position -> position of the camera
	-	vector3 a_v3Target -> target to look at
	-	vector3 a_v3Upward -> what up means
	OUTPUT:
	*/
	void SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
	/*
	USAGE: Translates from mouse coordinates (inside of window) to world space
	ARGUMENTS: 
	-	uint a_nMouseX -> position X
	-	uint a_nMouseY -> position Y
	OUTPUT: Click Position in World space
	*/
	vector3 GetClickOnWorldSpace(uint a_nMouseX, uint a_nMouseY);
	/*
	USAGE: Get where in the window you clicked and the direction that click would take you
	ARGUMENTS:
	-	uint a_nMouseX -> position X
	-	uint a_nMouseY -> position Y
	OUTPUT: pair of start and direction
	*/
	std::pair<vector3,vector3> GetClickAndDirectionOnWorldSpace(uint a_nMouseX, uint a_nMouseY);
	/*
	USAGE: Gets the space on which the camera is located on the global space
	ARGUMENTS: ---
	OUTPUT: camera space
	*/
	matrix4 GetCameraSpace(void);
	/*
	USAGE: Gets the space just in front of the camera in global space
	ARGUMENTS: ---
	OUTPUT: space just in front of the camera with a small offset
	*/
	matrix4 GetCameraSpaceAdjusted(void);
	/*
	USAGE: Gets the plane space just in front of the camera
	ARGUMENTS: ---
	OUTPUT: plane just in front of the camera
	*/
	matrix4 GetCameraPlane(void);
	/*
	USAGE: Gets the space just under the mouse pointer
	ARGUMENTS: ---
	OUTPUT: space under the mouse
	*/
	matrix4 GetSpaceUnderMouse(void);
	/*
	USAGE: Translates the camera forward or backward
	ARGUMENTS: float a_fDistance = 0.1f -> amount of movement
	OUTPUT: ---
	*/
	void MoveForward(float a_fDistance = 0.1f);
	/*
	USAGE: Translates the camera Upward or downward
	ARGUMENTS: float a_fDistance = 0.1f -> amount of movement 
	OUTPUT: ---
	*/
	void MoveVertical(float a_fDistance = 0.1f);
	/*
	USAGE: Translates the camera right or left
	ARGUMENTS: float a_fDistance = 0.1f -> amount of movement
	OUTPUT: ---
	*/
	void MoveSideways(float a_fDistance = 0.1f);
	/*
	USAGE: Rotates the camera Pitch
	ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
	OUTPUT: ---
	*/
	void ChangePitch(float a_fDegree = 0.001f);
	/*
	USAGE: Rotates the camera Yaw
	ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
	OUTPUT: ---
	*/
	void ChangeYaw(float a_fDegree = 0.001f);
	/*
	USAGE: Rotates the camera Roll
	ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
	OUTPUT: ---
	*/
	void ChangeRoll(float a_fDegree = 0.001f);
	/*
	USAGE: Sets the camera in First Person Shooter mode, if false it will work like an aircraft
	ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
	OUTPUT: ---
	*/
	void SetFPS(bool a_bFPS = true);
	/*
	USAGE: Sets the camera in Perspective mode, if false it will work as an orthographic camera
	ARGUMENTS: BTO_CAMERAMODE a_nMode = BTO_CAMERAMODE::CAM_PERSP -> mode to set
	OUTPUT: ---
	*/
	void SetCameraMode(BTO_CAMERAMODE a_nMode = BTO_CAMERAMODE::CAM_PERSP);
	/*
	USAGE: Returns the current value for the camera mode
	ARGUMENTS: ---
	OUTPUT: mode of the camera
	*/
	BTO_CAMERAMODE GetCameraMode(void);
	/*
	USAGE: Resets the value of the camera
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ResetCamera(void);
	/*
	USAGE: Sets the view Matrix overriding the internal values
	note, to reset the camera to use internal values it needs to be reset
	ARGUMENTS: matrix4 input -> view matrix
	OUTPUT: ---
	*/
	void SetViewMatrix(matrix4 input);
	/*
	USAGE: Sets the projection Matrix overriding the internal values
	note, to reset the camera to use internal values it needs to be reset
	ARGUMENTS: matrix4 input -> projection matrix
	OUTPUT: ---
	*/
	void SetProjectionMatrix(matrix4 input);

private:
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initialize the object's fields
	ARGUMENTS:
	-	vector3 a_v3Position -> position of the camera
	-	vector3 a_v3Target -> what we are looking at
	-	vector3 a_v3Upward -> what is up
	OUTPUT: ---
	*/
	void Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
	/*
	USAGE: Swaps the contents of the object with another object's content
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(Camera& other);
};

	EXPIMP_TEMPLATE template class SimplexDLL std::vector<Camera>;
	EXPIMP_TEMPLATE template class SimplexDLL std::vector<Camera*>;
}//namespace Simplex

#endif //__CAMERACLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/