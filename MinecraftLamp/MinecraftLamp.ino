  int bluePin=13;
  int greenPin=12;
  int redPin=11;
  int buttonPin=10;
  int pressCount=0;

void setup() {
  pinMode(bluePin, OUTPUT); //blue led
  pinMode(greenPin, OUTPUT); //green led
  pinMode(redPin, OUTPUT); //red led
  pinMode(buttonPin, INPUT);  //pushbutton
}

void loop() {
  if(digitalRead(buttonPin)==HIGH){ //pushbutton pressed, cycle colors
    pressCount++;
    delay(250); //pause to mitigate button bounce

    if(pressCount>6){ //reset presses
      pressCount=0;
    }
  }

  switch(pressCount){
   case 0: //red light
     digitalWrite(redPin, HIGH);
     digitalWrite(greenPin, LOW);
     digitalWrite(bluePin, LOW);
     break;
   case 1: //green light
     digitalWrite(redPin, LOW);
     digitalWrite(greenPin, HIGH);
     digitalWrite(bluePin, LOW);
     break;
   case 2: //blue light
     digitalWrite(redPin, LOW);
     digitalWrite(greenPin, LOW);
     digitalWrite(bluePin, HIGH);
     break;
   case 3: //magenta light
     digitalWrite(redPin, HIGH);
     digitalWrite(greenPin, LOW);
     digitalWrite(bluePin, HIGH);
     break;
   case 4: //yellow light
     digitalWrite(redPin, HIGH);
     digitalWrite(greenPin, HIGH);
     digitalWrite(bluePin, LOW);
     break;
   case 5: //cyan light
     digitalWrite(redPin, LOW);
     digitalWrite(greenPin, HIGH);
     digitalWrite(bluePin, HIGH);
     break;
   case 6: //white light
     digitalWrite(redPin, HIGH);
     digitalWrite(greenPin, HIGH);
     digitalWrite(bluePin, HIGH);
     break;
   default:
     break;
  }

}//end loop
