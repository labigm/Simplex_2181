/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/07
----------------------------------------------*/
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyRigidBody.h"

namespace Simplex
{

//System Class
class MyEntity
{
	bool m_bInMemory = false; //loaded flag
	bool m_bSetAxis = false; //render axis flag
	String m_sUniqueID = ""; //Unique identifier name

	uint m_uMainDimension = 0; //which is the dimension this object lives at
	uint m_nDimensionCount = 0; //tells how many dimensions this entity lives in
	std::vector<uint> m_DimensionList; //Dimensions on which this entity is located

	Model* m_pModel = nullptr; //Model associated with this MyEntity
	MyRigidBody* m_pRigidBody = nullptr; //Rigid Body associated with this MyEntity

	matrix4 m_m4ToWorld = IDENTITY_M4; //Model matrix associated with this MyEntity
	MeshManager* m_pMeshMngr = nullptr; //For rendering shapes

	static std::map<String, MyEntity*> m_IDMap; //a map of the unique ID's

public:
	/*
	Usage: Constructor that specifies the name attached to the MyEntity
	Arguments:
	-	String a_sFileName -> Name of the model to load
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	Output: class object instance
	*/
	MyEntity(String a_sFileName, String a_sUniqueID = "NA");
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyEntity(MyEntity const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyEntity& operator=(MyEntity const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyEntity(void);
	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	void Swap(MyEntity& other);
	/*
	USAGE: Gets the model matrix associated with this entity
	ARGUMENTS: ---
	OUTPUT: model to world matrix
	*/
	matrix4 GetModelMatrix(void);
	/*
	USAGE: Sets the model matrix associated with this entity
	ARGUMENTS: matrix4 a_m4ToWorld -> model matrix to set
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: ---
	OUTPUT: Model
	*/
	Model* GetModel(void);
	/*
	USAGE: Gets the Rigid Body associated with this entity
	ARGUMENTS: ---
	OUTPUT: Rigid Body
	*/
	MyRigidBody* GetRigidBody(void);
	/*
	USAGE: Will reply to the question, is the MyEntity Initialized?
	ARGUMENTS: ---
	OUTPUT: initialized?
	*/
	bool IsInitialized(void);
	/*
	USAGE: Adds the entity to the render list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddToRenderList(bool a_bDrawRigidBody = false);
	/*
	USAGE: Tells if this entity is colliding with the incoming one
	ARGUMENTS: MyEntity* const other -> inspected entity
	OUTPUT: are they colliding?
	*/
	bool IsColliding(MyEntity* const other);
	/*
	USAGE: Gets the MyEntity specified by unique ID, nullptr if not exists
	ARGUMENTS: String a_sUniqueID -> unique ID if the queried entity
	OUTPUT: MyEntity specified by unique ID, nullptr if not exists
	*/
	static MyEntity* GetEntity(String a_sUniqueID);
	/*
	USAGE: Will generate a unique id based on the name provided
	ARGUMENTS: String& a_sUniqueID -> desired name
	OUTPUT: will output though the argument
	*/
	void GenUniqueID(String& a_sUniqueID);
	/*
	USAGE: Gets the Unique ID name of this model
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	String GetUniqueID(void);
	/*
	USAGE: Sets the visibility of the axis of this MyEntity
	ARGUMENTS: bool a_bSetAxis = true -> axis visible?
	OUTPUT: ---
	*/
	void SetAxisVisible(bool a_bSetAxis = true);
	/*
	USAGE: Will set a dimension to the MyEntity
	ARGUMENTS: uint a_uDimension -> dimension to set
	OUTPUT: ---
	*/
	void AddDimension(uint a_uDimension);
	/*
	USAGE: Will remove the entity from the specified dimension
	ARGUMENTS: uint a_uDimension -> dimension to remove
	OUTPUT: ---
	*/
	void RemoveDimension(uint a_uDimension);
	/*
	USAGE: will remove all dimensions from entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearDimensionSet(void);
	/*
	USAGE: Will ask if the MyEntity is located in a particular dimension
	ARGUMENTS: uint a_uDimension -> dimension queried
	OUTPUT: result
	*/
	bool IsInDimension(uint a_uDimension);
	/*
	USAGE: Asks if this entity shares a dimension with the incoming one
	ARGUMENTS: MyEntity* const a_pOther -> queried entity
	OUTPUT: shares at least one dimension?
	*/
	bool SharesDimension(MyEntity* const a_pOther);

	/*
	USAGE: Clears the collision list of this entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearCollisionList(void);

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

#endif //__MYENTITY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/