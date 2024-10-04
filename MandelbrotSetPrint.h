#pragma once

#include "framework.h"
#include "MandelbrotSet.h"
#include "cmath"
#include <complex>

using namespace std;

static double GetDistance(double x, double y)
{
    return sqrt((x * x) + (y * y));
}

static double Formula(complex<double>* Z, complex<double> C)
{
    *Z = pow(*Z, 2) + C;
    return GetDistance(Z->real(), Z->imag());
}

static COLORREF Count(int x, int y, RECT rect)
{
    unsigned long iterations = 0;
    double a = (((rect.left / static_cast<double>(2)) - x + 1000) / 300) * -1;
    double b = (((rect.bottom / static_cast<double>(2)) - y - 150) / 300) * -1;
    complex<double> C(a, b);
    complex<double> Z(a, b);
    double distance = GetDistance(a, b);
    if(distance < 2)
    while (distance < 2 && iterations < 1000000)
    {
        distance = Formula(&Z, C);
        iterations += 10;
    }
    if (iterations >= 1000000)
        iterations = 0;
    else if (iterations != 0)
    {
        if (iterations > 0x00000100)
            iterations |= 0x000000ff;
        if (iterations > 0x00010000)
            iterations |= 0x0000ffff;
        if (iterations > 0x01000000)
            iterations |= 0x00ffffff;
    }
    unsigned long it1 = 0;
    unsigned long it2 = (iterations & 0x000000ff) * 0x10000;
    unsigned long it3 = 0;
    it1 = pow(((it2 / 0x10000) / 37), 3);
    it1 = it1 > 0x000000ff ? it1 | 0x000000ff : it1;
    it3 = pow((((it2 / 0x100) / 45)) / 0x100, 3) * 0x100;
    it3 = (it3 & 0xffffff00) > 0x0000ff00 ? it3 | 0x0000ff00 : it3;
    return COLORREF((it1 | it2 | it3) & 0x00ffffff);
}

static void Begin(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT rect;
    if (GetWindowRect(hWnd, &rect))
        for (int i = 0; i < rect.right; i++)
            for (int j = 0; j < rect.bottom; j++)
                SetPixel(hdc, i, j, Count(i, j, rect));
    EndPaint(hWnd, &ps);
}




