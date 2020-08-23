//Headers
#include<Windows.h>
#include <process.h>
#define TIMER1 1000000
//global function declarations
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int cxClient, cyClient;
//Win main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    //Variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyApp");

    //code
    //intialization of WNDCLASSEX
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //register above class


    RegisterClassEx(&wndclass);

    //create window
    hwnd = CreateWindow(szAppName,
        TEXT("Cancer zodiac star sign"),
        WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN)-700)/2,
        (GetSystemMetrics(SM_CYSCREEN) -700)/2,
        700,
        700,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    //message window
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int)msg.wParam);
}
LRESULT	CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hbrush = CreateSolidBrush(RGB(0, 0,20));
    HPEN   hpen = CreatePen(PS_SOLID,3, RGB(255, 255, 255));
    POINT pt[2];
    int count = 1000;
    int x, y;
    //code

    switch (imsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, TIMER1, 500, NULL);
        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
        FillRect(hdc, &rc, hbrush);
        while (count !=0) //Star Printing loop
        {
            x = rand() % cxClient;
            y = rand() % cyClient;
            SetPixel(hdc, x,y, RGB(255, 255, 255));
            count--;
        }
        SelectObject(hdc, hpen);
        MoveToEx(hdc, ((cxClient / 2) - 165), ((cyClient / 2) - 5) - 190, NULL);
        LineTo(hdc, (cxClient / 2) - 50, (cyClient / 2)- 95);

        MoveToEx(hdc, (((cxClient / 2) - 5) - 45), ((cyClient / 2) - 5) - 95, NULL);
        LineTo(hdc, (cxClient / 2), (cyClient / 2));

        MoveToEx(hdc, (cxClient / 2), (cyClient / 2), NULL);
        LineTo(hdc, ((cxClient / 2) - 5) - 45, (cyClient / 2) + 95);

        MoveToEx(hdc, (cxClient / 2), (cyClient / 2), NULL);
        LineTo(hdc, ((cxClient / 2) + 200), (cyClient / 2) + 55);


        Ellipse(hdc, ((cxClient / 2)-170), ((cyClient / 2) - 5) - 195, ((cxClient / 2)- 160), ((cyClient / 2) + 5) - 195);//Top

        Ellipse(hdc, (((cxClient / 2) - 5) - 40), ((cyClient / 2) - 5) - 95, ((cxClient / 2) + 5) - 60, ((cyClient / 2) + 5) - 95);//Fisrt Upper of middle
        
        Ellipse(hdc, (cxClient / 2) - 5, (cyClient / 2) - 5, (cxClient / 2) + 5, (cyClient / 2) + 5);//Middle

        Ellipse(hdc, ((cxClient / 2) - 5)-40,((cyClient / 2) - 5)+95,((cxClient / 2) + 5)-60,((cyClient / 2) + 5)+95);//Left Bottom

        Ellipse(hdc, ((cxClient / 2) +200), (cyClient / 2)+50 , (cxClient / 2) + 210, ((cyClient / 2)+10)+50);//Right Bottom

       
        EndPaint(hwnd, &ps);
        break;
    case WM_TIMER:
        KillTimer(hwnd, TIMER1);
        InvalidateRect(hwnd, NULL, TRUE);
        SetTimer(hwnd, TIMER1, 500, NULL);
        break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        break;
    case WM_DESTROY:
        DeleteObject(hpen);
        DeleteObject(hdc);
        DeleteObject(hbrush);
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}
