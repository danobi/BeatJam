#include "keyboard_listener.h"

KeyboardListener::KeyboardListener(PianoBar * pb)
{
	// add listener(s) to the stage
	// we will check keyboard state only when a key is pressed, to increase performance
	getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this,&KeyboardListener::keyPressDownHandler)); // down press handler

	// initialize note private data
	_currentNote = '\0';
	_prevNote = '\0';

	// save the pianobar object
	_pianobar = pb;
}


void KeyboardListener::keyPressDownHandler(Event * ev)
{
	// figure out which note was chorded
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		updateKeyboard('C');
		log::messageln("chorded C");
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		updateKeyboard('D');
		log::messageln("chorded D");
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		updateKeyboard('E');
		log::messageln("chorded E");
	}
	else if (!state[SDL_SCANCODE_Q] && state[SDL_SCANCODE_W] && state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		updateKeyboard('F');
		log::messageln("chorded F");
	}
	else if (!state[SDL_SCANCODE_Q] && state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		updateKeyboard('G');
		log::messageln("chorded G");
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		updateKeyboard('A');
		log::messageln("chorded A");
	}
	else if (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		updateKeyboard('B');
		log::messageln("chorded B");
	}
}

void KeyboardListener::updateKeyboard(char nkey)
{
	_pianobar->keyboardUpdateKeys(nkey);
}
