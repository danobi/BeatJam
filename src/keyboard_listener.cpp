#include "keyboard_listener.h"

KeyboardListener::KeyboardListener(PianoBar * pb)
{
	// add listener(s) to the stage
	// we will check keyboard state only when a key is pressed, to increase performance
	getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this,&KeyboardListener::keyPressDownHandler)); // down press handler

	// initialize currentNote
	currentNote = '\0';

	// save the pianobar object
	_pianobar = pb;
}


void KeyboardListener::keyPressDownHandler(Event * ev)
{
	// figure out which note was chorded
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		if (currentNote != 'C') {
			char oldNote = currentNote;
			currentNote = 'C';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded C");
		}
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		if (currentNote != 'D') {
			char oldNote = currentNote;
			currentNote = 'D';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded D");
		}
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		if (currentNote != 'E') {
			char oldNote = currentNote;
			currentNote = 'E';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded E");
		}
	}
	else if (!state[SDL_SCANCODE_Q] && state[SDL_SCANCODE_W] && state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_F]) {
		if (currentNote != 'F') {
			char oldNote = currentNote;
			currentNote = 'F';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded F");
		}
	}
	else if (!state[SDL_SCANCODE_Q] && state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		if (currentNote != 'G') {
			char oldNote = currentNote;
			currentNote = 'G';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded G");
		}
	}
	else if (!state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		if (currentNote != 'A') {
			char oldNote = currentNote;
			currentNote = 'A';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded A");
		}
	}
	else if (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_W] && state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_R] &&
			!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && state[SDL_SCANCODE_F]) {
		if (currentNote != 'B') {
			char oldNote = currentNote;
			currentNote = 'B';
			updateKeyboard(oldNote,currentNote);
			log::messageln("chorded B");
		}
	}
}

void KeyboardListener::updateKeyboard(char okey, char nkey)
{
	_pianobar->updateKeys(okey,nkey);
}
