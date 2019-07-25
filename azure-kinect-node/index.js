const { AzureKinect } = require('bindings')('azure_kinect');

const DEVICE_ID = 0;

const kinect = new AzureKinect(DEVICE_ID);
kinect.open();
// kinect.startJumpAnalysis((err, body) => {
//   console.log(new Date(), body);
// });

kinect.captureFrames(100, (err, i) => {
  if (err) {
    throw err;
  }
  if (i === null) {
    console.log('DONE');
  }
  console.log('frame', i);
})
kinect.close();
