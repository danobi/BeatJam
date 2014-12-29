#ifndef BEATBORDER_H
#define BEATBORDER_H

#include "oxygine-framework.h"
#include "beatjam_constants.h"
#include "beat.h"

using namespace oxygine;

class BeatBorder : public Sprite
{
	public:
		/*
		 * creates a beat border according to scale
		 * does NOT set location
		 */
		BeatBorder(float scale);

		/*
		 * shows a border if it isn't already shown
		 * and then animates it
		 */
		void showBorder();

		/*
		 * hides a border if it isn't already shown
		 * and then animates it
		 */
		void hideBorder();

		/*
		 * animate a beat hit
		 */
		void animateBeatHit(Beat * beat);

		/*
		 * animate a beat miss
		 */
		void animateBeatMiss(Beat * beat);

		/*
		 * returns if the key is currently pressed or not
		 */
		bool isHidden();

		/*
		 * setters/getters for which note this beat border belongs to
		 */
		void setNote(char note);
		char getNote();

	private:
		/*
		 * private function to animate a highlight
		 */
		void _animateHide();

		/*
		 * private function to animate a un-highlight
		 */
		void _animateShow();

		/*
		 * simple click handler
		 */
		void _clickHandler(Event *);

		// private data
		Resources _gameResources;
		float _scale;
		char _note; 		// which note this belongs to
		Tween::EASE _ease;
		bool _isHidden;
};

#endif
