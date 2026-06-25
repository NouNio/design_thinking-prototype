import { Component } from '@angular/core';
import { Footer } from "../footer/footer";

@Component({
  selector: 'app-data',
  imports: [Footer],
  templateUrl: './data.html',
  styleUrl: './data.css',
})
export class Data {
data: string ='data';
}
