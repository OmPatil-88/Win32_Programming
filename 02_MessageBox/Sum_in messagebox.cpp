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
    //variables
    static int iNUM1 = 55, iNUM2 = 45, iAns = 0;
    TCHAR str[255];
    //code
    switch (imsg)
    {
    case WM_CREATE:
         iAns=iNUM1+iNUM2;
         wsprintf(str,TEXT("The sum of %d and %d is %d"),iNUM1,iNUM2,iAns);
        MessageBox(hwnd,str, TEXT("Message Box"), MB_OK);
        break;
    case WM_KEYDOWN:
        MessageBox(hwnd, TEXT("Key Pressed"), TEXT("Message Box"), MB_OK);
        break;
    case WM_LBUTTONDOWN:
        MessageBox(hwnd, TEXT("Mouse Left Click"), TEXT("Message Box"), MB_OK);
        break;
    case WM_RBUTTONDOWN:
        MessageBox(hwnd, TEXT("Mouse Right Click"), TEXT("Message Box"), MB_OK);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}
