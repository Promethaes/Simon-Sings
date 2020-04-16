#include "SimonScene.h"
#include <iostream>

SimonScene::SimonScene(bool yn)
	:Scene(yn), _in(true, std::nullopt)
{
	sequences.push_back(new ButtonSequence({ 1,2,3,4 }));
}

void SimonScene::childUpdate(float dt)
{
	FMOD_RESULT r;
	// Position the listener at the origin

	_attributes.forward.z = -1.0f;
	_attributes.up.y = 1.0f;
	r = StudioSound::_system->setListenerAttributes(0, &_attributes);
	StudioSound::checkFmodErrors(r, "attrib");

	if (!Ghoul.isEventPlaying(0))
		Ghoul.playEvent(0);

	Ghoul.getEvent(0)->set3DAttributes(&_attributes2);

	sequences[0]->update(_in);

}

bool SimonScene::init()
{
	glm::vec3 Test;
	Test.x = 0.0f;
	Test.y = 0.0f;
	Test.z = 3.0f;

	_attributes2.position.x = Test.x;
	_attributes2.position.y = Test.y;
	_attributes2.position.z = Test.z;
	_attributes2.forward.z = -1.0f;
	_attributes2.up.y = 1.0f;
	FMOD_RESULT r;

	Ghoul.addEvent("event:/Ghoul/22 spotted");
	Ghoul.getEvent(0)->set3DAttributes(&_attributes2);
	Ghoul.playEvent(0);
	// Position the listener at the origin
	FMOD_3D_ATTRIBUTES attributes = { { 0 } };
	attributes.position.z = 3.0f;
	attributes.forward.z = 1.0f;
	attributes.up.y = 1.0f;
	r = StudioSound::_system->setListenerAttributes(0, &attributes);

	return true;
}

bool SimonScene::exit()
{
	return true;
}

void SimonScene::mouseFunction(double xpos, double ypos)
{
}

ButtonSequence::ButtonSequence(const std::vector<unsigned>& sequence)
{
	_sequence = sequence;
}

void ButtonSequence::update(CappInput& _in)
{
	static bool newIteration = true;

	if (!lives || win)
		return;

	static std::vector<unsigned> subsequence;

	if (newIteration) {

		subsequence.clear();
		subsequence.reserve(_iteration);

		for (unsigned i = 0; i < _iteration; i++) {
			subsequence.push_back(_sequence[i]);
			std::cout << subsequence[i] << "\n";
		}

		inputsequence.clear();
		inputsequence.reserve(subsequence.size());
		newIteration = false;
	}

	static bool wCon(0), aCon(0), sCon(0), dCon(0);
	//W
	if (_in.keyboard->keyPressed(KeyEvent::W) && !wCon) {
		wCon = true;
		inputsequence.push_back(1);
		std::cout << "ONE!\n";
	}
	else if (_in.keyboard->keyReleased(KeyEvent::W) && wCon)
		wCon = false;

	//S
	if (_in.keyboard->keyPressed(KeyEvent::S) && !sCon) {
		sCon = true;
		inputsequence.push_back(2);
		std::cout << "TWO!\n";
	}
	else if (_in.keyboard->keyReleased(KeyEvent::S) && sCon)
		sCon = false;

	//A
	if (_in.keyboard->keyPressed(KeyEvent::A) && !aCon) {
		aCon = true;
		inputsequence.push_back(3);
		std::cout << "THREE!\n";
	}
	else if (_in.keyboard->keyReleased(KeyEvent::A) && aCon)
		aCon = false;

	//D
	if (_in.keyboard->keyPressed(KeyEvent::D) && !dCon) {
		dCon = true;
		inputsequence.push_back(4);
		std::cout << "FOUR!\n";
	}
	else if (_in.keyboard->keyReleased(KeyEvent::D) && dCon)
		dCon = false;

	if (inputsequence == subsequence && inputsequence.size() == subsequence.size()) {
		_iteration++;

		if (_iteration == _sequence.size() + 1) {
			win = true;
			printf("you win!\n");
		}
		else
			printf("next round!\n\n");

		newIteration = true;
	}
	else if (inputsequence != subsequence && inputsequence.size() == subsequence.size()) {
		lives--;
		if (!lives)
			printf("you ran out of lives!\n");
		printf("wrong! try again!\n");
	}


}

