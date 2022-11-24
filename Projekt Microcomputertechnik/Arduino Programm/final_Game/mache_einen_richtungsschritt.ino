bool mache_einen_richtungsschritt(int *y, int *x){
  bool status = true;
  char btn_richtung;

 if(digitalRead(taster_L)==HIGH){btn_richtung='L';}
 else if(digitalRead(taster_R)==HIGH){btn_richtung='R';}
 else if(digitalRead(taster_O)==HIGH){btn_richtung='O';}
 else if(digitalRead(taster_U)==HIGH){btn_richtung='U';}
 else if(digitalRead(taster_Quit)==HIGH){btn_richtung='Q';}
  else{btn_richtung='X';}

  delay(150);

  switch(btn_richtung){
    case 'L':
        LEDMatrix.setLed(0, *x, *y, false);
        *x=*x+1;                          //ein pixel nach links
        if(checke_spielfeldgraenzen(*y,*x)==false){*x=*x-1;}
        break;
    case 'R':
        LEDMatrix.setLed(0, *x, *y, false);
        *x=*x-1;                            //ein pixel nach rechts
        if(checke_spielfeldgraenzen(*y,*x)==false){*x=*x+1;}
        break;
    case 'O':
        LEDMatrix.setLed(0, *x, *y, false);
        *y=*y-1;                            //ein pixel nach oben
        if(checke_spielfeldgraenzen(*y,*x)==false){*y=*y+1;}
        break;
    case 'U':
        LEDMatrix.setLed(0, *x, *y, false);
        *y=*y+1;                            //ein pixel nach unten
        if(checke_spielfeldgraenzen(*y,*x)==false){*y=*y-1;}
        break;
    case 'Q':
        status = false;
        for(int i=0; i<= AnzahlMatrix; i++){
        LEDMatrix.clearDisplay(i);
        }
        break;
    default:
        break;
    }
    LEDMatrix.setLed(0, *x, *y, true);
    return status;
}
