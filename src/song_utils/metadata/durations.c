// GPL-V2.0
// AmilieDev; 18/10/2026
// Durations file, will have filler for Navidrome and Spotify too in the future. Only reads locally currently.

#include "../../logging/logging.h"
#include "./durations.h"
#include "../../api/local_files/get_file_metadata.h"

double local_duration_metadata(char *song_location){
	double duration = local_duration(song_location);

	if(duration < 0.0){
		logger(ERROR, "Failed to get songs duration.");
	}else{
		int minutes = (int)duration / 60;
		int seconds = (int)duration % 60;

		// Checks if we need to format it in minutes, or seconds.
		if(minutes >= 1){
			logger(INFO, "Song duration is: %i:%is", minutes, seconds);
		} else if(minutes < 1) {
			logger(INFO, "Song duration is: %is", seconds);
		} else {
			logger(ERROR, "Invalid input made for duration.");
		}
	}

    return duration;
}