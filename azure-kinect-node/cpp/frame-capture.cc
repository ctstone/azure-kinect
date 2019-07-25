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
    int timeoutMs = 1000;
    k4a_capture_t capture = NULL;
    while (this->frameCount_-- > 0)
    {
      k4a_image_t image;
      k4a_wait_result_t result = k4a_device_get_capture(this->device_, &capture, timeoutMs);
      if (result == K4A_WAIT_RESULT_TIMEOUT)
      {
        printf("Timed out waiting for a capture\n");
        continue;
      }
      else if (result == K4A_WAIT_RESULT_FAILED)
      {
        printf("Failed to read a capture\n");
        break;
      }
      image = k4a_capture_get_color_image(capture);

      Napi::Int32Array array = Napi::Int32Array::New(Env(), 2);

      if (image)
      {
        int height = k4a_image_get_height_pixels(image);
        int width = k4a_image_get_width_pixels(image);

        array.Set(Napi::Number::New(Env(), 0), Napi::Number::New(Env(), width));
        array.Set(Napi::Number::New(Env(), 1), Napi::Number::New(Env(), height));

        k4a_image_release(image);
        k4a_capture_release(capture);
      }

      Napi::HandleScope scope(Env());
      Callback().Call({
          Env().Null(),
          array,
      });
    }

    Callback().Call({Env().Null(),
                     Env().Null()});
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
