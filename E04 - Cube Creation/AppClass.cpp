#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	//Generate a circle
	//m_pMesh->GenerateCircle(2.0f, 5, C_RED);

	m_pMesh->GenerateCone(1.0f,2.0f,5,C_RED);

	m_pMesh1 = new MyMesh();
	//m_pMesh1->GenerateCone(1.0f, 1.0f, 5, C_BLUE);
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
	
	// Translate a given mesh, each mesh is a different shape
	matrix4 mTranslate;
	mTranslate[3] = vector4(-8,0,0,1);

	//Render the mesh
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mTranslate * ToMatrix4(m_qArcBall));
	m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));

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
	//Safely release the memory
	SafeDelete(m_pMesh);
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}