#include "Framework.h"
#include <locale>
#include <codecvt>

namespace {
HWND gWinHandle = nullptr;

static LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wParam,
                                LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      DestroyWindow(hwnd);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE) PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
}

HWND createWindow(const std::string& winTitle, uint32_t& width,
                  uint32_t& height) {
  LPCSTR className = "DxrWindowClass";
  DWORD winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME |
                   WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

  // Register the window class
  WNDCLASS wc = {};
  wc.lpfnWndProc = msgProc;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.lpszClassName = className;

  if (RegisterClass(&wc) == 0) {
    msgBox("RegisterClass() failed");
    return nullptr;
  }

  // Window size we have is for client area, calculate actual window size
  RECT r{0, 0, (LONG)width, (LONG)height};
  AdjustWindowRect(&r, winStyle, false);

  int windowWidth = r.right - r.left;
  int windowHeight = r.bottom - r.top;

  // create the window
  //   std::wstring wTitle = string2wstring(winTitle);
  HWND hWnd = CreateWindowEx(
      0, className, winTitle.c_str(), winStyle, CW_USEDEFAULT, CW_USEDEFAULT,
      windowWidth, windowHeight, nullptr, nullptr, wc.hInstance, nullptr);
  if (hWnd == nullptr) {
    msgBox("CreateWindowEx() failed");
    return nullptr;
  }

  return hWnd;
}

void msgLoop(Application& app) {
  MSG msg;
  while (1) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      app.onFrameRender();
    }
  }
}

}  // namespace

// std::wstring string2wstring(const std::string& s) {
//   std::wstring_convert<std::codecvt_utf8<WCHAR>> cvt;
//   std::wstring ws = cvt.from_bytes(s);
//   return ws;
// }

// std::string wstring2string(const std::wstring& ws) {
//   std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
//   std::string s = cvt.from_bytes(ws);
//   return s;
// }

void msgBox(const std::string& msg) {
  MessageBoxA(gWinHandle, msg.c_str(), "Error", MB_OK);
}

void d3dTraceHR(const std::string& msg, HRESULT hr) {
  char hr_msg[512];
  FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, hr, 0, hr_msg,
                 ARRAYSIZE(hr_msg), nullptr);

  std::string error_msg = msg + ".\nError! " + hr_msg;
  msgBox(error_msg);
}

void Framework::run(Application& app, const std::string& winTitle,
                    uint32_t width, uint32_t height) {
  gWinHandle = createWindow(winTitle, width, height);

  // Calculate the client-rect area
  RECT r;
  GetClientRect(gWinHandle, &r);
  width = r.right - r.left;
  height = r.bottom - r.top;

  // Call onLoad()
  app.onLoad(gWinHandle, width, height);

  // Show the window
  ShowWindow(gWinHandle, SW_SHOWNORMAL);

  // Start the msgLoop()
  msgLoop(app);

  // Cleanup
  app.onShutdown();
  DestroyWindow(gWinHandle);
}