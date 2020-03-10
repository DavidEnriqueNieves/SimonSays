/*

   TO DO LIST

   ADD DEBOUNCING


*/

const unsigned short debounceDelay = 100;

unsigned long lastTimeButtonsChanged[4] = {0, 0, 0, 0};

const int ROUNDS = 4;
const int NUM_LIGHTS = 4;
const int buttonPin[NUM_LIGHTS] = {7, 6, 5, 4};
unsigned int lastKnownButtonStates[NUM_LIGHTS] = {0 , 0, 0 , 0 };
unsigned int VICTORY = 8;
enum Lights {BLUE = 0, RED, YELLOW, GREEN};

const unsigned short ERRORS = 7;
const int ledPin[NUM_LIGHTS] = {12, 11, 10, 9};
unsigned short ledStates[NUM_LIGHTS] = {LOW, LOW, LOW, LOW};
unsigned short ledBuzzerFreq[NUM_LIGHTS] = {587, 440, 784, 880};
//the times that each led waits in between for each sound play
//THIS IS IN MICROSECONDS
unsigned short ledColorMIDWaits[NUM_LIGHTS] = {851, 1136, 638, 568};
unsigned short ledWaitDef = 150;


unsigned short errorSoundFreqs[2] = {250, 150};
unsigned short errorSoundWait  = 250;

const int buzzerPin = 3;

const unsigned short GlobalInterruptBit = 7;
unsigned int counter = 0;

short NumberSequence[10]  = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

unsigned short PlayerInput[10]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  for (unsigned int i = 0; i < NUM_LIGHTS; i++)
  {
    pinModeGeneric(buttonPin[i], INPUT);
  }
  for (unsigned int u = 0; u < NUM_LIGHTS; u++)
  {
    pinModeGeneric(ledPin[u], OUTPUT);
  }

}

bool Input = false;
unsigned long LastInputTime = 0;
unsigned long InputTimeout = (1000 * 60);

short inputNum = -1;

