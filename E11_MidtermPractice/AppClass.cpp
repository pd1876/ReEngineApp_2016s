#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static float dTotalTime = 0.0; //Total time of the simulation
	float dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	// rotate steve around origin
	//quaternion q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	//quaternion q2 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f));
	//quaternion q3;
	//float animationTime = 5.0f;
	//float fPercentage = MapValue(dTotalTime, 0.0f, animationTime, 0.0f, 1.0f);
	//q3 = glm::mix(q1, q2, fPercentage);
	// end rotation around origin

	// position lerp variables
	float lerpTime = 5.0f;
	float lerpPercentage = MapValue(dTotalTime, 0.0f, lerpTime, 0.0f, 1.0f);
	vector3 v3Lerp;

	// lerp position
	if (animCounter == 0) {
		v3Lerp = glm::lerp(vector3(0.0f, 0.0f, 0.0f), vector3(5.0f, 5.0f, 0.0f), lerpPercentage);
	}
	else if (animCounter == 1) {
		v3Lerp = glm::lerp(vector3(5.0f, 5.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), lerpPercentage);
	}
	// end lerp position

	// convert quaternion to matrix
	//m_m4Steve = ToMatrix4(q3);

	// translate matrix
	m_m4Steve *= glm::translate(v3Lerp);
	
	// after 5 seconds
	// start second half of the animation
	if (dTotalTime >= 5.0f && animCounter == 0) {
		dTotalTime = 0.0f;
		animCounter++;
	}
	// after the second 5 seconds
	// restart animation
	else if (dTotalTime >= 5.0f && animCounter == 1) {
		dTotalTime = 0.0f;
		animCounter--;
	}
	
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
