import { AzureKinect } from 'azure-kinect-node';
import express from 'express';
import fs from 'fs';
import watch from 'watch';
import WebSocket from 'ws';

const PORT = 8080;
const RESULTS_TXT = '/gigitest/results.txt';

const server = express()
  .get('/', (req, res, next) => {
    res.json({ hello: 'world' });
  })
  .get('/test', (req, res, next) => {
    // const k = new AzureKinect(0);

    // const results = [];
    // results.push(k.open());
    // results.push(k.startCameras());
    // results.push(k.stopCameras());
    // results.push(k.close());

    // res.status(200).json(results);
    next(new Error());
  })
  .listen(PORT, () => console.log(`Listening on port ${PORT}`));

new WebSocket.Server({ server })
  .on('connection', (socket) => {

    fs.watchFile(RESULTS_TXT, (c, p) => {
      fs.readFile(RESULTS_TXT, 'utf8', (err, data) => {
        socket.send(data);
      });
    });

    socket.send('[5,0,0,0,0]');

    socket.on('message', (message) => {
      console.log('client said', message);
    });
  })
  ;
