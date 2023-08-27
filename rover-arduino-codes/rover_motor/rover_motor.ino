#include <ros.h>
#include <geometry_msgs/Twist.h>

#include "motor.h"

ros::NodeHandle nh;
void node_callback(const geometry_msgs::Twist& twist);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &node_callback);

Motor motor1(6, 7);
Motor motor3(9, 8);
Motor motor2(11, 10);
Motor motor4(12, 13);

char buffer[64]; // log message buffer

void setup() {
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub);
    nh.loginfo("arduino ready...");
}


void loop() {
    nh.spinOnce();

    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
}

void node_callback(const geometry_msgs::Twist& twist) {
    int x = int(twist.linear.x * 255);
    int z = int(twist.angular.z * 255);

    int lv = constrain(x + z/2, -255, 255);
    int rv = constrain(x - z/2, -255, 255);

    motor1.set(lv);
    motor2.set(rv);
    motor3.set(rv);
    motor4.set(lv);

    sprintf(buffer, "x: %d, z: %d, lv: %d, rv: %d", x, z, lv, rv);
    nh.loginfo(buffer);

    sprintf(
        buffer, "m1: %d, m2: %d, m3: %d, m4: %d",
        motor1.rmp.getTarget(),
        motor2.rmp.getTarget(),
        motor3.rmp.getTarget(),
        motor4.rmp.getTarget()
    );

    nh.loginfo(buffer);
}
