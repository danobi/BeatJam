#include "beatstage.h"

BeatStage::BeatStage(spPianoBar pb)
{
	// save parameter(s) / init stuff
	_pb = pb;
	_timeSinceLastSubBeat = 0;
	_timeSinceLastBeat = 0; 	// not sure if bad idea
	_currentBeat = 1;
	_currentSubBeat = 1;

	// set up the beat "holder"
	setSize((int)WINDOW_WIDTH,(int)BEATSTAGE_HEIGHT);
	setX(0);
	setY(PIANOKEY_HEIGHT);
	setColor(Color::DarkSlateGray);

	// set up the beat borders (where the beat gets consumed)
	_addBeatBorders();

	// seed random generator
	srand(time(NULL));

	// set up beatscore stuff
	bsp = new BeatscoreParser(std::string("beatscore/test.beatj"));
	_BPM = bsp->getBPM();
	_songlength = bsp->getLength();
	_songname = bsp->getSongName();
	if (!DEBUG_MODE) {
		// interval = length of song / num total beats
		_beatInterval = (float)_songlength/ ((float)_songlength / 60 * _BPM);
		_subBeatInterval = _beatInterval / 4;
	}
	else {
		_beatInterval = 3.0; 			// once every 3 seconds
	}


	// DEBUG WORK HERE
	/*
	BeatscoreParser bsp(std::string("beatscore/test.beatj"));
	log::messageln("%c%c%c%c",bsp.getNoteAtBeat(1,1),bsp.getNoteAtBeat(1,2),bsp.getNoteAtBeat(1,3),bsp.getNoteAtBeat(1,4));
	log::messageln("%c%c%c%c",bsp.getNoteAtBeat(226,1),bsp.getNoteAtBeat(226,2),bsp.getNoteAtBeat(226,3),bsp.getNoteAtBeat(226,4));
	log::messageln("%c%c%c%c",bsp.getNoteAtBeat(157,1),bsp.getNoteAtBeat(157,2),bsp.getNoteAtBeat(157,3),bsp.getNoteAtBeat(157,4));
	*/
}

BeatStage::~BeatStage()
{
	delete bsp;
}

