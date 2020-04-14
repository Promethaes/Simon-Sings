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
		_attributes.position.z += 3.0f * dt;
	_attributes.forward.z = -1.0f;
	_attributes.up.y = 1.0f;
	r = StudioSound::_system->setListenerAttributes(0, &_attributes);
	StudioSound::checkFmodErrors(r, "attrib");


	r = eventInstance->set3DAttributes(&_attributes2);
	StudioSound::checkFmodErrors(r, "attrib");
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
	FMOD::Studio::EventDescription* eventDescription = NULL;
	r = StudioSound::_system->getEvent("event:/Vehicles/Ride-on Mower", &eventDescription);
	StudioSound::checkFmodErrors(r, "vehicles event desc");


	r = eventDescription->createInstance(&eventInstance);
	StudioSound::checkFmodErrors(r, "create instance");

	r = eventInstance->setParameterByName("RPM", 650.0f);
	StudioSound::checkFmodErrors(r, "RPM meme");

	r = eventInstance->start();
	StudioSound::checkFmodErrors(r, "starting event");
	// Position the listener at the origin
	FMOD_3D_ATTRIBUTES attributes = { { 0 } };
	attributes.position.z = 3.0f;
	attributes.forward.z = 1.0f;
	attributes.up.y = 1.0f;
	r = StudioSound::_system->setListenerAttributes(0, &attributes);

	// Position the event 2 units in front of the listener
	attributes.position.z = 2.0f;
	r = eventInstance->set3DAttributes(&attributes);

	return true;
}

bool SimonScene::exit()
{
	return true;
}

void SimonScene::mouseFunction(double xpos, double ypos)
{
}
