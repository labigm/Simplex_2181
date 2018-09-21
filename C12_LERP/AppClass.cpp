#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);
	
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(0.5f, 1.0f, 5, C_WHITE);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	
	//Matrix of the model, its position in the world
	/* //Sol 1
	float fStartPos = -5.0f;
	float fEndPos = 5.0f;
	static DWORD dStartTime = GetTickCount();
	DWORD dCurrentTime = GetTickCount();
	DWORD dTime = dCurrentTime - dStartTime;
	float fTime = dTime / 1000.0f;
	float fTotalAnimationTime = 10.0f;
	//fTotal -> 1.0f
	//fTime -> x
	float fPercentage = fTime  / fTotalAnimationTime;
	float fCurrentPos = glm::lerp(fStartPos, fEndPos, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, vector3(fCurrentPos, 0.0f, 0.0f));
	*/

	//Sol2
	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//Calculate list of Stops
	static std::vector<vector3> v3Stop;
	static bool bInit = false; //Initialize once
	if (!bInit)
	{
		v3Stop.push_back(vector3(-3, -0, 0));
		v3Stop.push_back(vector3(3, -0, 0));
		v3Stop.push_back(vector3(0, 2.5, 0));
		v3Stop.push_back(vector3(0, -2.5, 0));
		bInit = true;
	}

	vector3 v3Start; //start point
	vector3 v3End; //end point
	static uint route = 0; //current route
	v3Start = v3Stop[route]; //start at the current route
	v3End = v3Stop[(route + 1) % v3Stop.size()]; //end at route +1 (if overboard will restart from 0)
	
	//get the percentace
	float fTimeBetweenStops = 2.0;//in seconds
	//map the value to be between 0.0 and 1.0
	float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);

	//calculate the current position
	vector3 v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, v3CurrentPos);

	//if we are done with this route
	if (fPercentage >= 1.0f)
	{
		route++; //go to the next route
		fTimer = m_pSystem->GetDeltaTime(uClock);//restart the clock
		route %= v3Stop.size();//make sure we are within boundries
	}
		
	// render the object
	m_pMesh->Render(m4Projection, m4View, m4Model);
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	// draw stops to know we are within stops
	for (uint i = 0; i < v3Stop.size(); ++i)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(v3Stop[i]) * glm::scale(vector3(0.15f)), C_RED, RENDER_WIRE);
	}

	
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
	//release the mesh
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}
