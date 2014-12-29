#include "pianobar.h"

PianoBar::PianoBar()
{
	// set object name
	this->setName("pianobar");
	
	// init private variables
	_keyboard_prev_pressed = NULL;
	_keyboard_curr_pressed = NULL;

	// set up the piano key "holder"
	setSize((int)WINDOW_WIDTH,(int)PIANOKEY_HEIGHT);
	setX(0);
	setY(0);
	setColor(Color::DarkSlateGray);

	// put the keys in the right spots
	for (int i = 0; i < NUM_PIANO_KEYS; ++i)
	{
		// init PianoKey
		_piano_keys[i] = new PianoKey();

		// set position
		_piano_keys[i]->setPosition(i * PIANOKEY_WIDTH,0);

		// set size
		_piano_keys[i]->setSize((int)PIANOKEY_WIDTH,(int)PIANOKEY_HEIGHT);

		// set color
		if (i % 2 == 0)
			_piano_keys[i]->setColor(Color::White);
		else
			_piano_keys[i]->setColor(Color::Salmon);

		// set name
		switch (i)
		{
			case 0: 
				_piano_keys[i]->setNote(KEY_0);
				break;
			case 1: 
				_piano_keys[i]->setNote(KEY_1);
				break;
			case 2: 
				_piano_keys[i]->setNote(KEY_2);
				break;
			case 3: 
				_piano_keys[i]->setNote(KEY_3);
				break;
			case 4: 
				_piano_keys[i]->setNote(KEY_4);
				break;
			case 5: 
				_piano_keys[i]->setNote(KEY_5);
				break;
			case 6: 
				_piano_keys[i]->setNote(KEY_6);
				break;
		}

		// add child
		addChild(_piano_keys[i]);
	}
}

void PianoBar::keyboardUpdateKeys(char nkey)
{
	// TODO: possibly add a mutex here since animations take longer than multiple game loops
	// set the previous keyboard key pressed
	 _keyboard_prev_pressed = _keyboard_curr_pressed; 

	// unpress the previous key
	if (_keyboard_prev_pressed)  // make sure not null
		_keyboard_prev_pressed->keyUnPress();

	// update and press the _keyboard_curr_pressed
	switch (nkey)
	{
		case KEY_0:
			if (!_piano_keys[0]->isPressed()) {
				_piano_keys[0]->keyPress();
				_keyboard_curr_pressed = _piano_keys[0];
			}
			break;
		case KEY_1:
			if (!_piano_keys[1]->isPressed()) {
				_piano_keys[1]->keyPress();
				_keyboard_curr_pressed = _piano_keys[1];
			}
			break;
		case KEY_2:
			if (!_piano_keys[2]->isPressed()) {
				_piano_keys[2]->keyPress();
				_keyboard_curr_pressed = _piano_keys[2];
			}
			break;
		case KEY_3:
			if (!_piano_keys[3]->isPressed()) {
				_piano_keys[3]->keyPress();
				_keyboard_curr_pressed = _piano_keys[3];
			}
			break;
		case KEY_4:
			if (!_piano_keys[4]->isPressed()) {
				_piano_keys[4]->keyPress();
				_keyboard_curr_pressed = _piano_keys[4];
			}
			break;
		case KEY_5:
			if (!_piano_keys[5]->isPressed()) {
				_piano_keys[5]->keyPress();
				_keyboard_curr_pressed = _piano_keys[5];
			}
			break;
		case KEY_6:
			if (!_piano_keys[6]->isPressed()) {
				_piano_keys[6]->keyPress();
				_keyboard_curr_pressed = _piano_keys[6];
			}
			break;
	}
}


std::vector<spPianoKey> PianoBar::getPressedKeys()
{
	std::vector<spPianoKey> re; 
	for (int i = 0; i < NUM_PIANO_KEYS; ++i)
	{
		if (_piano_keys[i]->isPressed())
			re.push_back(_piano_keys[i]);
	}
	return re;  // returns a deep copy
}
