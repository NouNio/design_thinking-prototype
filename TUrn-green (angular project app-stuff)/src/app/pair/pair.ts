import { Component } from '@angular/core';

@Component({
  selector: 'app-pair',
  imports: [],
  templateUrl: './pair.html',
  styleUrl: './pair.css',
})
export class Pair {
devices: string[] = [
  'id0',
    'id1',
  'id2'

];
scanned: boolean=false;

set(): void {
  this.scanned = true;
  }
}
