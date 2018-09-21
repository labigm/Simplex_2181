#include "BasicX\Camera\Camera.h"
using namespace BasicX;
//  Camera
void Camera::Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_bFPS = true;
	m_nMode = BTO_CAMERAMODE::CAM_PERSP;
	m_fFOV = 45.0f;
	m_v2NearFar = vector2(0.001f, 1000.0f);
	m_v3PitchYawRoll = vector3(0.0f);

	m_bInternalCalculation = true;

	return SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward);
}
void Camera::Swap(Camera& other)
{
	std::swap(m_bFPS, other.m_bFPS);

	std::swap(m_nMode, other.m_nMode);

	std::swap(m_fFOV, other.m_fFOV);

	std::swap(m_v2NearFar, other.m_v2NearFar);

	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Above, other.m_v3Above);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightward, other.m_v3Rightward);

	std::swap(m_v3PitchYawRoll, other.m_v3PitchYawRoll);

	std::swap(m_m4Projection, other.m_m4Projection);
	std::swap(m_m4View, other.m_m4View);
}
void Camera::Release(void){}
//The big 3
Camera::Camera()
{
	Init(vector3(0.0f, 0.0f, 5.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f));
}
Camera::Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	Init(a_v3Position, a_v3Target, a_v3Upward);
}
Camera::Camera(Camera const& other)
{
	m_bFPS = other.m_bFPS;

	m_nMode = other.m_nMode;

	m_fFOV = other.m_fFOV;

	m_v2NearFar = other.m_v2NearFar;

	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Above = other.m_v3Above;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightward = other.m_v3Rightward;

	m_v3PitchYawRoll = other.m_v3PitchYawRoll;

	m_m4Projection = other.m_m4Projection;
	m_m4View = other.m_m4View;
}
Camera& Camera::operator=(Camera const& other)
{
	if (this != &other)
	{
		Release();
		Init(other.m_v3Position, other.m_v3Target, other.m_v3Upward);
		Camera temp(other);
		Swap(temp);
	}
	return *this;
}
Camera::~Camera(){ Release(); };
//Accessors
vector3 Camera::GetPosition(void){ return m_v3Position; }
vector3 Camera::GetForward(void) { return m_v3Forward; }
vector3 Camera::GetUpward(void) { return m_v3Upward; }
vector3 Camera::GetRightward(void) { return m_v3Rightward; }
void Camera::SetForward(vector3 a_v3Input) { m_v3Forward = a_v3Input; }
void Camera::SetUpward(vector3 a_v3Input) { m_v3Upward = a_v3Input; }
void Camera::SetRightward(vector3 a_v3Input) { m_v3Rightward = a_v3Input; }
matrix4 Camera::GetViewMatrix(void){ CalculateView(); return m_m4View; }
matrix4 Camera::GetProjectionMatrix(void){ CalculateProjection(); return m_m4Projection; }
void Camera::SetNearFarPlanes(float a_fNear, float a_fFar){ m_v2NearFar = vector2(a_fNear, a_fFar); }
void Camera::SetFOV(float a_fFOV){ m_fFOV = a_fFOV; }
void Camera::SetFPS(bool a_bFPS){ m_bFPS = a_bFPS; }
void Camera::SetCameraMode(BTO_CAMERAMODE a_nMode){ m_nMode = a_nMode; ResetCamera(); }
BTO_CAMERAMODE Camera::GetCameraMode(void){ return m_nMode; }
void Camera::SetPosition(vector3 a_v3Position)
{
	return SetPositionTargetAndUpward(a_v3Position, m_v3Target, m_v3Upward);
}
void Camera::SetTarget(vector3 a_v3Target)
{
	return SetPositionTargetAndUpward(m_v3Position, a_v3Target, m_v3Upward);
}
matrix4 Camera::GetMVP(matrix4 a_m4ModelToWorld)
{
	if (m_bInternalCalculation)
	{
		CalculateView();
		CalculateProjection();
	}
	return m_m4Projection * m_m4View * a_m4ModelToWorld;
}
matrix4 Camera::GetVP(void)
{
	if (m_bInternalCalculation)
	{
		CalculateView();
		CalculateProjection();
	}
	return m_m4Projection * m_m4View;
}
//--- Non Standard Singleton Methods
void Camera::CalculateProjection(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	float fRatio = static_cast<float>(pSystem->GetWindowWidth()) / static_cast<float>(pSystem->GetWindowHeight());
	float fPos = 0;
	switch (m_nMode)
	{
	default:
		m_m4Projection = glm::perspective(m_fFOV, fRatio, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTO_CAMERAMODE::CAM_ORTHO_X:
		fPos = m_v3Position.x;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTO_CAMERAMODE::CAM_ORTHO_Y:
		fPos = m_v3Position.y;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTO_CAMERAMODE::CAM_ORTHO_Z:
		fPos = m_v3Position.z;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;
	}
}
void Camera::CalculateView(void)
{
	//Code removed for assignment purposes
	
	//Calculate the look at
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Upward);
}
void Camera::MoveForward(float a_fDistance)
{
	m_v3Position += m_v3Forward * a_fDistance;
	m_v3Target += m_v3Forward * a_fDistance;
	m_v3Above += m_v3Forward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Above - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
	if (m_nMode != BTO_CAMERAMODE::CAM_PERSP)
	{
		CalculateProjection();
	}
}
vector3 Camera::GetClickOnWorldSpace(uint a_nMouseX, uint a_nMouseY)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	float posX = static_cast<float>(a_nMouseX - pSystem->GetWindowX());
	float posY = static_cast<float>(a_nMouseY - pSystem->GetWindowY());
	float width = static_cast<float>(pSystem->GetWindowWidth());
	float height = static_cast<float>(pSystem->GetWindowHeight());
	float x = (posX / width - 0.5f) * 2.0f; // [0,w] -> [-1,1]
	float y = (posY / height - 0.5f) * 2.0f; // [0,h] -> [-1,1]
	y *= -1;
	//Translate that to World Space
	vector4 v4NDC(x, y, -1.0f, 1.0f); //Normalized Device Coordinates
	matrix4 m4InverseVP = glm::inverse(GetVP()); //inverse of the view projection
	vector4 v4World = m4InverseVP * v4NDC; //translate device space to world coordinates
	v4World /= v4World.w;//normalize
	return vector3(v4World);
}
std::pair<vector3, vector3> Camera::GetClickAndDirectionOnWorldSpace(uint a_nMouseX, uint a_nMouseY)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	
	float posX = static_cast<float>(a_nMouseX - pSystem->GetWindowX());
	float posY = static_cast<float>(a_nMouseY - pSystem->GetWindowY());
	
	float width = static_cast<float>(pSystem->GetWindowWidth());
	float height = static_cast<float>(pSystem->GetWindowHeight());

	float x = (posX / width - 0.5f) * 2.0f; // [0,w] -> [-1,1]
	float y = (posY / height - 0.5f) * 2.0f; // [0,h] -> [-1,1]
	y *= -1;

	matrix4 m4InverseVP = glm::inverse(GetVP()); //inverse of the view projection

	//Translate that to World Space
	vector4 v4NDC(x, y, -1.0f, 1.0f); //Normalized Device Coordinates
	vector4 v4Start = m4InverseVP * v4NDC; //translate device space to world coordinates
	v4Start /= v4Start.w;//normalize

	//Translate that to World Space
	v4NDC = vector4(x, y, 0.0f, 1.0f);
	vector4 v4End = m4InverseVP * v4NDC; //translate device space to world coordinates
	v4End /= v4End.w;//normalize

	vector4 v4Direction = glm::normalize(v4End - v4Start);

	return std::pair<vector3, vector3> (vector3(v4Start), vector3(v4Direction));
}
void Camera::MoveVertical(float a_fDistance)
{
	m_v3Position += m_v3Upward * a_fDistance;
	m_v3Target += m_v3Upward * a_fDistance;
	m_v3Above += m_v3Upward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Above - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
	if (m_nMode != BTO_CAMERAMODE::CAM_PERSP)
	{
		CalculateProjection();
	}
}
void Camera::MoveSideways(float a_fDistance)
{
	m_v3Position += m_v3Rightward * a_fDistance;
	m_v3Target += m_v3Rightward * a_fDistance;
	m_v3Above += m_v3Rightward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Above - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
	if (m_nMode != BTO_CAMERAMODE::CAM_PERSP)
	{
		CalculateProjection();
	}
}
void Camera::ChangePitch(float a_fDegree)
{
	//Code removed for assignment purposes
}
void Camera::ChangeYaw(float a_fDegree)
{
	//Code removed for assignment purposes
}
void Camera::ChangeRoll(float a_fDegree)
{
	//Code removed for assignment purposes
}
void Camera::SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_v3Position = a_v3Position;
	m_v3Target = a_v3Target;
	m_v3Upward = glm::normalize(a_v3Upward);

	m_v3Above = a_v3Position + m_v3Upward;
	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
	CalculateProjection();
}
void Camera::ResetCamera(void)
{
	m_bInternalCalculation = true;
	m_v3PitchYawRoll = vector3(0.0f);

	switch (m_nMode)
	{
	default:
		m_v3Position = vector3(0.0f, 0.0f, 10.0f);
		m_v3Target = vector3(0.0f, 0.0f, 9.0f);
		m_v3Above = vector3(0.0f, 1.0f, 10.0f);

		m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	case BTO_CAMERAMODE::CAM_ORTHO_X:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(10.0f, 0.0f, 0.0f);
		m_v3Target = vector3(9.0f, 0.0f, 0.0f);
		m_v3Above = vector3(10.0f, 1.0f, 0.0f);

		m_v3Forward = vector3(-1.0f, 0.0f, 0.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(0.0f, 0.0f, -1.0f);
		break;
	case BTO_CAMERAMODE::CAM_ORTHO_Y:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(0.0f, 10.0f, 0.0f);
		m_v3Target = vector3(0.0f, 9.0f, 0.0f);
		m_v3Above = vector3(0.0f, 10.0f, -1.0f);

		m_v3Forward = vector3(0.0f, -1.0f, 0.0f);
		m_v3Upward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	case BTO_CAMERAMODE::CAM_ORTHO_Z:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(0.0f, 0.0f, 10.0f);
		m_v3Target = vector3(0.0f, 0.0f, 9.0f);
		m_v3Above = vector3(0.0f, 1.0f, 10.0f);

		m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	}
}
matrix4 Camera::GetCameraSpace(void)
{
	CalculateView();
	return glm::inverse(m_m4View);
}
matrix4 Camera::GetCameraSpaceAdjusted(void)
{
	return GetCameraSpace() * glm::translate(vector3(0.0f, 0.0f, -1.2085f));
}
matrix4 Camera::GetSpaceUnderMouse(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	UINT	MouseX, MouseY;		// Coordinates for the mouse

	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	int nW = pSystem->GetWindowWidth();
	int nH = pSystem->GetWindowHeight();

	float fRatio = static_cast<float>(nW) / static_cast<float>(nH);
	float fW = 0.5;

	float fDelta = 0.001f;

	//16*9
	if(fRatio >= (16.0f / 9.0f - fDelta) && fRatio <= (16.0f / 9.0f + fDelta))
		fW = 0.89f;

	//9*16
	if (fRatio >= (9.0f / 16.0f - fDelta) && fRatio <= (9.0f / 16.0f + fDelta))
		fW = 0.281f;

	//3*4
	if (fRatio >= (3.0f / 4.0f - fDelta) && fRatio <= (3.0f / 4.0f + fDelta))
		fW = 0.335f;

	//4*3
	if (fRatio >= (4.0f / 3.0f - fDelta) && fRatio <= (4.0f / 3.0f + fDelta))
		fW = 0.75f;

	fW = (nW / static_cast<float>(nH) / 2.0f);

	float fH = 0.5f;

	float fX = MapValue( static_cast<float>(MouseX), static_cast<float>(pSystem->GetWindowX()),
		static_cast<float>(pSystem->GetWindowX() + pSystem->GetWindowWidth()), -fW, fW);

	float fY = MapValue( static_cast<float>(MouseY), static_cast<float>(pSystem->GetWindowY()),
		static_cast<float>(pSystem->GetWindowY() + pSystem->GetWindowHeight()), fH, -fH);

	return GetCameraSpaceAdjusted() * glm::translate(vector3(fX, fY, 0.0f)) * glm::scale(vector3(0.05f));
}
matrix4 Camera::GetCameraPlane(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	float fSize = pSystem->GetWindowWidth() / static_cast<float>(pSystem->GetWindowHeight());
	return GetCameraSpaceAdjusted() * glm::scale(vector3(fSize, 1.0f, 0.0f));
}

void Camera::SetViewMatrix(matrix4 input) { m_m4View = input; m_bInternalCalculation = false; }
void Camera::SetProjectionMatrix(matrix4 input) { m_m4Projection = input; m_bInternalCalculation = false; }
