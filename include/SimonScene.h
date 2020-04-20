#pragma once

#include "Cappuccino/SceneManager.h"
#include "Cappuccino/SoundSystem.h"
#include "Cappuccino/CappInput.h"
using namespace Cappuccino;

class ButtonSequence {
public:
	//1 is W, 2 is A, 3 is S, 4 is D
	ButtonSequence(const std::vector<unsigned>& sequence);

	//this is where all the game code is pretty much
	void update(CappInput& _in, SoundBank& bank);

	void playQueue(SoundBank& bank);
private:
	std::vector<unsigned> playQ;
	std::vector<bool> playedEvent;
	bool win = false;
	std::vector<unsigned> inputsequence;

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
	static FMOD_3D_ATTRIBUTES _attributes2;//tom fuckery

private:
	std::vector<ButtonSequence*> sequences;

	FMOD_3D_ATTRIBUTES _attributes = { { 0 } };
	CappInput _in;
	SoundBank master{ "Master.bank" };
	SoundBank masterStrings{ "Master.strings.bank" };
	SoundBank Music{ "Music.bank" };

};