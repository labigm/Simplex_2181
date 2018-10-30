/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __MYMESH_H_
#define __MYMESH_H_

#include "Definitions.h"
#include "MyCamera.h"

namespace Simplex
{

class MyMesh
{
	bool m_bBinded = false;		//Binded flag
	uint m_uVertexCount = 0;	//Number of vertices in this MyMesh
	GLuint m_VAO = 0;			//OpenGL Vertex Array Object
	GLuint m_VBO = 0;			//OpenGL Vertex Array Object

	std::vector<vector3> m_lVertex;		//Composed vertex array
	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors

	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager

public:
	/*
	USAGE: Initialize the object's fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyMesh();
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyMesh();
	/*
	USAGE: Copy Constructor -> MyMesh does not allow to copy
	from other MyMesh objects, create an empty MyMesh
	and use the Instantiate method instead
	ARGUMENTS: class object (to copy)
	OUTPUT: class object
	*/
	MyMesh(MyMesh& other);
	/*
	USAGE: Copy Assignment Operator -> MyMesh does not allow to copy
	from other SimpleMesh objects, use the Instantiate method instead.
	ARGUMENTS: class object (to copy)
	OUTPUT: class object
	*/
	MyMesh& operator=(MyMesh& other);
	/*
	USAGE: Swaps the contents of the object with another object's content
	ARGUMENTS: class object  (to swap with)
	OUTPUT: ---
	*/
	void Swap(MyMesh& other);
	/*
	USAGE: Completes the information missing to create the mesh
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompleteMesh(vector3 a_v3Color = vector3(1.0f, 0.0f, 0.0f));
	/*
	USAGE: Adds a new point to the vector of vertices
	ARGUMENTS:
	-	vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexPosition(vector3 a_v3Input);
	/*
	USAGE: Adds a new color to the vector of vertices
	ARGUMENTS:
	-	vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexColor(vector3 a_v3Input);
	/*
	USAGE: Compiles the MyMesh for OpenGL 3.X use
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);
	/*
	USAGE: Renders the mesh on the specified position by the
	provided camera view and projection
	ARGUMENTS:
	-	matrix4 a_mProjection -> Projection matrix
	-	matrix4 a_mView -> View matrix
	-	matrix4 a_mModel -> matrix of the model in the world
	OUTPUT: ---
	*/
	void Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel);
	/*
	USAGE: Renders the mesh on the specified position by the
	provided camera view and projection
	ARGUMENTS: MyCamera a_mCamera -> the camera I want to see my scene from
	OUTPUT: ---
	*/
	void Render(MyCamera* a_pCamera, matrix4 a_mModel);
	/*
	USAGE: Will render this mesh a_ToWorlsList size times
	ARGUMENTS:
	-	MyCamera* a_pCamera
	-	std::vector<matrix4> a_ToWorldList
	OUTPUT: ---
	*/
	void Render(MyCamera* a_pCamera, std::vector<matrix4> a_ToWorldList);
	/*
	USAGE: Adds a tri to the list points in the buffer to be compiled
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C
	ARGUMENTS:
	-	vector3 a_vBottomLeft (A)
	-	vector3 a_vBottomRight (B)
	-	vector3 a_vTopLeft (C)
	OUTPUT: ---
	*/
	void AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft);
	/*
	USAGE: Adds a quad to the list points in the buffer to be compiled
	//C--D
	//|  |
	//A--B
	//Will make the triangle A->B->C and then the triangle C->B->D
	ARGUMENTS:
	-	vector3 a_vBottomLeft (A)
	-	vector3 a_vBottomRight (B)
	-	vector3 a_vTopLeft (C)
	-	vector3 a_vTopRight (D)
	OUTPUT: ---
	*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
#pragma region 3D Primitives
	/*
	USAGE: Generates a cube
	ARGUMENTS:
	-	float a_fSize -> Size of each side
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateCube(float a_fSize, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cuboid
	ARGUMENTS:
	-	vector3 a_v3Dimensions -> Dimensions of each side of the cuboid
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cone mesh
	ARGUMENTS:
	-	float a_fRadius -> radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions of the cap
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cylinder mesh
	ARGUMENTS:
	-	float a_fRadius -> radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a tube mesh
	ARGUMENTS:
	-	float a_fOuterRadius -> outer radius
	-	float a_fInnerRadius -> inner radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	-	a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a torus mesh
	ARGUMENTS:
	-	float a_fOuterRadius -> Outer radius
	-	float a_fInnerRadius -> Inner Radius
	-	int a_nSubdivisionHeight -> divisions vertical
	-	int a_nSubdivisionAxis -> divisions along the roundness of the mesh
	-	a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a Sphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
	-	a_v3Color -> Color of the mesh
	OUTPUT: ---
	*/
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
#pragma endregion
};

}//namespace Simplex

#endif //__MYMESH_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/