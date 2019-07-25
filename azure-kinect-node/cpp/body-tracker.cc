// #include <napi.h>
// #include <chrono>
// #include <thread>

// #include <k4a.h>
// #include <k4a/k4abt.h>

// class BodyTracker : public Napi::AsyncWorker
// {
// public:
//   BodyTracker(
//       Napi::Function &cb,
//       k4a_device_t device,
//       k4abt_tracker_t tracker)
//       : Napi::AsyncWorker(cb)
//   {
//     this->device_ = device;
//     this->tracker_ = tracker;
//   }
//   ~BodyTracker() {}

//   void Execute()
//   {
//     int bodyIndex = 0;
//     k4a_capture_t sensorCapture = NULL;
//     k4abt_frame_t bodyFrame = NULL;
//     while (this->shouldRun_)
//     {
//       k4a_wait_result_t getCaptureResult = k4a_device_get_capture(this->device_, &sensorCapture, 0);
//       k4a_wait_result_t queueCaptureResult = k4abt_tracker_enqueue_capture(this->tracker_, sensorCapture, 0);
//       k4a_capture_release(sensorCapture);

//       k4a_wait_result_t popFrameResult = k4abt_tracker_pop_result(this->tracker_, &bodyFrame, 0);
//       if (k4abt_frame_get_num_bodies(bodyFrame) > 0)
//       {
//         k4abt_body_t body;
//         k4abt_frame_get_body_skeleton(bodyFrame, bodyIndex, &body.skeleton);
//         body.id = k4abt_frame_get_body_id(bodyFrame, bodyIndex);

//         Callback().Call({Env().Null(),
//                          Napi::Buffer<k4abt_body_t>::New(Env(), &body, sizeof(k4abt_body_t))});
//       }
//     }
//   }

//   void OnOK()
//   {
//     Napi::HandleScope scope(Env());
//     Callback().Call({Env().Null(),
//                      Napi::String::New(Env(), "hello")});
//   }

//   void Stop()
//   {
//     this->shouldRun_ = false;
//   }

// private:
//   k4a_device_t device_;
//   k4abt_tracker_t tracker_;
//   bool shouldRun_ = true;
// };
