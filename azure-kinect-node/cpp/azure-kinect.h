
#ifndef AZURE_KINECT_H
#define AZURE_KINECT_H

#include <napi.h>
#include <k4a.h>
#include <k4a/k4abt.h>

class AzureKinect : public Napi::ObjectWrap<AzureKinect>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  AzureKinect(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;
  Napi::Value Open(const Napi::CallbackInfo &info);
  void Close(const Napi::CallbackInfo &info);
  Napi::Value GetCalibration(const Napi::CallbackInfo &info);
  // Napi::Value StartJumpAnalysis(const Napi::CallbackInfo &info);

  int index_;
  k4a_device_t device;
};

#endif