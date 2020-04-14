#include "SimonScene.h"

SimonScene::SimonScene(bool yn)
	:Scene(yn), _in(true, std::nullopt)
{
}

void SimonScene::childUpdate(float dt)
{
	FMOD_RESULT r;
	// Position the listener at the origin

	if (_in.keyboard->keyPressed(KeyEvent::W))
		_attributes.position.x += 3.0f * dt;
	_attributes.forward.z = -1.0f;
	_attributes.up.y = 1.0f;
	r = StudioSound::_system->setListenerAttributes(0, &_attributes);
	StudioSound::checkFmodErrors(r, "attrib");

	if (!Ghoul.isEventPlaying(0))
		Ghoul.playEvent(0);

	Ghoul.getEvent(0)->set3DAttributes(&_attributes2);
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
