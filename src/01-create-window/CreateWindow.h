#pragma once
#include "Framework.h"

class CreateWindowApp : public Application {
 public:
  void onLoad(HWND winHandle, uint32_t winWidth, uint32_t winHeight) override;
  void onFrameRender() override;
  void onShutdown() override;

 private:
};