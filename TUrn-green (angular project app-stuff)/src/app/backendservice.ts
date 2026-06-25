import { HttpClient } from '@angular/common/http';
import { Injectable, Service } from '@angular/core';
import { Observable } from 'rxjs';
import { catchError, tap } from 'rxjs/operators';

@Injectable()
export class Backendservice {

      private apiRoot = 'http://debian.local:5000';
      user?: string;
    
      constructor(private http: HttpClient) { }

        getkms(): Observable<any> {
            console.log('in service')
             return this.http.get<any>(this.apiRoot.concat('/distance'));
        } 

            login(usr: string, pass: string): Observable<any> {
            console.log('in service')
            //body = r
                         return this.http.get<any>(this.apiRoot.concat('/distance'));

            // return this.http.put<any>(this.apiRoot.concat('/login'));
        } 
  }