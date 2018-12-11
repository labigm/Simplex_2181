#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Music
	String sRoute = m_pSystem->m_pFolder->GetFolderData();
	sRoute += m_pSystem->m_pFolder->GetFolderAudio();

#pragma region Make some meshes, add them to a group and add the group to a model
	/*
	Mesh* pMesh1 = new Mesh();
	Mesh* pMesh2 = new Mesh();
	Mesh* pMesh3 = new Mesh();
	pMesh1->GenerateCone(1.0f, 1.0f, 10, C_RED);
	pMesh2->GenerateTorus(1.0f, 0.7f, 10, 10, C_MAGENTA);
	pMesh3->GenerateTube(1.0f, 0.7f, 1.0f, 10, C_BLUE);
	int nMesh1 = m_pMngr->AddMesh(pMesh1);
	int nMesh2 = m_pMngr->AddMesh(pMesh2);

	Group* pGroup1 = new Group();
	pGroup1->AddMesh(nMesh1, MeshOptions(glm::translate(AXIS_Y), WIRE));
	pGroup1->AddMesh(nMesh2, MeshOptions(glm::translate(-AXIS_Y), SOLID));
	Group* pGroup2 = new Group();
	pGroup2->AddMesh(pMesh3, MeshOptions(IDENTITY_M4, SOLID | WIRE));

	m_pModel1 = new Simplex::Model();
	m_pModel1->AddGroup(pGroup1);
	m_pModel1->AddGroup(pGroup2);
	*/
#pragma endregion
#pragma region Load Model and change its rendering properties
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	*/
#pragma endregion
#pragma region Load Model and change its materials
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model disconect and change its materials
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->DuplicateMaterialsUnique(-1, "_copy"); //dupliocate existing materials
	m_pModel1->CreateMaterials(); //duplicate one per mesh
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model and duplicate onto another one
	/*
	m_pModel3 = new Simplex::Model();
	m_pModel3->Load("Macross\\YF19.BTO");
	m_pModel1 = new Simplex::Model();
	m_pModel1->Instance(m_pModel3, "_copy_");
	*/
#pragma endregion
#pragma region Load Model
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	*/
#pragma endregion
#pragma region Sandbox
	//Background music
	m_soundBGM.openFromFile(sRoute + "elementary-wave-11.ogg");
	m_soundBGM.play();
	m_soundBGM.setLoop(true);

	//sound effect
	m_soundBuffer.loadFromFile(sRoute + "12C.wav");
	m_sound.setBuffer(m_soundBuffer);

	//load model
	m_pModel = new Simplex::Model();
	m_pModel->Load("Lego\\Unikitty.BTO");
#pragma endregion
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Move light... just for fun...
	static double dTimer = 0.0f; //create a variable to store time
	static uint uClock = m_pSystem->GenClock(); //generate a clock to track time
	dTimer += m_pSystem->GetDeltaTime(uClock); //get the time difference since last time called
	double dAngle = MapValue(dTimer, 0.0, 5.0, 0.0, 360.0);//map the value so we do not need to wait 360 seconds, only 5
	
	static vector3 v3Color(C_WHITE); //color of the light
	vector3 v3Position(glm::sin(glm::radians(dAngle)) * 5.0f, 2.5f, glm::cos(glm::radians(dAngle)) * 5.0f);//holds position of light
	m_pLightMngr->SetPosition(v3Position, 1); //set the position of first light(0 is reserved for global light)
	m_pLightMngr->SetIntensity(5.0f, 1); //set the intensity of first light
	m_pLightMngr->SetColor(v3Color, 1); //set the color of first light
	m_pMeshMngr->AddSphereToRenderList(glm::translate(v3Position) * glm::scale(vector3(0.15f)), v3Color, RENDER_SOLID); //add a sphere to "see" it
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	// set the model matrix of the model
	m_pModel->SetModelMatrix(ToMatrix4(m_qArcBall));
	//play the default sequence of the model
	m_pModel->PlaySequence();
	
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
	//release GUI
	ShutdownGUI();

	//release variables
	SafeDelete(m_pModel);
}