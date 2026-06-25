import { ComponentFixture, TestBed } from '@angular/core/testing';

import { Finder } from './finder';

describe('Finder', () => {
  let component: Finder;
  let fixture: ComponentFixture<Finder>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [Finder],
    }).compileComponents();

    fixture = TestBed.createComponent(Finder);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
