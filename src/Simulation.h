#pragma once

#include <vector>
#include <map>

typedef enum {
	STARTUP,
	GUI,
	LOADING,
	CANCEL_LOADING,
	SIMULATION,
	SHUTDOWN
} SimulationState;

class Simulation {

public:
	Simulation();
	virtual ~Simulation();

public:
	bool requestStateChange(SimulationState state);
	bool lockState();
	bool unlockState();
	SimulationState getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() { return m_frame_time; }

protected:
	SimulationState m_state;
	bool m_locked;
	float m_frame_time;
};

