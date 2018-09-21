#include "AppClass.h"
void GLFWApp::InitVariables(void)
{
	//setup camera position
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What I'm looking at
		AXIS_Y);//What is up
	//init variables
	m_pModel = new Simplex::Model();
	//load model
	m_pModel->Load("Lego\\Unikitty.BTO");
}
void GLFWApp::Update(void)
{
	//Take screen changes in account
	Reshape();

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), C_RED);
}
void GLFWApp::Display(void)
{
	// Clear the screen
	ClearScreen();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	m_pMeshMngr->AddSkyboxToRenderList();
	//set the model matrix of the model
	m_pModel->SetModelMatrix(ToMatrix4(m_qArcBall));
	//play the default sequence of the model
	m_pModel->PlaySequence();
	//render list call
	m_pMeshMngr->Render();
	//clear the render list
	m_pMeshMngr->ClearRenderList();
	// Swap buffers
	glfwSwapBuffers(m_pWindow);
	//poll events in glfw
	glfwPollEvents();
}

void GLFWApp::Release(void)
{
	//release variables
	SafeDelete(m_pModel);
}