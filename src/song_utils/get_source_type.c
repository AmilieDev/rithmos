// GPL-V2.0
// AmilieDev; 18/10/2026
// Source location for meta data output appropriately. Checks if it is local or remote.

#include <stdio.h>
#include <string.h>

#include "../logging/logging.h"
#include "../api/local_files/get_file_metadata.h"
#include "./metadata/durations.h"
#include "./get_source_type.h"

source_type get_source_type(char *song_location){
	if(song_location == NULL || song_location[0] == '\0'){
		logger(WARNING, "Source type is invalid");
		return SOURCE_INVALID;
	}

	if(strncmp(song_location, "http://", 7) == 0 || strncmp(song_location, "https://", 8) == 0){
		logger(WARNING, "Source type is Spotify / Navidrome");
		return SOURCE_SPOTIFY;
	}

	// Pull local song duration, and output it appropriately.
	local_duration_metadata(song_location);

	return SOURCE_LOCAL;
}