#ifndef PIANOBAR_H
#define PIANOBAR_H

#include <vector>
#include "oxygine-framework.h"
#include "beatjam_constants.h"
#include "pianokey.h"

using namespace oxygine;

class PianoBar : public ColorRectSprite
{
	public:
		/*
		 * initializes the pianobar
		 */
		PianoBar();

		/*
		 * this function will press and animate the new key
		 * while also unpressing and "un"-animating the old key
		 * Note: this is for keyboard input only
		 */
		void keyboardUpdateKeys(char nkey); 

		/* 
		 * this function will return a vector of currently pressed PianoKey pointers
		 */
		std::vector<PianoKey*> getPressedKeys();
		
	private:
		/*
		PianoKey * key_c;  => piano_keys[0]
		PianoKey * key_d;  => piano_keys[1]
		PianoKey * key_e;  => etc
		PianoKey * key_f;
		PianoKey * key_g;
		PianoKey * key_a;
		PianoKey * key_b;
		*/
		PianoKey * _piano_keys[NUM_PIANO_KEYS];
		PianoKey * _keyboard_prev_pressed;
		PianoKey * _keyboard_curr_pressed;
};

#endif
