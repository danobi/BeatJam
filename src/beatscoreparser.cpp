#include "beatscoreparser.h"

BeatscoreParser::BeatscoreParser(std::string fname)
{
	// init stuff
	_fname = fname;
	_inBeatSection = false;
	_line = 0;

	// open the file up
	std::ifstream bsfile(_fname.c_str());	

	// check to see if we actually opened it
	if (!bsfile.is_open()) {
		fprintf(stderr,"Error -> could not open file %s\n",_fname.c_str());
		exit(EXIT_FAILURE);
	}

	// begin parsing
	std::string line;
	while (std::getline(bsfile,line)) {
		// update line number we're parsing
		_line++;

		// get it in cstring form so we can better parse it
		const char * ln = line.c_str();

		// determine if line is a comment
		// check if beginning of string is a //
		if (strstr(ln,GCOMMENT) == ln) 
			continue;

		// determine if line is a game argument
		// check if first character on line is a #
		const char * a = strchr(ln,GARG);
		if (a != NULL && a == ln) {
			_handleGameArgument(a);
		}

		// parse next 4 beat lines if we're in the beat section
		if (_inBeatSection) {
			_parseSingleBeat(&bsfile, line.c_str());
		}
	}

	// close the file
	bsfile.close();
	
}

void BeatscoreParser::_handleGameArgument(const char * a)
{
	// determine which game argument this is
	const char * b = strstr(a+1,GARG_SONG);
	const char * c = strstr(a+1,GARG_LENGTH);
	const char * d = strstr(a+1,GARG_BPM);
	const char * e = strstr(a+1,GARG_BEGIN);
	const char * f = strstr(a+1,GARG_END);
	if (b) {
		if (*(b+strlen(GARG_SONG)+1) == '\0') {
			fprintf(stderr,"Error -> mising #SONG game argument on line %d\n",_line);
			exit(EXIT_FAILURE);
		}
		else {
			_song = std::string((b+strlen(GARG_SONG)+1));
			std::cout << "Song is: " << _song << std::endl;
		}
	}
	else if (c) {
		if (*(c+strlen(GARG_LENGTH)+1) == '\0') {
			fprintf(stderr,"Error -> mising #LENGTH game argument on line %d\n",_line);
			exit(EXIT_FAILURE);
		}
		else {
			_length = atoi((c+strlen(GARG_LENGTH)+1));
			std::cout << "Length is: " << _length << std::endl;
		}
	}
	else if (d) {
		if (*(d+strlen(GARG_BPM)+1) == '\0') {
			fprintf(stderr,"Error -> mising #BPM game argument on line %d\n",_line);
			exit(EXIT_FAILURE);
		}
		else {
			_BPM = atoi((d+strlen(GARG_BPM)+1));
			std::cout << "BPM is: "<< _BPM << std::endl;
		}
	}
	else if (e) {
		_inBeatSection = true;
		std::cout << "Entered beat section!" << std::endl;
	}
	else if (f) {
		_inBeatSection = false;
		std::cout << "Exited beat section!" << std::endl;
	}
	else {
		printf("error string: %s\n",a);
		fprintf(stderr,"Error -> unrecognized game argument on line %d\n",_line);
		exit(EXIT_FAILURE);
	}
}

void BeatscoreParser::_parseSingleBeat(std::ifstream * bsfile, const char * fline)
{
	const char * b = strchr(fline,GBEATSEPARATOR);
	if (!b) return;  	// this is sort of a hack for when #BEGIN is parsed, since _inBeatSection is true immediately after
	int beatnum = atoi(b+1);

	// sanity check
	assert(beatnum >= 1);

	parsedSubBeat * subbeats = new parsedSubBeat[NUM_SUBBEATS];
	std::string line;

	for (int i = 0; i < NUM_SUBBEATS; ++i) {
		// update line we're parsing
		_line++;

		// get the line and process it
		std::getline(*bsfile,line);
		const char * a = line.c_str();
		const char * c = strchr(a,GSUBBEATTERMINATOR);

		// verify that GSUBBEATTERMINATOR actually exists
		if (!c) {
			fprintf(stderr,"BeatscoreParser: error -> could not find \'%c\' symbol on line %d\n",GSUBBEATTERMINATOR,_line);
			exit(EXIT_FAILURE);
		}

		// see if beatscore has any beats for this subbeat
		if (*(c+1) == '\0' || *(c+1) == ' ') {
			// do nothing, the parsedSubBeat struct will just be empty
		}
		else {
			char * d = (char*)(c+1);    // cast into a non-const pointer of first char after ->
			while (*d) {
				// check if we have a mouse beat
				if (*d == 'm') {
					if (*(d+1)) {
						d++;
						if (_isValidNote(*d)) {
							subBeatNote subn = {*d,MOUSE_BEAT};
							subbeats[i].notes.push_back(subn);
						}
						else {
							fprintf(stderr,"BeatscoreParser: error -> \'m\' designator found, but invalid note %c on line %d\n"
									,*d,_line);
							exit(EXIT_FAILURE);
						}
					}
					else {
						fprintf(stderr,"BeatscoreParser: error -> \'m\' designator found, but missing note on line %d\n",_line);
						exit(EXIT_FAILURE);
					}
				}
				// check if it's a regular keyboard beat
				else if (_isValidNote(*d)) {
					subBeatNote subn = {*d,KEYBOARD_BEAT};
					subbeats[i].notes.push_back(subn);
				}
				// else it's unrecognized
				else {
					fprintf(stderr,"BeatscoreParser: error -> unrecognized note %c on line %d\n",*d,_line);
					exit(EXIT_FAILURE);
				}
			// increment d pointer
			d++;
			}
		}
	}

	// now put the subbeats into the vector
	_beatscore.push_back(subbeats);

	// sanity check
	assert(_beatscore.size() == beatnum);
}

BeatscoreParser::~BeatscoreParser()
{
	// TODO: for some reason this is segfaulting, can't see why atm
	// delete all heap structs
	for (int i = 0; i < _beatscore.size(); ++i) {
		delete [] _beatscore[i];
	}
}

parsedSubBeat BeatscoreParser::getNotesAtBeat(int beat, int subbeat)
{
	if (beat > _beatscore.size() || beat < 0) {
		fprintf(stderr,"Error -> requested beat is out of range");
		exit(EXIT_FAILURE);
	}
	if (subbeat > NUM_SUBBEATS || subbeat < 0) {
		fprintf(stderr,"Error -> requested subbeat is out of range");
		exit(EXIT_FAILURE);
	}
	return _beatscore[beat-1][subbeat-1];
}

bool BeatscoreParser::_isValidNote(char c)
{
	return (c == KEY_0 || c == KEY_1 || c == KEY_2 || c == KEY_3 || c == KEY_4 || c == KEY_5 || c == KEY_6);
}

int BeatscoreParser::getLength()
{
	return _length;
}

int BeatscoreParser::getBPM()
{
	return _BPM;
}

std::string BeatscoreParser::getSongName()
{
	return _song;
}
