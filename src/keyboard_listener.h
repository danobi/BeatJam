#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "oxygine-framework.h"
#include "pianobar.h"
#include <vector>

using namespace oxygine;

DECLARE_SMART(KeyboardListener,spKeyboardListener);

// TODO: find a better class to inherit from
class KeyboardListener : public ColorRectSprite
{
	public:
		/*
		 * this initializes a KeyboardListener, which 
		 * requires an already created PianoBar
		 * TODO: find a way to uncouple these classes
		 */
		KeyboardListener(spPianoBar pb);
	private:
		/*
		 * a helper function to make the code cleaner
		 * this function will make the appropirate calls to 
		 * press down a key and un-press the old key
		 */
		void updateKeyboard(char nkey);

		/*
		 * this helper function is called whenever a key is 
		 * pressed down, it determines which keys are currently
		 * pressed down, and makes appropriate calls to press down 
		 * one key and unpress the old one (if needed)
		 */
		void keyPressDownHandler(Event * ev);

		// private data
		char _currentNote;
		char _prevNote;
		spPianoBar _pianobar;
};

#endif
