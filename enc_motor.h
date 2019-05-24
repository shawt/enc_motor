//
//  enc_motor.h
//  enc_motor
//
//  Created by Trevor Shaw on 5/14/19.
//  Copyright © 2019 Trevor Shaw. All rights reserved.
//

#ifndef enc_motor_h
#define enc_motor_h

#include "Arduino.h"

class enc_motor
{
public:
    enc_motor(int ratio, int encApin, int encBpin);
    void pciSetup(byte pin);
    void enc_tickA();
    void enc_tickB();
    
    void enc_fwd(double turns, int speed);
    void enc_bak(double turns, int speed);
    void enc_spinRt(double turns, int speed);
    void enc_spinLt(double turns, int speed);
    void enc_stop();
    
    void enc_fwdA(double turns, int speed);
    void enc_bakA(double turns, int speed);
    void enc_spinRtA(double turns, int speed);
    void enc_spinLtA(double turns, int speed);
    void enc_stopA();
    
    void enc_fwdB(double turns, int speed);
    void enc_bakB(double turns, int speed);
    void enc_spinRtB(double turns, int speed);
    void enc_spinLtB(double turns, int speed);
    void enc_stopB();

    
private:
    int _ratio;
    int _aIn1;
    int _aIn2;
    int _aPwm;
    int _bIn1;
    int _bIn2;
    int _bPwm;
    int _partialTurn;
    int _kp; //constant divider for errors
    volatile long _ticksA;
    volatile float _turnsA;
    volatile long _ticksB;
    volatile float _turnsB;
    
};

#endif /* enc_motor_hpp */
