/** Jonathan So, jds7523@rit.edu
* Prof. Bobadilla
* IGME-309-02
* 19 November 2018
* MyOctant.cpp implements the header file for MyOctantExample.h, renamed in this project to MyOctant.h.
*/
#include "MyOctant.h"
using namespace Simplex;

uint MyOctant::m_uOctantCount = 0;
uint MyOctant::m_uIdealEntityCount = 0;
uint MyOctant::m_uMaxLevel = 0;

MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount) {
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	Init();

	// Replacement for GetEntityList from the in-class demo of C21
	uint count = m_pEntityMngr->GetEntityCount();
	
	std::vector<MyEntity> l_EntityList;
	
	for (uint i = 0; i < count; i++) {
		l_EntityList.push_back(*(m_pEntityMngr->GetEntity(i)));
	}
	std::vector<vector3> minMax;
	// For each rigidbody, find the minimum and maximum coordinates.
	for (uint i = 0; i < count; i++) {
		MyRigidBody* currRB = l_EntityList[i].GetRigidBody();
		vector3 v3Min = currRB->GetMinGlobal();
		vector3 v3Max = currRB->GetMaxGlobal();
		minMax.push_back(v3Min);
		minMax.push_back(v3Max);
	}
	m_pRigidBody = new MyRigidBody(minMax);
	m_pRigidBody->MakeCubic();
	m_uID = m_uOctantCount;
	IsColliding();
	Subdivide();
}

MyOctant::MyOctant(vector3 a_v3Center, float a_fSize) {
	Init();
	std::vector<vector3> minMax;
	minMax.push_back(a_v3Center - vector3(a_fSize));
	minMax.push_back(a_v3Center + vector3(a_fSize));
	m_pRigidBody = new MyRigidBody(minMax);
	m_uOctantCount++;
	IsColliding();
	m_uID = m_uOctantCount;
}

MyOctant::MyOctant(MyOctant const& other) {

}

MyOctant& MyOctant::operator=(MyOctant const& other) {

}

MyOctant::~MyOctant(void) {

}

void MyOctant::Swap(MyOctant& other) {

}

float MyOctant::GetSize(void) {
	return m_fSize;
}

vector3 MyOctant::GetCenterGlobal(void) {
	return m_v3Center;
}

vector3 MyOctant::GetMinGlobal(void) {
	return m_v3Min;
}

vector3 MyOctant::GetMaxGlobal(void) {
	return m_v3Max;
}

// bool MyOctant::IsColliding(uint a_uRBIndex) {
bool MyOctant::IsColliding() {
	// Replacement for GetEntityList from the in-class demo of C21
	uint count = m_pEntityMngr->GetEntityCount();
	std::vector<MyEntity> l_EntityList;
	for (uint i = 0; i < count; i++) {
		l_EntityList.push_back(*(m_pEntityMngr->GetEntity(i)));
	}
	for (uint i = 0; i < count; ++i)
	{
		MyRigidBody* pRB = l_EntityList[i].GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody)) {
			l_EntityList[i].AddDimension(m_uID);
			m_EntityList.push_back(i);
		}
	}
}

void MyOctant::Display(uint a_nIndex, vector3 a_v3Color) {
	
}

void MyOctant::Display(vector3 a_v3Color) {
	m_pRigidBody->AddToRenderList();
	for (uint i = 0; i < 8; i++) {
		if (m_pChild[i])
			m_pChild[i]->Display(a_v3Color);
	}
}

void MyOctant::DisplayLeafs(vector3 a_v3Color) {

}

void MyOctant::ClearEntityList(void) {
	m_EntityList.clear();
	// Base case: if we've reached a leaf node, don't recurse.
	if (IsLeaf()) {
		return;
	}
	// Recursively call this on children.
	for (uint i = 0; i < 8; i++) {
		m_pChild[i]->ClearEntityList();
	}
}

void MyOctant::Subdivide(void) {
	// Subdivide if we've hit the maximum level or if we're under or at the ideal entity count.
	if (m_uLevel > m_uMaxLevel || !ContainsMoreThan(m_uIdealEntityCount)) {
		return;
	}
	vector3 v3Center = m_pRigidBody->GetCenterLocal();
	vector3 v3HalfWidth = m_pRigidBody->GetHalfWidth();
	float fSize = (v3HalfWidth.x) / 2.0f;
	float fCenters = fSize;
	// Figure out the positions of each child octant, first with the front...
	m_pChild[0] = new MyOctant(v3Center + vector3(fCenters, fCenters, fCenters), fSize);
	m_pChild[1] = new MyOctant(v3Center + vector3(-fCenters, fCenters, fCenters), fSize);
	m_pChild[2] = new MyOctant(v3Center + vector3(-fCenters, -fCenters, fCenters), fSize);
	m_pChild[3] = new MyOctant(v3Center + vector3(fCenters, -fCenters, fCenters), fSize);
	// then the back octants.
	m_pChild[4] = new MyOctant(v3Center + vector3(fCenters, fCenters, -fCenters), fSize);
	m_pChild[5] = new MyOctant(v3Center + vector3(-fCenters, fCenters, -fCenters), fSize);
	m_pChild[6] = new MyOctant(v3Center + vector3(-fCenters, -fCenters, -fCenters), fSize);
	m_pChild[7] = new MyOctant(v3Center + vector3(fCenters, -fCenters, -fCenters), fSize);
	// Each of these octants will be set up with a reference to the parent and their level.
	for (uint i = 0; i < 8; i++) {
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->Subdivide();
	}
}

MyOctant* MyOctant::GetChild(uint a_nChild) {
	// Handle the case where a user may accidentally try to request a child out-of-bounds.
	if (a_nChild > 7 || a_nChild < 0) {
		return nullptr;
	}
	return m_pChild[a_nChild];
}

MyOctant* MyOctant::GetParent(void) {
	return m_pParent;
}

bool MyOctant::IsLeaf(void) {
	return m_pChild[0] == nullptr;
}

bool MyOctant::ContainsMoreThan(uint a_nEntities) {
	return m_EntityList.size() > a_nEntities;
}

void MyOctant::KillBranches(void) {
	// Base case: if we've reached a leaf node, don't recurse.
	if (IsLeaf()) {
		for (uint i = 0; i < 8; i++) {
			SafeDelete(m_pChild[i]);
		}
		return;
	}
	// Recursively call this on children.
	for (uint i = 0; i < 8; i++) {
		m_pChild[i]->KillBranches();
	}
}

void MyOctant::ConstructTree(uint a_nMaxLevel) {

}

void MyOctant::AssignIDtoEntity(void) {

}

uint MyOctant::GetOctantCount(void) {
	return m_uOctantCount;
}

void MyOctant::Release(void) {

}

void MyOctant::Init(void) {
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	// Set up null pointers for all children.
	for (uint i = 0; i < 8; i++) {
		m_pChild[i] = nullptr;
	}
}

void MyOctant::ConstructList(void) {

}