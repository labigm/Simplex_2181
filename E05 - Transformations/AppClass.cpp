#include "AppClass.h"
void Application::InitVariables(void)
{
	meshes = new MyMesh*[46];
	for (int i = 0; i < 46; i++) {
		MyMesh* newMesh = new MyMesh();
		meshes[i] = newMesh;
		meshes[i]->GenerateCube(1.0f, C_BLACK);
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

	// Move the invader.
	static float fdisp = 0; // If we declare it as static, this line will only run on frame one...
	fdisp += 0.05f; // Allowing us to update it each frame.

	// Draw the invader via glm::translate. We will translate it across the screen by adding fdisp to each cube's X-component.
	meshes[0]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-5.0f + fdisp, 0.0f, 0.0f)));
	meshes[1]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-5.0f + fdisp, -1.0f, 0.0f)));
	meshes[2]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-5.0f + fdisp, -2.0f, 0.0f)));
	meshes[3]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + fdisp, 0.0f, 0.0f)));
	meshes[4]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + fdisp, 1.0f, 0.0f)));
	meshes[5]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, -2.0f, 0.0f)));
	meshes[6]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, -1.0f, 0.0f)));
	meshes[7]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, 0.0f, 0.0f)));
	meshes[8]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, 1.0f, 0.0f)));
	meshes[9]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, 2.0f, 0.0f)));
	meshes[10]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-3.0f + fdisp, 4.0f, 0.0f)));
	meshes[11]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + fdisp, -3.0f, 0.0f)));
	meshes[12]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + fdisp, -1.0f, 0.0f)));
	meshes[13]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + fdisp, 0.0f, 0.0f)));
	meshes[14]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + fdisp, 2.0f, 0.0f)));
	meshes[15]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + fdisp, 3.0f, 0.0f)));
	meshes[16]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-1.0f + fdisp, -1.0f, 0.0f)));
	meshes[17]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-1.0f + fdisp, 0.0f, 0.0f)));
	meshes[18]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-1.0f + fdisp, 1.0f, 0.0f)));
	meshes[19]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-1.0f + fdisp, 2.0f, 0.0f)));
	meshes[20]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + fdisp, -1.0f, 0.0f)));
	meshes[21]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + fdisp, 0.0f, 0.0f)));
	meshes[22]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + fdisp, 1.0f, 0.0f)));
	meshes[23]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + fdisp, 2.0f, 0.0f)));
	meshes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(1.0f + fdisp, -1.0f, 0.0f)));
	meshes[25]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(1.0f + fdisp, 0.0f, 0.0f)));
	meshes[26]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(1.0f + fdisp, 1.0f, 0.0f)));
	meshes[27]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(1.0f + fdisp, 2.0f, 0.0f)));
	meshes[28]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + fdisp, -3.0f, 0.0f)));
	meshes[29]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + fdisp, -1.0f, 0.0f)));
	meshes[30]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + fdisp, 0.0f, 0.0f)));
	meshes[31]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + fdisp, 2.0f, 0.0f)));
	meshes[32]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + fdisp, 3.0f, 0.0f)));
	meshes[33]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, -2.0f, 0.0f)));
	meshes[34]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, -1.0f, 0.0f)));
	meshes[35]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, 0.0f, 0.0f)));
	meshes[36]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, 1.0f, 0.0f)));
	meshes[37]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, 2.0f, 0.0f)));
	meshes[38]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(3.0f + fdisp, 4.0f, 0.0f)));
	meshes[39]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + fdisp, 0.0f, 0.0f)));
	meshes[40]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + fdisp, 1.0f, 0.0f)));
	meshes[41]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(5.0f + fdisp, 0.0f, 0.0f)));
	meshes[42]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(5.0f + fdisp, -1.0f, 0.0f)));
	meshes[43]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(5.0f + fdisp, -2.0f, 0.0f)));
	meshes[44]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-1.0f + fdisp, -3.0f, 0.0f)));
	meshes[45]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(1.0f + fdisp, -3.0f, 0.0f)));
		
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
	// Deallocate all cubes meshes at the end.
	for (int i = 0; i < 46; i++) {
		MyMesh* m_pMesh = meshes[i];
		if (m_pMesh != nullptr)
		{
			delete m_pMesh;
			m_pMesh = nullptr;
		}
	}
	delete[] meshes; // Delete the dynamically-allocated array of MyMesh*, as well.
	meshes = nullptr;
	//release GUI
	ShutdownGUI();
}