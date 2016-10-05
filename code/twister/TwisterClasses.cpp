//    Tetrode Twister Control Software
//    Copyright (C) 2011 Josh Siegle
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "TwisterClasses.h"

// Buzzer methods:

Buzzer::Buzzer(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Buzzer::high()
{
  tone(_pin,2000,200);
}

void Buzzer::low()
{
  tone(_pin,1000,200);
}

// Inputs methods:

Inputs::Inputs(int pin1, int pin2, int pin3)
{
  pinMode(pin1, INPUT);
  _buttonPin = pin1;
  _knobPin1 = pin2;
  _knobPin2 = pin3;
  buttonState = 0;
  fwdTurns = 0;
  revTurns = 0;
  isUpdated = true;
}

void Inputs::check(boolean isTurning, int verPCB)
{
  buttonState = digitalRead(_buttonPin); // read button state
  int knob1;
  int knob2;


  if (!isTurning) { // allow changes only if twister isn't turning

      if (verPCB) {
      // Board ver 1.1:
      knob1 = analogRead(_knobPin1) / 4 * 100 / 255;
      knob2 = analogRead(_knobPin2) / 4 * 100 / 255;
    } 
    else {
      // Board ver 1.0:
      knob1 = (255-(analogRead(_knobPin1) / 4)) * 100 / 255;
      knob2 = (255-(analogRead(_knobPin2) / 4)) * 100 / 255;
    }

    // constrain values to be between 0 and 100
    knob1 = min(knob1,100); 
    knob1 = max(knob1,0);
    knob2 = min(knob2,100); 
    knob2 = max(knob2,0);

    if (knob1 != fwdTurns || knob2 != revTurns) { // check to see if values have been updated
      isUpdated = true;
    }
    fwdTurns = knob1;
    revTurns = knob2;
  }
}


// StateTracker methods:

StateTracker::StateTracker()
{
  isTurning = false;
  isTurningFWD = true;
  isUpdated = false;
  totalTurns = 0;
}


