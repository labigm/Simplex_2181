/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __MYMESHMANAGER_H_
#define __MYMESHMANAGER_H_
#include "MyMesh.h"
#include "MyCamera.h"
namespace Simplex
{

//MyMeshManager singleton
class MyMeshManager
{
	MyCamera* m_pCamera = nullptr; //Camera to use for all meshes
	std::vector<MyMesh*> m_meshList; //List of all the meshes added to the system
	std::vector<std::vector<matrix4>> m_renderList; //list of lists of render calls
	static MyMeshManager* m_pInstance; // Singleton pointer

public:
	//Singleton Methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static MyMeshManager* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Adds a mesh to the list of meshes
	ARGUMENTS: MyMesh* a_pMesh -> mesh to add
	OUTPUT: index of the mesh in the list, if -1 there was an error
	*/
	int AddMesh(MyMesh* a_pMesh);
	/*
	USAGE: Gets the MyMesh pointer from the map by name;
	WARNING: DO NOT change the name of the mesh or it will lose its position in map
	DO NOT delete the pointer outside of the manager
	ARGUMENTS: String a_sName -> name of the inquired mesh
	OUTPUT: index of the mesh in the mesh list, -1 if not found
	*/
	int GetMeshIndex(MyMesh* a_pMesh);
	/*
	USAGE: Returns the mesh specified by index from the list of Meshes
	ARGUMENTS: uint nMesh -> index of the mesh
	OUTPUT: Inquired mesh
	*/
	MyMesh* GetMesh(uint nMesh);
	/*
	USAGE: Generates a cube
	ARGUMENTS:
	-	float a_fSize -> Size of each side
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateCube(float a_fSize, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cuboid
	ARGUMENTS:
	-	vector3 a_v3Dimensions -> Dimensions of each side of the cuboid
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE:Generates a cone mesh
	ARGUMENTS:
	-	float a_fRadius -> radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions of the cap
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cylinder mesh
	ARGUMENTS:
	-	float a_fRadius -> radiu44444s
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	-	vector3 a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a tube mesh
	ARGUMENTS:
	-	float a_fOuterRadius -> outer radius
	-	float a_fInnerRadius -> inner radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	-	4a_v3Color -> Color of the mesh
	OUTPUT: name of the generated Mesh4
	*/
	int GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a torus mesh
	ARGUMENTS:
	-	float a_fOuterRadius -> Outer radius
	-	float a_fInnerRadius -> Inner Radius
	-	int a_nSubdivisionHeight -> divisions vertical
	-	int a_nSubdivisionAxis -> divisions along the roundness of the mesh
	-	a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a Sphere mesh
	ARGUMENTS:
	-	float a_fDiameter -> diameter of the sphere (radius times 2)
	-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subdivisions
	-	a_v3Color -> Color of the mesh
	OUTPUT: name of the generated MyMesh
	*/
	int GenerateSphere(float a_fDiameter, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddCubeToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddConeToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddCylinderToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddTubeToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddTorusToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:	matrix4 a_m4ToWorld -> Space to render the primitive onto
	OUTPUT: ---
	*/
	void AddSphereToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Finds the specified mesh and specifies a transform to display
	ARGUMENTS:
	-	uint a_nIndex -> index of the mesh to apply transform to
	-	matrix4 a_m4Transform -> transform to apply
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddMeshToRenderList(uint a_nIndex, matrix4 a_m4Transform);
	/*
	USAGE: Applies a transform to display to the specified mesh, the mesh will be lookout
	for in the map of meshes, using the mesh index if know will result in faster additions
	ARGUMENTS:
	-	MyMesh* a_pMesh -> mesh to apply transform to
	-	matrix4 a_m4Transform -> transform to apply
	int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddMeshToRenderList(MyMesh* a_pMesh, matrix4 a_m4Transform);
	/*
	USAGE: Clears the map of transforms
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearRenderList(void);
	/*
	USAGE: Draws all the meshes in the transform map
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Render(void);
	/*
	USAGE: Get the number of meshes in the mesh manager
	ARGUMENTS: ---
	OUTPUT: number of meshes
	*/
	uint GetMeshCount(void);
	/*
	USAGE: Sets the camera to use for mesh drawing
	ARGUMENTS:
	OUTPUT:
	*/
	void SetCamera(MyCamera* a_pCamera);
private:
	//Rule of 3
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	MyMeshManager(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MyMeshManager(MyMeshManager const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MyMeshManager& operator=(MyMeshManager const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyMeshManager(void);
	//Other methods
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

} //namespace Simplex

#endif //__MYMyMeshManager_H_
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/