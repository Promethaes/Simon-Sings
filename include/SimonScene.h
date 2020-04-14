#pragma once

#include "Cappuccino/SceneManager.h"
#include "Cappuccino/SoundSystem.h"
#include "Cappuccino/CappInput.h"
using namespace Cappuccino;
class SimonScene : public Scene {
public:
	SimonScene(bool yn);

	void childUpdate(float dt) override;

	bool init() override;
	bool exit() override;

	void mouseFunction(double xpos, double ypos) override;
private:
	FMOD_3D_ATTRIBUTES _attributes = { { 0 } };
	FMOD_3D_ATTRIBUTES _attributes2 = { { 0 } };
	FMOD::Studio::EventInstance* eventInstance = NULL;
	CappInput _in;
	SoundBank master{ "Master.bank" };
	SoundBank masterStrings{ "Master.strings.bank" };
	SoundBank vehicles{ "Vehicles.bank" };

};