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
    navigator.mediaDevices.getUserMedia({ video: true })
      .then((stream) => {
        video.srcObject = stream;
        this.deviceReady = true;
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
