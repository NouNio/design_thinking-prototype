import { Routes } from '@angular/router';
import { Start } from './start/start';
import { Login } from './login/login';
import { Nopaired } from './nopaired/nopaired';
import { Finder } from './finder/finder';
import { Pair } from './pair/pair';
import { Events } from './events/events';
import { Delete } from './delete/delete';
import { Data } from './data/data';
import { Dashboard } from './dashboard/dashboard';
import { Success } from './success/success';
import { MapComponent } from './map-component/map-component';

export const routes: Routes = [

    { path: '', redirectTo: 'start', pathMatch: 'full' },
    { path: 'start', component: Start },
    { path: 'login', component: Login
     },
        { path: 'finder', component: Finder
     },
        { path: 'nopaired', component: Nopaired
     },
           { path: 'pair', component: Pair
     },
           { path: 'map', component: MapComponent
     },
          { path: 'events', component: Events
     },
          { path: 'delete', component: Delete
     },
         { path: 'data', component: Data
     },
         { path: 'dashboard', component: Dashboard
     },
         { path: 'success', component: Success
     },
];
