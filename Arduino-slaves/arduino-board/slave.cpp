#include <Arduino.h>
#include <AccelStepper.h>
#include "order.h"
#include "slave.h"
#include "parameters.h"

bool is_connected = false; ///< True if the connection with the master is available
int8_t motor_speed = 0;
int8_t motor_number = 0;
int16_t servo_angle = INITIAL_THETA;
unsigned long time;
char val;
bool update = false;
// Define 6 steppers and the pins they will use
AccelStepper stepper1(2, 3, 2);
AccelStepper stepper2(2, 5, 4);
AccelStepper stepper3(2, 7, 6);
AccelStepper stepper4(2, 9, 8);
AccelStepper stepper5(2, 11, 10);
AccelStepper stepper6(2, 13, 12);
int16_t motor1Speed = 700;
int16_t motor2Speed = 700;
int16_t motor3Speed = 700;
int16_t motor4Speed = 700;
int16_t motor5Speed = 700;
int16_t motor6Speed = 700;
void setup()
{
    // Init Serial
    Serial.begin(SERIAL_BAUD);
    // Wait until the arduino is connected to master
    while (!is_connected)
    {
        write_order(HELLO);
        wait_for_bytes(1, 1000);
        get_messages_from_serial();
        write_order(ALREADY_CONNECTED);
    }
    stepper1.setMaxSpeed(1000);
    stepper1.setSpeed(motor1Speed);

    stepper2.setMaxSpeed(1000);
    stepper2.setSpeed(motor2Speed);

    stepper3.setMaxSpeed(1000);
    stepper3.setSpeed(motor3Speed);

    stepper4.setMaxSpeed(1000);
    stepper4.setSpeed(motor4Speed);

    stepper5.setMaxSpeed(1000);
    stepper5.setSpeed(motor5Speed);

    stepper6.setMaxSpeed(1000);
    stepper6.setSpeed(motor6Speed);
}

String inputString = "";
char user_input;
String readString = "", substring;
boolean stringComplete = true;
boolean done = false;
unsigned long motorStartMillis;
unsigned long motorRunMillis;
int motor_combo;
int motor_in = 0;

void loop()
{
    get_messages_from_serial();
    step_motors();
}

void step_motors()
{
    stepper1.runSpeed();
    stepper2.runSpeed();
    stepper3.runSpeed();
    stepper4.runSpeed();
    stepper5.runSpeed();
    stepper6.runSpeed();
    // if (stepper1.isRunning())
    // {
    //     stepper1.runSpeed();
    // }
    // if (stepper2.isRunning())
    // {
    //     stepper2.runSpeed();
    // }
    // if (stepper3.isRunning())
    // {
    //     stepper3.runSpeed();
    // }
    // if (stepper4.isRunning())
    // {
    //     stepper4.runSpeed();
    // }
    // if (stepper5.isRunning())
    // {
    //     stepper5.runSpeed();
    // }
    // if (stepper6.isRunning())
    // {
    //     stepper6.runSpeed();
    // }
}

void update_motors_orders(int8_t m_number, int speed)
{
    speed = constrain(speed, 0, 1000);
    switch (m_number)
    {
    case 0:
        // Do nothing
        break;
    case 1:
        motor1Speed = speed;
        stepper1.setSpeed(motor1Speed);
        stepper1.runSpeed();
        write_order(MOTOR1);
        break;
    case 2:
        motor2Speed = speed;
        stepper1.setSpeed(motor2Speed);
        write_order(MOTOR2);
        break;
    case 3:
        motor3Speed = speed;
        stepper1.setSpeed(motor3Speed);
        write_order(MOTOR3);
        break;
    case 4:
        motor4Speed = speed;
        stepper1.setSpeed(motor4Speed);
        write_order(MOTOR4);
        break;
    case 5:
        motor5Speed = speed;
        stepper1.setSpeed(motor5Speed);
        write_order(MOTOR5);
        break;
    case 6:
        motor6Speed = speed;
        stepper1.setSpeed(motor6Speed);
        write_order(MOTOR6);
        break;
    default:
        write_order(ERROR);
    }
}

void stop()
{
    int16_t motor1Speed = 0;
    int16_t motor2Speed = 0;
    int16_t motor3Speed = 0;
    int16_t motor4Speed = 0;
    int16_t motor5Speed = 0;
    int16_t motor6Speed = 0;
    stepper1.setSpeed(motor1Speed);
    stepper2.setSpeed(motor2Speed);
    stepper3.setSpeed(motor3Speed);
    stepper4.setSpeed(motor4Speed);
    stepper5.setSpeed(motor5Speed);
    stepper6.setSpeed(motor6Speed);
}
void start()
{
    stepper1.setSpeed(900);
    stepper2.setSpeed(900);
    stepper3.setSpeed(900);
    stepper4.setSpeed(900);
    stepper5.setSpeed(900);
    stepper6.setSpeed(900);
}

