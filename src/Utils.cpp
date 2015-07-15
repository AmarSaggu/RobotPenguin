#include "Utils.hpp"

double sign(double n)
{
	if (n > 0.0) {
		return 1.0;
	} else if (n < 0.0) {
		return -1.0;
	} else {
		return 0.0;
	}
}
