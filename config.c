#include "config.h"
#include <time.h>

Size WINDOW_SIZE = { 1600.f,900.f };

int getRand(void) {
	const unsigned long seed = time(NULL);  // good practice to const everything you dont change
	srand(seed);
	return rand();
}