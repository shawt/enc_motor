//
//  enc_motor.cpp
//  enc_motor
//
//  Created by Trevor Shaw on 5/14/19.
//  Copyright © 2019 Trevor Shaw. All rights reserved.
//

#include "Arduino.h"
#include "enc_motor.h"

enc_motor::enc_motor(int ratio)
{
    _ratio = ratio;
    _aPwm = 3;
    _aIn1 = 4;
    _aIn2 = 5;
    _bPwm = 6;
    _bIn1 = 7;
    _bIn2 = 8;
   
    
}

void enc_motor::enc_tickA()
{
    int partialTurn = (_ratio * 8)/16; //8 pole magnet on the encoder measures 16ths of turns. Note that with a 1:1 ratio, the most precise we can be is 1/8th of a turn. Consider changing this.
    _ticksA++;
    if (_ticksA % partialTurn == 0)
    {
        _turnsA += .0625;
    }
}

void enc_motor::enc_tickB()
{
    int partialTurn = (_ratio * 8)/16; //8 pole magnet on the encoder measures 16ths of turns
    _ticksB++;
    if (_ticksB % partialTurn == 0)
    {
        _turnsB += .0625;
    }
}

void enc_motor::enc_fwd(double reqTurns, int speed)
{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, LOW);
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, LOW);
    
    while (_turnsA < reqTurns) //this function is for both motors, but we only need one encoder, so use A
    {
        
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    
}
