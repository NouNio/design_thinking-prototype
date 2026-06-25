import { Component } from '@angular/core';
import { Footer } from "../footer/footer";

@Component({
  selector: 'app-map-component',
  imports: [Footer],
  templateUrl: './map-component.html',
  styleUrl: './map-component.css',
})
export class MapComponent {
map: string = 'map';
}
