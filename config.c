/**
 * @file config.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file takes care of the project config
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#include "config.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include "data.h"
#include "cprocessing.h"


Size WINDOW_SIZE = { 1600.f,900.f };

/*audio between 0 and 1*/
double musicVolume = 1.0;
/*audio between 0 and 1*/
double sfxVolume = 1.0;

extern int SFX_GROUP;
extern int MUSIC_GROUP;
extern int MEME_SFX_GROUP;
extern int MEME_MUSIC_GROUP;

bool MEME_MODE = false;

void initAudio() {
    if (MEME_MODE) {
		CP_Sound_SetGroupVolume(MEME_SFX_GROUP, (float)sfxVolume);
		CP_Sound_SetGroupVolume(MEME_MUSIC_GROUP, (float)musicVolume);
		CP_Sound_SetGroupVolume(SFX_GROUP, 0);
		CP_Sound_SetGroupVolume(MUSIC_GROUP, 0);
	}
	else {
		CP_Sound_SetGroupVolume(MEME_SFX_GROUP, 0);
		CP_Sound_SetGroupVolume(MEME_MUSIC_GROUP, 0);
		CP_Sound_SetGroupVolume(SFX_GROUP, (float)sfxVolume);
		CP_Sound_SetGroupVolume(MUSIC_GROUP, (float)musicVolume);
	}
}

int init(void) {
	/* init rand seed */
	const unsigned long seed = (unsigned long)time(NULL);  // good practice to const everything you dont change
	srand(seed);

    /* init json data */
    cJSON* data = getDataObj();
    sfxVolume = cJSON_GetObjectItem(data, "sfxVolume")->valuedouble;
    musicVolume = cJSON_GetObjectItem(data, "musicVolume")->valuedouble;
    MEME_MODE = cJSON_GetObjectItem(data, "memeMode")->valueint;

	initAudio();

	/* return 1 to specify no errors */
	return 1;
}

/**
 * @brief Get the Rand object inclusive of min exclusive of max
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int getRand(int min, int max) {
	return rand()%(max-min)+min;
}


void debug_log(const char *format, ...) {
	if (!DEBUG_MODE) {
		return;
	}

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int i = va_arg(args, int);
                printf("%d", i);
            }
            else if (*format == 'f') {
                double lf = va_arg(args, double);
                printf("%lf", lf);
            }
        } else {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}
