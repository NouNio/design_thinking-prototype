import { ChangeDetectorRef, Component, OnInit } from '@angular/core';
import { Footer } from "../footer/footer";
import { Backendservice } from '../backendservice';
import { Observable } from 'rxjs';
import { Router, RouterLink } from "@angular/router";

@Component({
  selector: 'app-dashboard',
  imports: [Footer, RouterLink],
  templateUrl: './dashboard.html',
  styleUrl: './dashboard.css',
})
export class Dashboard implements OnInit{
  km: any;
  error: any;
you: string = 'you';
  constructor(private service: Backendservice,
    private cd: ChangeDetectorRef,
    private router: Router
  ) {
   }
    ngOnInit(): void {
      if(!this.service.user){
        //this.router.navigate(['/start']);
      }
      console.log('want to get')
    this.service.getkms().subscribe(
        (n: any) => {this.km = n.sum
          console.log(this.km)
              this.cd.detectChanges()

        },
      (error: any) => this.error=error
    );

  }

}
