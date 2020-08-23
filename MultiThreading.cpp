//Headers
#include<Windows.h>

//global function declarations
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
int mystrlen(TCHAR* str);

//Win main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    //Variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyApp");

    //cotde
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
    //code
    static HANDLE hThreadProcOne = NULL, hThreadProcTwo = NULL;
    switch (imsg)
    {
    case WM_CREATE:
        hThreadProcOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
        hThreadProcTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
        break;
    case WM_LBUTTONDOWN:
        MessageBox(hwnd, TEXT("Mouse Right Click"), TEXT("Message Box"), MB_OK);
        break;
    case WM_DESTROY:
        CloseHandle(hThreadProcOne);
        CloseHandle(hThreadProcTwo);
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}
DWORD WINAPI ThreadProcOne(LPVOID Param)
{
    static HDC hdc;
    unsigned long i;
    TCHAR str[255];

    hdc = GetDC((HWND)Param);
    for (i = 0; i <= ULLONG_MAX; i++)
    {
        wsprintf(str, TEXT("Thread1:Incresing Order:%ul  "), i);
        TextOut(hdc, 5, 5, str, mystrlen(str));
    }
    ReleaseDC((HWND)Param, hdc);
    return 0;
}
DWORD WINAPI ThreadProcTwo(LPVOID Param)
{
    static HDC hdc;
    int i;
    TCHAR str[255];

    hdc = GetDC((HWND)Param);
    for (i = 32768; i >= 0; i--)
    {
        wsprintf(str, TEXT("Thread2:Decresing Order:%d  "), i);
        TextOut(hdc, 5, 40, str, mystrlen(str));
        //Sleep(100);
    }
    ReleaseDC((HWND)Param, hdc);
    return 0;
}
int mystrlen(TCHAR* str)
{
    unsigned long cnt = 0;
    while (*str != '\0')
    {
        str++;
        cnt++;
    }
    return cnt;
}