#include "pianobar.h"

PianoBar::PianoBar()
{
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
		piano_keys[i] = new PianoKey();

		// set position
		piano_keys[i]->setPosition(i * key_width,0);

		// set size
		piano_keys[i]->setSize(key_width,key_length);

		// set color
		if (i % 2 == 0)
			piano_keys[i]->setColor(Color::White);
		else
			piano_keys[i]->setColor(Color::Salmon);

		// set name
		switch (i)
		{
			case 0: 
				piano_keys[i]->setName("C");
				break;
			case 1: 
				piano_keys[i]->setName("D");
				break;
			case 2: 
				piano_keys[i]->setName("E");
				break;
			case 3: 
				piano_keys[i]->setName("F");
				break;
			case 4: 
				piano_keys[i]->setName("G");
				break;
			case 5: 
				piano_keys[i]->setName("A");
				break;
			case 6: 
				piano_keys[i]->setName("B");
				break;
		}

		// add child
		addChild(piano_keys[i]);
	}
}

void PianoBar::updateKeys(char okey, char nkey)
{
	switch (nkey)
	{
		case 'C':
			piano_keys[0]->keyPress();
			break;
		case 'D':
			piano_keys[1]->keyPress();
			break;
		case 'E':
			piano_keys[2]->keyPress();
			break;
		case 'F':
			piano_keys[3]->keyPress();
			break;
		case 'G':
			piano_keys[4]->keyPress();
			break;
		case 'A':
			piano_keys[5]->keyPress();
			break;
		case 'B':
			piano_keys[6]->keyPress();
			break;
	}

	switch (okey)
	{
		case 'C':
			piano_keys[0]->keyUnPress();
			break;
		case 'D':
			piano_keys[1]->keyUnPress();
			break;
		case 'E':
			piano_keys[2]->keyUnPress();
			break;
		case 'F':
			piano_keys[3]->keyUnPress();
			break;
		case 'G':
			piano_keys[4]->keyUnPress();
			break;
		case 'A':
			piano_keys[5]->keyUnPress();
			break;
		case 'B':
			piano_keys[6]->keyUnPress();
			break;
	}
}
