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
    static int xclient, yclient;
    static int cHight,cWidth;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    TEXTMETRIC tm;

    TCHAR str1[] = TEXT("The Pledge");
    TCHAR str2[] = TEXT("India is my country and all Indians are my brothers and sistersI love my country, and I am proud of its rich and varied heritage.");
    TCHAR str3[] = TEXT("I shall always strive to be worthy of it.I shall give respect to my parents, teachers and all the elders, and treat everyone with courtesy.");
    TCHAR str4[] = TEXT("To my country and my people, I pledge my devotion.In their well being and prosperity alone, lies my happiness.");
    //code
    switch (imsg)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cHight = tm.tmHeight+ tm.tmExternalLeading;
        cWidth = tm.tmAveCharWidth;
        ReleaseDC(hwnd, hdc);
        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255,255));
        TextOut(hdc, (xclient- (wcslen(str1)*cWidth)) / 2, yclient / 2, str1, wcslen(str1));

        SetTextColor(hdc, RGB(255,140,0));
        TextOut(hdc, (xclient - (wcslen(str2) * cWidth)) / 2, (yclient / 2)+cHight, str2, wcslen(str2));

        SetTextColor(hdc, RGB(255, 255, 255));
        TextOut(hdc, (xclient - (wcslen(str3) * cWidth)) / 2, (yclient / 2)+(cHight*2), str3, wcslen(str3));

        SetTextColor(hdc, RGB(0, 255,0));
        TextOut(hdc, (xclient - (wcslen(str4) * cWidth)) / 2, (yclient / 2)+(3*cHight), str4, wcslen(str4));
       
        EndPaint(hwnd, &ps);
        break;
    case WM_SIZE:
        xclient = LOWORD(lParam);
        yclient = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}