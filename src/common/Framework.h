#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GLM_FORCE_CTOR_INIT
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <string>
#include <d3d12.h>
#include <comdef.h>
#include <dxgi1_4.h>
#include <dxgiformat.h>
#include <fstream>
#include "dxcapi.use.h"
#include <vector>
#include <array>

using namespace glm;

#define MAKE_SMART_COM_PTR(_a) _COM_SMARTPTR_TYPEDEF(_a, __uuidof(_a))
MAKE_SMART_COM_PTR(ID3D12Device5);
MAKE_SMART_COM_PTR(ID3D12GraphicsCommandList4);
MAKE_SMART_COM_PTR(ID3D12CommandQueue);
MAKE_SMART_COM_PTR(IDXGISwapChain3);
MAKE_SMART_COM_PTR(IDXGIFactory4);
MAKE_SMART_COM_PTR(IDXGIAdapter1);
MAKE_SMART_COM_PTR(ID3D12Fence);
MAKE_SMART_COM_PTR(ID3D12CommandAllocator);
MAKE_SMART_COM_PTR(ID3D12Resource);
MAKE_SMART_COM_PTR(ID3D12DescriptorHeap);
MAKE_SMART_COM_PTR(ID3D12Debug);
MAKE_SMART_COM_PTR(ID3D12StateObject);
MAKE_SMART_COM_PTR(ID3D12RootSignature);
MAKE_SMART_COM_PTR(ID3DBlob);
MAKE_SMART_COM_PTR(IDxcBlobEncoding);

// Interface for the Application
class Application {
 public:
  virtual ~Application() {}
  virtual void onLoad(HWND winHandle, uint32_t winWidth,
                      uint32_t winHeight) = 0;
  virtual void onFrameRender() = 0;
  virtual void onShutdown() = 0;
};

class Framework {
 public:
  static void run(Application& app, const std::string& winTitle,
                  uint32_t width = 1920, uint32_t height = 1200);
};

static const uint32_t sDefaultSwapChainBuffers = 3;

#define d3d_call(a)       \
  {                       \
    HRESULT hr = a;       \
    if (FAILED(hr)) {     \
      d3dTraceHR(#a, hr); \
    }                     \
  }

#define arraysize(a) (sizeof(a) / sizeof(a[0]))
#define align_to(alignment, val) \
  (((val + alignment - 1) / alignmet) * alignment)

void msgBox(const std::string& msg);
void d3dTraceHR(const std::string& msg, HRESULT hr);
// std::wstring string2wstring(const std::string& s);
// std::string wstring2string(const std::wstring& ws);

template <class BlotType>
std::string convertBlobToString(BlotType* pBlob) {
  std::vector<char> infoLog(pBlob->GetBufferSize() + 1);
  memcpy(infoLog.data(), pBlob->GetBufferPointer(), pBlob->GetBufferSize());
  infoLog[pBlob->GetBufferSize()] = 0;
  return std::string(infoLog.data());
}