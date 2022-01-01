#include "CreateWindow.h"

void CreateWindowApp::onLoad(HWND winHandle, uint32_t winWidth,
                             uint32_t winHeight) {}

void CreateWindowApp::onFrameRender() {}

void CreateWindowApp::onShutdown() {}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  Framework::run(CreateWindowApp(), "01 - Create Window");
}