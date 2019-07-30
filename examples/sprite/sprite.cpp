#include "fr2dstg.h"
using namespace Fr2DSTG;

float x = 0, y = 0;
void keyboard() {

	if (getKey[VK_LEFT])
		x -= 5;
	if (getKey[VK_RIGHT])
		x += 5;
	if (getKey[VK_UP])
		y -= 5;
	if (getKey[VK_DOWN])
		y += 5;

}

bool Display();
HWND hwnd;
FrWnd *myWnd = new FrWnd(800, 600, Display, "hello");
Fr2D *myFr2D = new Fr2D(hwnd);
Fr2DBitmap s1img(L"enemy1.png");

void S1Show(Sprite* t) {
	myFr2D->DrawBitmap(*(t->image), t->x, t->y, t->x + 30, t->y + 30);
}

void S1Update(Sprite* t) {
	t->x = t->x + 0.1;
	t->y = t->y + 0.1;
}

void S2Update(Sprite* t) {
	t->x = t->x - 0.1;
	t->y = t->y - 0.1;
}

ObjectBuffer myOb;

void Init() {
	myFr2D->Create();

	s1img.Create();
	myFr2D->CreateBitmap(s1img);
	
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			if((i+j)%2==0)myOb.AddSon(new Sprite(0 + (15 * i), 0 + (15 * j), s1img, S1Show, S1Update));
			else myOb.AddSon(new Sprite(0 + (15 * i), 0 + (15 * j), s1img, S1Show, S2Update));
}

bool Display() {
	keyboard();
	myFr2D->BeginDraw();
	myFr2D->Clear(_FR2DCOLOR(White));

	myOb.Update();
	myOb.Show();

	return myFr2D->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
