import { ComponentFixture, TestBed } from '@angular/core/testing';

import { Nopaired } from './nopaired';

describe('Nopaired', () => {
  let component: Nopaired;
  let fixture: ComponentFixture<Nopaired>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [Nopaired],
    }).compileComponents();

    fixture = TestBed.createComponent(Nopaired);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
