#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <string>
#include "oxygine-framework.h"
#include "beatjam_constants.h"

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
		 * returns if the key is currently pressed or not
		 */
		bool isPressed();

		/*
		 * sets the name of the PianoKey
		 */
		void setNote(char n);

		/*
		 * gets the name of the PianoKey
		 */
		char getNote();

		/*
		 * gets who pressed the key
		 */
		int getPressedBy();
	private:
		/*
		 * private function to animate a press down
		 */
		void _animatePress();

		/*
		 * private function to animate a un-press
		 */
		void _animateUnPress();

		/* 
		 * handles the piano key being pressed
		 * mouse clicked keys have a different mechanic than keyboard activated
		 */
		void _clickHandler(Event *);

		/*
		 * this gets called when the tween animation is done
		 * this includes pressing and un-pressing
		 */
		void _tweenDone(Event *);

		// private data
		Tween::EASE _ease;
		char _note;
		bool _isPressed;
		int _whoPressed; 	// who the key was pressed by
};

#endif