void loop() {
  // put your main code here, to run repeatedly:
  /*
      randomSeed(millis());
    unsigned int h  =random(0,4);

    digitalWriteGeneric(ledPin[h], HIGH);
    delay(500);
     digitalWriteGeneric(ledPin[h], LOW);
    count++;

  */

  /*
      counter++;
      RandomSequencegen();
    SequenceInterpret();
  */
  if (inputNum == ROUNDS)
  {
    Serial.println("YOU WON!!!");
    PlaySound(VICTORY);
    while ((digitalReadGeneric(buttonPin[BLUE]) == LOW) && (digitalReadGeneric(buttonPin[RED]) == LOW) && (digitalReadGeneric(buttonPin[GREEN]) == LOW) && (digitalReadGeneric(buttonPin[YELLOW]) == LOW))
    {
      ChaserPattern1();
      ChaserPattern1();
      ChaserPattern1();
      ChaserPattern1();
      ChaserPattern2();
      ChaserPattern2();
      ChaserPattern2();
      ChaserPattern2();
    }
    if ((digitalReadGeneric(buttonPin[BLUE]) == HIGH) || (digitalReadGeneric(buttonPin[RED]) == HIGH) || (digitalReadGeneric(buttonPin[GREEN]) == HIGH) || (digitalReadGeneric(buttonPin[YELLOW]) == HIGH))
    {
      PlaySound(ERRORS);
      delayGeneric(1000);
      ResetSequences();
      inputNum = -1;
      counter = 0;
      Input = false;
    }
  }
  else if (Input == false)
  {

    RandomSequenceGen();
    SequenceInterpret();
    Input  = true;
  }
  else {
    inputNum = 0;

    do {
      if (debounce(buttonPin[BLUE]) == HIGH)
      {
        PlaySound(BLUE);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[BLUE], HIGH);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[BLUE], LOW);
        delayGeneric(50);
        inputNum++;
        LastInputTime = millis();
        PlayerInput[inputNum] = BLUE;
        Serial.println("BLUE PRESSED");
        Serial.println("NUMBER SEQUENCE[INPUTNUM] IS EQUAL TO");
        Serial.println(NumberSequence[inputNum - 1]);
        Serial.println("PLAYERINPUT[INPUTNUM} is eqaul to ");
        Serial.println(PlayerInput[inputNum]);
        delayGeneric(50);
        if (PlayerInput[inputNum] != NumberSequence[inputNum - 1])
        {
          Serial.println("RESETTING!!");

          PlaySound(ERRORS);
          delayGeneric(1000);
          ResetSequences();
          inputNum = -1;
          counter = 0;
          Input = false;
          break;
        }
        for (int i = 0; i < counter; i++)
        {
          String Message = String("Player Input: ") + String(PlayerInput[i]) + String("Number Sequence ") + String(NumberSequence[i]);
          Serial.println(Message);
        }

      }

      else if (debounce(buttonPin[RED]) == HIGH)
      {
        PlaySound(RED);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[RED], HIGH);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[RED], LOW);
        delayGeneric(50);
        inputNum++;
        LastInputTime = millis();
        PlayerInput[inputNum] = RED;
        Serial.println("RED PRESSED");
        Serial.println("NUMBER SEQUENCE[inputNum -1 ] IS EQUAL TO");
        Serial.println(NumberSequence[inputNum - 1]);
        Serial.println("PLAYERINPUT[INPUTNUM} is eqaul to ");
        Serial.println(PlayerInput[inputNum]);
        delayGeneric(50);
        if (PlayerInput[inputNum] != NumberSequence[inputNum - 1 ])
        {
          Serial.println("RESETTING!!");

          PlaySound(ERRORS);
          delayGeneric(1000);
          ResetSequences();
          inputNum = -1;
          counter = 0;
          Input = false;
          break;
        }
        for (int i = 0; i < counter; i++)
        {
          String Message = String("Player Input: ") + String(PlayerInput[i]) + String("Number Sequence ") + String(NumberSequence[i]);
          Serial.println(Message);
        }

      }
      else if (debounce(buttonPin[GREEN]) == HIGH)
      {
        PlaySound(GREEN);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[GREEN], HIGH);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[GREEN], LOW);
        delayGeneric(50);
        inputNum++;
        LastInputTime = millis();
        PlayerInput[inputNum] = GREEN;
        Serial.println("GREEN PRESSED");
        Serial.println("NUMBER SEQUENCE[inputNum -1] IS EQUAL TO");
        Serial.println(NumberSequence[inputNum - 1]);
        Serial.println("PLAYERINPUT[INPUTNUM} is eqaul to ");
        Serial.println(PlayerInput[inputNum]);
        delayGeneric(50);
        if (PlayerInput[inputNum] != NumberSequence[inputNum - 1 ])
        {
          Serial.println("RESETTING!!");

          PlaySound(ERRORS);
          delayGeneric(1000);
          ResetSequences();
          inputNum = -1;
          counter = 0;
          Input = false;
          break;
        }
        for (int i = 0; i < counter; i++)
        {
          String Message = String("Player Input: ") + String(PlayerInput[i]) + String("Number Sequence ") + String(NumberSequence[i]);
          Serial.println(Message);
        }

      }

      else if (debounce(buttonPin[YELLOW]) == HIGH)
      {
        PlaySound(YELLOW);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[YELLOW], HIGH);
        delayGeneric(50);
        digitalWriteGeneric(ledPin[YELLOW], LOW);
        delayGeneric(50);
        inputNum++;
        LastInputTime = millis();
        PlayerInput[inputNum] = YELLOW;
        Serial.println("YELLOW PRESSED");
        Serial.println("NUMBER SEQUENCE[inputNum -1] IS EQUAL TO");
        Serial.println(NumberSequence[inputNum - 1]);
        Serial.println("PLAYERINPUT[INPUTNUM} is eqaul to ");
        Serial.println(PlayerInput[inputNum]);
        delayGeneric(50);
        if (PlayerInput[inputNum] != NumberSequence[inputNum - 1])
        {
          Serial.println("RESETTING!!");

          PlaySound(ERRORS);
          delayGeneric(1000);
          ResetSequences();
          inputNum = -1;
          counter = 0;
          Input = false;
          break;
        }
        for (int i = 0; i < counter; i++)
        {
          String Message = String("Player Input: ") + String(PlayerInput[i]) + String("Number Sequence ") + String(NumberSequence[i]);
          Serial.println(Message);
        }

      }
    } while (inputNum != counter);
    Input = false;

  }
}


