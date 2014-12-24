#ifndef BEATSTAGE_H
#define BEATSTAGE_H

#include "oxygine-framework.h"
#include "beat.h"

// TODO: these constants is also defined in pianobar.h, should find a way to consolidate this
#define NUM_SCREEN_SECTIONS 5
#define NUM_PIANO_KEYS 7

using namespace oxygine;

// TODO: find a better class to inherit from 
class BeatStage : public ColorRectSprite
{
	public:
		BeatStage();
		void addBeat(Beat * beat, int radius);
};

#endif
