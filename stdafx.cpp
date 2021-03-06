// stdafx.cpp : 只包括标准包含文件的源文件
// Fr2DSTG.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用


void Obj::Show(Fr2DHDL device, Fr2DBrush brush) {
	D2D1_SIZE_F size = hpic->GetSize();
	device->DrawBitmap(hpic,D2D1::RectF(x,y,x + size.width,y + size.height));
}

void Obj::Update(float dx, float dy) {
	x += dx;
	y += dy;
	OutOfScreen();
}

void Obj::OutOfScreen() {
	if (x > scrsize.height || y > scrsize.width || x < 0 || y < 0)
		del = true;
}

Bul::Bul(float sx, float sy, FrPicHDL h, float s,int height,int width) {
	x = sx;
	y = sy;
	size = s;
	hpic = h;
	del = false;
	scrsize.height = height;
	scrsize.width = width;
}

/*
bul::bul(float x, float y, FrPicHDL h, float s=10) {
	sx = x;
	sy = y;
	size = s;
	hbulpic = h;
}

void bul::show(Fr2DHDL device, Fr2DBrush brush) {

	D2D1_SIZE_F size = hbulpic->GetSize();
	device->DrawBitmap(
		hbulpic,
		D2D1::RectF(
			sx,
			sy,
			sx + size.width,
			sy + size.height)
	);
}

void bul::update(float x,float y) {
	sx += x;
	sy += y;
}
*/