#include "SimonScene.h"
#include <iostream>
#include <ctime>

FMOD_3D_ATTRIBUTES SimonScene::_attributes2 = { { 0 } };

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

	if (!Music.isEventPlaying(0)) {//change the condition later

		
	}

	sequences[0]->update(_in,Music);

}

bool SimonScene::init()
{
	srand(time(0));
	glm::vec3 Test;
	Test.x = 0.0f;
	Test.y = 0.0f;
	Test.z = 0.0f;

	_attributes2.position.x = Test.x;
	_attributes2.position.y = Test.y;
	_attributes2.position.z = Test.z;
	_attributes2.forward.z = -1.0f;
	_attributes2.up.y = 1.0f;
	FMOD_RESULT r;

	Music.addEvent("event:/Fur Elise");
	Music.getEvent(0)->set3DAttributes(&_attributes2);

	//Music.getEvent(0)->setParameterByName("parameter:/note1", 1.0f);
	//Music.playEvent(0);
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
	
}

void ButtonSequence::update(CappInput& _in, SoundBank& bank)
{
	static bool newIteration = true;

	if (!lives || win)
		return;


	if (newIteration) {
		
		_sequence.clear();
		for (unsigned i = 0; i < _iteration; i++) {

			glm::vec3 Test;
			Test.x = 0.0f;
			Test.y = 0.0f;
			Test.z = 0.0f;

			auto randStore = 1 + (rand() % 4);

			if (randStore == 3)
				Test.x += 3.0f;
			else if (randStore == 4)
				Test.x -= 3.0f;
			else if (randStore == 1)
				Test.z += 3.0f;
			else if (randStore == 2)
				Test.z -= 3.0f;

			_sequence.push_back(randStore);
			std::cout << _sequence[i] << "\n";

			SimonScene::_attributes2.position.x = Test.x;
			SimonScene::_attributes2.position.y = Test.y;
			SimonScene::_attributes2.position.z = Test.z;
			bank.getEvent(0)->set3DAttributes(&SimonScene::_attributes2);
			auto param = "parameter:/note" + std::to_string(_iteration);
			bank.getEvent(0)->setParameterByName(param.c_str(), 1.0f);
			bank.playEvent(0);

		}


		inputsequence.clear();
		inputsequence.reserve(_sequence.size());
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

	if (inputsequence == _sequence && inputsequence.size() == _sequence.size()) {
		_iteration++;

		if (_iteration == 20) {
			win = true;
			printf("you win!\n");
		}
		else
			printf("next round!\n\n");

		newIteration = true;
	}
	else if (inputsequence != _sequence && inputsequence.size() == _sequence.size()) {
		lives--;
		if (!lives)
			printf("you ran out of lives!\n");
		else {
			printf("wrong! try again!\n");
			newIteration = true;
		}
	}


}

