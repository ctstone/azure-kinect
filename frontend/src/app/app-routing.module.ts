import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { InfoComponent } from './info/info.component';
import { WorkoutsSquatComponent } from './workouts-squat/workouts-squat.component';
import { WorkoutsComponent } from './workouts/workouts.component';

const routes: Routes = [
  { path: '', pathMatch: 'full', component: InfoComponent },
  { path: 'workouts', component: WorkoutsComponent, children: [
    { path: '', pathMatch: 'full', redirectTo: 'squat' },
    { path: 'squat', component: WorkoutsSquatComponent },
  ]}
  // { path: '', component: HomeComponent, children: [
  //   { path: '', pathMatch: 'full', component: InfoComponent,  },
  //   { path: 'workouts', component: WorkoutsComponent, children: [
  //     { path: '', pathMatch: 'full', redirectTo: 'squat' },
  //     { path: 'squat', component: WorkoutsSquatComponent },
  //   ] },
  // ] },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
