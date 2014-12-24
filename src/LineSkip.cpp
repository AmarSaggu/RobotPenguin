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
	return diff > 1;	
}

bool operator==(const Line& a, const Line& b) {
	return a.t == b.t && a.b == b.t;
}

bool operator!=(const Line& a, const Line& b) {
	return !(a == b);
}

LineNode::LineNode(struct Line line)
:line(line)
{
	//
}

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

void LineSkip::Add(Line line)
{
	if (!line.IsValid()) {
		return;
	}
	
	LineNode *curr = GetNode(line);
	
	if (!curr || curr->line.t > line.b) {
		// Insert new node
		Insert(line);
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

		/*while (curr->next[0] && curr->next[0]->line.t <= line.b) {
			LineNode *next = curr->next[0];
			
			Delete(curr->line);
			curr = next;
		}*/
		
		//curr = curr->next[0];
		
		Line bot = {line.b, line.b}; // Currently invalid
		
		while (curr && curr->line.t <= line.b) {
			LineNode *next = curr->next[0];
			
			bot.b = curr->line.b;
			
			Delete(curr->line);
			curr = next;
		}

		Add(top);	
		Add(bot);
		/*if (curr) {
			Line bot = {line.b, curr->line.b};
			Add(bot);
		}*/
		
	}
}

/*
	struct LineNode *update[LINESKIP_MAX_LEVEL];
	struct LineNode *iter = &skip->head;
	
	for (int i = skip->level - 1; i >= 0; i--) {
		while (iter->next[i] && line.t > iter->next[i]->line.b) {
			iter = iter->next[i];
		}
		update[i] = iter;
	}
	iter = iter->next[0];
	
	if (!iter || line.b < iter->line.t) {
		// Add a node
		struct LineNode *new_node = LineNode_Create(line);
		int level = rand_level();
		
		for (int i = MIN(level, skip->level) - 1; i >= 0; i--) {
				new_node->next[i] = update[i]->next[i];
				update[i]->next[i] = new_node;
			}
		
		// Increase height
		if (level > skip->level) {
			for (int i = level - 1; i >= skip->level; i--) {
				skip->head.next[i] = new_node;
				new_node->next[i] = NULL;
			}
			skip->level = level;
		}
	} else if (!iter->next[0] || iter->next[0]->line.t > line.b) {
		// Resize existing node	
		if( line.t < iter->line.t ) {
			iter->line.t = line.t;
		}
		if( line.b > iter->line.b ) {
			iter->line.b = line.b;
		}
	} else {
		// yep.
	}
	*/
	
	
	/* 
	else if (line.b < next->line.t) {
		for (int i = 0; i < level; i++) {
			new_node->next[i] = update[i]->next[i];
			update[i]->next[i] = new_node;
		}
	}*/
//}


