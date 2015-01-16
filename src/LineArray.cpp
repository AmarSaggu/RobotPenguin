#include "LineArray.hpp"
#include "LineSkip.hpp"

LineSkip *LineArray::Get(int x)
{
	return &lineMap[x];
}
