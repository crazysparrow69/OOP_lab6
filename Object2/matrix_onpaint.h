#pragma once
#include "framework.h"
#include <string>
#include <random>
#include <sstream>
#include <codecvt>

class MatrixOnPaint
{
private:
	MatrixOnPaint() {}
	MatrixOnPaint(const MatrixOnPaint& root) = delete;
	MatrixOnPaint& operator = (const MatrixOnPaint&) = delete;

	int N = 0;
	int min = 0;
	int max = 0;

	int** matrix = 0;
	std::string matrixText = "";
public:
	static MatrixOnPaint& getInstance()
	{
		static MatrixOnPaint instance;
		return instance;
	}

	void CopyData(HWND, WPARAM, LPARAM);
	void OnPaint(HWND, HDC);
	int** CreateMatrix(int, int, int);
	std::string GetMatrix(int**, int);
	int PutToClipboard(HWND, const char*);
};