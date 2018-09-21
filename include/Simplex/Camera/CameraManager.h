/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
Modified: 2017/06
----------------------------------------------*/
#ifndef __CAMERAMANAGER_H_
#define __CAMERAMANAGER_H_

#include "Simplex\Camera\Camera.h"

namespace Simplex
{

//Camera Manager Singleton
class SimplexDLL CameraManager
{
	static CameraManager* m_pInstance; // Singleton pointer
	std::vector<Camera*> m_lCamera; //Camera list holder
	uint m_uActiveCamera = 0; //number of the active camera
	uint m_uCameraCount = 0; //number of cameras in the camera manager
public:
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static CameraManager* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: AddCamera will create a new Camera object and add it to the list
	- returning the index in the list
	ARGUMENTS:
	OUTPUT:
	*/
	uint AddCamera(vector3 a_v3Eye, vector3 a_v3Target, vector3 a_v3Upwards);
	/*
	USAGE: Calculates the view of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	OUTPUT: ---
	*/
	void CalculateView(int a_nIndex = -1);
	/*
	USAGE: Calculates the Projection of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	- int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void CalculateProjection(int a_nIndex = -1);
	/*
	USAGE: Sets the active camera flag from the list
	ARGUMENTS:
	-	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetActiveCamera(uint a_nIndex = 0);
	/*
	USAGE: Gets the active camera index
	ARGUMENTS: ---
	OUTPUT: index of the active camera
	*/
	uint GetActiveCamera(void);
	/*
	USAGE: Gets the View matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 GetViewMatrix(int a_nIndex = -1);
	/*
	USAGE: Gets the Projection matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 GetProjectionMatrix(int a_nIndex = -1);
	/*
	USAGE: Gets the ModelViewProjection matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 GetMVP(matrix4 a_m4ModelToWorld, int a_nIndex = -1);
	/*
	USAGE: Gets the ViewProjection matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 GetVP(int a_nIndex = -1);
	/*
	USAGE: Gets the position of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	vector3 GetPosition(int a_nIndex = -1);
	/*
	USAGE:  Gets the forward vector of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetForward(int a_nIndex = -1);
	/*
	USAGE:  Gets the upward vector of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetUpward(int a_nIndex = -1);
	/*
	USAGE:  Gets the sidewards vector of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetRightward(int a_nIndex = -1);
	/*
	USAGE:  Sets the Forward vector of the camera
	ARGUMENTS: input
	OUTPUT: ---
	*/
	void SetForward(vector3 a_v3Input, int a_nIndex = -1);
	/*
	USAGE:  Sets the Upward vector of the camera
	ARGUMENTS: input
	OUTPUT: ---
	*/
	void SetUpward(vector3 a_v3Input, int a_nIndex = -1);
	/*
	USAGE:  Sets the Forward vector of the camera
	ARGUMENTS: input
	OUTPUT: ---
	*/
	void SetRightward(vector3 a_v3Input, int a_nIndex = -1);
	/*
	USAGE: Sets the camera specified by index at the specified position and target, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward, int a_nIndex = -1);
	/*
	USAGE: Translates from mouse coordinates (inside of window) to world space
	ARGUMENTS:
	- uint a_nMouseX
	- uint a_nMouseY
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: Click Position in World space
	*/
	vector3 GetClickOnWorldSpace(uint a_nMouseX, uint a_nMouseY, int a_nIndex = -1);
	/*
	USAGE: Get where in the window you clicked and the direction that click would take you
	ARGUMENTS:
	- uint a_nMouseX
	- uint a_nMouseY
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: pair of start and direction
	*/
	std::pair<vector3, vector3> GetClickAndDirectionOnWorldSpace(uint a_nMouseX, uint a_nMouseY, int a_nIndex = -1);
	/*
	USAGE: Gets the space on which the camera is located on the global space
	ARGUMENTS:
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: space of the camera
	*/
	matrix4 GetCameraSpace(int a_nIndex = -1);
	/*
	USAGE: Gets the space just in front of the camera in global space
	ARGUMENTS:
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: space in front of the camera
	*/
	matrix4 GetCameraSpaceAdjusted(int a_nIndex = -1);
	/*
	USAGE: Gets the plane space just in front of the camera
	ARGUMENTS:
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: plane just in front of the camera
	*/
	matrix4 GetCameraPlane(int a_nIndex = -1);

