  int bluePin=11;
  int greenPin=10;
  int redPin=9;
  int cyclePin=8;
  int brightnessPin=7;
  int pressCount1=0, pressCount2=0; //for the two pushbuttons
  int currentRGB[3]={0,0,0}; //for brightness changing
  float newRGB[3]={0.0,0.0,0.0}; //for brightness changing
  int currColor, prevColor;

void setup() {
  pinMode(bluePin, OUTPUT); //blue led
  pinMode(greenPin, OUTPUT); //green led
  pinMode(redPin, OUTPUT); //red led
  pinMode(cyclePin, INPUT);  //pushbutton that cycles light colors
  pinMode(brightnessPin, INPUT); //pushbutton that changes light brightness
}

void loop() {
  if(digitalRead(cyclePin)==HIGH){ //pushbutton1 pressed, cycle colors
    delay(250); //pause to mitigate button bounce

    if(pressCount1>6){ //reset presses
      pressCount1=0;
    }

    switch(pressCount1){
      case 0: //light-brown light (iron ore)
        setRGB(115, 11, 1);
        break;
      case 1: //yellow light (gold ore)
        setRGB(255, 60, 0);
        break;
      case 2: //cyan light (diamond)
        setRGB(0, 255, 255);
        break;
      case 3: //green light (emerald)
        setRGB(0, 255, 0);
        break;
      case 4: //red light (redstone)
        setRGB(255, 0, 0);
        break;
      case 5: //blue light (lapis)
        setRGB(0, 0, 255);
        break;
      case 6: //purple light (why not)
        setRGB(100, 0, 255);
        break;
      default:
        break;
    }//end switch
    pressCount1++;
  }//end color selection

  if(digitalRead(brightnessPin)==HIGH){ //pushbutton2 pressed, change brightness
    delay(250);
    currColor=pressCount1; //track light color setting
    
    if(pressCount2==0){ //dim the lights, duty cycle 10%
      newRGB[0]=currentRGB[0]/10; //red
      newRGB[1]=currentRGB[1]/10; //green
      newRGB[2]=currentRGB[2]/10; //blue
      setRGB(int(newRGB[0]), int(newRGB[1]), int(newRGB[2])); //typecast to save float in other vars for restoration purposes
      pressCount2=1; //next button press restores light value
      prevColor=currColor; //track previous light setting      
    }

    else if(pressCount2==1){ //restore to full brightness if appropriate
      if(currColor==prevColor){ //color selection hasn't changed, restore brightness
        newRGB[0] = newRGB[0]*10;
        newRGB[1] = newRGB[1]*10;
        newRGB[2] = newRGB[2]*10;
        setRGB(int(newRGB[0]), int(newRGB[1]), int(newRGB[2]));
        pressCount2=0; //next button press dims light value
      }

      else{ //color selection changed, dim before attempting restore on next button press
        newRGB[0]=currentRGB[0]/10; //red
        newRGB[1]=currentRGB[1]/10; //green
        newRGB[2]=currentRGB[2]/10; //blue        
        setRGB(int(newRGB[0]), int(newRGB[1]), int(newRGB[2]));
        pressCount2=1; //next button press restores light value if color is unchanged
      }
      prevColor=currColor;
    }
  }//end brightness adjustment
}//end loop

void setRGB(int redLevel, int greenLevel, int blueLevel){ //simplify RGB value assignment
  analogWrite(redPin, redLevel);
  analogWrite(greenPin, greenLevel);
  analogWrite(bluePin, blueLevel);
  currentRGB[0]=redLevel;
  currentRGB[1]=greenLevel;
  currentRGB[2]=blueLevel;
}
