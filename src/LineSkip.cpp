#include "LineSkip.hpp"

#include <stdlib.h>

static int rand_level(void)
{
	int level = 1;
	
	while (level < LINESKIP_MAX_LEVEL && rand() % 2) {
		level++;
	}
	return level;
}

bool Line::IsValid() const
{
	int64_t diff = b - t;
	return diff > 2;	
}

bool Line::operator==(const Line& line) {
	return t == line.t && b == line.t;
}

bool Line::operator!=(const Line& line) {
	return !operator==(line);
}

LineNode::LineNode(struct Line line)
:line(line)
{}

void LineNode::Clear()
{
	for (int i = 0; i < LINESKIP_MAX_LEVEL; i++) {
		next[i] = NULL;
	}
}

LineSkip::LineSkip()
: level(0)
{
	head.Clear();
}


LineSkip::~LineSkip()
{
	Clear();
}

/*
Removes all elements of the skip list
*/
void LineSkip::Clear()
{
	LineNode *curr = head.next[0];

	while (curr) {
		LineNode *next = curr->next[0];
		delete curr;
		curr = next;
	}

	head.Clear();
	level = 0;
}

int LineSkip::GetSize()
{
	int count = 0;
	
	LineNode *curr = head.next[0];

	while (curr) {
		curr = curr->next[0];
		count++;
	}
	return count;
}

/*
 Retrieves the first element
*/
 LineNode *LineSkip::GetHead()
{
	return head.next[0];
}

/*
Gets the next node intersecting or after the Line (if any)
*/
LineNode *LineSkip::GetNode(Line line)
{
	LineNode *curr = &head;

	for (int i = level - 1; i >= 0; i--) {
		while (curr->next[i] && curr->next[i]->line.b < line.t) {
			curr = curr->next[i];
		}
	}
	curr = curr->next[0];
	return curr;
}

/*
Inserts a new element into the list
*/
void LineSkip::Insert(Line line)
{	
	LineNode *node = new LineNode(line);
	
	int new_level = rand_level();
	
	if (new_level > level) {
		level = new_level;
	}

	LineNode *iter = &head;

	for (int i = level - 1; i >= 0; i--) {
		while (iter->next[i] && iter->next[i]->line.b < line.t) {
			iter = iter->next[i];
		}
		
		// Only update the appropriate levels
		if (i < new_level) {
			node->next[i] = iter->next[i];
			iter->next[i] = node;
		}
	}
}

/*
Deletes an element from the list
*/
void LineSkip::Delete(Line line)
{
	LineNode *iter = &head;
	LineNode *old_node = NULL;
	
	for (int i = level - 1; i >= 0; i--) {
		while (iter->next[i] && iter->next[i]->line.t < line.t) {
			iter = iter->next[i];
		}
		
		// Only delete if element is equal
		if (iter->next[i] && iter->next[i]->line != line) {
			old_node = iter->next[i];
			iter->next[i] = iter->next[i]->next[i];
		}
	}
	
	delete old_node;
	old_node = NULL;
	
	// Reduce level
	for (int i = level - 1; i >= 0; i--) {
		if (!head.next[i]) {
			level--;
		}
	}
}

/*
Adds or extends adjacent nodes to fill
in the Line.
*/
void LineSkip::Add(Line line)
{
	if (!line.IsValid()) {
		return;
	}
	
	LineNode *curr = GetNode(line);
	
	if (!curr || curr->line.t > line.b) {
		Insert(line); // Just insert the new node
	} else if (!curr->next[0] || curr->next[0]->line.t > line.b) {
		// Resize existing node
		if (line.t < curr->line.t) {
			curr->line.t = line.t;
		}
		if (line.b > curr->line.b) {
			curr->line.b = line.b;
		}
	} else {
		// delete & resize
		if (curr->line.t < line.t) {
			line.t = curr->line.t;
		}

		while (curr && curr->line.t <= line.b) {
			if (line.b < curr->line.b) {
				line.b = curr->line.b;
			}

			LineNode *next = curr->next[0];
			
			Delete(curr->line);
			curr = next;
		}

		Insert(line);
	}
}

/*
Removes the space around a given Line
*/
void LineSkip::Sub(Line line)
{
	if (!line.IsValid()) {
		return;
	}
	
	LineNode *curr = GetNode(line);
	
	if (!curr || curr->line.t > line.b) {
		// No need to remove anything
	} else if (!curr->next[0] || line.b < curr->next[0]->line.t) {
		// Remove line and add edges
		Line top = {curr->line.t, line.t};
		Line bot = {line.b, curr->line.b};

		Delete(curr->line);

		Add(top);
		Add(bot);
	} else {
		Line top = {curr->line.t, line.t};
		Line bot = {line.b, line.b}; // Currently invalid
		
		while (curr && curr->line.t <= line.b) {
			LineNode *next = curr->next[0];
			
			bot.b = curr->line.b; // the lowest point
			
			Delete(curr->line);
			curr = next;
		}

		Add(top);	
		Add(bot);
	}
}
