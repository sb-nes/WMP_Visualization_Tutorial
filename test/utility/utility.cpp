#include "utility.h"

int utl::overlap(int value, int min, int max){ return value>max? value<min? max - value : min + (value-max):value; }