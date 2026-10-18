#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "../logging/logging.h"
#include "get_song_location.h"

char *get_user_song(void){
	// Character method created by nbro on StackOverflow, adapted for Rithmos C.
	// 05/06/2016; nbro
	// https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
	char *song_location = NULL;
	int c;
	size_t i = 0, j = 1;

	printf("[info]: We need to get the song location. Please enter the location of the song on your file system, or remotely:\n> ");

	// Whilst we aren't looking at a new line, grab from standard keyboard input.
	while((c = getc(stdin)) != '\n' && c != EOF){

		// Reallocate based on the memory, so that the character can be stored appropriately. This also patches a memory leak!
		char *temporary = realloc(song_location, (j + 1) * sizeof(char));

		if(temporary == NULL){
			free(song_location);
			logger(PANIC, "Failed to allocate song location memory.");
			exit(EXIT_FAILURE);
		}

		song_location = temporary;

		// Store the read character, by ponting it to C.
		song_location[i] = (char)c;

		i++;
		j++;
	}

	// Remove trailing spaces, and tabs until the song is actually playable.
	while(i > 0 && (song_location[i - 1] == ' ' || song_location[i - 1] == '\t')) {
		i--;
	}

	if(i == 0){
		free(song_location);
		logger(WARNING, "No song location was provided. You need to provide a song.");
		return get_user_song();
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
	(len < 5 || strcmp(song_location + len - 5, ".flac") != 0)){
		logger(ERROR, "Invalid file extension. Valid extensions; .wav, .mp3, .flac");
		return get_user_song();
	}

	return song_location;
}