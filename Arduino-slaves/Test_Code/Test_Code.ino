#include <AccelStepper.h>

//    __
//  /\  _`\         /\_ \  /\_ \                        /\ \              /\ \       
//  \ \ \_\ \     __\//\ \ \//\ \       __       ___    \ \ \         __  \ \ \____
//   \ \  _ <'  /'__`\\ \ \  \ \ \    /'__`\   /' _ `\   \ \ \  __  /'__`\ \ \ '__`\ 
//    \ \ \_\ \/\  __/ \_\ \_ \_\ \_ /\ \_\.\_ /\ \/\ \   \ \ \_\ \/\ \_\.\_\ \ \_\ \
//     \ \____/\ \____\/\____\/\____\\ \__/.\_\\ \_\ \_\   \ \____/\ \__/.\_\\ \_,__/
//      \/___/  \/____/\/____/\/____/ \/__/\/_/ \/_/\/_/    \/___/  \/__/\/_/ \/___/
//

//*------------------------------------------------------------------------------*//
// Code written by Brian O'Grady and Peter Vallimarescu
//*------------------------------------------------------------------------------*//

/*Ignore this part....
 */
unsigned long time;
char val;
//unsigned long elapsedTime;

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    while (!Serial)
        ;
    Serial.flush();
    delay(200);
    Serial.println("Running in Pi mode (1) or debug mode? (2)");
    delay(200);
    Serial.println("Press 1 or 2 and hit enter!");
    while (Serial.available() == 0)
        ;
    val = Serial.read() - '0';
}
void loop()
{
    if (val == 2)
    {
        delay(200);
        Serial.println("How many motors would you like to test?");
        delay(200);
        Serial.println("Press 1-6 and hit enter!");
        delay(200);
        while (Serial.available() == 0)
            ;
        char num = Serial.read() - '0';

        if (num == 1)
        {
            //Serial.println(val);
            delay(200);
            Serial.println(" ");
            delay(200);
            Serial.println("Spinning one motor! ");
            delay(200);
            Serial.println(" ");
            delay(200);
            Serial.println("Ready...");
            delay(200);
            Serial.println(" ");
            delay(200);
            Serial.println("Set...");
            delay(200);
            Serial.println(" ");
            delay(100);
            Serial.println("Perfuse!");
            delay(200);
            Serial.println(" ");
            delay(100);
        }
        else if (num != 1)
        {
            Serial.println(" ");
            Serial.println("Then why did you start me!?!");
            Serial.println(" ");
            Serial.println("Fine");
            Serial.println(" ");
            Serial.println("Are you ready to run some motors NOW?");
            Serial.println(" ");
            while (Serial.available() == 0)
                ;
            return;
        }

        /*....... And start here!
    *
    * This is where you will write your sequence of motors, speed and time
    * This is the section without loops, so it will only run for the time
    * you put in and then stop.
    */

        //   run1(1, 1000, 1);
        //  run2(1, 1000, 5, 100, 20);
        //  run3(1, 1000, 5, 100, 6, 100, 80);
        //  run4(1, 1000, 4, 100, 5, 100, 6, 100, 40);
        //  run5(1, 1000, 2, 100, 3, 100, 4, 100, 6, 100, 10);
        run6(1, 1000, 2, 1000, 3, 1000, 4, 1000, 5, 1000, 6, 1000, 1);

        /*This is the section to run loops
    -----This is the number of loops/cycles to run-------
                                    |
                                    |
                                    V                */
        for (int loops = 1; loops <= 200; loops++)
        {
            Serial.println(">>>>>>>>>>CYCLE NUMBER<<<<<<<<<< ");
            Serial.print("              ");
            Serial.print("[");
            Serial.print(loops);
            Serial.print("]");
            Serial.println(" ");
            Serial.println(" ");

            Serial.print("Elapsed Time: ");
            time = millis() / 60000;
            Serial.print(time);
            Serial.print(" minutes");
            Serial.println(" ");
            Serial.println(" ");

            //  run1(1, 2000, 1);
            //  run2(1, 100, 5, 100, 20);
            //  run3(1, 100, 5, 100, 6, 100, 80);
            //  run4(1, 100, 4, 100, 5, 100, 6, 100, 40);
            //  run5(1, 100, 2, 100, 3, 100, 4, 100, 6, 100, 10);
            // run6(1, 100, 2, 100, 3, 100, 4, 100, 5, 100, 6, 100, 1);

            stop;
        }
    }
    else if (val == 1)
    {
        // Raspberry Pi mode
        // testing code - sending bytes
        for (byte n = 0; n < 255; n++)
        {
            Serial.write(n);
            delay(50);
        }
    }
}

