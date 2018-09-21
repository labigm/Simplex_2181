#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 13.0f), //Position
		vector3(0.0f, 0.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	//creeper
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");

	//steve
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow");
	//set the model matrix
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(2.0f, -1.5f, -1.0f)));
	
	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	//set the model matrix
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -2.5f, 0.0f)));

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig");
	//set the model matrix
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-2.0f, -1.0f, -1.0f)));

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mCreeper, "Creeper");


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.5f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");


	//Move the last entity added slowly to the right
	matrix4 lastMatrix = m_pEntityMngr->GetModelMatrix();// get the model matrix of the last added
	lastMatrix *= glm::translate(IDENTITY_M4, vector3(0.01f, 0.0f, 0.0f)); //translate it
	m_pEntityMngr->SetModelMatrix(lastMatrix); //return it to its owner

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
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
	//release the entity manager
	m_pEntityMngr->ReleaseInstance();

	//release GUI
	ShutdownGUI();
}