#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(	vector3(0.0f, 3.0f, 13.0f), //Position
											vector3(0.0f, 3.0f, 12.0f),	//Target
											AXIS_Y );					//Up

	//Set the position of the light
	m_pLightMngr->SetPosition(vector3(10.0f));

	//Initialize models

	//creeper
	m_pCreeper = new Model();
	m_pCreeper->Load("Sorted\\SphereCube.fbx");
	//m_pCreeper->Load("Minecraft\\Creeper.obj");
	//m_pCreeper->Load("Lego\\Unikitty.bto");
	//m_pCreeper->ChangeMeshOptions(MeshOptions(IDENTITY_M4, RENDER_SOLID | RENDER_WIRE), nullptr, -1);
	m_pCreeperRB = new MyRigidBody(m_pCreeper->GetVertexList());

	//steve
	m_pSteve = new Model();
	//m_pSteve->Load("Minecraft\\Steve.obj");
	//m_pSteveRB = new MyRigidBody(m_pSteve->GetVertexList());
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//reset the color of the rigid bodies to white 
	m_pCreeperRB->SetColor(C_WHITE);
	//m_pSteveRB->SetColor(C_WHITE);

	//Set model matrix to the creeper
	m_pCreeper->SetModelMatrix(glm::translate(m_v3Creeper) * ToMatrix4(m_qArcBall));
	//m_pModelRB->SetModelMatrix(glm::translate(m_v3Creeper) * ToMatrix4(m_qArcBall));
	
	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f));
	m_pSteve->SetModelMatrix(mSteve);
	//m_pSteveRB->SetModelMatrix(mSteve);
	

	m_pCreeper->AddToRenderList();
	//m_pCreeper->PlaySequence();
	m_pCreeperRB->AddToRenderList();

	//m_pSteve->AddToRenderList();
	//m_pSteveRB->AddToRenderList();
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//Add grid to the scene
	//m_pMeshMngr->AddGridToRenderList();

	//Add skybox
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
	//release the model
	SafeDelete(m_pCreeper);

	//release the rigid body for the model
	SafeDelete(m_pCreeperRB);

	//release the model
	SafeDelete(m_pSteve);

	//release the rigid body for the model
	SafeDelete(m_pSteveRB);
	
	//release GUI
	ShutdownGUI();
}
