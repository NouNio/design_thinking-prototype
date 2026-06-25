import { ComponentFixture, TestBed } from '@angular/core/testing';

import { Pair } from './pair';

describe('Pair', () => {
  let component: Pair;
  let fixture: ComponentFixture<Pair>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [Pair],
    }).compileComponents();

    fixture = TestBed.createComponent(Pair);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
