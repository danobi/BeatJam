#include "pianokey.h"

PianoKey::PianoKey()
{
	// set tween ease
	_ease = Tween::ease_outInBounce;
	
	// potential for mobile users pushing the keyboard
	this->addEventListener(TouchEvent::CLICK, CLOSURE(this,&PianoKey::_clickHandler));

	// init note to nothing
	_note = '\0';

	_isPressed = false;
	_whoPressed = MOUSE_PRESS;
}
void PianoKey::keyPress()
{
	// press the key if it is not currently pressed
	if (!_isPressed) 	
	{
		_isPressed = !_isPressed;
		_animatePress();
		_whoPressed = KEYBOARD_PRESS;
	}
	else
		log::messageln("Key %c: already is pressed",getNote());
}

void PianoKey::keyUnPress()
{
	// press the key if it is not currently pressed
	if (_isPressed) 	
	{
		_isPressed = !_isPressed;
		_animateUnPress();
	}
	else
		log::messageln("Key %c: already is un-pressed",getNote());
}

void PianoKey::_animatePress()
{
	// make the new key shrink a little 
	spTween tween = createTween(Actor::TweenScale(KEY_ORIGINAL_SIZE_FACTOR,KEY_SHRINK_FACTOR),TWEEN_DURATION,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
	tween->addEventListener(TweenEvent::DONE,CLOSURE(this,&PianoKey::_tweenDone));
}

void PianoKey::_animateUnPress()
{
	// make the old tween return to original size
	spTween tween = createTween(Actor::TweenScale(KEY_ORIGINAL_SIZE_FACTOR,KEY_ORIGINAL_SIZE_FACTOR),TWEEN_DURATION,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
	tween->addEventListener(TweenEvent::DONE,CLOSURE(this,&PianoKey::_tweenDone));
}

void PianoKey::_clickHandler(Event *)
{
	log::messageln("Clicked key %c",getNote());
	if (!_isPressed)
	{
		keyPress();
		_whoPressed = MOUSE_PRESS; 	// kind of a hack, this executes after keyPress(..) sets it to keyboard press
	}
	else
		keyUnPress();
}

void PianoKey::_tweenDone(Event *)
{
	// tween is done
	//log::messageln("Finished tween: %s",this->_name.c_str());
}

bool PianoKey::isPressed()
{
	return _isPressed;
}

void PianoKey::setNote(char n)
{
	_note = n;
}

char PianoKey::getNote()
{
	return _note;;
}

int PianoKey::getPressedBy()
{
	return _whoPressed;
}
