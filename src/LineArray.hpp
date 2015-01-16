#pragma once

#include "LineSkip.hpp"

#include <unordered_map>

class LineArray {
	public:
	LineSkip *Get(int x);

private:
	std::unordered_map<int, LineSkip> lineMap;
};
