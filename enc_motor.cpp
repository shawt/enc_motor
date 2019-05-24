//
//  enc_motor.cpp
//  enc_motor
//
//  Created by Trevor Shaw on 5/14/19.
//  Copyright © 2019 Trevor Shaw. All rights reserved.
//

#include "Arduino.h"
#include "enc_motor.h"

enc_motor::enc_motor(int ratio, int encApin, int encBpin)
{
    _ratio = ratio;
    //based on pinout for Sparkfun Wireless motor shield
    _aPwm = 3;
    _aIn1 = 4;
    _aIn2 = 5;
    _bPwm = 6;
    _bIn1 = 7;
    _bIn2 = 8;
    _kp =1;
    _partialTurn = (_ratio * 8) / 16; //8 pole magnet will generate 8 pin-change interrupt calls per encoder rotation. This means that th$
    
    pinMode (encApin, INPUT_PULLUP);
    pinMode (encBpin, INPUT_PULLUP);
    enc_motor::pciSetup(encApin);
    enc_motor::pciSetup(encBpin);
    
    
    pinMode(_aPwm, OUTPUT);
    pinMode(_aIn1, OUTPUT);
    pinMode(_aIn2, OUTPUT);
    pinMode(_bPwm, OUTPUT);
    pinMode(_bIn1, OUTPUT);
    pinMode(_bIn2, OUTPUT);
    
    
    
}

void enc_motor::enc_tickA()
{
    //handle pin change interrupt for D0-7
    _ticksA++;
    _errTicksA++;
    if (_ticksA % _partialTurn == 0)
    {
        _ticksA = 0;
        _turnsA += .0625; //one sixteenth of a turn
    }
}


void enc_motor::enc_tickB()
{
    //handle pin change interrupt for D8-13
    _ticksB++;
    _errTicksB++;
    
    if (_ticksB % _partialTurn == 0)
    {
        _ticksB = 0;
        _turnsB += .0625; //one sixteenth of a turn
        
    }
}


void enc_motor::pciSetup(byte pin)
{
    //enable the given pin as an interrupt
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void enc_motor::enc_fwd(double reqTurns, int speed)

{
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, LOW);
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, LOW);
    
    int speedA = speed;
    int speedB = speed;
    int error = 0;
    _ticksA = 0;
    _ticksB = 0;
    _errTicksA = 0;
    _errTicksB = 0;
    
    
    
    while (_turnsA < reqTurns && _turnsB < reqTurns) //this function is for both motors
    {
        delay(100);
        error = (_ticksA - _ticksB) / _kp;
        speedB += error;
        analogWrite(_bPwm,speedB);
        //_errTicksA = 0;
        //_errTicksB = 0;
        
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    _turnsB = 0.0;
    
}


void enc_motor::enc_bak(double reqTurns, int speed)

{
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, LOW);
    digitalWrite(_bIn2, HIGH);
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, LOW);
    digitalWrite(_aIn2, HIGH);

    int speedA = speed;
    int speedB = speed;
    int error = 0;
    _ticksA = 0;
    _ticksB = 0;
    
    
    while (_turnsA < reqTurns && _turnsB < reqTurns) //this function is for both motors
    {
        delay(100);
        error = (_ticksA - _ticksB) / _kp;
        speedB += error;
        analogWrite(_bPwm,speedB);
        //_errTicksA = 0;
        //_errTicksB = 0;
        
        
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    _turnsB = 0.0;
    
    
}

void enc_motor::enc_spinRt(double reqTurns, int speed)
{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, LOW);
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, LOW);
    digitalWrite(_bIn2, HIGH);
    int speedA = speed;
    int speedB = speed;
    int error = 0;
    _ticksA = 0;
    _ticksB = 0;
    
 
    while (_turnsA < reqTurns && _turnsB < reqTurns) //this function is for both motors
    {
        
        error = (_ticksA - _ticksB) / _kp;
        speedB += error;
        analogWrite(6,speedB);
        delay(100);
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    _turnsB = 0.0;
}
void enc_motor::enc_spinLt(double reqTurns, int speed)
{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, LOW);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, LOW);
    int speedA = speed;
    int speedB = speed;
    int error = 0;
    _ticksA = 0;
    _ticksB = 0;
    

    while (_turnsA < reqTurns && _turnsB < reqTurns) //this function is for both motors
    {
        
        error = (_ticksA - _ticksB) / _kp;
        speedB += error;
        analogWrite(6,speedB);
        delay(100);
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    _turnsB = 0.0;
}

void enc_motor::enc_stop()
{
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsA = 0.0;
    _turnsB = 0.0;
}

void enc_motor::enc_fwdA(double reqTurns, int speed)

{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, LOW);
    
    
    
    while (_turnsA < reqTurns)
    {
        
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    _turnsA = 0.0;
    
}

void enc_motor::enc_bakA(double reqTurns, int speed)

{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, LOW);
    digitalWrite(_aIn2, HIGH);
   
 
  
    while (_turnsA < reqTurns)
    {
       
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    _turnsA = 0.0;
    
}

void enc_motor::enc_spinRtA(double reqTurns, int speed)
{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, LOW);
    
    while (_turnsA < reqTurns )
    {
        
     
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    _turnsA = 0.0;
}
void enc_motor::enc_spinLtA(double reqTurns, int speed)
{
    analogWrite(_aPwm, speed);
    digitalWrite(_aIn1, LOW);
    digitalWrite(_aIn2, HIGH);
    
   
    while (_turnsA < reqTurns )
    {
      
    }
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    
    _turnsA = 0.0;
  
}

void enc_motor::enc_stopA()
{
    analogWrite(_aPwm, 0);
    digitalWrite(_aIn1, HIGH);
    digitalWrite(_aIn2, HIGH);
    _turnsA = 0.0;

}

void enc_motor::enc_fwdB(double reqTurns, int speed)

{
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, LOW);

    
   
    while ( _turnsB < reqTurns)
    {
        
       
    }
    
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsB = 0.0;
    
}

void enc_motor::enc_bakB(double reqTurns, int speed)

{
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, LOW);
    digitalWrite(_bIn2, HIGH);

    
   
    while (_turnsB < reqTurns) //this function is for both motors
    {
      
    }

    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);

    _turnsB = 0.0;
    
}

void enc_motor::enc_spinRtB(double reqTurns, int speed)
{

    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, LOW);
    digitalWrite(_bIn2, HIGH);

    while (_turnsB < reqTurns)
    {
       
    }
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsB = 0.0;
}
void enc_motor::enc_spinLtB(double reqTurns, int speed)
{
    
    analogWrite(_bPwm, speed);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, LOW);

    while (_turnsB < reqTurns)
    {
        
        
    }
    
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsB = 0.0;
}

void enc_motor::enc_stopB()
{
    analogWrite(_bPwm, 0);
    digitalWrite(_bIn1, HIGH);
    digitalWrite(_bIn2, HIGH);
    _turnsB = 0.0;
}
