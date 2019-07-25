const { AzureKinect } = require('bindings')('azure_kinect');

const DEVICE_ID = 0;

const k = new AzureKinect(DEVICE_ID);

// console.log('open', k.open());
// console.log('start', k.startCameras());
// console.log('stop', k.stopCameras());
// console.log('close', k.close());


k.open();
console.log(k.startCameras());
k.captureFrames(100, (err, i) => {
  if (err) {
    throw err;
  }
  if (i === null) {
    console.log('DONE');
    k.stopCameras();
    k.close();
  } else {
    console.log('frame', i);
  }
});

// process.on('exit', () => {
//   kinect;
// });
