import { AzureKinect } from 'azure-kinect-node';
import express from 'express';
import WebSocket from 'ws';

const PORT = 8080;

const server = express()
  .get('/', (req, res, next) => {
    res.json({ hello: 'world' });
  })
  .get('/test', (req, res, next) => {
    const k = new AzureKinect(0);

    const results = [];
    results.push(k.open());
    results.push(k.startCameras());
    results.push(k.stopCameras());
    results.push(k.close());

    res.status(200).json(results);
  })
  .listen(PORT, () => console.log(`Listening on port ${PORT}`));

new WebSocket.Server({ server })
  .on('connection', (socket) => {
    socket.on('message', (message) => {
      console.log('client said', message);
    });

    socket.send('Welcome to WebSockets');
  })
  ;
