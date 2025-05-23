#include <cstdint>
#include <stdexcept>
#include <windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_ERASEBKGND: {
    HDC hdc = (HDC)wParam;
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Create a solid brush with the desired color (e.g., blue)
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));

    // Fill the background with the brush
    FillRect(hdc, &rect, hBrush);

    // Clean up the brush
    DeleteObject(hBrush);

    // Return 1 to indicate that the background has been erased
    return 1;
  }
  case WM_CLOSE:
    DestroyWindow(hwnd);
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}

void CoolWindow(std::uint32_t width, std::uint32_t height) {
  HWND window_;
  WNDCLASSA wc_;

  wc_ = {};

  wc_.lpfnWndProc = WindowProc;
  wc_.hInstance = GetModuleHandleA(nullptr);
  wc_.lpszClassName = "mainwindow";
  wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

  if (RegisterClassA(&wc_) == 0) {
    throw std::runtime_error("Failed to register window class");
  }

  RECT rect{
      .left = {},
      .top = {},
      .right = static_cast<int>(width),
      .bottom = static_cast<int>(height),
  };

  if (AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) == 0) {
    throw std::runtime_error("Could not resize window");
  }

  window_ = CreateWindowExA(0,                 // Optional window styles.
                            wc_.lpszClassName, // Window class
                            "Learn to Program Windows", // Window text
                            WS_OVERLAPPEDWINDOW,        // Window style

                            // Size and position
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            rect.right - rect.left, rect.bottom - rect.top,

                            NULL,          // Parent window
                            NULL,          // Menu
                            wc_.hInstance, // Instance handle
                            NULL           // Additional application data
  );
  ShowWindow(window_, SW_SHOW);
  UpdateWindow(window_);
}
