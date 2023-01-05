#pragma once
#include "framework.h"
#include "resource1.h"
#include <string>
#include <cmath>

class MatrixMain
{
private:
	MatrixMain() {}
	MatrixMain(const MatrixMain& root) = delete;
	MatrixMain& operator = (const MatrixMain&) = delete;
public:
	static MatrixMain& getInstance()
	{
		static MatrixMain instance;
		return instance;
	}
	static std::wstring GetEnteredData(HWND, int);
	static void SendData(HWND, HWND, void*, long);
	void Start(HINSTANCE, HWND);
	void End();
};