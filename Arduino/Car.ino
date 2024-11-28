#include <Servo.h>

class Car {
private:
    int _motorLF;
    int _motorRF;
    int _motorLB;
    int _motorRB;

    int _lightLF;
    int _lightRF;
    int _lightLB;
    int _lightRB;
    int _lightLF2;
    int _lightRF2;
    int _lightLB2;
    int _lightRB2;

    Servo _verticalServo;
    Servo _horizontalServo;

public:
    Car(int motorLF, int motorRF, int motorLB, int motorRB, int lightLF, int lightRF, int lightLB, int lightRB, int lightLF2, int lightRF2, int lightLB2, int lightRB2, int verticalPin, int horizontalPin) 
    {
        _motorLF = motorLF;
        _motorRF = motorRF;
        _motorLB = motorLB;
        _motorRB = motorRB;
        _lightLF = lightLF;
        _lightRF = lightRF;
        _lightLB = lightLB;
        _lightRB = lightRB;
        _lightLF2 = lightLF2;
        _lightRF2 = lightRF2;
        _lightLB2 = lightLB2;
        _lightRB2 = lightRB2;

        pinMode(_motorLF, OUTPUT);
        pinMode(_motorRF, OUTPUT);
        pinMode(_motorLB, OUTPUT);
        pinMode(_motorRB, OUTPUT);

        pinMode(_lightLF, OUTPUT);
        pinMode(_lightRF, OUTPUT);
        pinMode(_lightLB, OUTPUT);
        pinMode(_lightRB, OUTPUT);
        pinMode(_lightLF2, OUTPUT);
        pinMode(_lightRF2, OUTPUT);
        pinMode(_lightLB2, OUTPUT);
        pinMode(_lightRB2, OUTPUT);

        _verticalServo.attach(verticalPin);
        _horizontalServo.attach(horizontalPin);
    }

    void Movement(String direction)
    {
        if (direction == "Forward")
        {
            digitalWrite(_motorLF, HIGH);
            digitalWrite(_motorLB, LOW);
            digitalWrite(_motorRF, HIGH);
            digitalWrite(_motorRB, LOW);
        }
        else if (direction == "Backward")
        {
            digitalWrite(_motorLF, LOW);
            digitalWrite(_motorLB, HIGH);
            digitalWrite(_motorRF, LOW);
            digitalWrite(_motorRB, HIGH);
        }
        else if (direction == "Left")
        {
            digitalWrite(_motorLF, LOW);
            digitalWrite(_motorLB, HIGH);
            digitalWrite(_motorRF, HIGH);
            digitalWrite(_motorRB, HIGH);
        }
        else if (direction == "Right")
        {
            digitalWrite(_motorLF, HIGH);
            digitalWrite(_motorLB, HIGH);
            digitalWrite(_motorRF, LOW);
            digitalWrite(_motorRB, HIGH);
        }
        else if (direction == "Stop")
        {
            digitalWrite(_motorLF, HIGH);
            digitalWrite(_motorLB, HIGH);
            digitalWrite(_motorRF, HIGH);
            digitalWrite(_motorRB, HIGH);
            Lights(true, false);
        }
    }

    void Lights(bool on, bool forward)
    {
        if (forward)
        {
            digitalWrite(_lightLF, on ? HIGH : LOW);
            digitalWrite(_lightRF, on ? HIGH : LOW);
            digitalWrite(_lightLF2, on ? HIGH : LOW);
            digitalWrite(_lightRF2, on ? HIGH : LOW);
        }
        else
        {
            if (on)
            {
                digitalWrite(_lightLB, HIGH);
                digitalWrite(_lightRB, HIGH);
                digitalWrite(_lightLB2, HIGH);
                digitalWrite(_lightRB2, HIGH);
                delay(300);
                digitalWrite(_lightLB, LOW);
                digitalWrite(_lightRB, LOW);
                digitalWrite(_lightLB2, LOW);
                digitalWrite(_lightRB2, LOW);
            }
            else
            {
                digitalWrite(_lightLB, LOW);
                digitalWrite(_lightRB, LOW);
                digitalWrite(_lightLB2, LOW);
                digitalWrite(_lightRB2, LOW);
            }
        }
    }

    void MoveVertical(int angle)
    {
        _verticalServo.write(angle);
    }

    void MoveHorizontal(int angle)
    {
        _horizontalServo.write(angle);
    }
};

Car car(6, 8, 2, 4, 10, 11, 12, 13, 14, 15, 16, 17, 5, 7);

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    if (Serial.available()) 
    {
        char receivedChar = Serial.read();

        if(receivedChar != 'S')
        {
            car.Lights(false, false);
        }
        else
        {
            car.Movement("Stop");
        }

        if (receivedChar == 'F') 
        {
            car.Movement("Forward");
        } 
        else if (receivedChar == 'B') 
        {
            car.Movement("Backward");
        } 
        else if (receivedChar == 'L') 
        {
            car.Movement("Left");
        } 
        else if (receivedChar == 'R') 
        {
            car.Movement("Right");
        }
        else if (receivedChar == 'Y') 
        {
            car.Lights(true, true);
        } 
        else if (receivedChar == 'I') 
        {
            car.Lights(false, true);
        }
        else if (receivedChar == 'P')
        {
            car.MoveVertical(50);
        }
        else if (receivedChar == 'O') 
        {
            car.MoveVertical(0);
        }
        else if (receivedChar == 'K') 
        {
            car.MoveHorizontal(90); 
        }
        else if (receivedChar == 'J')
        {
            car.MoveHorizontal(0);
        }
    }
}
