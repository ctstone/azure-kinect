#include "azure-kinect.h"

Napi::FunctionReference AzureKinect::constructor;

Napi::Object AzureKinect::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  auto members = {InstanceMethod("open", &AzureKinect::Open),
                  InstanceMethod("close", &AzureKinect::Close),
                  InstanceMethod("getCalibration", &AzureKinect::GetCalibration)};
  Napi::Function func = DefineClass(env, "AzureKinect", members);

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("AzureKinect", func);
  return exports;
}

AzureKinect::AzureKinect(const Napi::CallbackInfo &info) : Napi::ObjectWrap<AzureKinect>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->index_ = info[0].As<Napi::Number>().Int32Value();
}

Napi::Value AzureKinect::Open(const Napi::CallbackInfo &info)
{
  k4a_result_t result = k4a_device_open(this->index_, &this->device);
  return Napi::Number::New(info.Env(), result);
}

void AzureKinect::StartJumpAnalysis(const Napi::CallbackInfo &info)
{
  k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  deviceConfig.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_OFF;

  // start the cameras
  k4a_device_start_cameras(this->device, &deviceConfig);

  // get calibration
  k4a_calibration_t sensorCalibration;
  k4a_device_get_calibration(device, deviceConfig.depth_mode, deviceConfig.color_resolution, &sensorCalibration);

  // tracker
  k4abt_tracker_t tracker = NULL;
  k4abt_tracker_create(&sensorCalibration, &tracker);
}

Napi::Value AzureKinect::GetCalibration(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  // TODO expose args
  auto color_resolution = K4A_COLOR_RESOLUTION_1080P;
  auto depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;

  k4a_calibration_t calibration;
  if (K4A_RESULT_SUCCEEDED == k4a_device_get_calibration(this->device, depth_mode, color_resolution, &calibration))
  {
    // return Napi::Object::<k4a_calibration_t>(env, calibration);
    return Napi::Buffer<k4a_calibration_t>::New(env, &calibration, sizeof(calibration));
  }
  else
  {
    return env.Undefined();
  }
}

void AzureKinect::Close(const Napi::CallbackInfo &info)
{
  k4a_device_close(this->device);
}

// Napi::Value AzureKinect::GetValue(const Napi::CallbackInfo &info)
// {
//   double num = this->value_;

//   return Napi::Number::New(info.Env(), num);
// }

// Napi::Value AzureKinect::PlusOne(const Napi::CallbackInfo &info)
// {
//   this->value_ = this->value_ + 1;

//   return AzureKinect::GetValue(info);
// }

// Napi::Value AzureKinect::Multiply(const Napi::CallbackInfo &info)
// {
//   Napi::Number multiple;
//   if (info.Length() <= 0 || !info[0].IsNumber())
//   {
//     multiple = Napi::Number::New(info.Env(), 1);
//   }
//   else
//   {
//     multiple = info[0].As<Napi::Number>();
//   }

//   Napi::Object obj = constructor.New({Napi::Number::New(info.Env(), this->value_ * multiple.DoubleValue())});

//   return obj;
// }