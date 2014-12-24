#pragma once

#include <cstdint>

#define LINESKIP_MAX_LEVEL 1

struct Line {
	std::int32_t t, b;
	
	bool IsValid() const;
	
	friend bool operator==(const Line& a, const Line& b);
	friend bool operator!=(const Line& a, const Line& b);
};

struct LineNode {
	Line line;
	LineNode *next[LINESKIP_MAX_LEVEL];
	
	LineNode() = default;
	LineNode(Line line);
	void Clear();
};

class LineSkip {
public:
	LineSkip();
	~LineSkip();
	
	void Clear();
	

	LineNode *GetNode(Line line);
	LineNode *GetHead();
	int GetSize();
	
	void Add(Line line);
	void Sub(Line line);

private:
	int level;
	LineNode head;

	void Insert(Line line);
	void Delete(Line line);
};
