//This function registers and creates window

////INCLUDES/////////////////////////////////
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 

////DEFINES/////////////////////////////////
//defines for windows
#define WINDOW_CLASS_NAME "WINCLASS1"  // class name
#define WINDOW_WIDTH  640              // size of window
#define WINDOW_HEIGHT 480

////PROTOTYPES//////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

////FUNCTIONS///////////////////////////////

HWND RegisterWindow(HINSTANCE hinstance)
{	
	WNDCLASS winclass;	// this will hold the class created
	HWND hwnd;          //this will hold the windows handle

	//fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	
	// register the window class
	if (!RegisterClass(&winclass) )
		return(0);

	// create the window
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
							  "Bouncing on the desktop",	 // title
							  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						 	  200,200,	   // x,y
							  WINDOW_WIDTH,  // width
						      WINDOW_HEIGHT, // height
							  NULL,	   // handle to parent 
							  NULL,	   // handle to menu
							  hinstance,// instance
							  NULL)))	// creation parms
	{
		MessageBox(hwnd, "Window Could not be Created", NULL, MB_OK); //NULL is default for Error
		return(0);
	}

	return(hwnd);
}