const { AzureKinect } = require('bindings')('azure_kinect');

// const DEVICE_ID = 0;

// const k = new AzureKinect(DEVICE_ID);

// console.log('open', k.open());
// console.log('start', k.startCameras());
// console.log('stop', k.stopCameras());
// console.log('close', k.close());


// k.open();
// console.log(k.startCameras());
// const start = new Date().getTime();
// k.captureFrames(100, (err, i) => {
//   if (err) {
//     throw err;
//   }
//   if (i === null) {
//     console.log('DONE', new Date().getTime() - start);
//     k.stopCameras();
//     k.close();
//   } else {
//     console.log('frame', i);
//   }
// });

// k.startJumpAnalysis((err, x) => {
//   console.log('JUMP', x);
// });


exports.AzureKinect = AzureKinect;
