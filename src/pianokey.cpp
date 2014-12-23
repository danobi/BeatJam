#include "pianokey.h"

PianoKey::PianoKey()
{
	// set ease
	_ease = Tween::ease_outInBounce;

	// set tween duration
	_tween_dur = 200;

	// potential for mobile users pushing the keyboard
	this->addEventListener(TouchEvent::CLICK, CLOSURE(this,&PianoKey::clickHandler));

	// init name to nothing
	_name = "";

	_isPressed = false;
}
void PianoKey::keyPress()
{
	// press the key if it is not currently pressed
	if (!_isPressed) 	
	{
		_isPressed = !_isPressed;
		animatePress();
	}
	else
		log::messageln("Key %s: already is pressed",getName());
}

void PianoKey::keyUnPress()
{
	// press the key if it is not currently pressed
	if (_isPressed) 	
	{
		_isPressed = !_isPressed;
		animateUnPress();
	}
	else
		log::messageln("Key %s: already is un-pressed",getName());
}

void PianoKey::animatePress()
{
	// make the new key shrink a little 
	spTween tween = createTween(Actor::TweenScale(KEY_ORIGINAL_SIZE_FACTOR,KEY_SHRINK_FACTOR),_tween_dur,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
	tween->addEventListener(TweenEvent::DONE,CLOSURE(this,&PianoKey::tweenDone));
}

void PianoKey::animateUnPress()
{
	// make the old tween return to original size
	spTween tween = createTween(Actor::TweenScale(KEY_ORIGINAL_SIZE_FACTOR,KEY_ORIGINAL_SIZE_FACTOR),_tween_dur,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
	tween->addEventListener(TweenEvent::DONE,CLOSURE(this,&PianoKey::tweenDone));
}

void PianoKey::clickHandler(Event *)
{
	log::messageln("Clicked key %s",getName());
	if (!_isPressed)
		keyPress();
	else
		keyUnPress();
}

void PianoKey::tweenDone(Event *)
{
	// tween is done
	log::messageln("Finished tween: %s",this->_name.c_str());
}

bool PianoKey::isPressed()
{
	return _isPressed;
}

void PianoKey::setName(std::string n)
{
	this->_name = n;
}

const char * PianoKey::getName()
{
	return this->_name.c_str();
}
