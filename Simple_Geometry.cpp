//Headers
#include<Windows.h>
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
        TEXT("Ellipse"),
        WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN)-500)/2,
        (GetSystemMetrics(SM_CYSCREEN) -500)/2,
        500,
        500,
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
    static int cxClient, cyClient;
    static RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hbrush_Ylow = CreateSolidBrush(RGB(255,255, 0));
    //code
    switch (imsg)
    {
    case WM_CREATE:
            break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, hbrush_Ylow); //////////////////Outer Yellow
        Ellipse(hdc, rc.left+200, rc.top+200, rc.right-200, rc.bottom-200);
        EndPaint(hwnd, &ps);
        
        break;
    case WM_SIZE:
        GetClientRect(hwnd,&rc);
        InvalidateRect(hwnd, &rc, TRUE);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}