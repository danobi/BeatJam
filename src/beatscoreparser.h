#ifndef BEATSCOREPARSER_H
#define BEATSCOREPARSER_H

#include <iostream> // for debugging
#include <assert.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include "beatjam_constants.h"

// this represents ONE concurrent beat in a subbeat
typedef struct _subBeatNote_t {
	char note;
	int type;
} subBeatNote;

// represents concurrent notes in subbeat
typedef struct parsedSubBeat_t {
	std::vector<subBeatNote> notes;   
} parsedSubBeat;


class BeatscoreParser
{
	public:
		/*
		 * this constructor will look for beatscore/fname and then load the contents into the internal datastructure
		 */
		BeatscoreParser(std::string fname);

		~BeatscoreParser();

		/*
		 * this function will return a KEY_ constant or NOKEY depending on if there is a note at this time
		 * time is specified by a beat number (begins at 1) and a subbeat (1 <= subbeat <= 4)
		 */
		parsedSubBeat getNotesAtBeat(int beat, int subbeat);

		/*
		 * getters for beatscore data
		 * DO NOT call any of these without calling the non-default constructor first
		 */
		int getLength();
		int getBPM();
		std::string getSongName();  // returns songname AND extension

	private:
		/*
		 * private helper to handle game arguments
		 * this function will store all the game args like _BPM as well as set _inBeatSection
		 */
		void _handleGameArgument(const char * a);

		/*
		 * private helper function to parse a single beat (comprised of 4 subbeats)
		 * it will set the appropriate values in _beatscore
		 * Note: not sure if this is a good idea to pass a ptr to a stack obj, but I don't want to make a variable on the heap
		 */
		void _parseSingleBeat(std::ifstream * bsfile, const char * fline);  

		/*
		 * private helper to determine if a char is one of the KEY constants
		 */
		bool _isValidNote(char c);

		// private data members
		std::vector< parsedSubBeat* > _beatscore;  	// main data structure
		std::string _fname;
		int _BPM;
		int _length;
		std::string _song;
		bool _inBeatSection;
		int _line; 			// current line we're parsing
};

#endif
