#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;

	// start and end point
	static vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	static vector3 v3End = vector3(0.0f, 3.0f, 0.0f);

	// lerp up and down
	float fPercentage = MapValue(fTimer, 0.0f, 2.0f, 0.0f, 1.0f);
	vector3 v3Lerp = glm::lerp(v3Start, v3End, fPercentage);
	// end lerp

	// rotate object
	quaternion q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q2 = glm::angleAxis(180.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q3 = glm::mix(q1, q2, fPercentage*2.0f);
	// end rotation

	// set model matrix
	modelMatrix = glm::translate(v3Lerp) * ToMatrix4(q3);

	// reset timer
	if (fPercentage > 1.0) {
		std::swap(v3Start, v3End);
		fTimer = 0.0f;
	}
#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

