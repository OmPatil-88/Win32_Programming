#include<Windows.h>
#include"Resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND  hwnd;
	TCHAR Appname[] = TEXT("MYCLASS");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYIOCN));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = Appname;
	wndclass.lpszMenuName = TEXT("MENUDEMO");
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYIOCN));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(Appname,TEXT("Menu Window"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	static int idColor[5] = {WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH,DKGRAY_BRUSH, BLACK_BRUSH};

	static int idSelection = IDM_BG_WHITE;
	HMENU hmenu;
	HCURSOR hCursor;
	HINSTANCE hInstance;
	switch (imsg)
	{
    case WM_CREATE:
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_FILE_NEW:
			break;
		case IDM_FILE_OPEN:
			break;
		case IDM_FILE_SAVE:
			break;
		case IDM_FILE_SAVE_AS:
			break;
		case IDM_FILE_EXIT:           
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;                                       
		case IDM_BG_BLACK:
		case IDM_BG_GRY:
		case IDM_BG_WHITE:
		case IDM_BG_LIGHTGRY:
		case IDM_BG_SYKBLUE:
			hmenu = GetMenu(hwnd);

			CheckMenuItem(hmenu, idSelection, MF_UNCHECKED);
			idSelection = LOWORD(wParam);
			CheckMenuItem(hmenu, idSelection, MF_CHECKED);

			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(idColor[idSelection - IDM_BG_WHITE]));
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, imsg, wParam, lParam));
}
