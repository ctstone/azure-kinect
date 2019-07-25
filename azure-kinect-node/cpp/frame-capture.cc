#include <napi.h>
#include <chrono>
#include <thread>

#include <k4a.h>

class FrameCapture : public Napi::AsyncWorker
{
public:
  FrameCapture(
      Napi::Function &cb,
      k4a_device_t device,
      int frameCount)
      : Napi::AsyncWorker(cb)
  {
    this->device_ = device;
    this->frameCount_ = frameCount;
  }
  ~FrameCapture() {}

  void Execute()
  {
    int bodyIndex = 0;
    k4a_capture_t sensorCapture = NULL;
    while (this->frameCount_-- > 0)
    {
      Callback().Call({
          Env().Null(),
          Napi::Number::New(Env(), this->frameCount_),
      });
    }
  }

  void OnOK()
  {
    Napi::HandleScope scope(Env());
    Callback().Call({Env().Null(),
                     Env().Null()});
  }

private:
  k4a_device_t device_;
  int frameCount_;
};
