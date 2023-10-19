#include "config.h"
#include <time.h>

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