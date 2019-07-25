#include <napi.h>
#include <k4a.h>
#include "azure-kinect.h"

Napi::Number GetInstalledCount(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int count = k4a_device_get_installed_count();
  return Napi::Number::New(env, count);
}

void Temp(Napi::Env env, k4a_device_t *data)
{
  printf("GARBAGE COLLECTION");
}

Napi::Value DeviceOpen(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int32_t index = info[0].As<Napi::Number>().Int32Value();
  k4a_device_t device = NULL;

  if (K4A_RESULT_SUCCEEDED == k4a_device_open(index, &device))
  {
    auto _temp1 = Napi::External<k4a_device_t>::New(env, &device, Temp);
    auto _temp2 = _temp1.As<Napi::External<k4a_device_t>>().Data();
    k4a_device_close(*_temp2);

    return Napi::External<k4a_device_t>::New(env, &device, Temp);
  }
  else
  {
    return env.Undefined();
  }
}

void DeviceClose(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  k4a_device_t *device = info[0].As<Napi::External<k4a_device_t>>().Data();
  k4a_device_close(*device);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getInstalledCount"),
              Napi::Function::New(env, GetInstalledCount));

  AzureKinect::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)