#include "beatstage.h"

BeatStage::BeatStage(PianoBar * pb)
{
	// save parameter(s) / init stuff
	_pb = pb;
	_timeSinceLastBeat = 0; 	// not sure if bad idea
	_beatInterval = 1; 			// once a second 

	// set up the beat "holder"
	setSize((int)WINDOW_WIDTH,(int)BEATSTAGE_HEIGHT);
	setX(0);
	setY(PIANOKEY_HEIGHT);
	setColor(Color::DarkSlateGray);

	// seed random generator
	srand(time(NULL));

	// a test beat
}

void BeatStage::_addBeat(Beat * beat)
{
	// set the original position of the beat (randomly)
	int random = rand() % (NUM_PIANO_KEYS + 1);     // random number between 0 and NUM_PIANO_KEYS, inclusive
	float xpos = random * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
	beat->setPosition(xpos,WINDOW_HEIGHT);
	beat->beginFall(5);  	// 5 seconds for beat to hit pianobar

	// set the note
	switch (random)
	{
		case 0: 
			beat->setNote('C');
			break;
		case 1: 
			beat->setNote('D');
			break;
		case 2: 
			beat->setNote('E');
			break;
		case 3: 
			beat->setNote('F');
			break;
		case 4: 
			beat->setNote('G');
			break;
		case 5: 
			beat->setNote('A');
			break;
		case 6: 
			beat->setNote('B');
			break;
	}

	_beats.push_back(beat);
	addChild(beat);
}

void BeatStage::update(const UpdateState & us)
{
	// first we must determine if any beats can be consumed (ie out of bounds or correctly chorded)
	for (int i = 0; i < _beats.size(); ++i)
	{
		if ((float)_beats[i]->getY() <= 0) 	// beat is in the consume zone; it's <= 0 b/c of the beatstage area
		{
			// TODO: change _consumeBeat to take in a vector, so we can have multiple beats at the same time
			if(_consumeBeat(_beats[i]))
			{
				// TODO: add score calulation
				log::messageln("Correct note(s) were pressed!");
			}
			else
			{
				log::messageln("A beat was missed");
			}

			// TODO: fade out the beat
			this->removeChild(_beats[i]);
			_beats.erase(_beats.begin()+i); 		// removes this beat from the array
													// don't need to increment i because array *should* "slide down"
		}
	}

	// now let's see if we want to add a beat (based on time interval)
	// NOTE: subject to change when music gets added
	if (_timeSinceLastBeat >= 1000*_beatInterval)
	{
		_addBeat(new Beat(PIANOKEY_WIDTH-BEAT_RADIUS_OFFSET));
		_timeSinceLastBeat = 0;
	}
	else
		_timeSinceLastBeat += us.dt;
	
	// update children -> since we overrode update, we must manually update children
	for (int i = 0; i < _beats.size(); ++i)
	{
		_beats[i]->update(us);
	}
}

bool BeatStage::_consumeBeat(Beat * beat)
{
	std::vector<PianoKey*> pressedKeys = _pb->getPressedKeys();
	
	// following code subject to change (when _consumeBeat accepts a vector of beats)
	if (pressedKeys.size() == 1 && *(pressedKeys[0]->getName()) == beat->getNote())
		return true;
	return false;
}
