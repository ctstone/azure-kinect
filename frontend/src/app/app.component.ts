import { Component, OnInit } from '@angular/core';
import { BackendService } from './shared/backend.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {

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
