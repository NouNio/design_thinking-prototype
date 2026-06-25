import { Component } from '@angular/core';
import { Footer } from "../footer/footer";

@Component({
  selector: 'app-events',
  imports: [Footer],
  templateUrl: './events.html',
  styleUrl: './events.css',
})
export class Events {
events: string = 'events';
}
