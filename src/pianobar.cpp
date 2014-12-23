#include "pianobar.h"

PianoBar::PianoBar()
{
	// init private variables
	_keyboard_prev_pressed = NULL;
	_keyboard_curr_pressed = NULL;

	// calculate dimesions for piano keys
	int screen_length = getStage()->getHeight();
	int screen_width = getStage()->getWidth();
	int key_length = screen_length / NUM_SCREEN_SECTIONS;
	int key_width = screen_width / NUM_PIANO_KEYS;
	
	// set up the piano key "holder"
	setSize(screen_width,key_length); 
	setX(0);
	setY(0);
	setColor(Color::Black);

	// put the keys in the right spots
	for (int i = 0; i < NUM_PIANO_KEYS; ++i)
	{
		// init PianoKey
		_piano_keys[i] = new PianoKey();

		// set position
		_piano_keys[i]->setPosition(i * key_width,0);

		// set size
		_piano_keys[i]->setSize(key_width,key_length);

		// set color
		if (i % 2 == 0)
			_piano_keys[i]->setColor(Color::White);
		else
			_piano_keys[i]->setColor(Color::Salmon);

		// set name
		switch (i)
		{
			case 0: 
				_piano_keys[i]->setName("C");
				break;
			case 1: 
				_piano_keys[i]->setName("D");
				break;
			case 2: 
				_piano_keys[i]->setName("E");
				break;
			case 3: 
				_piano_keys[i]->setName("F");
				break;
			case 4: 
				_piano_keys[i]->setName("G");
				break;
			case 5: 
				_piano_keys[i]->setName("A");
				break;
			case 6: 
				_piano_keys[i]->setName("B");
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
		case 'C':
			if (!_piano_keys[0]->isPressed()) {
				_piano_keys[0]->keyPress();
				_keyboard_curr_pressed = _piano_keys[0];
			}
			break;
		case 'D':
			if (!_piano_keys[1]->isPressed()) {
				_piano_keys[1]->keyPress();
				_keyboard_curr_pressed = _piano_keys[1];
			}
			break;
		case 'E':
			if (!_piano_keys[2]->isPressed()) {
				_piano_keys[2]->keyPress();
				_keyboard_curr_pressed = _piano_keys[2];
			}
			break;
		case 'F':
			if (!_piano_keys[3]->isPressed()) {
				_piano_keys[3]->keyPress();
				_keyboard_curr_pressed = _piano_keys[3];
			}
			break;
		case 'G':
			if (!_piano_keys[4]->isPressed()) {
				_piano_keys[4]->keyPress();
				_keyboard_curr_pressed = _piano_keys[4];
			}
			break;
		case 'A':
			if (!_piano_keys[5]->isPressed()) {
				_piano_keys[5]->keyPress();
				_keyboard_curr_pressed = _piano_keys[5];
			}
			break;
		case 'B':
			if (!_piano_keys[6]->isPressed()) {
				_piano_keys[6]->keyPress();
				_keyboard_curr_pressed = _piano_keys[6];
			}
			break;
	}

}
