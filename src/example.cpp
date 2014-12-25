#include "example.h"

Resources gameResources;

void example_preinit()
{
	// do nothing
}

//called from entry_point.cpp
void example_init()
{
	//load xml file with resources definition
	gameResources.loadXML("res.xml");
		
	// add a pianokey actor
	PianoBar * pb = new PianoBar();
	getStage()->addChild(pb);

	// add the keyboard listener
	getStage()->addChild(new KeyboardListener(pb));

	// add the beat stage
	getStage()->addChild(new BeatStage(pb));
}


//called each frame from entry_point.cpp	
void example_update()
{	
}

//called each frame from entry_point.cpp	
void example_destroy()
{
	//free previously loaded resources
	gameResources.free();
}
