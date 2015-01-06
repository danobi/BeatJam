#ifndef BEATSTAGE_H
#define BEATSTAGE_H

#include <vector>
#include <time.h>
#include "oxygine-framework.h"
//#include "SoundPlayer.h"
//#include "SoundSystem.h"
//#include "SoundInstance.h"
#include "beatjam_constants.h"
#include "pianobar.h"
#include "beat.h"
#include "beatborder.h"
#include "beatscoreparser.h"

using namespace oxygine;

// TODO: find a better class to inherit from 
class BeatStage : public ColorRectSprite
{
	public:
		// TODO: find a way to decouple PianoBar
		BeatStage(spPianoBar pb);

		~BeatStage();

		/*
		 * overrides the default doUpdate, this checks to see if the user has presed the correct chord
		 */
		virtual void doUpdate(const UpdateState & us);
	private:
		/*
		 * adds a beat to a starting point based on the beatscore(on the bottom of the screen -> ie opposite to the pianobar
		 */
		void _addScoreBeat();

		/*
		 * adds a random x-position beat, used in debug mode
		 * beat must be initialized before passing it in
		 */
		void _addRandomBeat(spBeat beat);

		/*
		 * this function will check to see if the user has the right keys chorded at the instant this is called
		 * it will return whether or not the user had the notes pressed
		 * there are no side effects
		 */
		//bool _consumeBeat(spBeat beat);
		bool _consumeBeat(std::vector<spBeat> beats);

		/*
		 * this function will add NUM_PIANO_KEYS number of beat borders at the right locations
		 */
		void _addBeatBorders();

		// private data
		std::vector<spBeat> _beats;  		// array of currently VALID beats in the beatstage
		std::vector<spBeatBorder> _beatborders;
		spPianoBar _pb;
		BeatscoreParser * bsp;
		float _beatborder_ypos; 			// to help determine where consume zone is
		int _BPM;
		int _songlength;
		std::string _songname;
		int _currentBeat;
		int _currentSubBeat;
		int _timeSinceLastSubBeat;
		int _timeSinceLastBeat; 			// time in ms since last beat was added
											// NOTE: subject to change when music is added
	 	float _beatInterval; 					// how often a beat should be added in seconds
											// NOTE: subject to change when music is added
		float _subBeatInterval;
};

#endif
