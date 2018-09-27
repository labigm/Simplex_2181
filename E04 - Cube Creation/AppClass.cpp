#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh1 = new MyMesh();
	m_pMesh2 = new MyMesh();
	m_pMesh3 = new MyMesh();
	//Generate a circle
	//m_pMesh->GenerateCircle(2.0f, 5, C_RED);
	m_pMesh->GenerateCone(1.0f, 2.0f, 5, C_BLUE);
	m_pMesh1->GenerateCylinder(1.0f, 3.0f, 5, C_RED);
	m_pMesh2->GenerateTube(1.0f, 0.75f, 3.0f, 5, C_ORANGE);
	m_pMesh3->GenerateSphere(2.0f,5,C_YELLOW);

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
	mTranslate[3] = vector4(5, 0, 0, 1);
	matrix4 mTranslate1;
	mTranslate1[3] = vector4(-5, 0, 0, 1);
	matrix4 mTranslate2;
	mTranslate2[3] = vector4(1, 5, 0, 1);
	matrix4 mTranslate3;
	mTranslate3[3] = vector4(1, 0, 0, 1);

	//Render the mesh
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mTranslate * ToMatrix4(m_qArcBall));
	m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mTranslate1 * ToMatrix4(m_qArcBall));
	m_pMesh2->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mTranslate2 * ToMatrix4(m_qArcBall));
	m_pMesh3->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mTranslate3 * ToMatrix4(m_qArcBall));

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
	SafeDelete(m_pMesh2);
	SafeDelete(m_pMesh3);
	SafeDelete(m_pMesh4);
	//release GUI
	ShutdownGUI();
}