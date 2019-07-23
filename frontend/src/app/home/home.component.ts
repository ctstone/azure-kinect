import { Component, OnInit } from '@angular/core';
import { BackendService } from '../shared/backend.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {

  constructor(private backend: BackendService) { }

  ngOnInit() {
    this.backend.test().subscribe();

    const ws = new WebSocket(`ws://${window.document.location.host}/api`);
    ws.addEventListener('open', () => {
      console.log('CLIENT CONNECTED');
      ws.send('HELLO FROM THE CLIENT');
    });

    ws.addEventListener('error', (err) => {
      console.error(err);
    });

    ws.addEventListener('message', (message) => {
      console.log('MESSAGE', message);
    });

    ws.addEventListener('close', () => {
      console.log('CLIENT DISCONNECTED');
    });
  }

}
