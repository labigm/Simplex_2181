#include "MyEntity.h"
using namespace Simplex;
std::map<String, MyEntity*> MyEntity::m_IDMap;
//  Accessors
matrix4 Simplex::MyEntity::GetModelMatrix(void){ return m_m4ToWorld; }
void Simplex::MyEntity::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (!m_bInMemory)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_pModel->SetModelMatrix(m_m4ToWorld);
	m_pRigidBody->SetModelMatrix(m_m4ToWorld);
}
Model* Simplex::MyEntity::GetModel(void){return m_pModel;}
MyRigidBody* Simplex::MyEntity::GetRigidBody(void){	return m_pRigidBody; }
bool Simplex::MyEntity::IsInitialized(void){ return m_bInMemory; }
String Simplex::MyEntity::GetUniqueID(void) { return m_sUniqueID; }
void Simplex::MyEntity::SetAxisVisible(bool a_bSetAxis) { m_bSetAxis = a_bSetAxis; }
//  MyEntity
void Simplex::MyEntity::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();
	m_bInMemory = false;
	m_bSetAxis = false;
	m_pModel = nullptr;
	m_pRigidBody = nullptr;
	m_m4ToWorld = IDENTITY_M4;
	m_sUniqueID = "";
	m_nDimensionCount = 0;
	m_uMainDimension = 0;
}
void Simplex::MyEntity::Swap(MyEntity& other)
{
	m_bInMemory = false;
	std::swap(m_pModel, other.m_pModel);
	std::swap(m_pRigidBody, other.m_pRigidBody);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);
	std::swap(m_pMeshMngr, other.m_pMeshMngr);
	std::swap(m_bInMemory, other.m_bInMemory);
	std::swap(m_sUniqueID, other.m_sUniqueID);
	std::swap(m_bSetAxis, other.m_bSetAxis);
	std::swap(m_DimensionList, other.m_DimensionList);
	std::swap(m_nDimensionCount, other.m_nDimensionCount);
	std::swap(m_uMainDimension, other.m_uMainDimension);
}
void Simplex::MyEntity::Release(void)
{
	m_pMeshMngr = nullptr;
	//it is not the job of the entity to release the model, 
	//it is for the mesh manager to do so.
	m_pModel = nullptr; 
	SafeDelete(m_pRigidBody);
	m_IDMap.erase(m_sUniqueID);
}
//The big 3
Simplex::MyEntity::MyEntity(String a_sFileName, String a_sUniqueID)
{
	Init();
	m_pModel = new Model();
	m_pModel->Load(a_sFileName);
	//if the model is loaded
	if (m_pModel->GetName() != "")
	{
		GenUniqueID(a_sUniqueID);
		m_sUniqueID = a_sUniqueID;
		m_IDMap[a_sUniqueID] = this;
		m_pRigidBody = new MyRigidBody(m_pModel->GetVertexList()); //generate a rigid body
		m_bInMemory = true; //mark this entity as viable
	}
}
Simplex::MyEntity::MyEntity(MyEntity const& other)
{
	m_bInMemory = other.m_bInMemory;
	m_pModel = other.m_pModel;
	//generate a new rigid body we do not share the same rigid body as we do the model
	m_pRigidBody = new MyRigidBody(m_pModel->GetVertexList());
	m_m4ToWorld = other.m_m4ToWorld;
	m_pMeshMngr = other.m_pMeshMngr;
	m_sUniqueID = other.m_sUniqueID;
	m_bSetAxis = other.m_bSetAxis;
	m_DimensionList = other.m_DimensionList;
	m_nDimensionCount = other.m_nDimensionCount;
	m_uMainDimension = other.m_uMainDimension;
}
MyEntity& Simplex::MyEntity::operator=(MyEntity const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyEntity temp(other);
		Swap(temp);
	}
	return *this;
}
MyEntity::~MyEntity(){Release();}
//--- Methods
void Simplex::MyEntity::AddToRenderList(bool a_bDrawRigidBody)
{
	//if not in memory return
	if (!m_bInMemory)
		return;

	//draw model
	m_pModel->AddToRenderList();
	
	//draw rigid body
	if(a_bDrawRigidBody)
		m_pRigidBody->AddToRenderList();

	if (m_bSetAxis)
		m_pMeshMngr->AddAxisToRenderList(m_m4ToWorld);
}
MyEntity* Simplex::MyEntity::GetEntity(String a_sUniqueID)
{
	//look the entity based on the unique id
	auto entity = m_IDMap.find(a_sUniqueID);
	//if not found return nullptr, if found return it
	return entity == m_IDMap.end() ? nullptr : entity->second;
}
void Simplex::MyEntity::GenUniqueID(String& a_sUniqueID)
{
	static uint index = 0;
	String sName = a_sUniqueID;
	MyEntity* pEntity = GetEntity(a_sUniqueID);
	//while MyEntity exists keep changing name
	while (pEntity)
	{
		a_sUniqueID = sName + "_" + std::to_string(index);
		index++;
		pEntity = GetEntity(a_sUniqueID);
	}
	return;
}
void Simplex::MyEntity::AddDimension(uint a_uDimension)
{
	//we need to check that this dimension is not already allocated in the list
	if (IsInDimension(a_uDimension))
		return;//it is, so there is no need to add

	//insert the entry
	m_DimensionList.push_back(a_uDimension);
	++m_nDimensionCount;

	m_uMainDimension = m_DimensionList[0];
}
void Simplex::MyEntity::RemoveDimension(uint a_uDimension)
{
	//if there are no dimensions return
	if (m_DimensionList.size() == 0)
		return;

	//if the last dimension in the list is the one we pop from the list
	if (m_DimensionList[m_DimensionList.size() -1] == a_uDimension)
	{
		m_DimensionList.pop_back();
		--m_nDimensionCount;
		//if there is still dimensions in the list make the main dimension the first
		if(m_nDimensionCount > 0)
			m_uMainDimension = m_DimensionList[0];
		else //if there are not then make it the special dimension
			m_uMainDimension = 0;
		return;
	}
	//If we continue we look one by one if its the one wanted
	for (uint i = 0; i < m_DimensionList.size(); i++)
	{
		if (m_DimensionList[i] == a_uDimension)
		{
			//if it is, then we swap it with the last one and then we pop
			std::swap(m_DimensionList[i], m_DimensionList[m_DimensionList.size() - 1]);
			m_DimensionList.pop_back();
			--m_nDimensionCount;
			//if there is still dimensions in the list make the main dimension the first
			if (m_nDimensionCount > 0)
				m_uMainDimension = m_DimensionList[0];
			else //if there are not then make it the special dimension
				m_uMainDimension = 0;
			return;
		}
	}
}
void Simplex::MyEntity::ClearDimensionSet(void)
{
	m_DimensionList.clear();
	m_nDimensionCount = 0;
	m_uMainDimension = 0;
}
bool Simplex::MyEntity::IsInDimension(uint a_uDimension)
{
	//see if the entry is in the set
	for (uint i = 0; i < m_DimensionList.size(); i++)
	{
		if (m_DimensionList[i] == a_uDimension)
			return true;
	}
	return false;
}
bool Simplex::MyEntity::SharesDimension(MyEntity* const a_pOther)
{
	//special case: if there are no dimensions on either MyEntity
	//if both entities have no dimension set then they live in the special global dimension
	if (0 == m_nDimensionCount)
	{
		//if no spatial optimization all cases should fall here as every 
		//entity is by default, under the special global dimension only
		if(0 == a_pOther->m_nDimensionCount)
			return true;
	}

	//special case if there are only one dimension on each MyEntity
	if (1 == m_nDimensionCount)
	{
		if (1 == a_pOther->m_nDimensionCount)
		{
			//as there is only one dimension we check the main dimension only
			return m_uMainDimension == a_pOther->m_uMainDimension;
		}
	}
	
	//we tried to avoid this case as indexing is more expensive
	//for each dimension on both Entities we check if there is a common dimension
	for (uint i = 0; i < m_nDimensionCount; ++i)
	{
		for (uint j = 0; j < a_pOther->m_nDimensionCount; j++)
		{
			if (m_DimensionList[i] == a_pOther->m_DimensionList[j])
				return true; //as soon as we find one we know they share dimensionality
		}
	}

	//could not find a common dimension
	return false;
}
bool Simplex::MyEntity::IsColliding(MyEntity* const other)
{
	//if not in memory return
	if (!m_bInMemory || !other->m_bInMemory)
		return true;

	//if the entities are not living in the same dimension
	//they are not colliding
	if (!SharesDimension(other))
		return false;

	return m_pRigidBody->IsColliding(other->GetRigidBody());
}
void Simplex::MyEntity::ClearCollisionList(void)
{
	m_pRigidBody->ClearCollidingList();
}