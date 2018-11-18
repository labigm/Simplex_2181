#include "MyOctant.h"
using namespace Simplex;
//  MyOctant
void MyOctant::Init(void)
{
	m_nData = 0;
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	std::vector<MyEntity*> l_Entity_List = m_pEntityMngr->GetEntityList();
	uint iEntityCount = l_Entity_List.size();
	std::vector<vector3> v3MaxMin_list;
	for (uint i = 0; i < iEntityCount; i++) {
		MyRigidBody* pRB = l_Entity_List[i]->GetRigidBody();
		vector3 v3Min = pRB->GetMinGlobal();
		vector3 v3Max = pRB->GetMaxGlobal();
		v3MaxMin_list.push_back(v3Min);
		v3MaxMin_list.push_back(v3Max);
		/*
		vector3 v3Position - pRB->GetCenterGlobal();
		if (v3Position.x < 0.0f)
		{
		if (v3Position.x < -17.0f)
		m_pEntityMngr->AddDimension(i, 1);
		else
		m_pEntityMngr->AddDimension(i, 2);
		}
		else if (v3Position.x > 0.0f)
		{
		if (v3Position.x > 17.0f)
		m_pEntityMngr->AddDimension(i, 3);
		else
		m_pEntityMngr->AddDimension(i, 4);
		}
		*/
	}
	for (uint i = 0; i < 8; i++ {
		m_pChild[i] = nullptr;
	})
	m_pRigidBody = new RigidBody(v3MaxMin_list); // Audomatically gives us a max and min.
}
void MyOctant::Swap(MyOctant& other)
{
	std::swap(m_nData, other.m_nData);
	std::swap(m_lData, other.m_lData);
}
void MyOctant::Release(void)
{
	m_lData.clear();
}
void Simplex::MyOctant::Display(void)
{
	m_pRigidBody->AddToRenderList();
	//m_pMeshMngr->AddWireCubeToRenderList(glm::scale(vector3(70)), C_YELLOW));
}
void Simplex::MyOctant::IsColliding(void){
	std::vector<MyEntity*> l_Entity_List = m_pEntityMngr->GetEntityList();
	uint iEntityCount = l_Entity_List.size();
	for (uint i = 0; i < iEntityCount; i++) {
		MyRigidBody* pRB = l_Entity_List[i]->GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody)) {
			l_Entity_List[i]->AddDimension(m_iId);
		}
	}
}

void Simplex::MyOctant::Subdivide(void) {
	for (int i = 0; i < 8; i++) {
		m_pChild[i] = new MyOctant();
		// W I L L   C R E A T E   A N    E N D L E S S   L O O P 
	}
	
}

//The big 3
MyOctant::MyOctant(){Init();}
MyOctant::MyOctant(MyOctant const& other)
{
	m_nData = other.m_nData;
	m_lData = other.m_lData;
}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant(){Release();};
//Accessors
void MyOctant::SetData(int a_nData){ m_nData = a_nData; }
int MyOctant::GetData(void){ return m_nData; }
void MyOctant::SetDataOnVector(int a_nData){ m_lData.push_back(a_nData);}
int& MyOctant::GetDataOnVector(int a_nIndex)
{
	int nIndex = static_cast<int>(m_lData.size());
	assert(a_nIndex >= 0 && a_nIndex < nIndex);
	return m_lData[a_nIndex];
}
//--- Non Standard Singleton Methods

