#include "beatstage.h"

BeatStage::BeatStage(PianoBar * pb)
{
	// save parameter(s) / init stuff
	_pb = pb;
	_timeSinceLastBeat = 0; 	// not sure if bad idea
	_beatInterval = 3; 			// once a second 

	// set up the beat "holder"
	setSize((int)WINDOW_WIDTH,(int)BEATSTAGE_HEIGHT);
	setX(0);
	setY(PIANOKEY_HEIGHT);
	setColor(Color::DarkSlateGray);

	// set up the beat borders (where the beat gets consumed)
	_addBeatBorders();

	// seed random generator
	srand(time(NULL));
}

void BeatStage::_addBeat(Beat * beat)
{
	// set the original position of the beat (randomly)
	int random = rand() % NUM_PIANO_KEYS;     // random number between 0 and NUM_PIANO_KEYS-1, inclusive
	float xpos = random * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
	beat->setPosition(xpos,WINDOW_HEIGHT);
	beat->beginFall(5);  	// 5 seconds for beat to hit pianobar

	// set the note
	switch (random)
	{
		case 0: 
			beat->setNote(KEY_0);
			break;
		case 1: 
			beat->setNote(KEY_1);
			break;
		case 2: 
			beat->setNote(KEY_2);
			break;
		case 3: 
			beat->setNote(KEY_3);
			break;
		case 4: 
			beat->setNote(KEY_4);
			break;
		case 5: 
			beat->setNote(KEY_5);
			break;
		case 6: 
			beat->setNote(KEY_6);
			break;
	}

	_beats.push_back(beat);
	addChild(beat);
}

void BeatStage::doUpdate(const UpdateState & us)
{
	// we must determine if any beats can be consumed (ie out of bounds or correctly chorded)
	for (int i = 0; i < _beats.size(); ++i)
	{
		if ((float)_beats[i]->getY() <= _beatborder_ypos) 	// beat is in the consume zone
		{
			// TODO: change _consumeBeat to take in a vector, so we can have multiple beats at the same time
			if(_consumeBeat(_beats[i]))
			{
				// TODO: add score calulation
				
				// find the right border to animate a hit on
				for (int z = 0; z < _beatborders.size(); ++z)
				{
					if (_beatborders[z]->getNote() == _beats[i]->getNote()) {
						_beatborders[z]->animateBeatHit(_beats[i]);
						break;
					}
				}
			}
			else
			{
				// find the right border to animate a hit on
				for (int z = 0; z < _beatborders.size(); ++z)
				{
					if (_beatborders[z]->getNote() == _beats[i]->getNote()) {
						_beatborders[z]->animateBeatMiss(_beats[i]);
						break;
					}
				}

			}

			this->removeChild(_beats[i]);
			_beats.erase(_beats.begin()+i); 		// removes this beat from the array
													// don't need to increment i because array *should* "slide down"
		}
	}

	// now let's see if we want to add a beat (based on time interval) NOTE: subject to change when music gets added
	if (_timeSinceLastBeat >= 1000*_beatInterval)
	{
		int random = rand() * 100; 	// random number between 0 and 99 inclusive
		if (random <= 25)
			_addBeat(new Beat(BEAT_RADIUS,MOUSE_BEAT));
		else
			_addBeat(new Beat(BEAT_RADIUS,KEYBOARD_BEAT));

		// reset counter
		_timeSinceLastBeat = 0;
	}
	else
		_timeSinceLastBeat += us.dt;
	
	for (int i = 0; i < _beatborders.size(); ++i)
	{
		// see if we need to highlight or unhighlight border
		std::vector<PianoKey*> pressedkeys = _pb->getPressedKeys();
		bool foundkey = false;
		for (int j = 0; j < pressedkeys.size(); ++j)
			if (pressedkeys[j]->getNote() == _beatborders[i]->getNote())
				foundkey = true;
		if (foundkey)
			_beatborders[i]->showBorder();
		else
			_beatborders[i]->hideBorder();
	}
}

bool BeatStage::_consumeBeat(Beat * beat)
{
	std::vector<PianoKey*> pressedKeys = _pb->getPressedKeys();
	
	// following code subject to change (when _consumeBeat accepts a vector of beats)
	if (pressedKeys.size() == 1 && pressedKeys[0]->getNote() == beat->getNote() && pressedKeys[0]->getPressedBy() == beat->getType())
		return true;
	return false;
}

void BeatStage::_addBeatBorders()
{
	BeatBorder temp(1.0f);  	// this temp beat border has scale 1.0
	float scale = (float)BEAT_RADIUS / temp.getWidth() + BEATBORDER_SCALE_OFFSET;

	for (int i = 0; i < NUM_PIANO_KEYS; ++i)
	{
		BeatBorder * bb = new BeatBorder(scale);

		// do position calculation
		float xpos = i * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
		float ypos = BEATBORDER_Y_OFFSET + scale * (float)bb->getHeight() / 2;
		_beatborder_ypos = ypos;
		bb->setPosition(xpos,ypos);

		// hide it to begin
		bb->hideBorder();

		// set notes
		switch (i)
		{
			case 0: 
				bb->setNote(KEY_0);
				break;
			case 1: 
				bb->setNote(KEY_1);
				break;
			case 2: 
				bb->setNote(KEY_2);
				break;
			case 3: 
				bb->setNote(KEY_3);
				break;
			case 4: 
				bb->setNote(KEY_4);
				break;
			case 5: 
				bb->setNote(KEY_5);
				break;
			case 6: 
				bb->setNote(KEY_6);
				break;
		}
		_beatborders.push_back(bb);
		addChild(bb);
	}
}
