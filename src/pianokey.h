#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <string>
#include "oxygine-framework.h"

#define KEY_SHRINK_FACTOR .7
#define KEY_ORIGINAL_SIZE_FACTOR 1

using namespace oxygine;

class PianoKey : public ColorRectSprite
{
	public:
		/*
		 * initializes a default PianoKey
		 */
		PianoKey();

		/*
		 * presses a key down (if it is unpressed already)
		 * and then animates it
		 */
		void keyPress();

		/*
		 * un-presses a key (if it is already pressed)
		 * and then animates it
		 */
		void keyUnPress();

		/*
		 * sets the name of the PianoKey
		 */
		void setName(std::string n);

		/*
		 * gets the name of the PianoKey
		 */
		const char * getName();
	private:
		/*
		 * private function to animate a press down
		 */
		void animatePress();

		/*
		 * private function to animate a un-press
		 */
		void animateUnPress();

		/* 
		 * handles the piano key being pressed
		 * mouse clicked keys have a different mechanic than keyboard activated
		 */
		void clickHandler(Event *);

		/*
		 * this gets called when the tween animation is done
		 * this includes pressing and un-pressing
		 */
		void tweenDone(Event *);

		// private data
		Tween::EASE _ease;
		int _tween_dur;
		std::string _name;
		bool _isPressed;
};

#endif
