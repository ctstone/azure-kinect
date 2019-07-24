#include <napi.h>
#include <k4a.h>

Napi::String Method(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  return Napi::String::New(env, "world");
}

Napi::Number GetInstalledCount(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int count = k4a_device_get_installed_count();
  return Napi::Number::New(env, count);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Method));

  exports.Set(Napi::String::New(env, "getInstalledCount"),
              Napi::Function::New(env, GetInstalledCount));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)