#include "beatborder.h"

BeatBorder::BeatBorder(float scale)
{
	// init stuff
	_scale = scale;
	_gameResources.loadXML("res.xml");
	setResAnim(_gameResources.getResAnim("beat_border"));
	_note = '\0';
	_ease = Tween::ease_outInBounce;
	_isHidden = false;

	// anchor is the "center" of the object
	setAnchor(Vector2(.5f,.5f));
	
	// set scale
	this->setScale(scale,scale);
	
	// add a click handler
	this->addEventListener(TouchEvent::CLICK, CLOSURE(this,&BeatBorder::_clickHandler));
}

void BeatBorder::showBorder()
{
	// show border if it isn't already shown
	if (_isHidden) 	
	{
		_isHidden = !_isHidden;
		_animateShow();
	}
}

void BeatBorder::hideBorder()
{
	// hide border if it isn't already hidden
	if (!_isHidden) 	
	{
		_isHidden = !_isHidden;
		_animateHide();
	}
}

void BeatBorder::_animateShow()
{
	// make beat border visible
	spTween tween = createTween(Actor::TweenAlpha(255),TWEEN_DURATION,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
}

void BeatBorder::_animateHide()
{
	// make beat border invisible again
	spTween tween = createTween(Actor::TweenAlpha(0),TWEEN_DURATION,1,false);
	tween->setEase(_ease);
	this->addTween(tween);
}

bool BeatBorder::isHidden()
{
	return _isHidden;
}

void BeatBorder::setNote(char note)
{
	_note = note;
}

char BeatBorder::getNote()
{
	return _note;
}

void BeatBorder::_clickHandler(Event *)
{
	log::messageln("Clicked beat border");
}
