#include "SimonScene.h"
#include <iostream>
#include <ctime>

FMOD_3D_ATTRIBUTES SimonScene::_attributes2 = { { 0 } };

SimonScene::SimonScene(bool yn)
	:Scene(yn), _in(true, std::nullopt)
{
	//these numbers actually dont matter
	sequences.push_back(new ButtonSequence(6));
}

void SimonScene::childUpdate(float dt)
{

	// Position the listener at the origin
	_attributes.forward.z = -1.0f;
	_attributes.up.y = 1.0f;
	FMOD_RESULT r;
	r = StudioSound::_system->setListenerAttributes(0, &_attributes);
	StudioSound::checkFmodErrors(r, "attrib");

	static int whichSequence = 0;

	//this is where the magic happens
	sequences[0]->update(_in, Music);
	sequences[0]->playQueue(Music);

}

bool SimonScene::init()
{
	//preliminary setup, and yes i know i can't spell
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

	//adding the proper event,neato burrito
	Music.addEvent("event:/Moonlight Sonata 1");
	Music.addEvent("event:/Moonlight Sonata 2");
	Music.addEvent("event:/Moonlight Sonata 3");
	Music.addEvent("event:/Moonlight Sonata 4");
	Music.addEvent("event:/Moonlight Sonata 5");
	Music.addEvent("event:/Moonlight Sonata 6");
	Music.getEvent(0)->set3DAttributes(&_attributes2);

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

ButtonSequence::ButtonSequence(unsigned numEvents)
	:_numEvents(numEvents)
{

}

void ButtonSequence::update(CappInput& _in, SoundBank& bank)
{
	static bool newIteration = true;

	if (!lives || win)
		return;


	//every new iteration, we want to add another note to the sequence (kinda doesnt work as intended right now)
	if (newIteration) {
		playQ.clear();
		playedEvent.clear();
		_sequence.clear();
		for (unsigned i = 0; i < _iteration; i++) {

			//decide which direction the sound should come from
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

			//put the number into the sequence
			_sequence.push_back(randStore);

			//this print statement is a debug feature
			std::cout << _sequence[i] << "\n";

			//set the 3D attributes of the sound
			SimonScene::_attributes2.position.x = Test.x;
			SimonScene::_attributes2.position.y = Test.y;
			SimonScene::_attributes2.position.z = Test.z;
			bank.getEvent(i)->set3DAttributes(&SimonScene::_attributes2);

			playQ.push_back(i);
			playedEvent.push_back(0);

		}



		//clear the player's input
		inputsequence.clear();
		inputsequence.reserve(_sequence.size());
		newIteration = false;
	}

	//static boooooooooooooooooooooooooooooooooooooooool
	//ive realised that this could be a function but i aint gonna recode it right now
	//all these if else statements just control the input keys so that you dont enter 3000 W's when you wanna enter 1
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

	//if the sequence is equal and they're the same size, the player has won the round and should advance 
	//(can prolly change this comparison around)
	if (inputsequence == _sequence && inputsequence.size() == _sequence.size()) {
		_iteration++;

		//hardcoded win condition for now
		if (_iteration == _numEvents) {
			win = true;
			printf("you win!\n");
		}
		else
			printf("next round!\n\n");

		newIteration = true;
	}
	//if the player failed the sequence, tell them they dun goofed and restart the round
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

void ButtonSequence::playQueue(SoundBank& bank)
{
	for (unsigned i = 0; i < playQ.size(); i++) {
		bool otherEventsPlaying = false;
		for (unsigned j = 0; j < playQ.size(); j++) {
			if (i == j)
				continue;
			if (bank.isEventPlaying(j)) {
				otherEventsPlaying = true;
				break;
			}
		}
		if (otherEventsPlaying)
			continue;
		else if (!bank.isEventPlaying(i) && !playedEvent[i]) {
			bank.playEvent(i);
			playedEvent[i] = true;
		}

	}
}

