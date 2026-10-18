// GPL-V2.0
// AmilieDev; 16/10/2026
// Created this init file, seperated the basics out from the main.c - couldn't do anything elsewise.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include own headers, this is needed for declarations for the song location.
#include "init.h"

// We need MiniAudio.h obviously.
#include "../external/miniaudio/miniaudio.h"

// Include logging for the sake of making sure we can actually output to terminal.
#include "../logging/logging.h"
#include "../song_utils/get_song_location.h"

int init(void){
	ma_result result;
	ma_engine engine;
	logger(INFO, "Started MiniAudio correctly!");

	result = ma_engine_init(NULL, &engine);
        if(result != MA_SUCCESS){
		logger(PANIC, "Failed to initialise engine! Literally cannot continue!!!");
                return -1;
        }

	// Get the song location from the location function, play it back - and then free it up.
	char *song_location = get_user_song();
	logger(WARNING, song_location);

	get_source_type(song_location);

    ma_engine_play_sound(&engine, song_location, NULL);

	// Check if the audio player (MiniAudio) can actually read the file. If not - why? Then uninit engine, free memory and crash.
	if(result != MA_SUCCESS){
		logger(ERROR, ma_result_description(result));
		logger(PANIC, "Failed to play the audio file. Please check why!");
		ma_engine_uninit(&engine);
		free(song_location);
		return -1;
	}else{
		logger(INFO, "Successfully played your song!");
	}

	free(song_location);

    logger(INFO, "Press enter to exit.");
    getchar();

	// Temporarily terminate the engine here.
	ma_engine_uninit(&engine);
	return 0;
}