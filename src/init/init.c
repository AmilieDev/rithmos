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
		log_panic("Failed to initialise engine! Literally cannot continue!!!");
                return -1;
        }

	log_warning("Potential issue: If assets/sound.wav does not exist, the application will not play audio. Please ensure it exists.\nBeing replaced with an audio selector via key input soon anyway. Hopefully will make this GUI one day. Just keep notes.");
        ma_engine_play_sound(&engine, "assets/sound.wav", NULL);
	log_info("Sound played! You should have heard a beep!");
        log_info("Press enter to exit.\n");
        getchar();

	// Temporarily terminate the engine here.
	ma_engine_uninit(&engine);
}
