#include <windows.h>
#include<iostream>
using namespace std;


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void myText(int x, int y, const char* text, int R, int G, int B, int size = 24, const char* fontName = "Arial")
{
	HWND console_handle = GetConsoleWindow();
	HDC dc = GetDC(console_handle);

	wchar_t wFont[100];
	size_t outSize1;
	mbstowcs_s(&outSize1, wFont, fontName, 100);
	wchar_t wText[300];
	size_t outSize2;
	mbstowcs_s(&outSize2, wText, text, 300);

	// Create font
	HFONT font = CreateFontW(
		size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
		VARIABLE_PITCH, wFont
	);

	SetTextColor(dc, RGB(R, G, B));
	SetBkMode(dc, TRANSPARENT);
	SelectObject(dc, font);

	TextOutW(dc, x, y, wText, wcslen(wText));

	DeleteObject(font);
	ReleaseDC(console_handle, dc);
}


void myLineEdited(int x1, int y1, int x2, int y2, int R, int G, int B, int width) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, width, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}

void myLine(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	// Create a pen with full RGB support
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(R, G, B));
	SelectObject(device_context, pen);

	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

void myTriangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);

	int mid = (x1 + x2) / 2;
	MoveToEx(device_context, mid, y1, NULL);
	LineTo(device_context, x2, y2);
	LineTo(device_context, x1, y2);
	LineTo(device_context, mid + 1, y1);

	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B));  //Fill color is black
	SelectObject(device_context, brush);

	FloodFill(device_context, mid, (y1 + y2) / 2, RGB(R, G, B));

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);




}
void mytriangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);

	int mid = (x1 + x2) / 2;
	MoveToEx(device_context, mid, y1, NULL);
	LineTo(device_context, x1, y2);
	LineTo(device_context, x2, y1);
	LineTo(device_context, mid, y1);

	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B));  //Fill color is black
	SelectObject(device_context, brush);

	FloodFill(device_context, mid, (y1 + y2) / 2, RGB(0, 0, 255));

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);




}

bool isCursorKeyPressed(int& whickKey)   //whichKey passed as reference.... 
{
	char key;
	key = (char)GetAsyncKeyState(37);
	if (key == 1)
	{
		whickKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = (char)GetAsyncKeyState(38);
	if (key == 1)
	{

		whickKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = (char)GetAsyncKeyState(39);
	if (key == 1)
	{

		whickKey = 3; // 3 if right key is pressed
		return true;
	}
	key = (char)GetAsyncKeyState(40);
	if (key == 1)
	{

		whickKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = (char)GetAsyncKeyState(13);
	if (key == 1)
	{

		whickKey = 5;   // 5 if enter key is pressed
		return true;
	}
	key = GetAsyncKeyState(VK_SHIFT);
	if (key == 1)
	{
		whickKey = 6;
		return true;     // 6 if shift key is pressed
	}
	return false;
}


void myRect(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B)); //Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myRectOutline(int x1, int y1, int x2, int y2, int R, int G, int B, int width)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	HPEN pen = CreatePen(PS_SOLID, width, RGB(R, G, B)); // border pen
	SelectObject(device_context, pen);

	// Use NULL_BRUSH so the rectangle isn't filled
	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}

void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipseEdited(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}