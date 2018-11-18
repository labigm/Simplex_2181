#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	
	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	uint uInstances = 500;
	int nSquare = static_cast<int>(std::sqrt(uInstances));
	uInstances = nSquare * nSquare;
	uint uIndex = 0;
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(50.0f, 0.0f, 0.0f)));

	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 0; j < nSquare; j++)
		{
			m_pEntityMngr->AddEntity("Minecraft\\Cube.obj");
			vector3 v3Position = vector3(glm::sphericalRand(34.0f));
			matrix4 m4Position = glm::translate(v3Position);
			m_pEntityMngr->SetModelMatrix(m4Position);
			m_pEntityMngr->AddDimension(-1, uIndex);
			uIndex++;
		}
	}
	m_pEntityMngr->Update();
	m_pRoot = new MyOctant();
	//m_pRoot = new MyOctant(vector3(10.0f, 10.0f, 10.0f), 50.0f);
	//steve
	//m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	//Update Entity Manager
	m_pEntityMngr->Update();

	/*m_pMeshMngr->AddGridToRenderList(glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
	m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(-17.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
	m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(17.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));*/
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	m_pRoot->Display();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
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
	SafeDelete(m_pRoot);
	//release GUI
	ShutdownGUI();
}