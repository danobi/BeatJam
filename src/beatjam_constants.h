#ifndef BEATJAM_CONSTANTS_H
#define BEATJAM_CONSTANTS_H

// ---------> begin constants
#define WINDOW_HEIGHT (630)
#define WINDOW_WIDTH (WINDOW_HEIGHT/2)

#define NUM_SCREEN_SECTIONS (5)
#define NUM_PIANO_KEYS (7)

#define BEATSTAGE_HEIGHT ((float)(((float)NUM_SCREEN_SECTIONS - 1)/ (float)NUM_SCREEN_SECTIONS) * (float)WINDOW_HEIGHT)
#define PIANOKEY_HEIGHT ((float)WINDOW_HEIGHT / (float)NUM_SCREEN_SECTIONS)
#define PIANOKEY_WIDTH ((float)WINDOW_WIDTH / (float)NUM_PIANO_KEYS)

#define BEAT_RADIUS_OFFSET (8)
#define KEY_SHRINK_FACTOR (.7)
#define KEY_ORIGINAL_SIZE_FACTOR (1)
// ---------> end constants



#endif
