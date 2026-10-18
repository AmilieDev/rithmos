// GPL-V2.0
// AmilieDev; 18/10/2026
// Header file for verifying source location and where it came from.

#ifndef GET_SOURCE_TYPE_H
#define GET_SOURCE_TYPE_H

typedef enum{
	SOURCE_LOCAL,
	SOURCE_SPOTIFY,
	SOURCE_NAVIDROME,
	SOURCE_INVALID
} source_type;

source_type get_source_type(char *song_location);

#endif