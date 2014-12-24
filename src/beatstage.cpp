#include "beatstage.h"

BeatStage::BeatStage()
{
	// calculate screen positions
	int screen_length = getStage()->getHeight();
	int screen_width = getStage()->getWidth();
	int pianobar_length = screen_length / NUM_SCREEN_SECTIONS;
	int pianokey_width = screen_width / NUM_PIANO_KEYS;
	int beatstage_length = screen_length - pianobar_length;
	
	// set up the piano key "holder"
	setSize(screen_width,beatstage_length); 
	setX(0);
	setY(pianobar_length);
	setColor(Color::DarkSlateGray);

	// a test beat
	addBeat(new Beat(),pianokey_width);
}

void BeatStage::addBeat(Beat * beat, int radius)
{
	beat->setPosition(100,200);

	// TODO: the size isn't showing up correctly, probably has to do with sprite image being too big
	// must figure out how to resize spirte image
	beat->setSize(radius,radius);
	addChild(beat);
}
