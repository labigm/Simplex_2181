#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Jonathan So - jds7523@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager

		// Based on E04 - Circle Creation's code...
		// Add the required vertices as stops in our stopList. Use fSize as our radius, since that increases with every loop in accordance with each torus.
		float theta = 0;
		for (uint n = 0; n < i; n++) {
			m_stopsList.push_back(vector3(fSize * cos(theta), fSize * sin(theta), 0));
			theta += ((2 * PI) / i);
		}

		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}
	// This calculates the initial starting and ending positions of every sphere and stores it in m_startPtList and m_endPtList.
	for (uint i = 0; i < m_uOrbits; ++i) {
		vector3 v3InitPos; // The initial starting position.
		vector3 v3EndPos; // The initial ending position. 
		if (i <= 0) { // Calculate the start position of the very first sphere, which resides at index 0.
			v3InitPos = m_stopsList[0];
			v3EndPos = m_stopsList[1];
			m_indexList.push_back(0);
			m_maxIndexList.push_back(2);
		}
		else { // Use the formula to calculate the index of the starting position of subsequent spheres. 
			int index = 0;
			// The formula is that for the number of sides on the shape, take the sum of all numbers of sides starting from three up to and excluding the number of sides of the current shape.
			// For example, for a pentagon, its starting vertex is index 7, so triangle 3 + rectangle 4 = index 7. 
			for (uint j = 0; j < i; j++) {
				index += (j + 3);
			}
			v3InitPos = m_stopsList[index];
			v3EndPos = m_stopsList[index + 1]; // Initial end point is the very next stop in the list.
			m_indexList.push_back(index); 
			m_maxIndexList.push_back(index + (i + 3) - 1); // Calculate the index of the last vertex in the current shape as well.
		}
		m_startPtList.push_back(v3InitPos);
		m_endPtList.push_back(v3EndPos);
		m_timerList.push_back(0.0f); // Set the initial timer value for all timers equal to 0.0f.
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z);

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i) {
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 1.5708f, AXIS_X));
		m_timerList[i] += 0.05f; // Increase the timer for this sphere.

		//calculate the current position
		vector3 v3CurrentPos;
		v3CurrentPos = glm::lerp(m_startPtList[i], m_endPtList[i], m_timerList[i]); // Use lerp in conjunction with the timer to figure out where we are between the start and end point.
		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);

		// Resetting the timer
		if (m_timerList[i] >= 1.0f) {
			std::swap(m_startPtList[i], m_endPtList[i]); // Change the start point to the one we're current on (the previous end).
			if (m_indexList[i] >= m_maxIndexList[i]) { // If we've hit the last stop...
				// Go back to the first point.
				int index = 0;
				for (uint j = 0; j < i; j++) {
					index += (j + 3);
				}
				m_endPtList[i] = m_stopsList[index];
				m_indexList[i] = index;
			}
			else { // Go to the next point.
				m_indexList[i]++;
				m_endPtList[i] = m_stopsList[m_indexList[i]];
			}
			m_timerList[i] = 0.0f; // Make sure to reset the timer.
		}
		
		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.1)), C_WHITE);
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
	//release GUI
	ShutdownGUI();
}