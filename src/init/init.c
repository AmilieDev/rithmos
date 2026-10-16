// MIT No Attribution
// AmilieDev; 16/10/2026
// Created this init file, seperated the basics out from the main.c - couldn't do anything elsewise.

#include <stdio.h> 

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
                return -1;
        }

        ma_engine_play_sound(&engine, "assets/sound.wav", NULL);
        log_info("[Info] Press enter to exit.\n");
        getchar();

	// Temporarily terminate the engine here.
	ma_engine_uninit(&engine);
}
