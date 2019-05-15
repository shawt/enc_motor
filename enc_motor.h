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
    enc_motor(int ratio);
    void enc_tickA();
    void enc_tickB();
    void enc_fwd(double turns, int speed);
    void enc_bak(double turns, int speed);
    void enc_spinRt(double turns, int speed);
    void enc_spinLt(double turns, int speed);
    
private:
    int _ratio;
    int _aIn1;
    int _aIn2;
    int _aPwm;
    int _bIn1;
    int _bIn2;
    int _bPwm;
    volatile int _ticksA;
    volatile float _turnsA;
    volatile int _ticksB;
    volatile int _turnsB;
    
};

#endif /* enc_motor_hpp */