void digitalWriteGeneric (unsigned char pin_number, unsigned char pin_setting)
{
  //make sure to define
  //PORTx
  bool isPinD;

  // If pin is controlled by Port B
  if (pin_number > 7)
  {
    // Pin 8 in the board is mapped to bit 0 of port b register.
    pin_number = pin_number - 8;
    isPinD = false;
  }
  else
  {
    //pin_number <= 7 (pin is in Port D)
    //do not need to modify the pin_number
    isPinD = true;
  }

  //NOT SURE IF THIS IS NECESSARY

  // Disable global interrupts.
  ((isPinD == true) ? DDRD : DDRB) = ((isPinD == true) ? DDRD : DDRB) & (HIGH << pin_number);

  SREG = SREG & (LOW << GlobalInterruptBit);

  // Write the value to it.
  if ( pin_setting == HIGH )
    ((isPinD == true) ? PORTD : PORTB)  = ((isPinD == true) ? PORTD : PORTB) | (pin_setting << pin_number);
  else
    ((isPinD == true) ? PORTD : PORTB)  = ((isPinD == true) ? PORTD : PORTB) & (pin_setting << pin_number);

  // Enable global interrupts.
  SREG = SREG | (HIGH << GlobalInterruptBit);

}



int digitalReadGeneric (unsigned char pin_number)
{
  bool isPinD;
  //make sure to define
  //PORTx
  //DDRx
  //PINx
  //ARE WE ONLY GOING TO USE PORTS B AND D???
  // If pin is controlled by Port B
  if (pin_number > 7)
  {
    isPinD = false;
    // Pin 8 in the board is mapped to bit 0 of port b register.
    pin_number = pin_number - 8;
  } else
  {
    isPinD = true;
  }
  //FIX THIS PART!!!!
  ((isPinD == true) ? DDRD : DDRB) = ((isPinD == true) ? DDRD : DDRB) & (LOW << pin_number);

  // Enable pull-up resistor to read a stable HIGH always.
  ((isPinD == true) ? PORTD : PORTB)  = ((isPinD == true) ? PORTD : PORTB) | (HIGH << pin_number);


  unsigned char result;


  // Disable global interrupts.
  SREG = SREG & (LOW << GlobalInterruptBit);
  //write the actual reading in here...
  result  = ((isPinD == true) ? PIND : PINB) & (HIGH << pin_number);

  if ((((isPinD == true) ? PIND : PINB) & (HIGH << pin_number) ) == LOW) {
    // Button pressed on pin 3.
    SREG = SREG | (HIGH << GlobalInterruptBit);
    return LOW;
  }
  else {
    // no button pressed on pin 3.
    SREG = SREG | (HIGH << GlobalInterruptBit);
    return HIGH;
  }



}


void pinModeGeneric (unsigned char pin_number, unsigned char data_direction)
{
  bool isPinD;

  // If pin is controlled by Port B
  if (pin_number > 7)
  {
    // Pin 8 in the board is mapped to bit 0 of port b register.
    isPinD  = false;
    pin_number = pin_number - 8;
  }
  else isPinD = true;


  if (data_direction == OUTPUT)
  {
    if (isPinD == true)
    {

      // Set the data direction register to input, which is accomplished by a LOW (0) value.
      DDRD = DDRD | (HIGH << pin_number);
    }
    else
    {
      DDRB = DDRB | (HIGH << pin_number);

    }
  }
  else
  {
    if (isPinD == true)
    {

      // Set the data direction register to input, which is accomplished by a LOW (0) value.
      DDRD = DDRD & (LOW << pin_number);
    }
    else
    {
      DDRB = DDRB & (LOW << pin_number);

    }
  }

}




void PlaySound(unsigned int color)
{

  if (color == ERRORS)
  {
    tone(buzzerPin, errorSoundFreqs[0], errorSoundWait);
    delayMicrosecondsGeneric(errorSoundWait);
    tone(buzzerPin, errorSoundFreqs[1], errorSoundWait);
    Serial.println("ERROR!!!! ");
  }
  else if (color == VICTORY)
  {
    tone(buzzerPin, 600, 173);
    delayGeneric(250);
    tone(buzzerPin, 600, 173);
    delayGeneric(250);
    tone(buzzerPin, 600, 173);
    delayGeneric(250);
    tone(buzzerPin, 600, 500);
    delayGeneric(250);
    tone(buzzerPin, 455, 550);
    delayGeneric(550);
    tone(buzzerPin, 500, 200);
    delayGeneric(250);
    tone(buzzerPin, 600, 500);
    delayGeneric(250);
    tone(buzzerPin, 500, 173);
    delayGeneric(250);
    tone(buzzerPin, 600, 550);
    delayGeneric(250);
  }
  else
  {
    tone(buzzerPin, ledBuzzerFreq[color], ledWaitDef);
    delayMicrosecondsGeneric(ledColorMIDWaits[color]);
    tone(buzzerPin, ledBuzzerFreq[color], ledWaitDef);
  }


}







