#ifndef BEATBORDER_H
#define BEATBORDER_H

#include "oxygine-framework.h"
#include "beatjam_constants.h"
#include "beat.h"

using namespace oxygine;

DECLARE_SMART(BeatBorder,spBeatBorder);

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
		void animateBeatHit(spBeat beat);

		/*
		 * animate a beat miss
		 */
		void animateBeatMiss(spBeat beat);

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
		 * private function to animate a beatborder fade out
		 */
		void _animateHide();

		/*
		 * private function to animate a beatborder fade in
		 */
		void _animateShow();

		/*
		 * private (hacky) fucntion to animate a red beatborder in
		 * and then it will fade out by itself in TWEEN_DURATION*3 time
		 */
		void _animateShowAndRedden();

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
