
#include "stdafx.h"
#include "Container.h"
#include "Resource.h"
#include "TV_series.h"
#include "KSeriesVisitor.h"
#include "MVC.h"
#include <Windows.h>



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



static HWND hBut1;
static HWND hBut2;
static HWND hBut3;
static HWND hBut4;
static HWND hBut5;

static HWND hEdit1;
static HWND hEdit2;
static HWND hEdit3;
static HWND hEdit4;
static HWND hEdit5;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
   
    LoadStringW(hInstance, IDS_APP_TITLE, 0, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEQUE_MVC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEQUE_MVC));

    MSG msg;

 
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance){
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEQUE_MVC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEQUE_MVC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, 0, WS_OVERLAPPEDWINDOW,
      30, 70, 600, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   hBut1 = CreateWindow("button", "Sum of seasons",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	  
	   20, 160,
	   110, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON1,
	   hInstance, NULL);

   hBut2 = CreateWindow("button", "Sum of episods",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 200,
	   110, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON2,
	   hInstance, NULL);

   hBut3 = CreateWindow("button", "Push Season",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 80,
	   110, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON3,
	   hInstance, NULL);

   hBut4 = CreateWindow("button", "Push Episods",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	  
	   20, 120,
	   110, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON4,
	   hInstance, NULL);
   hBut5 = CreateWindow("button", "Pop",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

	   20, 240,
	   110, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON5,
	   hInstance, NULL);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	static DataSubject<Series> Subject;
	
	static DataObserver<Series> Obs3(&Subject, &hEdit5);
	static Controller<Series> Ctrl(&Subject);

	static ObserverForUser<Series> ObsChangeData(&Subject, &hEdit5, &Ctrl);

	switch (message) {
	case WM_CREATE:
		hEdit1 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			 160, 164, 150, 20,
			hWnd, (HMENU)ID_EDIT1, hInst, NULL);

		hEdit2 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			160, 204,150, 20,
			hWnd, (HMENU)ID_EDIT2, hInst, NULL);

		hEdit3 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			160, 84, 150, 20,
			hWnd, (HMENU)ID_EDIT3, hInst, NULL);

		hEdit4 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			160, 124, 150, 20,
			hWnd, (HMENU)ID_EDIT4, hInst, NULL);

		hEdit5 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			100, 44, 180, 25,
			hWnd, (HMENU)ID_EDIT5, hInst, NULL);
		

		break;

    case WM_COMMAND:{
		static bool IsChangeDate = false;
		int wmId = LOWORD(wParam);
		switch (wmId) {

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
			
		case IDB_BUTTON1: 
			Subject.GetSumSeas(&hEdit1);
			InvalidateRect(hWnd, 0, TRUE);
		break;

		case IDB_BUTTON2: 
			Subject.GetSumEp(&hEdit2);
			InvalidateRect(hWnd, 0, TRUE);
	    break;

		case IDB_BUTTON3: 
			Subject.PushFl(hEdit3);
		break;
			
		case IDB_BUTTON4: 
			Subject.PushRm(hEdit4);
		break;

		case IDB_BUTTON5:
			Subject.PopEl(&hEdit5);
			break;

		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
        break;

	case WM_SETFOCUS:{
		SetFocus(hEdit1);
		return 0;
	}

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)  {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

