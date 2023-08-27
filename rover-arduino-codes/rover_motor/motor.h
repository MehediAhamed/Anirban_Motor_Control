#ifndef _motor_h
#define _motor_h

#include <Arduino.h>
#include <Ramp.h>

struct Motor {
    byte fwd, bkd;
    rampInt rmp;

    Motor(int f, int b) {
        fwd = f;
        bkd = b;
        rmp.go(0, 0, LINEAR, ONCEFORWARD);

        pinMode(fwd, OUTPUT);
        pinMode(bkd, OUTPUT);
    }

    void set(int pwm) {
        rmp.go(pwm, 100, LINEAR, ONCEFORWARD);
    }

    void run() {
        int p = rmp.update();

        if (p >= 0) {
            analogWrite(fwd, p);
            analogWrite(bkd, 0);
        } else {
            analogWrite(fwd, 0);
            analogWrite(bkd, p);
        }
    }
};

#endif

