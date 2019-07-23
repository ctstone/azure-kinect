import express from 'express';
import WebSocket from 'ws';

const PORT = 8080;

const server = express()
  .get('/', (req, res, next) => {
    res.json({ hello: 'world' });
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
