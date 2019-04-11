#include <Arduino.h>
#include <AccelStepper.h>
#include "order.h"
#include "slave.h"
#include "parameters.h"

bool is_connected = false; ///< True if the connection with the master is available
int8_t motor_speed = 0;
int16_t servo_angle = INITIAL_THETA;
unsigned long time;
char val;

void setup()
{
    // Init Serial
    Serial.begin(SERIAL_BAUD);

    // Wait until the arduino is connected to master
    run1(1, 1000, 1);
    while (!is_connected)
    {
        write_order(HELLO);
        wait_for_bytes(1, 1000);
        get_messages_from_serial();
    }
}

// Define 6 steppers and the pins they will use
AccelStepper stepper1(2, 3, 2);
AccelStepper stepper2(2, 5, 4);
AccelStepper stepper3(2, 7, 6);
AccelStepper stepper4(2, 9, 8);
AccelStepper stepper5(2, 11, 10);
AccelStepper stepper6(2, 13, 12);

void loop()
{
    get_messages_from_serial();
    update_motors_orders();
}

void update_motors_orders()
{
    // servomotor.write(constrain(servo_angle, THETA_MIN, THETA_MAX));
    // motor_speed = constrain(motor_speed, -SPEED_MAX, SPEED_MAX);
    // // Send motor speed order
    // if (motor_speed > 0)
    // {
    //     digitalWrite(DIRECTION_PIN, LOW);
    // }
    // else
    // {
    //     digitalWrite(DIRECTION_PIN, HIGH);
    // }
    // analogWrite(MOTOR_PIN, convert_to_pwm(float(motor_speed)));
}

void stop()
{
    // analogWrite(MOTOR_PIN, 0);
    // digitalWrite(DIRECTION_PIN, LOW);
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
                write_order(HELLO);
            }
            else
            {
                // If we are already connected do not send "hello" to avoid infinite loop
                write_order(ALREADY_CONNECTED);
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
            case STOP:
            {
                motor_speed = 0;
                stop();
                if (DEBUG)
                {
                    write_order(STOP);
                }
                break;
            }
            case SERVO:
            {
                servo_angle = read_i16();
                if (DEBUG)
                {
                    write_order(SERVO);
                    write_i16(servo_angle);
                }
                break;
            }
            case MOTOR:
            {
                // between -100 and 100
                motor_speed = read_i8();
                if (DEBUG)
                {
                    write_order(MOTOR);
                    write_i8(motor_speed);
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
        write_order(RECEIVED); // Confirm the reception
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

void run1(int m, int s, float t)
{
    if (m == 1)
    {
        stepper1.setSpeed(s);
        Serial.print("Starting Motor 1 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }
    else if (m == 2)
    {
        stepper2.setSpeed(s);
        Serial.print("Starting Motor 2 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }
    else if (m == 3)
    {
        stepper3.setSpeed(s);
        Serial.print("Starting Motor 3 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }
    else if (m == 4)
    {
        stepper4.setSpeed(s);
        Serial.print("Starting Motor 4 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }
    else if (m == 5)
    {
        stepper5.setSpeed(s);
        Serial.print("Starting Motor 5 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }
    else if (m == 6)
    {
        stepper6.setSpeed(s);
        Serial.print("Starting Motor 6 at speed------> ");
        Serial.println(s);
        Serial.print("For ");
        Serial.print(t);
        Serial.println(" Minutes");
        Serial.println(" ");
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    if (m == 1)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper1.runSpeed();
            }

            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper1.setSpeed(0);
                stepper1.runSpeed();
                done = true;
            }
        }
        done = false;
    }

    else if (m == 2)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper2.runSpeed();
            }
            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper2.setSpeed(0);
                stepper2.runSpeed();
                done = true;
            }
        }
        done = false;
    }

    else if (m == 3)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper3.runSpeed();
            }
            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper3.setSpeed(0);
                stepper3.runSpeed();
                done = true;
            }
        }
        done = false;
    }

    else if (m == 4)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper4.runSpeed();
            }
            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper4.setSpeed(0);
                stepper4.runSpeed();
                done = true;
            }
        }
        done = false;
    }
    else if (m == 5)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper5.runSpeed();
            }
            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper5.setSpeed(0);
                stepper5.runSpeed();
                done = true;
            }
        }
        done = false;
    }
    else if (m == 6)
    {
        while (!done)
        {
            if (millis() - motorStartMillis < motorRunMillis)
            {
                stepper6.runSpeed();
            }
            else
            {
                Serial.println("*****************Turning all motors off*****************");
                Serial.println(" ");
                //Serial.print(m);
                stepper6.setSpeed(0);
                stepper6.runSpeed();
                done = true;
            }
        }
        done = false;
    }
}