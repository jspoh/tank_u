#include "config.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include "data.h"


Size WINDOW_SIZE = { 1600.f,900.f };

/*audio between 0 and 1*/
double musicVolume = 1.0;
/*audio between 0 and 1*/
double sfxVolume = 1.0;

int init(void) {
	/* init rand seed */
	const unsigned long seed = (unsigned long)time(NULL);  // good practice to const everything you dont change
	srand(seed);

    /* init json data */
    cJSON* data = getDataObj();
    sfxVolume = cJSON_GetObjectItem(data, "sfxVolume")->valuedouble;
    musicVolume = cJSON_GetObjectItem(data, "musicVolume")->valuedouble;

	/* return 1 to specify no errors */
	return 1;
}

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
