#pragma once
#include "fr_win.h"
#include "fr2d.h"

//////////
/*
process of window and message
into fr2dstg_msg.h
*/

bool getKey[256] = { 0 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		getKey[wParam] = true;
		return 0;

	case WM_KEYUP:
		getKey[wParam] = false;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

///////////

/*
process of time & random
into fr2dstg_time
*/

#include<time.h>

namespace FrTime {

	void RandRefresh();
	double RandDouble();
	unsigned long RandUL();
	int RandInt(int a, int b);
	
};


void FrTime::RandRefresh() {
	srand((unsigned)time(NULL));
}

double FrTime::RandDouble() {
	return rand() / double(RAND_MAX);
}

unsigned long FrTime::RandUL() {
	return (
		(((unsigned long)rand() << 24) & 0xFF000000ul)
		| (((unsigned long)rand() << 12) & 0x00FFF000ul)
		| (((unsigned long)rand()) & 0x00000FFFul));
}

int FrTime::RandInt(int a, int b) {
	return (RandUL() % (b - a + 1)) + a;
}

class FrTimer {
public:
	void SetTime();//start timing
	void Update();
	void StopTime();//end timing
	long long GetIntervalMilli();
private:
	SYSTEMTIME startTime;
	SYSTEMTIME now;
	bool stop;
};

void FrTimer::SetTime() {
	GetLocalTime(&now);
	startTime = now;
	stop = false;
}

void FrTimer::Update() {
	if(!stop)
		GetLocalTime(&now);
}

void FrTimer::StopTime() {
	stop = true;
}

long long FrTimer::GetIntervalMilli() {
	long long st = startTime.wMilliseconds + startTime.wSecond * 1000 + startTime.wMinute * 60 * 1000 
		+ startTime.wHour * 60 * 60 * 1000 + startTime.wDay * 24 * 60 * 60 * 1000;
	long long ed = now.wMilliseconds + now.wSecond * 1000 + now.wMinute * 60 * 1000
		+ now.wHour * 60 * 60 * 1000 + now.wDay * 24 * 60 * 60 * 1000;
	return ed - st;
		
}
//////////

/*
main functions of the engine
includes the objects
into the fr2dstg.h
*/
#include<list>

namespace Fr2DSTG{

	class Object {	//接口类，所有引擎内对象基类
	public:
		virtual void Show() = 0;
		virtual void Update() = 0;
		std::list<Object*> GetSon();
		void AddSon(Object* s);

	protected:
		bool del;
		std::list<Object*> son;

	};

	std::list<Object*> Object::GetSon() {
		return son;
	}

	void Object::AddSon(Object* s) {
		son.push_back(s);
	}

	//////////

	class Sprite :public Object {	//a universal object
	public:
		Sprite(double _x, double _y, Fr2DBitmap& _image, void(*showCallback)(Sprite*), void(*updateCallback)(Sprite*));
		void Show();
		void Update();
		Fr2DBitmap* image;
		double x, y;	//position
		double angle;	//the angle with the x axis of rad

	private:
		void(*showCallback)(Sprite*);
		void(*updateCallback)(Sprite*);
		
	};

	Sprite::Sprite(double _x, double _y, Fr2DBitmap& _image, void(*_showCallback)(Sprite*), void(*_updateCallback)(Sprite*)) {
		x = _x;
		y = _y;
		image = &_image;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
	}

	void Sprite::Show() {
		showCallback(this);
	}

	void Sprite::Update() {
		updateCallback(this);
	}

	
	class ObjectBuffer :public Object {
	public:
		void Show();
		void Update();
	};

	void ObjectBuffer::Show() {
		for (auto i = son.begin(); i != son.end(); i++)
			(*i)->Show();
	}

	void ObjectBuffer::Update() {
		for (auto i = son.begin(); i != son.end(); i++)
			(*i)->Update();
	}

}

//////////