void delayGeneric(unsigned long ms)
{
  unsigned long LastTime = millis();
  while (millis() - LastTime < ms)
  {
    SREG = SREG | (HIGH << GlobalInterruptBit);
  }
  SREG = SREG & (LOW << GlobalInterruptBit);

}


void delayMicrosecondsGeneric(unsigned long us)
{
  unsigned long long LastTime = micros();
  while (millis() - LastTime < us)
  {
    SREG = SREG | (HIGH << GlobalInterruptBit);
  }
  SREG = SREG & (LOW << GlobalInterruptBit);


}


void SequenceInterpret()
{
  for (unsigned int i = 0; i < counter; i++)
  {
    //    std::cout <<"\n10 " <<currentSequence%10-(static_cast<unsigned int>(pow(10, i-2)));
    //  std::cout <<"\n100 "<< (currentSequence%(static_cast<unsigned int>(pow(10, i))))-(static_cast<unsigned int>(pow(10, i-2))))/(static_cast<unsigned int>(pow(10,i-1)))));
    unsigned short digit = NumberSequence[i];
    PlaySound(digit);
    digitalWriteGeneric(ledPin[digit], HIGH);
    delayGeneric(500);
    digitalWriteGeneric(ledPin[digit], LOW);

  }

}



void RandomSequenceGen()
{

  randomSeed(micros());
  //unsigned short Last = random(1,5);
  //unsigned long LastSum = (Last)*(pow(10, counter)) + 1;
  unsigned short semiLast  = NumberSequence[counter - 1];
  unsigned short Last = random(0, 4);
  do
  {
    Last = static_cast<unsigned int>(random(0, 4));
    /*
      Serial.println("Semilast is");
      Serial.println(semiLast);
      Serial.println("Last is ...");
      Serial.println(Last);
    */
  } while (Last == semiLast);

  NumberSequence[counter]  = Last;
  counter++;
  Serial.println("Current Sequence is");
  for (unsigned int i = 0; i < counter; i++)
  {
    Serial.println(NumberSequence[i]);
  }
}





void ResetSequences()
{
  for (unsigned int h = 0; h < inputNum; h++)
  {
    NumberSequence[h] = 3;
    PlayerInput[h]  = 0;

  }
}




unsigned short debounce(unsigned int buttonPin)
{
  if (digitalReadGeneric(buttonPin) == HIGH) //if the buttonvalue is set to high
  {
    if ((millis() - lastTimeButtonsChanged[buttonPin]) > debounceDelay)
    {
      lastTimeButtonsChanged[buttonPin] = millis();
      return HIGH;
    }
  }
  else
  {
    return LOW;
  }

}


void ChaserPattern1()
{

  digitalWriteGeneric(ledPin[BLUE], HIGH);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[BLUE], LOW);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[RED], HIGH);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[RED], LOW);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[YELLOW], HIGH);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[YELLOW], LOW);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[GREEN], HIGH);
  delayGeneric(50);
  digitalWriteGeneric(ledPin[GREEN], LOW);
  delayGeneric(50);

}

void ChaserPattern2()
{
  digitalWriteGeneric(ledPin[BLUE], HIGH);
  digitalWriteGeneric(ledPin[RED], HIGH);
  delayGeneric(500);
  digitalWriteGeneric(ledPin[BLUE], LOW);
  digitalWriteGeneric(ledPin[RED], LOW);
  digitalWriteGeneric(ledPin[YELLOW], HIGH);
  digitalWriteGeneric(ledPin[GREEN], HIGH);
  delayGeneric(500);
  digitalWriteGeneric(ledPin[YELLOW], LOW);
  digitalWriteGeneric(ledPin[GREEN], LOW);
}
