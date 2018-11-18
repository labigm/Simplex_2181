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

/** Constructor: creates an octant which contains all entities in the scene.
  * param[a_nMaxLevel] - the maximum level of subdivisions. Default = 2.
  * param[a_nIdealEntityCount] - Ideal number of entities per octant. Default = 5.
  */
Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount) {
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	Init();
	std::vector<MyEntity*> l_EntityList = m_pEntityMngr->GetEntityList();
	uint count = l_EntityList.size();
	std::vector<vector3> minMax;
	// For each rigidbody, find the minimum and maximum coordinates.
	for (uint i = 0; i < count; i++) {
		MyRigidBody* currRB = l_EntityList[i]->GetRigidBody();
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

/** Make an octant by calculating the minimum and maximum points.
* param[a_v3Center] - center of the octant, globalized.
* param[a_fSize] - size of each side of the octant volume.
*/
Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize) {
	Init();
	std::vector<vector3> minMax; 
	minMax.push_back(a_v3Center - vector3(a_fSize)); 
	minMax.push_back(a_v3Center + vector3(a_fSize));
	m_pRigidBody = new MyRigidBody(minMax);
	m_uOctantCount++;
	IsColliding();
	m_uID = m_uOctantCount;
}

// #TODO
/** Copy constructor
*
*/
Simplex::MyOctant::MyOctant(MyOctant const & other)
{
}

// #TODO
// copy assignment operator
MyOctant & Simplex::MyOctant::operator=(MyOctant const & other)
{
	// TODO: insert return statement here
}

// #TODO
// Destructor
Simplex::MyOctant::~MyOctant(void)
{
}

// #TODO
// Swaps this octant's data for another one's.
// param[other] - the octant we want to swap data with.
void Simplex::MyOctant::Swap(MyOctant & other) {
}

/** Gets this octant's size.
 * return - the size of the octant.
 */
float Simplex::MyOctant::GetSize(void) {
	return m_fSize;
}

/** Gets the center point of the octant, globalized.
* return - the center point of the octant, globalized.
*/
vector3 Simplex::MyOctant::GetCenterGlobal(void) {
	return m_v3Center;
}

/** Gets the minimum corner of the octant, globalized.
* return - the minimum corner of the octant, globalized.
*/
vector3 Simplex::MyOctant::GetMinGlobal(void) {
	return m_v3Min;
}

/** Gets the maximum corner of the octant, globalized.
 * return - the maximum corner of the octant, globalized.
 */
vector3 Simplex::MyOctant::GetMaxGlobal(void) {
	return m_v3Max;
}

/** Checks to see if our RigidBody is colliding with another one.
 * param[a_uRBIndex] - the index of the RigidBody that we may or may not be colliding with.
 * return - whether or not our RB is colliding with the other RB.
 */
// bool Simplex::MyOctant::IsColliding(uint a_uRBIndex) {
bool Simplex::MyOctant::IsColliding() {
	std::vector<MyEntity*> l_EntityList = m_pEntityMngr->GetEntityList();

	uint count = l_EntityList.size();
	for (uint i = 0; i < count; ++i)
	{
		MyRigidBody* pRB = l_EntityList[i]->GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody)) {
			l_EntityList[i]->AddDimension(m_uID);
			m_EntityList.push_back(i);
		}
	}
}

// #TODO
// Displays a MyOctant as specified by index and color, including the octant's decendants.
// param[a_nIndex] - the octant we want to display.
// param[a_v3Color] - the color of the volume to display. By default, it's yellow.
void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color) {

}
// Displays this octant in the color specified.
// param[a_v3Color] - the color of the volume to display. By default, it's yellow.
void Simplex::MyOctant::Display(vector3 a_v3Color) {
	m_pRigidBody->AddToRenderList();
	for (uint i = 0; i < 8; i++) {
		if (m_pChild[i])
			m_pChild[i]->Display(a_v3Color);
	}
}

// #TODO
// Display all non-empty leaves in the octree.
// param[a_v3Color] - the color of the volume to display. By default, it's yellow.
void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color) {
}

// Clears the Entity List for each node.
void Simplex::MyOctant::ClearEntityList(void) {
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

/** Allocates 8 smaller octants in the child pointers.
 *
 */
void Simplex::MyOctant::Subdivide(void){
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

// Returns the child as specified by index.
// param[a_nChild] - the index of the requested child, from 0 to 7.
// return - a MyOctant child or a nullptr.
MyOctant * Simplex::MyOctant::GetChild(uint a_nChild) {
	// Handle the case where a user may accidentally try to request a child out-of-bounds.
	if (a_nChild > 7 || a_nChild < 0) {
		return nullptr;
	}
	return m_pChild[a_nChild];
}
 
// Returns the parent of this octant.
// return - the parent MyOctant.
MyOctant * Simplex::MyOctant::GetParent(void) {
	return m_pParent;
}

// Asks if this octant is a leaf. (Has no children)
// return - whether or not this octant is a leaf.
bool Simplex::MyOctant::IsLeaf(void) {
	return m_pChild[0] == nullptr; 
}

// Asks if MyOctant contains more than a specified number of bounding objects.
// param[a_nEntities] - the number of entities we want to check against.
// return - whether or not this octant contains more than the specified number of entities.
bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities) {
	return m_EntityList.size() > a_nEntities;
}

// Recursively deletes all children and their children.
void Simplex::MyOctant::KillBranches(void) {
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

// #TODO
/** Create a tree using subdivisions, the max number of objects and levels
 * param[a_nMaxLevel = 3] - Sets the max level of the tree while constructing it. Default is 3.
 */
void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel) {
}

// #TODO
/** Traverse the tree up to the leaves and sets the objects in them to the index.
* 
*/
void Simplex::MyOctant::AssignIDtoEntity(void) {
}

/** Get the total number of octants in the world.
 * return - number of octants in the world.
 */
uint Simplex::MyOctant::GetOctantCount(void) {
	return m_uOctantCount;
}

// #TODO
 // Deallocates member fields.
void Simplex::MyOctant::Release(void) {

}

// Allocates member fields.
void Simplex::MyOctant::Init(void){
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	// Set up null pointers for all children.
	for (uint i = 0; i < 8; i++) {
		m_pChild[i] = nullptr;
	}
	
}

// #TODO
// Creates the list of all leaves that contain objects.
void Simplex::MyOctant::ConstructList(void) {
	
}