// Define 6 steppers and the pins they will use
AccelStepper stepper1(2, 3, 2);
AccelStepper stepper2(2, 5, 4);
AccelStepper stepper3(2, 7, 6);
AccelStepper stepper4(2, 9, 8);
AccelStepper stepper5(2, 11, 10);
AccelStepper stepper6(2, 13, 12);

// Define array of stepper motors, indexed at their motor number - 1
// AccelStepper_t motors = [ stepper1, stepper2, stepper3, stepper4, stepper5, stepper6 ];

// the above might not work

String inputString = "";
char user_input;
String readString = "", substring;
boolean stringComplete = true;
boolean done = false;
unsigned long motorStartMillis;
unsigned long motorRunMillis;
int motor_combo;

// void genericStepper(AccelStepper_t motors, int motor, int speed, float time)
// {
//     if (motor > 6 || motor < 1)
//     {
//         Serial.println("Error: motor number not valid");
//         break
//     }
//     else
//     {
//         stepper = motors[motor - 1] stepper.setSpeed(speed);
//         Serial.print("Starting Motor 1 at speed------> ");
//         Serial.println(speed);
//         Serial.print("For ");
//         Serial.print(time);
//         Serial.println(" Minutes");
//         Serial.println(" ");
//         motorRunMillis = t * 60 * 1000;
//         motorStartMillis = millis();

//         while (!done)
//         {
//             if (millis() - motorStartMillis < motorRunMillis)
//             {
//                 stepper.runSpeed();
//             }

//             else
//             {
//                 Serial.println("*****************Turning motor off*****************");
//                 Serial.println(" ");
//                 //Serial.print(m);
//                 stepper.setSpeed(0);
//                 stepper.runSpeed();
//                 done = true;
//             }
//         }
//         done = false;
//     }
// }
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

