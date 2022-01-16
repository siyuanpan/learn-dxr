#pragma once
#include "Framework.h"

class AccelerationStructure : public Application {
 public:
  void onLoad(HWND winHandle, uint32_t winWidth, uint32_t winHeight) override;
  void onFrameRender() override;
  void onShutdown() override;

 private:
  void initDXR(HWND winHANDLE, uint32_t winWidth, uint32_t winHeight);
  uint32_t beginFrame();
  void endFrame(uint32_t rtvIndex);
  HWND mHwnd = nullptr;
  ID3D12Device5Ptr mpDevice;
  ID3D12CommandQueuePtr mpCmdQueue;
  IDXGISwapChain3Ptr mpSwapChain;
  uvec2 mSwapChainSize;
  ID3D12GraphicsCommandList4Ptr mpCmdList;
  ID3D12FencePtr mpFence;
  HANDLE mFenceEvent;
  uint64_t mFenceValue = 0;

  static const uint32_t kDefaultSwapChainBuffers = 3;

  struct {
    ID3D12CommandAllocatorPtr pCmdAllocator;
    ID3D12ResourcePtr pSwapChainBuffer;
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
  } mFrameObjects[kDefaultSwapChainBuffers];

  // Heap data
  struct HeapData {
    ID3D12DescriptorHeapPtr pHeap;
    uint32_t usedEntries = 0;
  };
  HeapData mRtvHeap;
  static const uint32_t kRtvHeapSize = 3;

  void createAccelerationStructures();
  ID3D12ResourcePtr mpVertexBuffer;
  ID3D12ResourcePtr mpTopLevelAS;
  ID3D12ResourcePtr mpBottomLevelAS;
  uint64_t mTlasSize = 0;
};