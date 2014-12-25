#ifndef BEATSTAGE_H
#define BEATSTAGE_H

#include <vector>
#include <time.h>
#include "oxygine-framework.h"
#include "beatjam_constants.h"
#include "pianobar.h"
#include "beat.h"

using namespace oxygine;

// TODO: find a better class to inherit from 
class BeatStage : public ColorRectSprite
{
	public:
		// TODO: find a way to decouple PianoBar
		BeatStage(PianoBar * pb);

		/*
		 * overrides the default update, this checks to see if the user has presed the correct chord
		 */
		virtual void update(const UpdateState & us);
	private:
		/*
		 * adds a beat to a *randomized* starting point (on the bottom of the screen -> ie opposite to the pianobar
		 * beat must be initialized before passing it in
		 */
		void _addBeat(Beat * beat);

		/*
		 * this function will check to see if the user has the right keys chorded at the instant this is called
		 * it will return whether or not the user had the notes pressed
		 * there are no side effects
		 */
		bool _consumeBeat(Beat * beat);

		// private data
		std::vector<Beat*> _beats;  		// array of currently VALID beats in the beatstage
		PianoBar * _pb;
		int _timeSinceLastBeat; 			// time in ms since last beat was added
											// NOTE: subject to change when music is added
	 	int _beatInterval; 					// how often a beat should be added in seconds
											// NOTE: subject to change when music is added
};

#endif
