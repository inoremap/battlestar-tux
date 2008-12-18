#include "Simulation.h"
#include "OgreStringConverter.h"

Simulation::Simulation() {
	m_state = STARTUP;
}

Simulation::~Simulation() {
}


SimulationState Simulation::getCurrentState() {
	return m_state;
}

// for the sake of clarity, I am not using actual thread synchronization 
// objects to serialize access to this resource. You would want to protect
// this block with a mutex or critical section, etc.
bool Simulation::lockState() {
	if (m_locked == false) {

		m_locked = true;
		return true;
	}
	else
		return false;
}

bool Simulation::unlockState() {
	if (m_locked == true) {
		m_locked = false;
		return true;
	}
	else
		return false;
}

bool Simulation::requestStateChange(SimulationState newState) {
	if (m_state == STARTUP) {
		m_locked = false;
		m_state = newState;

		return true;
	}

	// this state cannot be changed once initiated
	if (m_state == SHUTDOWN) {
		return false;
	}

	if ((m_state == GUI || m_state == SIMULATION || m_state == LOADING || m_state == CANCEL_LOADING) && 
			(newState != STARTUP) && (newState != m_state)) 
	{
		m_state = newState;
		return true;
	}
	else
		return false;
}

void Simulation::setFrameTime(float ms) {
	m_frame_time = ms;
}


