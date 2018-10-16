#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//initializing the model
	m_pModel = new Simplex::Model();

	//Load a model
	m_pModel->Load("Minecraft\\Steve.obj");

	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_RED);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);

#pragma region SLERP
	if (true)
	{
		quaternion q1; // IDENTITY
		quaternion q2 = glm::angleAxis(glm::radians(90.0f), vector3(0.0f, 0.0f, 1.0f)); // Not actually doing rotation; is orienting. That's why glm::radians(360.0f) will nOT WORK.
		// In fact, glm::radians(360.0f) will make it freak out due to float error.
		// Try 359.90f.
		float fPercentage = MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage); // Slerping is done via glm::mix
		m_m4Steve = glm::toMat4(qSLERP);
	}
#pragma endregion
#pragma region translate vector orientation into a matrix
	if (false)
	{
		matrix4 m4OrientX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.x), vector3(1.0f, 0.0f, 0.0f));
		matrix4 m4OrientY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.y), vector3(0.0f, 1.0f, 0.0f));
		matrix4 m4OrientZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.z), vector3(0.0f, 0.0f, 1.0f));

		matrix4 m4Orientation = m4OrientX * m4OrientY * m4OrientZ;
		m_m4Steve = glm::toMat4(m_qOrientation);
	}
#pragma endregion
#pragma region orientation using quaternions
	if (false)
	{
		m_m4Steve = glm::toMat4(m_qOrientation);
	}
#pragma endregion
	
	//Attach the model matrix that takes me from the world coordinate system
	m_pModel->SetModelMatrix(m_m4Steve);

	//Send the model to render list
	m_pModel->AddToRenderList();

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Model = glm::translate(m_v3Orientation);
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	// Camera Types: Ortho and Perspective
	// m4Projection = glm::ortho(0.0f, 7.5f, -5.0f, 5.0f, 0.01f, 20.0f);

	float fovy = 90.0f; // Field of view
	float aspect = static_cast<float> (m_pSystem->GetWindowWidth()) / static_cast<float> (m_pSystem->GetWindowHeight()); // Aspect Ratio
	float zNear = 0.01f; // Near clipping plane
	float zFar = 20.0f; // Far clipping plane
	m4Projection = glm::perspective(fovy, aspect, zNear, zFar);

	vector3 v3Position = vector3(0.0f, 0.0f, 7.0f);
	vector3 v3Target;
	vector3 v3Up = vector3(0.0f, 1.0f, 0.0f);
	m4View = glm::lookAt(v3Position, v3Target, v3Up);

	m_pMesh->Render(m4Projection, m4View, m4Model);

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	/*/
	float fovy = 45.0f; // Field of view
	float aspect = m_pSystem->GetWindowWidth() / m_pSystem->GetWindowHeight(); // Aspect Ratio
	float zNear = 0.01f; // Near clipping plane
	float zFar = 1000.0f; // Far clipping plane
	m4Projection = glm::perspective(fovy, aspect, zNear, zFar);

	// The two matrices will be modified somewhere else.
	// Use the below lines for the HW.
	m_pCameraMngr->SetProjectionMatrix(m4Projection);
	m_pCameraMngr->SetViewMatrix(m4View);
	*/

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release model
	SafeDelete(m_pModel);
	SafeDelete(m_pMesh); // In release, safedelete.
	//release GUI
	ShutdownGUI();
}
