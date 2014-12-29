#ifndef BEATSTAGE_H
#define BEATSTAGE_H

#include <vector>
#include <time.h>
#include "oxygine-framework.h"
#include "beatjam_constants.h"
#include "pianobar.h"
#include "beat.h"
#include "beatborder.h"

using namespace oxygine;

// TODO: find a better class to inherit from 
class BeatStage : public ColorRectSprite
{
	public:
		// TODO: find a way to decouple PianoBar
		BeatStage(spPianoBar pb);

		/*
		 * overrides the default doUpdate, this checks to see if the user has presed the correct chord
		 */
		virtual void doUpdate(const UpdateState & us);
	private:
		/*
		 * adds a beat to a *randomized* starting point (on the bottom of the screen -> ie opposite to the pianobar
		 * beat must be initialized before passing it in
		 */
		void _addBeat(spBeat beat);

		/*
		 * this function will check to see if the user has the right keys chorded at the instant this is called
		 * it will return whether or not the user had the notes pressed
		 * there are no side effects
		 */
		bool _consumeBeat(spBeat beat);

		/*
		 * this function will add NUM_PIANO_KEYS number of beat borders at the right locations
		 */
		void _addBeatBorders();

		// private data
		std::vector<spBeat> _beats;  		// array of currently VALID beats in the beatstage
		std::vector<spBeatBorder> _beatborders;
		spPianoBar _pb;
		int _timeSinceLastBeat; 			// time in ms since last beat was added
											// NOTE: subject to change when music is added
	 	int _beatInterval; 					// how often a beat should be added in seconds
											// NOTE: subject to change when music is added
		float _beatborder_ypos; 			// to help determine where consume zone is
};

#endif
