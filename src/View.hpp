#pragma once

class View {
public:
	View(int x, int y, int width, int height);
	
	int GetPositionX();
	int GetPositionY();
	
	int GetWidth();
	int GetHeight();
	
	void SetPosition(int x, int y);
private:
	int x, y;
	int width, height;
};
