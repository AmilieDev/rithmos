// GPL-V2.0
// AmilieDev; 18/10/2026
// Grabs local metadata for files, and then allows it to be converted into an easily readable and malleable format.

#include <stdio.h>

#include "../../external/miniaudio/miniaudio.h"
#include "get_file_metadata.h"

// Initializes a new MA instance, using a decoder and then sets the frames. Then checks if it is a valid song or not and then does some magic calculations
// to get the appropriate output. Puts it as duration and is then fed back to > get_song_location which has the appropriate function.
double local_duration(char *song_location){
    ma_decoder decoder;
    ma_uint64 frames = 0;

    ma_result result = ma_decoder_init_file(song_location, NULL, &decoder);

    if(result != MA_SUCCESS){
        return -1.0;
    }

    result = ma_decoder_get_length_in_pcm_frames(&decoder, &frames);

    if(result != MA_SUCCESS){
        return -1.0;
    }

    double duration = (double)frames / (double)decoder.outputSampleRate;

    ma_decoder_uninit(&decoder);

    return duration;
}