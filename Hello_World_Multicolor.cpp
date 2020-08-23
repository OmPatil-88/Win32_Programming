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
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    TCHAR str[] = TEXT("Hello World !!!");
    static int iPaintFlag = 0;
    //code
    switch (imsg)
    {
    case WM_CHAR:
        switch (wParam)
        {
        case 'r':
        case 'R':
            iPaintFlag = 1;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'G':
        case 'g':
            iPaintFlag = 2;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'B':
        case 'b':
            iPaintFlag = 3;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'c':
        case 'C':
            iPaintFlag = 4;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'm':
        case 'M':
            iPaintFlag = 5;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'y':
        case 'Y':
            iPaintFlag = 6;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        default:
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        iPaintFlag = 7;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_LBUTTONDOWN:
        iPaintFlag = 0;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        switch (iPaintFlag)
        {
        case 0:
            SetTextColor(hdc, RGB(255, 255, 255));
            break;
        case 1:
            SetTextColor(hdc, RGB(255, 0, 0));
            break;
        case 2:
            SetTextColor(hdc, RGB(0, 255, 0));
            break;
        case 3:
            SetTextColor(hdc, RGB(0, 0, 255));
            break;
        case 4:
            SetTextColor(hdc, RGB(0, 255, 255));
            break;
        case 5:
            SetTextColor(hdc, RGB(225, 0, 255));
            break;
        case 6:
            SetTextColor(hdc, RGB(255, 255, 0));
            break;
        case 7:
            SetTextColor(hdc, RGB(255, 150, 0));
            break;

        }
        DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}