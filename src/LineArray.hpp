#pragma once

#include "LineSkip.hpp"

#include <unordered_map>

/*
Stores the LineSkips
*/
class LineArray {
	public:
	LineSkip *Get(int x);

private:
	std::unordered_map<int, LineSkip> lineMap;
};
