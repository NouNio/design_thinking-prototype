import { TestBed } from '@angular/core/testing';

import { Backendservice } from './backendservice';

describe('Backendservice', () => {
  let service: Backendservice;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(Backendservice);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
