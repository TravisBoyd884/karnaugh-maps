#pragma once
#include <cstdint>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CoolWindow(std::uint32_t width, std::uint32_t height);
