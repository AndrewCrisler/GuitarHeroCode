int key1 = 4;  //from farthers out key to clossest key
int key2 = 6;
int key3 = 5;
int key4 = 7;
int key5 = 13;

int key6 = 12;
int key7 = 11;
int key8 = 9;
int key9 = 8;
int key10 = 10;

int lowStrum = A0;
int highStrum = A1;

int upOctiveKey = A2;
int downOctiveKey = A3;

int frequencyBar = A5;

int audioOut = 3; //squarewave signal pin

int noteF[] = {55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 350, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047};  //A1 - C6 0-51

int pinOrder[10] = {key1, key2, key3, key4, key5, key6, key7, key8, key9, key10};  // order in wich keys are checked

int keyValue[10] = {1, 3, 7, 15, 31, 63, 127, 225, 511, 1023};   //keyValue of the keys. determined by 2x+1 formula to make sure not sum values are equal

int keyNumber;  //number that determines what key is played
int strumValue = 0; //strum variable added in at the end
int noteOffset = 12; //note offseter to shift octives

void setup() {

  Serial.begin(9600);
  Serial.println("Current Frequency");

  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(key3, INPUT);
  pinMode(key4, INPUT);
  pinMode(key5, INPUT);

  pinMode(key6, INPUT);
  pinMode(key7, INPUT);
  pinMode(key8, INPUT);
  pinMode(key9, INPUT);
  pinMode(key10, INPUT);

  pinMode(lowStrum, INPUT);
  pinMode(highStrum, INPUT);
}

void loop() {
  //Serial.println("in loop");

  while (analogRead(upOctiveKey) < 50)  // check if up octive key is pushed
  {
    delay(10);
    if (analogRead(upOctiveKey) > 50)  //hold program untill button is open
    {
      if (noteOffset < 24)
      {
        noteOffset = noteOffset + 12;
      }
      break;
    }
  }

  while (analogRead(downOctiveKey) < 50)    //check if drop octive key is pushed
  {
    delay(10);
    if (analogRead(downOctiveKey) > 50)   //hold program untill buton is oper
    {
      if (noteOffset > 0)
      {
        noteOffset = noteOffset - 12;
      }
      break;
    }
  }

  while (analogRead(lowStrum) < 50)                 //if strum key pressed down
  {
    strumValue = 0;
    Serial.println("lowStrum");
    keyNumber = 0;

    for (int i = 0; i < 10; i++)                        //read the pins pushed and add there values together
    {
      if (digitalRead(pinOrder[i]) == LOW)
      {
        keyNumber = keyNumber + keyValue[i];
      }
    }
    Serial.println(keyNumber);
    switch (keyNumber)                              // based on keyValue get the correct note
    {
      case 1:
        playTone(0);     // A
        break;
      case 4:
        playTone(1);     // Bb
        break;
      case 3:
        playTone(2);     // B
        break;
      case 10:
        playTone(2);     // B
        break;
      case 7:
        playTone(3);     // C
        break;
      case 22:
        playTone(4);     // Db
        break;
      case 15:
        playTone(5);     // D
        break;
      case 46:
        playTone(6);     // Eb
        break;
      case 31:
        playTone(7);     // E
        break;
      case 94:
        playTone(7);     // E
        break;
      case 63:
        playTone(8);     // F
        break;
      case 190:
        playTone(9);     // Gb
        break;
      case 127:
        playTone(10);    // G
        break;
      case 352:
        playTone(11);    // Ab
        break;
      case 225:
        playTone(12);    // A
        break;
      case 736:
        playTone(13);    // Bb
        break;
      case 511:
        playTone(14);    // B
        break;
      case 1534:
        playTone(14);    // B
        break;
      case 1023:
        playTone(15);    // C
        break;
    }
  }


  while (analogRead(highStrum) < 50)                // if the stum key is pushed up
  {
    Serial.println("highStrum");
    strumValue = 12;
    keyNumber = 0;

    for (int i = 0; i < 10; i++)                        //read the pins pushed and add there values together
    {
      if (digitalRead(pinOrder[i]) == LOW)
      {
        keyNumber = keyNumber + keyValue[i];
      }
    }
    Serial.println(keyNumber);

    switch (keyNumber)                              // based on keyValue get the correct note
    {
      case 1:
        playTone(0);     // A
        break;
      case 4:
        playTone(1);     // Bb
        break;
      case 3:
        playTone(2);     // B
        break;
      case 10:
        playTone(2);     // B
        break;
      case 7:
        playTone(3);     // C
        break;
      case 22:
        playTone(4);     // Db
        break;
      case 15:
        playTone(5);     // D
        break;
      case 46:
        playTone(6);     // Eb
        break;
      case 31:
        playTone(7);     // E
        break;
      case 94:
        playTone(7);     // E
        break;
      case 63:
        playTone(8);     // F
        break;
      case 190:
        playTone(9);     // Gb
        break;
      case 127:
        playTone(10);    // G
        break;
      case 352:
        playTone(11);    // Ab
        break;
      case 225:
        playTone(12);    // A
        break;
      case 736:
        playTone(13);    // Bb
        break;
      case 511:
        playTone(14);    // B
        break;
      case 1534:
        playTone(14);    // B
        break;
      case 1023:
        playTone(15);    // C
        break;
    }
  }

  noTone(audioOut);

}


int playTone(int value)
{
  int frequency = value + strumValue + noteOffset;
  int frequencyBarValue = analogRead(frequencyBar);
  
  if(frequencyBarValue < 1020)
  {
    int distortedFrequency = (int) noteF[frequency] - 0.002 * (1023 - frequencyBarValue) * noteF[frequency];   //determined formula for frequency bar distortion
    tone(audioOut, distortedFrequency);
    Serial.println(distortedFrequency);
  }
  else
  {
  
  tone(audioOut, noteF[frequency]);
  Serial.println(noteF[frequency]);
  }
}


