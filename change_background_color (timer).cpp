//Headers
#include<Windows.h>
#define TIMER1 1000000
//global function declarations
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
        TEXT("MY WINDOW"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
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
    //Variables
    
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    static int iPaintFlag;
    static HBRUSH hbrush[8];
    //code
    switch (imsg)
    {
    case WM_CREATE:
        hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
        hbrush[1] = CreateSolidBrush(RGB(0, 255, 0));
        hbrush[2] = CreateSolidBrush(RGB(0, 0, 255));
        hbrush[3] = CreateSolidBrush(RGB(255, 0, 255));
        hbrush[4] = CreateSolidBrush(RGB(255, 255, 0));
        hbrush[5] = CreateSolidBrush(RGB(0, 255, 255));
        hbrush[6] = CreateSolidBrush(RGB(0, 0, 0));
        hbrush[7] = CreateSolidBrush(RGB(255, 255, 255));
        SetTimer(hwnd, TIMER1, 1000, NULL);
        break;
    case WM_TIMER:
        KillTimer(hwnd, TIMER1);
        if (iPaintFlag > 8)iPaintFlag = -1;
        iPaintFlag++;
        InvalidateRect(hwnd,NULL,TRUE);
        SetTimer(hwnd, TIMER1, 1000, NULL);
        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc,hbrush[iPaintFlag]);
        FillRect(hdc,&rc,hbrush[iPaintFlag]);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}