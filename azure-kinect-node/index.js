const { AzureKinect } = require('bindings')('azure_kinect');

const DEVICE_ID = 0;

const kinect = new AzureKinect(DEVICE_ID);
kinect.open();
kinect.close();
