// lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab2.h"
#include <windowsx.h>
#include "Shape.h"
#include "PointShape.h"
#include "LineShape.h"
#include "RectShape.h"
#include "EllipseShape.h"


enum ShapeType
{
    SHAPE_POINT,
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_ELLIPSE
};

ShapeType currentShape = SHAPE_LINE;

const int MAX_SHAPES = 126;

Shape* shapes[MAX_SHAPES] = {};
int shapeCount = 0;

bool isDrawing = false;

POINT startPoint = {};
POINT currentPoint = {};


#define MAX_LOADSTRING 100




// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{
    switch (message)
    {

    case WM_INITMENUPOPUP:
    {
        HMENU hMenu = (HMENU)wParam;

        CheckMenuItem(hMenu, ID_OBJECT_LINE,
            MF_BYCOMMAND | (currentShape == SHAPE_LINE ? MF_CHECKED : MF_UNCHECKED));

        CheckMenuItem(hMenu, ID_OBJECT_RECT,
            MF_BYCOMMAND | (currentShape == SHAPE_RECTANGLE ? MF_CHECKED : MF_UNCHECKED));

        CheckMenuItem(hMenu, ID_OBJECT_ELLIPSE,
            MF_BYCOMMAND | (currentShape == SHAPE_ELLIPSE ? MF_CHECKED : MF_UNCHECKED));

        CheckMenuItem(hMenu, ID_OBJECT_POINT,
            MF_BYCOMMAND | (currentShape == SHAPE_POINT ? MF_CHECKED : MF_UNCHECKED));

        break;
    }

    case WM_LBUTTONDOWN:
    {
        if (shapeCount >= MAX_SHAPES)
        {
            MessageBoxW(hWnd, L"Досягнуто ліміт 126 фігур!",
                L"Увага", MB_OK | MB_ICONWARNING);
            break;
        }

        startPoint.x = GET_X_LPARAM(lParam);
        startPoint.y = GET_Y_LPARAM(lParam);
        currentPoint = startPoint;

        isDrawing = true;
        SetCapture(hWnd);
        break;
    }

    case WM_MOUSEMOVE:
    {
        if (isDrawing)
        {
            currentPoint.x = GET_X_LPARAM(lParam);
            currentPoint.y = GET_Y_LPARAM(lParam);

            InvalidateRect(hWnd, nullptr, TRUE);
        }
        break;
    }

    case WM_LBUTTONUP:
    {
        if (isDrawing)
        {
            currentPoint.x = GET_X_LPARAM(lParam);
            currentPoint.y = GET_Y_LPARAM(lParam);

            Shape* newShape = nullptr;

            switch (currentShape)
            {
            case SHAPE_POINT:
                newShape = new PointShape(startPoint);
                break;

            case SHAPE_LINE:
                newShape = new LineShape(startPoint, currentPoint);
                break;

            case SHAPE_RECTANGLE:
                newShape = new RectShape(startPoint, currentPoint);
                break;

            case SHAPE_ELLIPSE:
                newShape = new EllipseShape(startPoint, currentPoint);
                break;
            }

            if (newShape != nullptr && shapeCount < MAX_SHAPES)
            {
                shapes[shapeCount] = newShape;
                shapeCount++;
            }

            isDrawing = false;
            ReleaseCapture();
            InvalidateRect(hWnd, nullptr, TRUE);
        }
        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {

        case ID_OBJECT_LINE:
            currentShape = SHAPE_LINE;
            break;

        case ID_OBJECT_RECT:
            currentShape = SHAPE_RECTANGLE;
            break;

        case ID_OBJECT_ELLIPSE:
            currentShape = SHAPE_ELLIPSE;
            break;

        case ID_OBJECT_POINT:
            currentShape = SHAPE_POINT;
            break;


        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;


    case WM_DESTROY:
    {
        for (int i = 0; i < shapeCount; i++)
        {
            delete shapes[i];
            shapes[i] = nullptr;
        }

        shapeCount = 0;

        PostQuitMessage(0);
        break;
    }


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        for (int i = 0; i < shapeCount; i++)
        {
            if (shapes[i] != nullptr)
            {
                shapes[i]->Draw(hdc);
            }
        }

        if (isDrawing)
        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
            HPEN oldPen = (HPEN)SelectObject(hdc, pen);

            HBRUSH oldBrush = (HBRUSH)SelectObject(
                hdc, GetStockObject(NULL_BRUSH));

            switch (currentShape)
            {
            case SHAPE_POINT:
                SetPixel(hdc, startPoint.x, startPoint.y,
                    RGB(0, 0, 255));
                break;

            case SHAPE_LINE:
                MoveToEx(hdc, startPoint.x, startPoint.y, nullptr);
                LineTo(hdc, currentPoint.x, currentPoint.y);
                break;

            case SHAPE_RECTANGLE:
            {
                int left = (startPoint.x < currentPoint.x)
                    ? startPoint.x : currentPoint.x;
                int top = (startPoint.y < currentPoint.y)
                    ? startPoint.y : currentPoint.y;
                int right = (startPoint.x > currentPoint.x)
                    ? startPoint.x : currentPoint.x;
                int bottom = (startPoint.y > currentPoint.y)
                    ? startPoint.y : currentPoint.y;

                Rectangle(hdc, left, top, right, bottom);
                break;
            }

            case SHAPE_ELLIPSE:
            {
                int dx = abs(currentPoint.x - startPoint.x);
                int dy = abs(currentPoint.y - startPoint.y);

                Ellipse(hdc,
                    startPoint.x - dx,
                    startPoint.y - dy,
                    startPoint.x + dx,
                    startPoint.y + dy);
                break;
            }
            }

            SelectObject(hdc, oldBrush);
            SelectObject(hdc, oldPen);
            DeleteObject(pen);
        }

        EndPaint(hWnd, &ps);
    }
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
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
