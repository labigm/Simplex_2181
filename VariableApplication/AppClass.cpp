#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Variable Application"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (Default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD);
}
void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 15.0f),//Camera position
		vector3(0.0f, 0.0f, 0.0f),//What I'm looking at
		AXIS_Y);//What is up

	m_bGUI_Window_Main = true;
	m_bGUI_Window_Secondary = false;
	InitIMGUI();

	Mesh* pMesh1 = new Mesh();
	pMesh1->GenerateSphere(1.0f, 5, C_RED);
	m_nMesh1 = m_pMeshMngr->AddMesh(pMesh1);
}
void AppClass::Update(void)
{
	//Update the system
	m_pSystem->Update();
	
	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
		
	//Add skybox to the list
	m_pMeshMngr->AddSkyboxToRenderList();

	//Add mesh to render list
	m_pMeshMngr->AddMeshToRenderList(m_nMesh1, ToMatrix4(m_qArcBall), RENDER_SOLID | RENDER_WIRE);
		
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	for(uint i = 0; i < 20; ++i)
		m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->Print("						");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);

	m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("RenderCalls: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(m_uRenderCallCount), C_YELLOW);
		
	m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), C_RED);
}
void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Display render list
	m_uRenderCallCount = m_pMeshMngr->Render();
	//Clear the render list for the next try
	m_pMeshMngr->ClearRenderList();
	//Draw the GUI
	DrawGUI();
	//Swap the OpenGL buffers so we get ready for the next frame
	m_pGLSystem->GLSwapBuffers();
}
void AppClass::Release(void)
{
	//Shutdown the GUI
	ShutdownGUI();
	//release the memory of the inherited fields
	super::Release(); 
}