void run2(int m1, int s1, int m2, int s2, float t)
{
    if (m1 == 1)
    {
        stepper1.setSpeed(s1);
    }
    else if (m1 == 2)
    {
        stepper2.setSpeed(s1);
    }
    else if (m1 == 3)
    {
        stepper3.setSpeed(s1);
    }
    else if (m1 == 4)
    {
        stepper4.setSpeed(s1);
    }
    else if (m1 == 5)
    {
        stepper5.setSpeed(s1);
    }

    if (m2 == 2)
    {
        stepper2.setSpeed(s2);
    }
    else if (m2 == 3)
    {
        stepper3.setSpeed(s2);
    }
    else if (m2 == 4)
    {
        stepper4.setSpeed(s2);
    }
    else if (m2 == 5)
    {
        stepper5.setSpeed(s2);
    }
    else if (m2 == 6)
    {
        stepper6.setSpeed(s2);
    }

    if (m1 == 1)
    {
        if (m2 == 2)
        {
            motor_combo = 1;

            Serial.print("Starting Motor 1 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 2 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 3)
        {
            motor_combo = 2;

            Serial.print("Starting Motor 1 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 3 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 4)
        {
            motor_combo = 3;

            Serial.print("Starting Motor 1 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 4 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }

        if (m2 == 5)
        {
            motor_combo = 4;
            Serial.print("Starting Motor 1 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 5 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }

        if (m2 == 6)
        {
            motor_combo = 5;
            Serial.print("Starting Motor 1 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 6 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
    }

    if (m1 == 2)
    {
        if (m2 == 3)
        {
            motor_combo = 6;
            Serial.print("Starting Motor 2 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 3 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 4)
        {
            motor_combo = 7;
            Serial.print("Starting Motor 2 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 4 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 5)
        {
            motor_combo = 8;
            Serial.print("Starting Motor 2 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 5 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 6)
        {
            motor_combo = 9;
            Serial.print("Starting Motor 2 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 6 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
    }

    if (m1 == 3)
    {
        if (m2 == 4)
        {
            motor_combo = 10;
            Serial.print("Starting Motor 3 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 4 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 5)
        {
            motor_combo = 11;
            Serial.print("Starting Motor 3 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 5 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
        if (m2 == 6)
        {
            motor_combo = 12;
            Serial.print("Starting Motor 3 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 6 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
    }

    if (m1 == 4)
    {
        if (m2 == 5)
        {
            motor_combo = 13;
            Serial.print("Starting Motor 4 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 5 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }

        if (m2 == 6)
        {
            motor_combo = 14;
            Serial.print("Starting Motor 4 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 6 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
    }
    if (m1 == 5)
    {
        if (m2 == 6)
        {
            motor_combo = 15;
            Serial.print("Starting Motor 5 at speed------> ");
            Serial.println(s1);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");

            Serial.print("Starting Motor 6 at speed------> ");
            Serial.println(s2);
            Serial.print("For ");
            Serial.print(t);
            Serial.println(" Minutes");
            Serial.println(" ");
        }
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    while (!done)
    {
        if (millis() - motorStartMillis < motorRunMillis)
        {
            switch (motor_combo)
            {
            case 1:
                stepper1.runSpeed();
                stepper2.runSpeed();
                break;
            case 2:
                stepper1.runSpeed();
                stepper3.runSpeed();
                break;
            case 3:
                stepper1.runSpeed();
                stepper4.runSpeed();
                break;
            case 4:
                stepper1.runSpeed();
                stepper5.runSpeed();
                break;
            case 5:
                stepper1.runSpeed();
                stepper6.runSpeed();
                break;

            case 6:
                stepper2.runSpeed();
                stepper3.runSpeed();
                break;
            case 7:
                stepper2.runSpeed();
                stepper4.runSpeed();
                break;
            case 8:
                stepper2.runSpeed();
                stepper5.runSpeed();
                break;
            case 9:
                stepper2.runSpeed();
                stepper6.runSpeed();
                break;

            case 10:
                stepper3.runSpeed();
                stepper4.runSpeed();
                break;
            case 11:
                stepper3.runSpeed();
                stepper5.runSpeed();
                break;
            case 12:
                stepper3.runSpeed();
                stepper6.runSpeed();
                break;

            case 13:
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 14:
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 15:
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            default:
                stop();
                break;
            }
        }
        else
        {
            Serial.println("*****************Turning all motors off*****************");
            Serial.println(" ");
            stop();
            done = true;
        }
    }
    done = false;
}

void run3(int m1, int s1, int m2, int s2, int m3, int s3, float t)
{
    if (m1 == 1)
    {
        stepper1.setSpeed(s1);
    }
    else if (m1 == 2)
    {
        stepper2.setSpeed(s1);
    }
    else if (m1 == 3)
    {
        stepper3.setSpeed(s1);
    }
    else if (m1 == 4)
    {
        stepper4.setSpeed(s1);
    }
    else if (m1 == 5)
    {
        stepper5.setSpeed(s1);
    }
    else if (m1 == 6)
    {
        stepper6.setSpeed(s1);
    }

    if (m2 == 2)
    {
        stepper2.setSpeed(s2);
    }
    else if (m2 == 3)
    {
        stepper3.setSpeed(s2);
    }
    else if (m2 == 4)
    {
        stepper4.setSpeed(s2);
    }
    else if (m2 == 5)
    {
        stepper5.setSpeed(s2);
    }
    else if (m2 == 6)
    {
        stepper6.setSpeed(s2);
    }

    if (m3 == 3)
    {
        stepper3.setSpeed(s3);
    }
    else if (m3 == 4)
    {
        stepper4.setSpeed(s3);
    }
    else if (m3 == 5)
    {
        stepper5.setSpeed(s3);
    }
    else if (m3 == 6)
    {
        stepper6.setSpeed(s3);
    }

    if (m1 == 1)
    {
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                motor_combo = 1;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 2)
        {
            if (m3 == 4)
            {
                motor_combo = 2;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 2)
        {
            if (m3 == 5)
            {
                motor_combo = 3;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 2)
        {
            if (m3 == 6)
            {
                motor_combo = 4;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }

        if (m2 == 3)
        {
            if (m3 == 4)
            {
                motor_combo = 5;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 3)
        {
            if (m3 == 5)
            {
                motor_combo = 6;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 3)
        {
            if (m3 == 6)
            {
                motor_combo = 7;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }

        if (m2 == 4)
        {
            if (m3 == 5)
            {
                motor_combo = 8;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 4)
        {
            if (m3 == 6)
            {
                motor_combo = 9;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }

        if (m2 == 5)
        {
            if (m3 == 6)
            {
                motor_combo = 10;

                Serial.print("Starting Motor 1 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
    }

    if (m1 == 2)
    {
        if (m2 == 3)
        {
            if (m3 == 4)
            {
                motor_combo = 11;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 3)
        {
            if (m3 == 5)
            {
                motor_combo = 12;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 3)
        {
            if (m3 == 6)
            {
                motor_combo = 13;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 4)
        {
            if (m3 == 5)
            {
                motor_combo = 14;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 4)
        {
            if (m3 == 6)
            {
                motor_combo = 15;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 5)
        {
            if (m3 == 6)
            {
                motor_combo = 16;

                Serial.print("Starting Motor 2 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
    }

    if (m1 == 3)
    {
        if (m2 == 4)
        {
            if (m3 == 5)
            {
                motor_combo = 17;

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 4)
        {
            if (m3 == 6)
            {
                motor_combo = 18;

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
        if (m2 == 5)
        {
            if (m3 == 6)
            {
                motor_combo = 19;

                Serial.print("Starting Motor 3 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
    }

    if (m1 == 4)
    {
        if (m2 == 5)
        {
            if (m3 == 6)
            {
                motor_combo = 20;

                Serial.print("Starting Motor 4 at speed------> ");
                Serial.println(s1);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 5 at speed------> ");
                Serial.println(s2);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");

                Serial.print("Starting Motor 6 at speed------> ");
                Serial.println(s3);
                Serial.print("For ");
                Serial.print(t);
                Serial.println(" Minutes");
                Serial.println(" ");
            }
        }
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    while (!done)
    {
        if (millis() - motorStartMillis < motorRunMillis)
        {
            switch (motor_combo)
            {
            case 1:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                break;
            case 2:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper4.runSpeed();
                break;
            case 3:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper5.runSpeed();
                break;
            case 4:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper6.runSpeed();
                break;
            case 5:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                break;
            case 6:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                break;
            case 7:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper6.runSpeed();
                break;
            case 8:
                stepper1.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 9:
                stepper1.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 10:
                stepper1.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 11:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                break;
            case 12:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                break;
            case 13:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper6.runSpeed();
                break;
            case 14:
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 15:
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 16:
                stepper2.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 17:
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 18:
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 19:
                stepper3.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 20:
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            default:
                stop();
                break;
            }
        }
        else
        {
            Serial.println("*****************Turning all motors off*****************");
            Serial.println(" ");
            stop();
            done = true;
        }
    }
    done = false;
}
void run4(int m1, int s1, int m2, int s2, int m3, int s3, int m4, int s4, float t)
{
    if (m1 == 1)
    {
        stepper1.setSpeed(s1);
    }
    else if (m1 == 2)
    {
        stepper2.setSpeed(s1);
    }
    else if (m1 == 3)
    {
        stepper3.setSpeed(s1);
    }
    else if (m1 == 4)
    {
        stepper4.setSpeed(s1);
    }
    else if (m1 == 5)
    {
        stepper5.setSpeed(s1);
    }
    else if (m1 == 6)
    {
        stepper6.setSpeed(s1);
    }
    if (m2 == 2)
    {
        stepper2.setSpeed(s2);
    }
    else if (m2 == 3)
    {
        stepper3.setSpeed(s2);
    }
    else if (m2 == 4)
    {
        stepper4.setSpeed(s2);
    }
    else if (m2 == 5)
    {
        stepper5.setSpeed(s2);
    }
    else if (m2 == 6)
    {
        stepper6.setSpeed(s2);
    }

    if (m3 == 3)
    {
        stepper3.setSpeed(s3);
    }
    else if (m3 == 4)
    {
        stepper4.setSpeed(s3);
    }
    else if (m3 == 5)
    {
        stepper5.setSpeed(s3);
    }
    else if (m3 == 6)
    {
        stepper6.setSpeed(s3);
    }

    if (m4 == 4)
    {
        stepper4.setSpeed(s4);
    }
    else if (m4 == 5)
    {
        stepper5.setSpeed(s4);
    }
    else if (m4 == 6)
    {
        stepper6.setSpeed(s4);
    }

    if (m1 == 1)
    {
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 4)
                {

                    motor_combo = 1;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 5)
                {

                    motor_combo = 2;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 6)
                {

                    motor_combo = 3;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {

                    motor_combo = 4;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 4)
            {
                if (m4 == 6)
                {

                    motor_combo = 5;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 6;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }

        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {

                    motor_combo = 7;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 6)
                {

                    motor_combo = 8;

                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 3)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 9;

                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }

        if (m2 == 4)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 10;
                    Serial.print("Starting Motor 1 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
    }

    if (m1 == 2)
    {
        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {

                    motor_combo = 11;
                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 6)
                {

                    motor_combo = 12;
                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 3)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 13;

                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
        if (m2 == 4)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 14;
                    Serial.print("Starting Motor 2 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
    }
    if (m1 == 3)
    {
        if (m2 == 4)
        {
            if (m3 == 5)
            {
                if (m4 == 6)
                {

                    motor_combo = 15;

                    Serial.print("Starting Motor 3 at speed------> ");
                    Serial.println(s1);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 4 at speed------> ");
                    Serial.println(s2);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 5 at speed------> ");
                    Serial.println(s3);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");

                    Serial.print("Starting Motor 6 at speed------> ");
                    Serial.println(s4);
                    Serial.print("For ");
                    Serial.print(t);
                    Serial.println(" Minutes");
                    Serial.println(" ");
                }
            }
        }
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    while (!done)
    {
        if (millis() - motorStartMillis < motorRunMillis)
        {
            switch (motor_combo)
            {
            case 1:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                break;
            case 2:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                break;
            case 3:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper6.runSpeed();
                break;
            case 4:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 5:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 6:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 7:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 8:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 9:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 10:
                stepper1.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 11:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 12:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 13:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 14:
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 15:
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            default:
                stop();
                break;
            }
        }
        else
        {
            Serial.println("*****************Turning all motors off*****************");
            Serial.println(" ");
            stop();
            done = true;
        }
    }
    done = false;
}

void run5(int m1, int s1, int m2, int s2, int m3, int s3, int m4, int s4, int m5, int s5, float t)
{
    if (m1 == 1)
    {
        stepper1.setSpeed(s1);
    }
    else if (m1 == 2)
    {
        stepper2.setSpeed(s1);
    }
    if (m2 == 2)
    {
        stepper2.setSpeed(s2);
    }
    else if (m2 == 3)
    {
        stepper3.setSpeed(s2);
    }

    if (m3 == 3)
    {
        stepper3.setSpeed(s3);
    }
    else if (m3 == 4)
    {
        stepper4.setSpeed(s3);
    }

    if (m4 == 4)
    {
        stepper4.setSpeed(s4);
    }
    else if (m4 == 5)
    {
        stepper5.setSpeed(s4);
    }
    if (m5 == 5)
    {
        stepper5.setSpeed(s5);
    }
    else if (m5 == 6)
    {
        stepper6.setSpeed(s5);
    }

    if (m1 == 1)
    {
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 4)
                {
                    if (m5 == 5)
                    {

                        motor_combo = 1;
                        Serial.print("Starting Motor 1 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 2 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 3 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 4 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 5 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 4)
                {
                    if (m5 == 6)
                    {

                        motor_combo = 2;
                        Serial.print("Starting Motor 1 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 2 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 3 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 4 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 6 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 5)
                {
                    if (m5 == 6)
                    {

                        motor_combo = 3;
                        Serial.print("Starting Motor 1 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 2 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 3 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 5 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 6 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }
        if (m2 == 2)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {
                    if (m5 == 6)
                    {

                        motor_combo = 4;
                        Serial.print("Starting Motor 1 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 2 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 4 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 5 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 6 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }

        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {
                    if (m5 == 6)
                    {

                        motor_combo = 5;
                        Serial.print("Starting Motor 1 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 3 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 4 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 5 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 6 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }
    }
    if (m1 == 2)
    {
        if (m2 == 3)
        {
            if (m3 == 4)
            {
                if (m4 == 5)
                {
                    if (m5 == 6)
                    {

                        motor_combo = 6;

                        Serial.print("Starting Motor 2 at speed------> ");
                        Serial.println(s1);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 3 at speed------> ");
                        Serial.println(s2);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 4 at speed------> ");
                        Serial.println(s3);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 5 at speed------> ");
                        Serial.println(s4);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");

                        Serial.print("Starting Motor 6 at speed------> ");
                        Serial.println(s5);
                        Serial.print("For ");
                        Serial.print(t);
                        Serial.println(" Minutes");
                        Serial.println(" ");
                    }
                }
            }
        }
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    while (!done)
    {
        if (millis() - motorStartMillis < motorRunMillis)
        {
            switch (motor_combo)
            {
            case 1:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                break;
            case 2:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper6.runSpeed();
                break;
            case 3:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 4:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 5:
                stepper1.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            case 6:
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            default:
                stop();
                break;
            }
        }
        else
        {
            Serial.println("*****************Turning all motors off*****************");
            Serial.println(" ");
            stop();
            done = true;
        }
    }
    done = false;
}

void run6(int m1, int s1, int m2, int s2, int m3, int s3, int m4, int s4, int m5, int s5, int m6, int s6, float t)
{
    if (m1 == 1)
    {
        stepper1.setSpeed(s1);
    }
    if (m2 == 2)
    {
        stepper2.setSpeed(s2);
    }
    if (m3 == 3)
    {
        stepper3.setSpeed(s3);
    }
    if (m4 == 4)
    {
        stepper4.setSpeed(s4);
    }
    if (m5 == 5)
    {
        stepper5.setSpeed(s5);
    }
    if (m6 == 6)
    {
        stepper6.setSpeed(s6);
    }

    if (m1 == 1)
    {
        if (m2 == 2)
        {
            if (m3 == 3)
            {
                if (m4 == 4)
                {
                    if (m5 == 5)
                    {
                        if (m6 == 6)
                        {

                            motor_combo = 1;
                            Serial.print("Starting Motor 1 at speed------> ");
                            Serial.println(s1);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");

                            Serial.print("Starting Motor 2 at speed------>");
                            Serial.println(s2);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");

                            Serial.print("Starting Motor 3 at speed------>");
                            Serial.println(s3);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");

                            Serial.print("Starting Motor 4 at speed------>");
                            Serial.println(s4);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");

                            Serial.print("Starting Motor 5 at speed------>");
                            Serial.println(s5);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");

                            Serial.print("Starting Motor 6 at speed------>");
                            Serial.println(s6);
                            Serial.print("For ");
                            Serial.print(t);
                            Serial.println(" Minutes");
                            Serial.println(" ");
                        }
                    }
                }
            }
        }
    }

    motorRunMillis = t * 60 * 1000;
    motorStartMillis = millis();

    while (!done)
    {
        if (millis() - motorStartMillis < motorRunMillis)
        {
            switch (motor_combo)
            {
            case 1:
                stepper1.runSpeed();
                stepper2.runSpeed();
                stepper3.runSpeed();
                stepper4.runSpeed();
                stepper5.runSpeed();
                stepper6.runSpeed();
                break;
            default:
                //stop();
                break;
            }
        }
        else
        {
            Serial.println("*****************Turning all motors off*****************");
            Serial.println(" ");
            stop();

            done = true;
        }
    }
    done = false;
}
void stop()
{
    stepper1.setSpeed(0);
    stepper2.setSpeed(0);
    stepper3.setSpeed(0);
    stepper4.setSpeed(0);
    stepper5.setSpeed(0);
    stepper6.setSpeed(0);

    stepper1.runSpeed();
    stepper2.runSpeed();
    stepper3.runSpeed();
    stepper4.runSpeed();
    stepper5.runSpeed();
    stepper6.runSpeed();
}
