#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_uEntityCount = 0;
	m_mEntityArray = nullptr;
	m_EntityList.clear();
}
void MyEntityManager::Release(void)
{
	for (uint uEntity = 0; uEntity < m_uEntityCount; ++uEntity)
	{
		MyEntity* pEntity = m_EntityList[uEntity];
		SafeDelete(pEntity);
	}
	m_uEntityCount = 0;
	m_EntityList.clear();
	m_mEntityArray = nullptr;
}
std::vector<MyEntity*> Simplex::MyEntityManager::GetEntityList(void)
{
	return m_EntityList;
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	//look one by one for the specified unique id
	for (uint uIndex = 0; uIndex < m_uEntityCount; ++uIndex)
	{
		if (a_sUniqueID == m_EntityList[uIndex]->GetUniqueID())
			return uIndex;
	}
	//if not found return -1
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_EntityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModel();
	}
	return nullptr;
}
MyRigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_EntityList[a_uIndex]->GetRigidBody();
}
MyRigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetRigidBody();
	}
	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return IDENTITY_M4;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_EntityList[a_uIndex]->GetModelMatrix();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModelMatrix();
	}
	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetModelMatrix(a_m4ToWorld);
	}
}
void Simplex::MyEntityManager::SetAxisVisibility(bool a_bVisibility, uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_EntityList[a_uIndex]->SetAxisVisible(a_bVisibility);
}
void Simplex::MyEntityManager::SetAxisVisibility(bool a_bVisibility, String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetAxisVisible(a_bVisibility);
	}
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount -1;

	m_EntityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& a_pOther){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& a_pOther) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{
	//Clear all collisions
	for (uint i = 0; i < m_uEntityCount; i++)
	{
		m_EntityList[i]->ClearCollisionList();
	}

	//check collisions
	for (uint i = 0; i < m_uEntityCount - 1; i++)
	{
		for (uint j = i + 1; j < m_uEntityCount; j++)
		{
			m_mEntityArray[i]->IsColliding(m_mEntityArray[j]);
		}
	}
}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	//Create a temporal entity to store the object
	MyEntity* pTemp = new MyEntity(a_sFileName, a_sUniqueID);
	//if I was able to generate it add it to the list
	if (pTemp->IsInitialized())
	{
		m_EntityList.push_back(pTemp);
		m_uEntityCount = m_EntityList.size();
	}

	SafeDelete(m_mEntityArray);
	m_mEntityArray = new PEntity[m_EntityList.size()];
	for (uint i = 0; i < m_EntityList.size(); ++i)
	{
		m_mEntityArray[i] = m_EntityList[i];
	}
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return;

	// if out of bounds choose the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	// if the entity is not the very last we swap it for the last one
	if (a_uIndex != m_uEntityCount - 1)
	{
		std::swap(m_EntityList[a_uIndex], m_EntityList[m_uEntityCount - 1]);
	}
	
	//and then pop the last one
	MyEntity* pTemp = m_EntityList[m_uEntityCount - 1];
	SafeDelete(pTemp);
	m_EntityList.pop_back();
	--m_uEntityCount;

	SafeDelete(m_mEntityArray);
	m_mEntityArray = new PEntity[m_EntityList.size()];
	for (uint i = 0; i < m_EntityList.size(); ++i)
	{
		m_mEntityArray[i] = m_mEntityArray[i];
	}
	return;
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	int nIndex = GetEntityIndex(a_sUniqueID);
	RemoveEntity((uint)nIndex);
	SafeDelete(m_mEntityArray);
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return "";
	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;
	return m_EntityList[a_uIndex]->GetUniqueID();
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_EntityList.size() == 0)
		return nullptr;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex];
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	//if out of bounds will do it for all
	if (a_uIndex >= m_uEntityCount)
	{
		//add for each one in the entity list
		for (a_uIndex = 0; a_uIndex < m_uEntityCount; ++a_uIndex)
		{
			m_EntityList[a_uIndex]->AddToRenderList(a_bRigidBody);
		}
	}
	else //do it for the specified one
	{
		m_EntityList[a_uIndex]->AddToRenderList(a_bRigidBody);
	}
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddToRenderList(a_bRigidBody);
	}
}
void Simplex::MyEntityManager::AddDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex]->AddDimension(a_uDimension);
}
void Simplex::MyEntityManager::AddDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddDimension(a_uDimension);
	}
}
void Simplex::MyEntityManager::RemoveDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex]->RemoveDimension(a_uDimension);
}
void Simplex::MyEntityManager::RemoveDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->RemoveDimension(a_uDimension);
	}
}
void Simplex::MyEntityManager::ClearDimensionSet(uint a_uIndex)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex]->ClearDimensionSet();
}
void Simplex::MyEntityManager::ClearDimensionSet(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->ClearDimensionSet();
	}
}
bool Simplex::MyEntityManager::IsInDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex]->IsInDimension(a_uDimension);
}
bool Simplex::MyEntityManager::IsInDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->IsInDimension(a_uDimension);
	}
	return false;
}
bool Simplex::MyEntityManager::SharesDimension(uint a_uIndex, MyEntity* const a_pOther)
{
	//if the list is empty return
	if (m_EntityList.size() == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_EntityList.size())
		a_uIndex = m_EntityList.size() - 1;

	return m_EntityList[a_uIndex]->SharesDimension(a_pOther);
}
bool Simplex::MyEntityManager::SharesDimension(String a_sUniqueID, MyEntity* const a_pOther)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->SharesDimension(a_pOther);
	}
	return false;
}