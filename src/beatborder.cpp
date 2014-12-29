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


void BeatBorder::animateBeatHit(spBeat beat)
{
	// add a fading out tween
	spTween fade_tween = createTween(Actor::TweenAlpha(0),TWEEN_DURATION,1,false);
	Tween::EASE ease = Tween::ease_outInBounce;
	fade_tween->setEase(ease);
	
	// add an expanding tween
	spTween expand_tween = createTween(Actor::TweenScale(2,2),TWEEN_DURATION,1,false);
	expand_tween->setEase(ease);

	// make a child that is a deep copy of "beat"
	spBeat nbeat = new Beat(beat->getRadius(),beat->getType());
	nbeat->setScale(1);	 // not sure why, but we have to do this to make the size correct
	nbeat->setPosition(this->getWidth()/2,this->getHeight()/2);

	// add animations
	nbeat->addAnimateTween(fade_tween);
	nbeat->addAnimateTween(expand_tween);
	nbeat->runAnimateTween();

	this->addChild(nbeat);
}

void BeatBorder::animateBeatMiss(spBeat beat)
{
	// add a fading out tween
	spTween fade_tween = createTween(Actor::TweenAlpha(0),TWEEN_DURATION,1,false);
	Tween::EASE ease = Tween::ease_outInBounce;
	fade_tween->setEase(ease);

	// add a redden tween
	spTween redden_tween = createTween(Sprite::TweenColor(Color(255,0,0,255)),TWEEN_DURATION,1,false);
	redden_tween->setEase(ease);
	
	// make a child that is a deep copy of "beat"
	spBeat nbeat = new Beat(beat->getRadius(),beat->getType());
	nbeat->setScale(1);	 // not sure why, but we have to do this to make the size correct
	nbeat->setPosition(this->getWidth()/2,this->getHeight()/2);

	// add animations
	//nbeat->addAnimateTween(fade_tween);
	nbeat->addAnimateTween(redden_tween);
	nbeat->runAnimateTween();

	_animateShowAndRedden();
	this->addChild(nbeat);
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

void BeatBorder::_animateShowAndRedden()
{
	// show border if it isn't already shown
	if (_isHidden) 	
	{
		// flip the flag
		_isHidden = !_isHidden;

		// do the animation
		spTween tween = createTween(Actor::TweenAlpha(255),TWEEN_DURATION*3,1,true);    // not sure why duration is *3
		tween->setEase(_ease);
		this->addTween(tween);

		// flip it again
		_isHidden = !_isHidden;
	}
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
