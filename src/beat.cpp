#include "beat.h"

Beat::Beat()
{
	// get the image from the res.xml file
	_gameResources.loadXML("res.xml");
	setResAnim(_gameResources.getResAnim("circle"));

	// anchor is the "center" of the object
	setAnchor(Vector2(.5f,.5f));

	// add a click handler
	this->addEventListener(TouchEvent::CLICK, CLOSURE(this,&Beat::_clickHandler));

	// defaults
	_radius = 0;
	_timeforfall = 0;   // perhaps this is a bad idea
	_isFalling = false;
	_note = '\0';
}

// not sure if this constructor delegation is allowed without using c++11
Beat::Beat(int radius) : Beat()
{
	_radius = radius;
	
	// make the beat the correct size (radius = width of pianokey)
	float scale = _radius / this->getWidth();
	this->setScale(scale,scale);
}

void Beat::beginFall(float timeforfall)
{
	_timeforfall = timeforfall;
	_isFalling = true;
}

void Beat::update(const UpdateState & us)
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

void Beat::setNote(char note)
{
	_note = note;
}

char Beat::getNote()
{
	return _note;
}
