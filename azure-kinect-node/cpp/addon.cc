#include <napi.h>
#include <k4a.h>
#include "azure-kinect.h"

// k4a_device_configuration_t DeviceConfig()
// {
//   k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//   deviceConfig.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
//   deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_1080P;
//   deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//   deviceConfig.camera_fps = K4A_FRAMES_PER_SECOND_30;
//   deviceConfig.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//   deviceConfig.synchronized_images_only = true;
//   return deviceConfig;
// }

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

// Napi::Value DeviceGetCalibration(const Napi::CallbackInfo &info)
// {
//   Napi::Env env = info.Env();
//   k4a_device_t *device = info[0].As<Napi::External<k4a_device_t>>().Data();
//   k4a_device_configuration_t deviceConfig = DeviceConfig();

//   k4a_calibration_t calibration;
//   if (K4A_RESULT_SUCCEEDED == k4a_device_get_calibration(*device, deviceConfig.depth_mode, deviceConfig.color_resolution, &calibration))
//   {
//     int width = calibration.depth_camera_calibration.resolution_width;
//     return Napi::Number::New(env, width);
//   }
//   else
//   {
//     return env.Undefined();
//   }
// }

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

  // exports.Set(Napi::String::New(env, "openDevice"),
  //             Napi::Function::New(env, DeviceOpen));

  // exports.Set(Napi::String::New(env, "closeDevice"),
  //             Napi::Function::New(env, DeviceClose));

  // exports.Set(Napi::String::New(env, "getDeviceCalibration"),
  //             Napi::Function::New(env, DeviceGetCalibration));

  AzureKinect::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)