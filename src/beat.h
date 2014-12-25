#ifndef BEAT_H
#define BEAT_H

#include "oxygine-framework.h"
#include "beatjam_constants.h"

using namespace oxygine;

class Beat : public Sprite
{
	public:
		Beat();
		Beat(int radius);

		/*
		 * this function will make the beat start "falling" towards the pianobar
		 * pretty much a public wrapper
		 * default "fall" rate is 80 pixels / sec
		 */
		void beginFall(float timeforfall);

		/*
		 * this function overrides the update for superclass Actor
		 * this is what will be called in the game mainloop
		 */
		virtual void update(const UpdateState & us);

		/*
		 * setters/getters for which note this beat belongs to
		 */
		void setNote(char note);
		char getNote();


	private:
		/*
		 * this private function will make the beat "fall" ONE pixel
		 */
		void _fall(float px);

		/*
		 * handles what happens when the beat is clicked
		 */ 
		void _clickHandler(Event *);

		Resources _gameResources;
		int _radius;
		float _timeforfall;       // number of seconds it takes for a beat to hit pianobar
		bool _isFalling;
		char _note; 			  // which note/key this beat belongs to
};

#endif