	/*
	USAGE: Gets the space just in under the pointer
	ARGUMENTS:
	- int a_nIndex = -1 -> index of the camera, -1 will return the active camera
	OUTPUT: space in under the camera
	*/
	matrix4 GetSpaceUnderMouse(int a_nIndex = -1);

	/*
	USAGE: Gets the camera pointer specified by index
	ARGUMENTS:
	- int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: Camera pointer
	*/
	Camera* GetCamera(int a_nIndex = -1);
	/*
	USAGE: Sets the camera in First Person Shooter mode, if false it will work like an aircraft,
	- if -1 it will use the active camera
	ARGUMENTS:
	- bool a_bFPS = true -> is this a first person camera?
	- int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetFPS(bool a_bFPS = true, int a_nIndex = -1);
	/*
	USAGE: Sets the camera in Perspective mode, if false it will work as an orthographic camera, if -1 
	- it will use the active camera
	ARGUMENTS:
	- BTO_CAMERAMODE a_nMode = BTO_CAMERAMODE::CAM_PERSP -> camera mode settings (see BTO_CAMERAMODE enum for more info)
	- int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetCameraMode(BTO_CAMERAMODE a_nMode = BTO_CAMERAMODE::CAM_PERSP, int a_nIndex = -1);
	/*
	USAGE: Returns the current value for the camera mode of the camera specified by index, if -1 it will 
	- use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	BTO_CAMERAMODE GetCameraMode(int a_nIndex = -1);
	/*
	USAGE: Returns the number of cameras in the list specified by index, if -1 it will use the active camera
	ARGUMENTS: ---
	OUTPUT: uint number of cameras
	*/
	uint GetCameraCount(void);
	/*
	USAGE: Changes the near and far planes of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetNearFarPlanes(float a_fNear, float a_fFar, int a_nIndex = -1);
	/*
	USAGE: Set Field of View
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetFOV(float a_fFOV, int a_nIndex = -1);
	/*
	USAGE:	Translates the camera forward or backward of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveForward(float a_fDistance = 0.1f, int a_nIndex = -1);
	/*
	USAGE:	Translates the camera Upward or downward of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveVertical(float a_fDistance = 0.1f, int a_nIndex = -1);
	/*
	USAGE:	Translates the camera right or left of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveSideways(float a_fDistance = 0.1f, int a_nIndex = -1);
	/*
	USAGE:	Rotates the camera Pitch of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangePitch(float a_fDegree = 1.0f, int a_nIndex = -1);
	/*
	USAGE:	Rotates the camera Yaw of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangeYaw(float a_fDegree = 1.0f, int a_nIndex = -1);
	/*
	USAGE: Rotates the camera Roll of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangeRoll(float a_fDegree = 1.0f, int a_nIndex = -1);
	/*
	USAGE: Sets the camera at the specified position of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_vPosition, int a_nIndex = -1);
	/*
	USAGE: Sets the Target of the camera specified by index at the specified position
	ARGUMENTS:
		vector3 a_vTarget -> 
		int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetTarget(vector3 a_vTarget, int a_nIndex = -1);

	/*
	USAGE: Sets the view Matrix overriding the internal values
	note, to reset the camera to use internal values it needs to be reset
	ARGUMENTS: matrix4 view matrix
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetViewMatrix(matrix4 input, int a_nIndex = -1);

	/*
	USAGE: Sets the projection Matrix overriding the internal values
	note, to reset the camera to use internal values it needs to be reset
	ARGUMENTS: matrix4 view matrix
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetProjectionMatrix(matrix4 input, int a_nIndex = -1);

	/*
	USAGE: Resets the value of the camera
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ResetCamera(int a_nIndex = -1);

private:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	CameraManager(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	CameraManager(CameraManager const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	CameraManager& operator=(CameraManager const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~CameraManager(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

} //namespace Simplex

#endif //__CAMERAMANAGER_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */