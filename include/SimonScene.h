#pragma once

#include "Cappuccino/SceneManager.h"
#include "Cappuccino/SoundSystem.h"
#include "Cappuccino/CappInput.h"
using namespace Cappuccino;

class ButtonSequence {
public:
	//1 is W, 2 is A, 3 is S, 4 is D
	ButtonSequence(const std::vector<unsigned>& sequence);

	void update(CappInput& _in);
private:
	unsigned lives = 3;
	std::vector<unsigned> _sequence;
	unsigned _iteration = 1;

};


class SimonScene : public Scene {
public:
	SimonScene(bool yn);

	void childUpdate(float dt) override;

	bool init() override;
	bool exit() override;

	void mouseFunction(double xpos, double ypos) override;
private:
	std::vector<ButtonSequence*> sequences;

	FMOD_3D_ATTRIBUTES _attributes = { { 0 } };
	FMOD_3D_ATTRIBUTES _attributes2 = { { 0 } };
	CappInput _in;
	SoundBank master{ "Master.bank" };
	SoundBank masterStrings{ "Master.strings.bank" };
	SoundBank Ghoul{ "Ghoul.bank" };

};