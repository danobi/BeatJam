#ifndef PIANOBAR_H
#define PIANOBAR_H

#include "oxygine-framework.h"
#include "pianokey.h"

#define NUM_SCREEN_SECTIONS 5
#define NUM_PIANO_KEYS 7

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
	private:
		/*
		PianoKey * key_c   => piano_keys[0]
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
