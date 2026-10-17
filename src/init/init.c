// GPL-V2.0
// AmilieDev; 16/10/2026
// Created this init file, seperated the basics out from the main.c - couldn't do anything elsewise.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include own headers, this is needed for declarations for the song location.
#include "init.h"

// We need MiniAudio.h obviously.
#include "../miniaudio/miniaudio.h"

// Include logging for the sake of making sure we can actually output to terminal.
#include "../logging/logging.h"

int init(void){
	ma_result result;
	ma_engine engine;
	log_info("Started MiniAudio correctly!");

	result = ma_engine_init(NULL, &engine);
        if(result != MA_SUCCESS){
		log_panic("Failed to initialise engine! Literally cannot continue!!!");
                return -1;
        }

	// Get the song location from the location function, play it back - and then free it up.
	char *song_location = get_user_song();
	log_warning(song_location);
    ma_engine_play_sound(&engine, song_location, NULL);

	// Check if the audio player (MiniAudio) can actually read the file. If not - why? Then uninit engine, free memory and crash.
	if(result != MA_SUCCESS){
		log_error(ma_result_description(result));
		log_panic("Failed to play the audio file. Please check why!");
		ma_engine_uninit(&engine);
		free(song_location);
		return -1;
	}else{
		log_info("Successfully played your song!");
	}

	free(song_location);

    log_info("Press enter to exit.");
    getchar();

	// Temporarily terminate the engine here.
	ma_engine_uninit(&engine);
	return 0;
}

char *get_user_song(void){
	// Character method created by nbro on StackOverflow, adapted for Rithmos C.
	// 05/06/2016; nbro
	// https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
	char *song_location = NULL;
	int c;
	int i = 0, j = 1;

	log_info("We need to get the song location. Please enter the location of the song on your file system: ");
	log_info("Starting to gather string input.");

	// Whilst we aren't looking at a new line, grab from standard keyboard input.
	while((c = getc(stdin)) != '\n' && c != EOF){

		// Reallocate based on the memory, so that the character can be stored appropriately.
		song_location = (char*)realloc(song_location, j * sizeof(char));

		// Store the read character, by ponting it to C.
		song_location[i] = c;

		i++;
		j++;
	}

	// Remove trailing spaces, and tabs until the song is actually playable.
	while(i > 0 && (song_location[i - 1] == ' ' || song_location[i - 1] == '\t')) {
		i--;
	}

	// Append a null character at the end of the string to mark the end of it.
	song_location[i] = '\0';


	size_t len = strlen(song_location);

	// Check if the song is a compatible audio type - if it not MP3, WAV or FLAC - reject it.
	// Initially created based upon https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
	// 14/04/2009; Anonymous
	// No longer based upon this, but worth crediting regardless.

	// TODO; Make this check based on hash, rather than pure string matching.
	if((len < 4 || strcmp(song_location + len - 4, ".wav") != 0) &&
	(len < 4 || strcmp(song_location + len - 4, ".mp3") != 0) &&
	(len < 5 || strcmp(song_location + len - 5, ".mp3") != 0)){
		log_panic("Invalid file extension. Valid extensions; .wav, .mp3, .flac");
		exit(1);
	}

	return song_location;
}