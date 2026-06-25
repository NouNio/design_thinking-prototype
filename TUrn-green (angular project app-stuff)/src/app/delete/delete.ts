import { Component } from '@angular/core';
import { Footer } from "../footer/footer";

@Component({
  selector: 'app-delete',
  imports: [Footer],
  templateUrl: './delete.html',
  styleUrl: './delete.css',
})
export class Delete {
data: string = 'data';
}
