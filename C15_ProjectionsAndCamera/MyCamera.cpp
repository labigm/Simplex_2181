#include "MyCamera.h"
using namespace Simplex;

//Accessors
void Simplex::MyCamera::SetPosition(vector3 a_v3Position) { m_v3Position = a_v3Position; }
vector3 Simplex::MyCamera::GetPosition(void) { return m_v3Position; }

void Simplex::MyCamera::SetTarget(vector3 a_v3Target) { m_v3Target = a_v3Target; }
vector3 Simplex::MyCamera::GetTarget(void) { return m_v3Target; }

void Simplex::MyCamera::SetUp(vector3 a_v3Up) { m_v3Up = a_v3Up; }
vector3 Simplex::MyCamera::GetUp(void) { return m_v3Up; }

matrix4 Simplex::MyCamera::GetProjectionMatrix(void) { return m_m4Projection; }
matrix4 Simplex::MyCamera::GetViewMatrix(void) { CalculateViewMatrix(); return m_m4View; }

Simplex::MyCamera::MyCamera()
{
	Init(); //Init the object with default values
}

Simplex::MyCamera::MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	Init(); //Initialize the object
	SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward); //set the position, target and up
}

Simplex::MyCamera::MyCamera(MyCamera const& other)
{
	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Up = other.m_v3Up;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightwart = other.m_v3Rightwart;

	m_m4View = other.m_m4View;
	m_m4Projection = other.m_m4Projection;
}

MyCamera& Simplex::MyCamera::operator=(MyCamera const& other)
{
	if (this != &other)
	{
		Release();
		SetPositionTargetAndUpward(other.m_v3Position, other.m_v3Target, other.m_v3Upward);
		MyCamera temp(other);
		Swap(temp);
	}
	return *this;
}

void Simplex::MyCamera::Init(void)
{
	ResetCamera();
	CalculateProjectionMatrix();
	CalculateViewMatrix();
	//No pointers to initialize here
}

void Simplex::MyCamera::Release(void)
{
	//No pointers to deallocate yet
}

void Simplex::MyCamera::Swap(MyCamera & other)
{
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Up, other.m_v3Up);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightwart, other.m_v3Rightwart);

	std::swap(m_m4View, other.m_m4View);
	std::swap(m_m4Projection, other.m_m4Projection);
}

Simplex::MyCamera::~MyCamera(void)
{
	Release();
}

void Simplex::MyCamera::ResetCamera(void)
{
	m_v3Position = vector3(0.0f, 0.0f, 10.0f); //Where my camera is located
	m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What I'm looking at
	m_v3Up = vector3(0.0f, 1.0f, 0.0f); //What is up

	m_v3Forward = vector3(0.0f, 0.0f, -1.0f); //View vector
	m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //where my head is pointing up
	m_v3Rightwart = vector3(0.0f, 1.0f, 0.0f); //What is to my right
}

void Simplex::MyCamera::SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_v3Position = a_v3Position;
	m_v3Target = a_v3Target;
	m_v3Up = a_v3Upward;
}

void Simplex::MyCamera::CalculateViewMatrix(void)
{
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Up);
}

void Simplex::MyCamera::CalculateProjectionMatrix(void)
{
	//perspective
	float fRatio = 1280.0f / 720.0f;
	m_m4Projection = glm::perspective(45.0f, fRatio, 0.001f, 1000.0f);
	//m_m4Projection = glm::ortho(-5.0f * fRatio, 5.0f * fRatio, -5.0f, 5.0f, 0.001f, 1000.0f);
}
