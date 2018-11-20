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

// Root constructor. 
MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount) {
	Init();
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_pRoot = this;
	// Find the minimum and maximum bounds for the root octant.
	std::vector<vector3> minMax;
	// Replacement for GetEntityList from the in-class demo of C21
	uint count = m_pEntityMngr->GetEntityCount();
	for (uint i = 0; i < count; i++) {
		MyEntity* currEntity = m_pEntityMngr->GetEntity(i);
		MyRigidBody* currRB = currEntity->GetRigidBody();
		minMax.push_back(currRB->GetMinGlobal());
		minMax.push_back(currRB->GetMinGlobal());
	}
	// The octant will be bounded by these minMax values.
	m_pRigidBody = new MyRigidBody(minMax);
	m_pRigidBody->MakeCubic();

	m_fSize = m_pRigidBody->GetHalfWidth().x;
	m_v3Center = m_pRigidBody->GetCenterGlobal();

	m_uID = m_uOctantCount;
	m_uOctantCount++;	
	ClearEntityList();
	AssignIDtoEntity();
	Subdivide();
	Display(); 
}

// Constructor based on position.
MyOctant::MyOctant(vector3 a_v3Center, float a_fSize) {
	Init();
	// Manually determine the min and max points, and construct the RB out of that.
	std::vector<vector3> minMax; 
	minMax.push_back(a_v3Center - vector3(a_fSize));
	minMax.push_back(a_v3Center + vector3(a_fSize));
	m_pRigidBody = new MyRigidBody(minMax);
	m_uID = m_uOctantCount;
	m_uOctantCount++;
	ClearEntityList();
	AssignIDtoEntity();
}

// Copy Constructor.
MyOctant::MyOctant(MyOctant const& other) {
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = other.m_uChildren;

	m_fSize = other.m_fSize;
	// These won't change
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pRigidBody = other.m_pRigidBody;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_pParent = other.m_pParent;
	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;

	for (uint i = 0; i < m_uChildren; i++) {
		m_pChild[i] = other.m_pChild[i];
	}
}

// Copy Assignment Operator.
MyOctant& MyOctant::operator=(MyOctant const& other) {
	if (this == &other) {
		return *this;
	}
	Release();
	Init();
	MyOctant swap(other);
	Swap(swap);
	return *this;
}

// Destructor calls the Release function.
MyOctant::~MyOctant(void) {
	Release();
}

// Changes this octant's contents for another's.
void MyOctant::Swap(MyOctant& other) {
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_fSize, other.m_fSize);
	// These won't change
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	std::swap(m_pRigidBody, other.m_pRigidBody);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_pParent, other.m_pParent);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);

	for (uint i = 0; i < m_uChildren; i++) {
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
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

// Is this octant colliding with a certain RB in our entity list?
bool MyOctant::IsColliding(uint a_uRBIndex) {
	return m_pEntityMngr->GetRigidBody(a_uRBIndex)->IsColliding(m_pRigidBody);
}

// Display a certain octant and its children.
void MyOctant::Display(uint a_nIndex, vector3 a_v3Color) {
	// See if this octant's ID matches the desired index.
	if (a_nIndex == m_uID) {
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize, m_fSize, m_fSize)), a_v3Color, 1);
		return;
	}
	// Otherwise, look for the matching octant within this octant's children.
	for (uint i = 0; i < m_uChildren; i++) {
		m_pChild[i]->Display(a_nIndex, a_v3Color); // Recursive call
	}
}

// Display this octant and its children.
void MyOctant::Display(vector3 a_v3Color) {
	m_pRigidBody->AddToRenderList();
	for (uint i = 0; i < m_uChildren; i++) {
		m_pChild[i]->Display(a_v3Color); // Recursive call
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize, m_fSize, m_fSize)), a_v3Color, 1);
}

// Display only the non-empty leaves in the octree.
void MyOctant::DisplayLeafs(vector3 a_v3Color) {
	for (uint i = 0; i < m_uChildren; i++) {
		if (!m_pChild[i]->IsLeaf()) {
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize, m_fSize, m_fSize)), a_v3Color, 1);
		}
		m_pChild[i]->DisplayLeafs(a_v3Color);
	}
}

// Clears the entity list for each node.
void MyOctant::ClearEntityList(void) {
	m_EntityList.clear();
	// Base case: if we've reached a leaf node, don't recurse.
	if (IsLeaf()) {
		return;
	}
	// Recursively call this on children.
	for (uint i = 0; i < m_uChildren; i++) {
		m_pChild[i]->ClearEntityList();
	}
}

// Recursively allocates 8 smaller octants in child pointers.
void MyOctant::Subdivide(void) {
	// Do not subdivide if we've hit the maximum level or if this octant already has children
	if (m_uLevel > m_uMaxLevel || m_uChildren > 0) {
		return;
	}
	vector3 v3Center = m_pRigidBody->GetCenterLocal();
	vector3 v3HalfWidth = m_pRigidBody->GetHalfWidth();
	float fSize = (v3HalfWidth.x) / 2.0f;
	float fCenters = fSize;
	m_uChildren = 8; 
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
	for (uint i = 0; m_uChildren < 8; i++) {
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		m_pChild[i]->m_pParent = this;
		// Make sure not to subdivide if the child has the correct number of entities (or less).
		if (m_pChild[i]->ContainsMoreThan(m_uIdealEntityCount)) {
			m_pChild[i]->Subdivide();
		}
	}
}

// Return a child octant given an index, and will return nullptr if the index is out of bounds.
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
	return m_uChildren <= 0;
}

// Whether or not this octant contains more than a specified number of entities.
bool MyOctant::ContainsMoreThan(uint a_nEntities) {
	return m_EntityList.size() > a_nEntities;
}

// Recursively deletes children.
void MyOctant::KillBranches(void) {
	// Recursively call this on children.
	for (uint i = 0; i < m_uChildren; i++) { // This solution handles the case when m_uChildren = 0.
		m_pChild[i]->KillBranches();
		delete(m_pChild[i]);
		m_pChild[i] = nullptr;
	}
	m_uChildren = 0;
}

// Creates a tree using subdivisions at the maximum level of the tree.
void MyOctant::ConstructTree(uint a_nMaxLevel) {
	
}

// For each object in a leaf, assign it one or more IDs for collision detection.
void MyOctant::AssignIDtoEntity(void) {
	// Keep traversing the tree down to its leaves.
	for (uint i = 0; i < m_uChildren; i++) {
		m_pChild[i]->AssignIDtoEntity(); 
	}
	// We've reached a leaf.
	if (IsLeaf()) {
		uint count = m_pEntityMngr->GetEntityCount();
		for (uint i = 0; i < count; i++) {
			if (IsColliding(i)) {
				m_EntityList.push_back(i);
				m_pEntityMngr->AddDimension(i, m_uID);
			}
		}
	}
}

uint MyOctant::GetOctantCount(void) {
	return m_uOctantCount;
}

void MyOctant::Release(void) {
	m_pRoot->KillBranches();
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
	// Recursively construct the list and check if leaves contain objects.
	for (uint i = 0; i < m_uChildren; i++) { 
		m_pChild[i]->ConstructList();
	}
	if (m_EntityList.size() > 0) { // Leaf has children
		m_pRoot->m_lChild.push_back(this);
	}
}
