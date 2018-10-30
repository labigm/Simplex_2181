/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __MYRIGIDBODY_H_
#define __MYRIGIDBODY_H_

#include "Simplex\Simplex.h"

namespace Simplex
{

//System Class
class MyRigidBody
{
	MeshManager* m_pMeshMngr = nullptr; //for displaying the Rigid Body

	bool m_bVisible = true; //Visibility

	float m_fRadius = 0.0f; //Radius

	vector3 m_v3Color = C_WHITE; //Color

	vector3 m_v3Center = vector3(0.0f); //center point in local space
	vector3 m_v3MinL = vector3(0.0f); //minimum coordinate in local space
	vector3 m_v3MaxL = vector3(0.0f); //maximum coordinate in local space

	vector3 m_v3MinG = vector3(0.0f); //minimum coordinate in global space
	vector3 m_v3MaxG = vector3(0.0f); //maximum coordinate in global space

	vector3 m_v3HalfWidth = vector3(0.0f); //half the size of all sides; difference between min/max for X, Y, and Z, divided by 2

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate

public:
	/*
	Usage: Constructor
	Arguments: std::vector<vector3> a_pointList -> list of points to make the Rigid Body for
	Output: class object instance
	*/
	MyRigidBody(std::vector<vector3> a_pointList);
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyRigidBody(MyRigidBody const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyRigidBody& operator=(MyRigidBody const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyRigidBody(void);
	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	void Swap(MyRigidBody& other);

	/*
	USAGE: Will render the Rigid Body at the model to world matrix
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddToRenderList(void);

	/*
	USAGE: Tells if the object is colliding with the incoming one
	ARGUMENTS: ---
	OUTPUT: are they colliding?
	*/
	bool IsColliding(MyRigidBody* const other);
#pragma region Accessors
	/*
	Usage: Gets visibility
	Arguments: ---
	Output: visibility
	*/
	bool GetVisible(void);
	/*
	Usage: Gets radius
	Arguments: ---
	Output: radius
	*/
	float GetRadius(void);
	/*
	Usage: Gets the color
	Arguments: ---
	Output: color
	*/
	vector3 GetColor(void);
	/*
	Usage: Sets the color
	Arguments: vector3 a_v3Color -> color
	Output: ---
	*/
	void SetColor(vector3 a_v3Color);
	/*
	Usage: Gets center in local space
	Arguments: ---
	Output: center
	*/
	vector3 GetCenterLocal(void);
	/*
	Usage: Gets minimum vector in local space
	Arguments: ---
	Output: min vector
	*/
	vector3 GetMinLocal(void);
	/*
	Usage: Gets maximum vector in local space
	Arguments: ---
	Output: max vector
	*/
	vector3 GetMaxLocal(void);
	/*
	Usage: Gets center in global space
	Arguments: ---
	Output: center
	*/
	vector3 GetCenterGlobal(void);
	/*
	Usage: Gets minimum vector in local space
	Arguments: ---
	Output: min vector
	*/
	vector3 GetMinGlobal(void);
	/*
	Usage: Gets max vector in global space
	Arguments: ---
	Output: max vector
	*/
	vector3 GetMaxGlobal(void);
	/*
	Usage: Gets the size of the model divided by 2
	Arguments: ---
	Output: halfwidth vector
	*/
	vector3 GetHalfWidth(void);
	/*
	Usage: Gets Model to World matrix
	Arguments: ---
	Output: model to world matrix
	*/
	matrix4 GetModelMatrix(void);
	/*
	Usage: Sets Model to World matrix
	Arguments: Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ModelMatrix);
#pragma endregion
	
private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

} //namespace Simplex

#endif //__MYRIGIDBODY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/