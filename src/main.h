#ifndef MAIN_H
#define MAIN_H

// //!!!!!!!!EXAMPLE
// extern int wideScreenWidth;

// #define MAIN_SCREEN_DEPTH			8
// #define MAIN_SCREEN_MIN_WIDTH		640
// #define MAIN_SCREEN_MIN_HEIGHT	480
// #define MAIN_SCREEN_PAGES			1
// #define MAIN_SCREEN_SCALING		0

// #define MAIN_WINDOW_WIDTH			wideScreenWidth
// #define MAIN_WINDOW_HEIGHT			480

// // This is our default mode.
// #define MAIN_AUDIO_RATE				11025
// #define MAIN_AUDIO_BITS				16
// #define MAIN_AUDIO_CHANNELS		1
// #define MAIN_AUDIO_BUFTIME			100
// #define MAIN_AUDIO_MAXBUFTIME		2000

// // This is our vanilla mode which contains just a couple
// // overrides to the default mode.  These should be used when the INI
// // or default audio specs fail.
// #define MAIN_VANILLA_AUDIO_RATE		22050
// #define MAIN_VANILLA_AUDIO_BITS		8
// //!!!!!!!!!!!!!!!!

#define DEBUG_ENABLED false

#define PROJECT_ROOT std::string((DEBUG_ENABLED) ? "./" : "../")

#endif // MAIN_H