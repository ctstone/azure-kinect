import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-workouts-squat',
  templateUrl: './workouts-squat.component.html',
  styleUrls: ['./workouts-squat.component.scss']
})
export class WorkoutsSquatComponent implements OnInit {

  VIDEOS = [
    { name: 'Video 1', path: 'assets/video/squats/video1.mp4' },
    { name: 'Video 2', path: 'assets/video/squats/video2.mp4' },
    { name: 'Video 3', path: 'assets/video/squats/video3.mp4' },
    { name: 'Video 4', path: 'assets/video/squats/video4.mp4' },
    { name: 'Video 5', path: 'assets/video/squats/video5.mp4' },
  ];

  videoIndex = 0;
  errorMessage: string;
  deviceReady = false;
  results: number[][];

  constructor() { }

  ngOnInit() {
    const ws = new WebSocket(`ws://${window.document.location.host}/api`);
    ws.addEventListener('message', (event) => {
      const data = JSON.parse(event.data) as number[];
      this.results = data.map((n) => new Array(n));
    });

    const video = document.getElementById('webcam-video') as HTMLVideoElement;
    const canvas = document.getElementById('webcam-canvas') as HTMLCanvasElement;
    const ctx = canvas.getContext('2d');

    const drawCanvas = () => {
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      ctx.drawImage(video, 0, 0);
      requestAnimationFrame(drawCanvas);
    };

    video.addEventListener('loadend', () => {
      const {
        videoWidth,
        videoHeight } = video;
      canvas.width = videoWidth;
      canvas.height = videoHeight;
      this.deviceReady = true;
      drawCanvas();
    });

    navigator.mediaDevices.getUserMedia({ video: true })
      .then((stream) => {
        video.srcObject = stream;
      })
      .catch((err) => {
        console.error(err.message);
        this.errorMessage = 'Could not find your webcam. Check connections to the device!';
      });
  }

  startVideo(i: number, video: HTMLVideoElement) {
    const path = this.VIDEOS[i].path;
    const onVideoLoad = () => {
      video.play();
      video.removeEventListener('loadeddata', onVideoLoad);
    };

    video.addEventListener('loadeddata', onVideoLoad);
    video.src = path;

    this.videoIndex = i;
  }

}
