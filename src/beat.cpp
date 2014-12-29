#include "beat.h"

Beat::Beat()
{
	// load resources
	_gameResources.loadXML("res.xml");  

	// anchor is the "center" of the object
	setAnchor(Vector2(.5f,.5f));

	// add a click handler
	this->addEventListener(TouchEvent::CLICK, CLOSURE(this,&Beat::_clickHandler));

	// defaults
	_radius = 0;
	_timeforfall = 0;   // perhaps setting to 0 is a bad idea
	_isFalling = false;
	_note = '\0';
	_type = KEYBOARD_BEAT;
}

// not sure if this constructor delegation is allowed without using c++11
Beat::Beat(int radius, int type) : Beat()
{
	_radius = radius;
	_type = type;

	if (_type == MOUSE_BEAT)
		setResAnim(_gameResources.getResAnim("mouse_beat"));
	else // if (_type == KEYBOARD_BEAT)
		setResAnim(_gameResources.getResAnim("keyboard_beat"));
	
	// make the beat the correct size 
	float scale = _radius / this->getWidth();
	this->setScale(scale,scale);
}

void Beat::beginFall(float timeforfall)
{
	_timeforfall = timeforfall;
	_isFalling = true;
}

void Beat::doUpdate(const UpdateState & us)
{
	// this takes into account the fall rate is linear
	if (_isFalling)
	{
		//log::messageln("we falling");
		float totaltimems = _timeforfall * 1000;     
		float deltafrac = ((float)us.dt) / totaltimems;
		_fall(BEATSTAGE_HEIGHT * deltafrac);
	}
}

void Beat::addAnimateTween(spTween tween)
{
	_tween_queue.push_back(tween);
}

void Beat::runAnimateTween()
{
	for (int i = 0; i < _tween_queue.size(); ++i)
	{
		this->addTween(_tween_queue[i]);

		// if this is the last tween in the queue, we want to remove the beat object from BeatBorder when done
		if (i == _tween_queue.size() - 1) 
			_tween_queue[i]->addEventListener(TweenEvent::DONE,CLOSURE(this,&Beat::_tweenDone));
	}
}

void Beat::_fall(float px)
{
	float oldy = this->getY();
	float newy = oldy - px;
	this->setPosition(this->getX(),newy);
}

void Beat::_clickHandler(Event *)
{
	log::messageln("Clicked beat");
}

void Beat::_tweenDone(Event *)
{
	log::messageln("Detaching (animation) beat from BeatBorder");
	this->detach();
}

void Beat::setNote(char note)
{
	_note = note;
}

char Beat::getNote()
{
	return _note;
}

void Beat::setRadius(int rad)
{
	_radius = rad;
}

int Beat::getRadius()
{
	return _radius;
}

void Beat::setType(int type)
{
	_type = type;
}

int Beat::getType()
{
	return _type;
}
