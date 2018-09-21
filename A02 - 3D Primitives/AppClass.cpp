#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//Allocate the memory for the shapes
	m_pCube = new MyMesh();
	m_pCube->GenerateCube(1.0f, C_RED);
	m_pCone = new MyMesh();
	m_pCone->GenerateCone(0.5f, 1.0f, 7, C_ORANGE);
	m_pCylinder = new MyMesh();
	m_pCylinder->GenerateCylinder(0.5f, 1.0f, 7, C_YELLOW);
	m_pTube = new MyMesh();
	m_pTube->GenerateTube(0.5f, 0.35f, 1.0f, 7, C_GREEN);
	m_pSphere = new MyMesh();
	m_pSphere->GenerateSphere(0.5f, 3, C_BLUE);
	m_pTorus = new MyMesh();
	m_pTorus->GenerateTorus(0.5f, 0.30f, 7, 7, C_VIOLET);

	//Make Mesh object
	m_pMesh = new MyMesh();
	int primitive = 0;
	switch (primitive)
	{
	default:
		m_pMesh->GenerateCube(2.0f, C_CYAN);
		break;
	case 1:
		m_pMesh->GenerateCone(1.0f, 2.0f, 10, C_CYAN);
		break;
	case 2:
		m_pMesh->GenerateCylinder(1.0f, 2.0f, 10, C_CYAN);
		break;
	case 3:
		m_pMesh->GenerateTube(1.0f, 0.7f, 1.0f, 10, C_CYAN);
		break;
	case 4:
		m_pMesh->GenerateSphere(1.0f, 5, C_CYAN);
		break;
	case 5:
		m_pMesh->GenerateTorus(1.0f, 0.6f, 10, 10, C_CYAN);
		break;
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_qArcBall));

	//Get some variable to position and rotate the other shapes out of the origin
	double dAngle = 360.0 / 6.0;
	vector3 v3Position;
	static uint uClock = m_pSystem->GenClock();
	static double dTimer = m_pSystem->GetDeltaTime(uClock);
	dTimer += m_pSystem->GetDeltaTime(uClock);

	//Cube
	v3Position = vector3(glm::sin(glm::radians(dAngle * 0)) * 3.0f, glm::cos(glm::radians(dAngle * 0)) * 3.0f, 0.0f);
	m_pCube->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	//Cone
	v3Position = vector3(glm::sin(glm::radians(dAngle * 1)) * 3.0f, glm::cos(glm::radians(dAngle * 1)) * 3.0f, 0.0f);
	m_pCone->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	//Cylinder
	v3Position = vector3(glm::sin(glm::radians(dAngle * 2)) * 3.0f, glm::cos(glm::radians(dAngle * 2)) * 3.0f, 0.0f);
	m_pCylinder->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	//Tube
	v3Position = vector3(glm::sin(glm::radians(dAngle * 3)) * 3.0f, glm::cos(glm::radians(dAngle * 3)) * 3.0f, 0.0f);
	m_pTube->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	//Sphere
	v3Position = vector3(glm::sin(glm::radians(dAngle * 4)) * 3.0f, glm::cos(glm::radians(dAngle * 4)) * 3.0f, 0.0f);
	m_pSphere->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	//Tourus
	v3Position = vector3(glm::sin(glm::radians(dAngle * 5)) * 3.0f, glm::cos(glm::radians(dAngle * 5)) * 3.0f, 0.0f);
	m_pTorus->Render(m4Projection, m4View, glm::rotate(glm::translate(v3Position), glm::radians(static_cast<float>(dTimer) * 20.0f), AXIS_X));

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
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
	SafeDelete(m_pMesh);
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(m_pTube);
	SafeDelete(m_pSphere);
	SafeDelete(m_pTorus);

	//release GUI
	ShutdownGUI();
}