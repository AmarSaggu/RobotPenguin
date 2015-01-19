#pragma once

#include <cstdint>

/*
A small skip list that's used to
handle each vertical slice of the
world.

This implementation could probably be
replaced by a unordered map, or even
just a linked list.

Also all of the LineNodes are allocated
with the maximum number of pointers, which
can use quite a bit of memory. 
I need to dynamically allocate the next
pointer array in LineNode to only allocate
pointers based on its level.
*/

#define LINESKIP_MAX_LEVEL 3

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
	
	// Adds & removes space around given Lines
	void Add(Line line);
	void Sub(Line line);

private:
	int level;
	LineNode head;

	// Internally inserts & deletes nodes
	void Insert(Line line);
	void Delete(Line line);
};
