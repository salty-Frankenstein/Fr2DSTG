#pragma once

#include<fr2dinit.h>
struct ScrSize {
	int height, width;
};

class Obj {
public:
	void Show(Fr2DHDL device, Fr2DBrush brush);
	void Update(float x, float y);
	void OutOfScreen();
	float x, y;
	float size;
	FrPicHDL hpic;
	bool del;
	ScrSize scrsize;
};

class Bul:public Obj {
public:
	Bul(float sx, float sy, FrPicHDL h, float s,int height,int width);
	~Bul(){}
private:

};