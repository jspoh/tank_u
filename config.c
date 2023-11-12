#include "config.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

Size WINDOW_SIZE = { 1600.f,900.f };

int init(void) {
	/* init rand seed */
	const unsigned long seed = (unsigned long)time(NULL);  // good practice to const everything you dont change
	srand(seed);

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
            // Handle other types...
        } else {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}