void BeatStage::doUpdate(const UpdateState & us)
{
	// determine if any beats can be consumed (ie out of bounds or correctly chorded)
	std::vector<spBeat> consum;
	for (int i = 0; i < _beats.size(); ++i) {
		if ((float)_beats[i]->getY() <= _beatborder_ypos) 	// beat is in the consume zone
			consum.push_back(_beats[i]);
	}

	// do score calculation / hit + miss animations
	if(_consumeBeat(consum)) {
		// TODO: add score calulation
		
		// find the right border to animate a hit on
		for (int i = 0; i < consum.size(); ++i) {
			for (int z = 0; z < _beatborders.size(); ++z) {
				if (_beatborders[z]->getNote() == consum[i]->getNote()) {
					_beatborders[z]->animateBeatHit(consum[i]);
				}
			}
		}
	} 
	else {
		// find the right border to animate a miss on
		for (int i = 0; i < consum.size(); ++i)
			for (int z = 0; z < _beatborders.size(); ++z) {
				if (_beatborders[z]->getNote() == consum[i]->getNote()) {
					_beatborders[z]->animateBeatMiss(consum[i]);
				}
			}
	}

	// remove the relevant beats from the beatstage
	for (int i = 0; i < consum.size(); ++i) {
		for (int j = 0; j < _beats.size(); ++j) {
			if (consum[i] == _beats[j]) {
				this->removeChild(_beats[j]);
				_beats.erase(_beats.begin()+j); 		// removes this beat from the array
														// don't need to increment i because array *should* "slide down"
				break;
			}
		}
	}

	// see if we need to add a beat
	if (!DEBUG_MODE) {
		// TODO: need to take into account that the game will wait 1 subbeat interval before dropping any beats
		if (_timeSinceLastSubBeat >= 1000*_subBeatInterval)	{
			_addScoreBeat();

			// update counters
			_timeSinceLastSubBeat = 0;
			_currentSubBeat < 4 ? _currentSubBeat++ : _currentSubBeat = 1;
			if (_currentSubBeat == 1) _currentBeat++;
		}
		else
			_timeSinceLastSubBeat += us.dt;
	}
	else {
		// debug mode, we add a random beat every _beatInterval seconds
		if (_timeSinceLastBeat >= 1000*_beatInterval) {
			int random = rand() * 100; 	// random number between 0 and 99 inclusive
			if (random <= 25) 
				_addRandomBeat(new Beat(BEAT_RADIUS,MOUSE_BEAT));
			else
				_addRandomBeat(new Beat(BEAT_RADIUS,KEYBOARD_BEAT));

			// update counter
			_timeSinceLastBeat = 0;
		} 
		else
			_timeSinceLastBeat += us.dt;
	}
	
	// see if we need to highlight or unhighlight border
	for (int i = 0; i < _beatborders.size(); ++i) {
		std::vector<spPianoKey> pressedkeys = _pb->getPressedKeys();
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

void BeatStage::_addScoreBeat()
{
	parsedSubBeat cbeat = bsp->getNotesAtBeat(_currentBeat,_currentSubBeat);
	if (cbeat.notes.size() > 0) {
		for (int i = 0; i < cbeat.notes.size(); ++i) {
			char note = cbeat.notes[i].note;
			int type = cbeat.notes[i].type;

			spBeat beat = new Beat(BEAT_RADIUS,type);
			beat->setNote(note);

			// set the position
			int x;
			switch (note) {
				case KEY_0: x = 0; break;
				case KEY_1: x = 1; break;
				case KEY_2: x = 2; break;
				case KEY_3: x = 3; break;
				case KEY_4: x = 4; break;
				case KEY_5: x = 5; break;
				case KEY_6: x = 6; break;
				default: 
					// if this executes, then something seriously went wrong
					// this should have been prevented by BeatscoreParser::_isValidNote(..) validation
					log::messageln("_addBeat: error -> unrecognized key, this should not have been possible!");
					exit(EXIT_FAILURE);
			}
			float xpos = x * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
			beat->setPosition(xpos,WINDOW_HEIGHT);
			beat->beginFall(5);  	// 5 seconds for beat to hit pianobar

			// add beat in
			_beats.push_back(beat);
			addChild(beat);
		}
	}
}

void BeatStage::_addRandomBeat(spBeat beat)
{
	// set the original position of the beat (randomly)
	int random = rand() % NUM_PIANO_KEYS;     // random number between 0 and NUM_PIANO_KEYS-1, inclusive
	float xpos = random * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
	beat->setPosition(xpos,WINDOW_HEIGHT);
	beat->beginFall(5);  	// 5 seconds for beat to hit pianobar

	// set the note
	switch (random) {
		case 0: beat->setNote(KEY_0); break;
		case 1: beat->setNote(KEY_1); break;
		case 2: beat->setNote(KEY_2); break;
		case 3: beat->setNote(KEY_3); break;
		case 4: beat->setNote(KEY_4); break;
		case 5: beat->setNote(KEY_5); break;
		case 6: beat->setNote(KEY_6); break;
	}

	// add beat in 
	_beats.push_back(beat);
	addChild(beat);
}

bool BeatStage::_consumeBeat(std::vector<spBeat> beats)
{
	// get all the pressed pianokeys at this moment
	std::vector<spPianoKey> pressedKeys = _pb->getPressedKeys();

	// fail the consume if more keys pressed than beats, or vis versa
	if (beats.size() != pressedKeys.size()) return false;

	// now do a detailed check -> make sure each beat has a corresponding keypress
	for (int i = 0; i < beats.size(); ++i) {
		bool foundkey = false;
		for (int j = 0; j < pressedKeys.size(); ++j) 
			if (beats[i]->getNote() == pressedKeys[i]->getNote() && beats[i]->getType() == pressedKeys[i]->getPressedBy())
				foundkey = true;
		if (!foundkey) return false;
	}
	return true;
}

void BeatStage::_addBeatBorders()
{
	BeatBorder temp(1.0f);  	// this temp beat border has scale 1.0
	float scale = (float)BEAT_RADIUS / temp.getWidth() + BEATBORDER_SCALE_OFFSET;

	for (int i = 0; i < NUM_PIANO_KEYS; ++i) {
		spBeatBorder bb = new BeatBorder(scale);

		// do position calculation
		float xpos = i * (float)PIANOKEY_WIDTH + (float)PIANOKEY_WIDTH / 2;
		float ypos = BEATBORDER_Y_OFFSET + scale * (float)bb->getHeight() / 2;
		_beatborder_ypos = ypos;
		bb->setPosition(xpos,ypos);

		// hide it to begin
		bb->hideBorder();

		// set notes
		switch (i) {
			case 0: bb->setNote(KEY_0); break;
			case 1: bb->setNote(KEY_1); break;
			case 2: bb->setNote(KEY_2); break;
			case 3: bb->setNote(KEY_3); break;
			case 4: bb->setNote(KEY_4); break;
			case 5: bb->setNote(KEY_5); break;
			case 6: bb->setNote(KEY_6); break;
		}
		_beatborders.push_back(bb);
		addChild(bb);
	}
}
