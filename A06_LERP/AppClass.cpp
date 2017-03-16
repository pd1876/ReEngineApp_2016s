#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	locs.push_back(vector3(-4.0f, -2.0f, 5.0f));
	locs.push_back(vector3(1.0f, -2.0f, 5.0f));
	locs.push_back(vector3(-3.0f, -1.0f, 3.0f));
	locs.push_back(vector3(2.0f, -1.0f, 3.0f));
	locs.push_back(vector3(-2.0f, 0.0f, 0.0f));
	locs.push_back(vector3(3.0f, 0.0f, 0.0f));
	locs.push_back(vector3(-1.0f, 1.0f, -3.0f));
	locs.push_back(vector3(4.0f, 1.0f, -3.0f));
	locs.push_back(vector3(0.0f, 2.0f, -5.0f));
	locs.push_back(vector3(5.0f, 2.0f, -5.0f));
	locs.push_back(vector3(1.0f, 3.0f, -5.0f));
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static float fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	// Use the clock...
	static DWORD startTimeSystem = GetTickCount(); // get systems start up time
	DWORD timeApplication = GetTickCount() - startTimeSystem; // get current time and substract start time
	float timer = timeApplication / 1000.0f; // convert time from ms to s

	// find the duration the movement is supposed to take
	float timerMapped = MapValue(fRunTime, 0.0f, fDuration, 0.0f, 1.0f);
	

	// draw location points
	for (int i = 0; i < locs.size(); i++) {
		// matrix for spheres for locations
		matrix4 m4Sphere1;
		m4Sphere1 = glm::translate(locs[i]) * glm::scale(vector3(0.1f));
		// adding sphere to render list
		m_pMeshMngr->AddSphereToRenderList(m4Sphere1, RERED, SOLID);
	}

	// calculate next location
	static int prevLoc = 0;
	static int nextLoc = 1;
	if (fRunTime >= fDuration) {
		prevLoc++;
		nextLoc++;

		if (nextLoc >= locs.size())
			nextLoc = 0;
		if (prevLoc >= locs.size())
			prevLoc = 0;
	}

	// Lerp model
	matrix4 m4WallEye;
	vector3 v3Lerp = glm::lerp(locs[prevLoc], locs[nextLoc], timerMapped);
	m4WallEye = glm::translate(v3Lerp);
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");

	if (timerMapped > 1.0f) {
		fRunTime = 0.0f;
	}

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->PrintLine("Time Span: " + std::to_string(fTimeSpan));
	m_pMeshMngr->PrintLine("Run Time: " + std::to_string(fRunTime));
	m_pMeshMngr->PrintLine("Duration: " + std::to_string(fDuration));

	// Print the FPS
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}