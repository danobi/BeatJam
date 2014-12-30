#ifndef BEATJAM_CONSTANTS_H
#define BEATJAM_CONSTANTS_H

// ---------> begin constants
#define DEBUG_MODE (true)
#define WINDOW_HEIGHT (630)
#define WINDOW_WIDTH (WINDOW_HEIGHT/2)

#define NUM_SCREEN_SECTIONS (5)
#define NUM_PIANO_KEYS (7)

#define NUM_SUBBEATS (4)

#define BEATSTAGE_HEIGHT ((float)(((float)NUM_SCREEN_SECTIONS - 1)/ (float)NUM_SCREEN_SECTIONS) * (float)WINDOW_HEIGHT)
#define PIANOKEY_HEIGHT ((float)WINDOW_HEIGHT / (float)NUM_SCREEN_SECTIONS)
#define PIANOKEY_WIDTH ((float)WINDOW_WIDTH / (float)NUM_PIANO_KEYS)
#define BEAT_RADIUS (PIANOKEY_WIDTH-BEAT_RADIUS_OFFSET)

#define TWEEN_DURATION (200)

#define BEAT_RADIUS_OFFSET (8)
#define BEATBORDER_Y_OFFSET (5)
#define BEATBORDER_SCALE_OFFSET ((float).05)
#define KEY_SHRINK_FACTOR (.7)
#define KEY_ORIGINAL_SIZE_FACTOR (1)

#define KEY_0 ('C')
#define KEY_1 ('D')
#define KEY_2 ('E')
#define KEY_3 ('F')
#define KEY_4 ('G')
#define KEY_5 ('A')
#define KEY_6 ('B')
#define NOKEY ('\0')
#define KEYBOARD_BEAT (1)
#define KEYBOARD_PRESS (1)
#define MOUSE_BEAT (0)
#define MOUSE_PRESS (0)

#define GBEATSEPARATOR ('-')
#define GSUBBEATTERMINATOR ('>')
#define GCOMMENT ("//")
#define GARG ('#')
#define GARG_SONG ("SONG")
#define GARG_LENGTH ("LENGTH")
#define GARG_BPM ("BPM")
#define GARG_BEGIN ("BEGIN")
#define GARG_END ("END")
// ---------> end constants



#endif
