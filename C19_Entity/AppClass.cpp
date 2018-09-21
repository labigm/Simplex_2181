#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(vector3(0.0f, 3.0f, 13.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	//creeper
	m_pCreeper = new MyEntity("Minecraft\\Creeper.obj", "Creeper");

	//steve
	m_pSteve = new MyEntity("Minecraft\\Steve.obj", "Steve");

	m_pCow = new MyEntity("Minecraft\\Cow.obj", "Cow");
	m_pZombie = new MyEntity("Minecraft\\Zombie.obj", "Zombie");
	m_pPig = new MyEntity("Minecraft\\Pig.obj", "Pig");
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
	m_pCreeper->SetModelMatrix(mCreeper);


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pSteve->SetModelMatrix(mSteve);

	matrix4 mCow = glm::translate(vector3(1.55f, 1.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	matrix4 mPig = glm::translate(vector3(0.0f, 0.5f, -1.5f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	matrix4 mZombie = glm::translate(vector3(1.55f, 0.0f, -3.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);


	m_pCow->SetModelMatrix(mCow);
	m_pPig->SetModelMatrix(mPig);
	m_pZombie->SetModelMatrix(mZombie);

	//Check collision
	bool bColliding = m_pCreeper->IsColliding(m_pSteve);

	//Add objects to render list
	m_pCreeper->AddToRenderList(true);
	m_pSteve->AddToRenderList(true);
	m_pZombie->AddToRenderList(true);
	m_pPig->AddToRenderList(true);
	m_pCow->AddToRenderList(true);

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
	//release the creeper
	SafeDelete(m_pCreeper);

	//release Steve
	SafeDelete(m_pSteve);

	SafeDelete(m_pZombie);
	SafeDelete(m_pCow);
	SafeDelete(m_pPig);

	//release GUI
	ShutdownGUI();
}