void getSpeeds()
{
    write_i16((int16_t)stepper1.speed());
    write_i16((int16_t)stepper2.speed());
    write_i16((int16_t)stepper3.speed());
    write_i16((int16_t)stepper4.speed());
    write_i16((int16_t)stepper5.speed());
    write_i16((int16_t)stepper6.speed());
}

void getSpeeds2()
{
    write_i16(motor1Speed);
    write_i16(motor2Speed);
    write_i16(motor3Speed);
    write_i16(motor4Speed);
    write_i16(motor5Speed);
    write_i16(motor6Speed);
}

int convert_to_pwm(float motor_speed)
{
    // TODO: compensate the non-linear dependency speed = f(PWM_Value)
    return (int)round(abs(motor_speed) * (255. / 100.));
}

void get_messages_from_serial()
{
    if (Serial.available() > 0)
    {
        // The first byte received is the instruction
        Order order_received = read_order();

        if (order_received == HELLO)
        {
            // If the cards haven't say hello, check the connection
            if (!is_connected)
            {
                is_connected = true;
                write_order(RECEIVED);
                //write_order(STOP);
            }
            else
            {
                // If we are already connected do not send "hello" to avoid infinite loop
                write_order(ERROR);
            }
        }
        else if (order_received == ALREADY_CONNECTED)
        {
            is_connected = true;
        }
        else
        {
            switch (order_received)
            {
            case ALLSTOP:
            {
                motor_speed = 0;
                stop();
                if (DEBUG)
                {
                    write_order(STOP);
                }
                break;
            }
            case ALLSTART:
            {
                start();
                break;
            }
            case SPEEDS:
            {
                getSpeeds2();
                if (DEBUG)
                {
                    write_order(SPEEDS);
                }
                break;
            }
            case MOTOR:
            {
                // between -100 and 100
                motor_number = read_i8();
                motor_speed = read_i8();
                // write_i8(motor_speed);
                motor_in = motor_speed * 10;
                update_motors_orders(motor_number, motor_in);
                if (DEBUG)
                {
                    write_order(MOTOR);
                    write_i8(motor_number);
                    write_i8(motor_speed / 10);
                }
                break;
            }
            // Unknown order
            default:
                write_order(ERROR);
                write_i16(404);
                return;
            }
        }
        //write_order(RECEIVED); // Confirm the reception
    }
}

Order read_order()
{
    return (Order)Serial.read();
}

void wait_for_bytes(int num_bytes, unsigned long timeout)
{
    unsigned long startTime = millis();
    //Wait for incoming bytes or exit if timeout
    while ((Serial.available() < num_bytes) && (millis() - startTime < timeout))
    {
    }
}

// NOTE : Serial.readBytes is SLOW
// this one is much faster, but has no timeout
void read_signed_bytes(int8_t *buffer, size_t n)
{
    size_t i = 0;
    int c;
    while (i < n)
    {
        c = Serial.read();
        if (c < 0)
            break;
        *buffer++ = (int8_t)c; // buffer[i] = (int8_t)c;
        i++;
    }
}

int8_t read_i8()
{
    wait_for_bytes(1, 100); // Wait for 1 byte with a timeout of 100 ms
    return (int8_t)Serial.read();
}

int16_t read_i16()
{
    int8_t buffer[2];
    wait_for_bytes(2, 100); // Wait for 2 bytes with a timeout of 100 ms
    read_signed_bytes(buffer, 2);
    return (((int16_t)buffer[0]) & 0xff) | (((int16_t)buffer[1]) << 8 & 0xff00);
}

int32_t read_i32()
{
    int8_t buffer[4];
    wait_for_bytes(4, 200); // Wait for 4 bytes with a timeout of 200 ms
    read_signed_bytes(buffer, 4);
    return (((int32_t)buffer[0]) & 0xff) | (((int32_t)buffer[1]) << 8 & 0xff00) | (((int32_t)buffer[2]) << 16 & 0xff0000) | (((int32_t)buffer[3]) << 24 & 0xff000000);
}

void write_order(enum Order myOrder)
{
    uint8_t *Order = (uint8_t *)&myOrder;
    Serial.write(Order, sizeof(uint8_t));
}

void write_i8(int8_t num)
{
    Serial.write(num);
}

void write_i16(int16_t num)
{
    int8_t buffer[2] = {(int8_t)(num & 0xff), (int8_t)(num >> 8)};
    Serial.write((uint8_t *)&buffer, 2 * sizeof(int8_t));
}

void write_i32(int32_t num)
{
    int8_t buffer[4] = {(int8_t)(num & 0xff), (int8_t)(num >> 8 & 0xff), (int8_t)(num >> 16 & 0xff), (int8_t)(num >> 24 & 0xff)};
    Serial.write((uint8_t *)&buffer, 4 * sizeof(int8_t));
}
