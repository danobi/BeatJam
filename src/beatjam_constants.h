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
// ---------> end constants



#endif
