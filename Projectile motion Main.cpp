//Draws falling balls on the desktop
// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib
					  //C:\Program Files\Microsoft Visual Studio\VC98\Lib
//// DEFINES ////////////////////////////////////////////////


//// MACROS /////////////////////////////////////////////////

// these read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//// PROTOTYPES /////////////////////////////////////////////
HWND RegisterWindow(HINSTANCE hinstance);

// GLOBALS ////////////////////////////////////////////////

HWND main_window_handle = NULL; // save the window handle
HINSTANCE main_instance = NULL; // save the instance
double angle=0;
char buffer[80];                // used to print text
char buffer2[80];

//// Structures ////////////////////////////////
struct BALL
{
	float vy;
	float vx;
	float x;
	float y;
};


//// FUNCTIONS //////////////////////////////////////////////

float deg2rad(float x)
{
	return (x/180*3.14159265f);
}

//\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	HWND	 hwnd;		  // generic window handle
	MSG		 msg;		  // generic message
	HDC      hdc;         // generic dc
	RECT     rect;        //create a rectangle structure
	int      ball_radius= 2;  //radius of the ball
	float    gravity= 1.1f,    //amount of gravity affecting the ball
			 friction= 0.995f, //amount of friction slowing the ball down
			 force= 50;
	BALL     ball;
	float      angle=160;

	HPEN black_pen= CreatePen(PS_SOLID, NULL, RGB(0,0,0)), 
		 red_pen= CreatePen(PS_SOLID, NULL, RGB(255,0,0)) ;
	HBRUSH black_brush= CreateSolidBrush(RGB(0,0,0)), 
		   red_brush= CreateSolidBrush(RGB(255,0,0));

	// save the window handle and instance in a global
	main_window_handle = hwnd = RegisterWindow(hinstance);
	main_instance      = hinstance;
	
	ball.vx = (float) sin( deg2rad(angle) ) * force;
	ball.vy = (float) cos( deg2rad(angle) ) * force;
	ball.x = 30;
	ball.y = 399;

	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
    
    	hdc= GetDC(hwnd);
		
		//--------- Erase The Ball -----------------------------
		//fill in rect struct for erasing ball
		rect.left = ball.x - ball_radius;
		rect.right = ball.x + ball_radius;
		rect.top = ball.y - ball_radius;
		rect.bottom = ball.y + ball_radius;
		
		//Draw erasing ball
		SelectObject(hdc, black_pen);
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//--------- End Erase The Ball --------------------------
		
		//------ Move the ball--------------
		
		ball.vy += gravity;
		ball.vy *= friction;
		ball.y += ball.vy;
		
		ball.vx += 0;
		ball.vx *= friction;
		ball.x +=  ball.vx;

		if(ball.y > 400)
		{
			ball.vy = -(ball.vy * 0.995);
			ball.y = 400;
		}
		if(ball.y <= 20)
		{
			ball.vy = -(ball.vy * 0.995);
			ball.y = 20;
		}
		if(ball.x >= 600)
		{
			ball.vx = -ball.vx;
			ball.x = 600;
		}
		if(ball.x <= 20)
		{
			ball.vx = -ball.vx;
			ball.x = 20;
		}
				
		//------ End Move ball -------------

		//---------- Draw The Ball ------------------------------
		//Redraw the ball in its new position
		
		//fill in rect struct for drawing ball
		rect.left = ball.x - ball_radius;
		rect.right = ball.x + ball_radius;
		rect.top = ball.y - ball_radius;
		rect.bottom = ball.y + ball_radius;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen);
		SelectObject(hdc, red_brush);
		Rectangle(hdc,20,400,50,409);
		MoveToEx(hdc,20,20,NULL);
		LineTo(hdc,20,400);
		LineTo(hdc,600,400);
		LineTo(hdc, 600,20);
		LineTo(hdc,20, 20);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//---------- End Draw The Ball --------------------------


		//slow things down a bit
		Sleep(25);
		ReleaseDC(hwnd, hdc);

	} // end while
	
	DeleteObject(red_pen);
	DeleteObject(red_brush);
	DeleteObject(black_brush);
	DeleteObject(black_pen);

	// return to Windows like this
	return(msg.wParam);

} // end WinMain


