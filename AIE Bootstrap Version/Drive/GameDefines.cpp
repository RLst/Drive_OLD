#include "GameDefines.h"
#include <random>

int craprandom(int min, int max) {
	return min + (rand() % (max - min + 1));
}