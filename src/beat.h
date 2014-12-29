#ifndef BEAT_H
#define BEAT_H

#include "oxygine-framework.h"
#include <vector>
#include "beatjam_constants.h"

using namespace oxygine;

DECLARE_SMART(Beat,spBeat);

class Beat : public Sprite
{
	public:
		Beat();
		Beat(int radius, int type);

		/*
		 * this function will make the beat start "falling" towards the pianobar
		 * pretty much a public wrapper
		 * default "fall" rate is 80 pixels / sec
		 */
		void beginFall(float timeforfall);

		/*
		 * this function overrides the doUpdate for superclass Actor
		 * this is what will be called in the game mainloop
		 */
		virtual void doUpdate(const UpdateState & us);

		/*
		 * this function will add the tween to the tween queue
		 */
		void addAnimateTween(spTween tween);

		/*
		 * this function will actually execute all the tweens in the queue
		 */
		void runAnimateTween();

		/*
		 * setters/getters for which note this beat belongs to
		 */
		void setNote(char note);
		char getNote();

		/* 
		 * setters/getters for radius
		 */
		void setRadius(int rad);
		int getRadius();

		/*
		 * setters/getters for beat type
		 */
		void setType(int type);
		int getType();

	private:
		/*
		 * this private function will make the beat "fall" ONE pixel
		 */
		void _fall(float px);

		/*
		 * handles what happens when the beat is clicked
		 */ 
		void _clickHandler(Event *);

		/*
		 * this private function will detatch the beat from the parent if called
		 * this *should* be used as a callback for when BeatBorder is done animating
		 */
		void _tweenDone(Event *);

		Resources _gameResources;
		std::vector<spTween> _tween_queue;
		int _radius;
		float _timeforfall;       // number of seconds it takes for a beat to hit pianobar
		bool _isFalling;
		char _note; 			  // which note/key this beat belongs to
		int _type;
};

#endif
