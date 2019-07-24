const azureKinect = require('bindings')('azure_kinect');

console.log(azureKinect.hello());
console.log(azureKinect.getInstalledCount());
