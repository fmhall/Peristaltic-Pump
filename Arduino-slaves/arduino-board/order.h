#ifndef ORDER_H
#define ORDER_H

// Define the orders that can be sent and received
enum Order
{
    HELLO = 0,
    SERVO = 1,
    MOTOR = 2,
    ALREADY_CONNECTED = 3,
    ERROR = 4,
    RECEIVED = 5,
    STOP = 6,
    MOTOR1 = 11,
    MOTOR2 = 12,
    MOTOR3 = 13,
    MOTOR4 = 14,
    MOTOR5 = 15,
    MOTOR6 = 16

};

typedef enum Order Order;

#endif
