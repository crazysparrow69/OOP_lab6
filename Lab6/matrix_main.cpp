#include "matrix_main.h"

INT_PTR CALLBACK Matrix(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            int N = 0;
            int min = 0;
            int max = 0;


            try
            {
                N = stod(MatrixMain::GetEnteredData(hDlg, IDC_N));
                min = stod(MatrixMain::GetEnteredData(hDlg, IDC_MIN));
                max = stod(MatrixMain::GetEnteredData(hDlg, IDC_MAX));
            }
            catch (...)
            {
                MessageBox(hDlg, L"Некоректні дані", L"Помилка", MB_ICONERROR);
                break;
            }
            

            if (min > max || N < 1 || N > 5 || abs(min) > 100 || abs(max) > 100)
            {
                MessageBox(hDlg, L"Некоректні дані", L"Помилка", MB_ICONERROR);
                break;
            }

            HWND hWnd2 = FindWindow(L"OBJECT2", NULL);
            if (!hWnd2)
            {
                WinExec("Object2.exe", SW_SHOW);
                hWnd2 = FindWindow(L"OBJECT2", NULL);
            }
            
            int parameters[3] = { N, min, max };
            MatrixMain::SendData(hWnd2, GetParent(hDlg), parameters, sizeof(parameters));

            HWND hWnd3 = FindWindow(L"OBJECT3", NULL);
            if (!hWnd3)
            {
                WinExec("Object3.exe", SW_SHOW);
                hWnd3 = FindWindow(L"OBJECT3", NULL);
            }
            PostMessage(hWnd3, WM_CLIPBOARDUPDATE, NULL, NULL);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void MatrixMain::Start(HINSTANCE hInst, HWND hWnd)
{
    DialogBox(hInst, MAKEINTRESOURCE(IDD_MATRIX), hWnd, Matrix);
}

std::wstring MatrixMain::GetEnteredData(HWND hWnd, int boxID)
{
    WCHAR buff[3];
    GetWindowText(GetDlgItem(hWnd, boxID), buff, 3);

    return buff;
}

void MatrixMain::SendData(HWND hWndDest, HWND hWndSrc, void* lp, long cb)
{
    COPYDATASTRUCT cds;

    cds.dwData = 1;
    cds.cbData = cb;
    cds.lpData = lp;

    SendMessage(hWndDest, WM_COPYDATA, (WPARAM)hWndSrc, (LPARAM)&cds);
}

void MatrixMain::End()
{
    HWND hWnd2 = FindWindow(L"OBJECT2", NULL);
    HWND hWnd3 = FindWindow(L"OBJECT3", NULL);

    if (hWnd2) PostMessage(hWnd2, WM_DESTROY, NULL, NULL);
    if (hWnd3) PostMessage(hWnd3, WM_DESTROY, NULL, NULL);
}