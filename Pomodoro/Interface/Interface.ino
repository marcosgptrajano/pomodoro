#include <TFT_eSPI.h> // Biblioteca do display+// Arquivo com a sua array de pixels
#include "Pomodoro.h"

TFT_eSPI tft = TFT_eSPI();


int item_selected = 2;
int last_item_selected = 2;
int j_x = 0;
int j_y = 0;
bool j_bt = false;

int timer = 0;
int last_timer = 0;
int cicles_choose = 0;
int last_cicles = 0;

int interface = 1;

int study_time = 0;
int breack_time = 0;
int cicles = 0;

double myTime;
double currentMillis;

void setup() {
  pinMode(20, INPUT_PULLUP);
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);

  // Parâmetros: (X, Y, Largura, Altura, Nome_da_Array)
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(5);
  tft.setCursor(40, 100);
  tft.print("Pomodoro");
  delay(1000);
  UIControl(configStudy());
}

void loop() {
  

}

void configStudyUI(){
  tft.fillRect(0, 0 , 320 , 240 , TFT_RED);
  delay(1000);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);

  // Menu superior
  //Item 01
  
  tft.fillRoundRect(7, 19, 99, 29, 5.5, TFT_DARKCYAN);
  tft.setTextSize(1.9);
  tft.setTextColor(TFT_WHITE, TFT_DARKCYAN);
  tft.setCursor(24, 30);
  tft.print("Study time");

  //Item 02
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.fillRoundRect(110, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setCursor(127, 30);
  tft.print("Breack time");


  //Item03
  tft.fillRoundRect(214, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setCursor(243, 30);
  tft.print("Cicles");

  // Menu inferior
  tft.fillRoundRect(11, 193, 99, 29, 5.5,  TFT_WHITE);
  tft.setCursor(34, 204);
  tft.print("< Back");

  tft.fillRoundRect(209.5, 193, 99, 29, 5.5,  TFT_WHITE);
  tft.setCursor(242, 204);
  tft.print("Next >");

  // Texto central
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setTextSize(15);
  tft.setCursor(55, 98);
  tft.print("00:00");
}

void configBreackUI(){
  configStudyUI();

  tft.fillRoundRect(7, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setTextSize(1.9);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(24, 30);
  tft.print("Study time");

  tft.setTextColor(TFT_BLACK, TFT_DARKCYAN);
  tft.fillRoundRect(110, 19, 99, 29, 5.5, TFT_DARKCYAN);
  tft.setCursor(127, 30);
  tft.print("Breack time");


}

void configCiclesUI(){
  configBreackUI();

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.fillRoundRect(110, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setCursor(127, 30);
  tft.print("Breack time");

  tft.setTextColor(TFT_BLACK, TFT_DARKCYAN);
  tft.fillRoundRect(214, 19, 99, 29, 5.5, TFT_DARKCYAN);
  tft.setCursor(243, 30);
  tft.print("Cicles");

}

int selection(int c){
  j_x = analogRead(27);
  j_bt = digitalRead(20)==0?true:false;
  
  //Serial.println("x: " + String(j_x)+ "y: " + String(j_y) + "bt: " + String(j_bt));
  
  if(c == 3){
    if(j_x > 600){
    if(item_selected < 3) {
      item_selected++;
    } 
    } else if(j_x < 400) {
    if(item_selected > 1){
      item_selected--;
    } 
  }
  } else if(c == 2){
    if(j_x > 600){
      if(item_selected < 2) {
       item_selected++;
      } 
    } else if(j_x < 400) {
      if(item_selected > 1){
        item_selected--;
      } 
    }
  }
  Serial.println("item_selected: " + String(item_selected) + " button state: " + String(j_bt) +" Timer: " + String(timer));
  delay(200);
  return(item_selected);
  

  

  
}

void interact(){
   j_bt = digitalRead(20)==0?true:false;
    if(item_selected == 2 && j_bt){

      if(interface <= 2){
        while(j_bt){j_bt = digitalRead(20)==0?true:false;}
        tft.setTextSize(15);
        tft.setTextColor(TFT_ORANGE, TFT_RED);
        tft.setTextSize(15);
        tft.setCursor(55, 98);
        tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
        last_timer = timer;
        while(!j_bt){
        j_bt = digitalRead(20)==0?true:false;
        j_y = analogRead(26);
        Serial.println("y: " + String(j_y) + " timer: " + String(timer));
        if(j_y >600){
        if(timer < 60){
          timer++;
          delay(100);
        }
        
        } else if( j_y < 400){
          if(timer > 1){
            timer--;
            delay(100);
          }
        }
        displayConfigTime(timer);
        }
    
    } else{
        while(j_bt){j_bt = digitalRead(20)==0?true:false;}
        tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
        tft.setTextSize(15);
        tft.setTextColor(TFT_ORANGE, TFT_RED);
        tft.setTextSize(15);
        tft.setCursor(114, 98);
        tft.print(  timer<10?"0" + String(cicles_choose):String(timer));
        last_cicles = cicles_choose;
        while(!j_bt){
        j_bt = digitalRead(20)==0?true:false;
        j_y = analogRead(26);
        if(j_y >600){
        if(cicles_choose < 60){
          cicles_choose++;
          delay(100);
        }
        
        } else if( j_y < 400){
          if(cicles_choose > 1){
            cicles_choose--;
            delay(100);
          }
        }
        displayConfigCicle(cicles_choose);
        }
    }
}

  if(item_selected == 3 && j_bt){
    Serial.print("Next");
    item_selected = 2;
    confirmUI(selection(2), interface);
  }

  if(interface > 1){
    if(interface > 2){
      if(item_selected == 1 && j_bt){
      item_selected = 2;
      interface--;
      timer = breack_time;
      UIControl(interface);
     }
    } else{
      if(item_selected == 1 && j_bt){
      item_selected = 2;
      interface--;
      timer = study_time;
      UIControl(interface);
      }
    }
  
  }
}


void displayConfigTime(int t){

  if(t != last_timer){
    tft.setTextSize(15);
    tft.setTextColor(TFT_ORANGE, TFT_RED);
    tft.setTextSize(15);
    tft.setCursor(55, 98);
    tft.print( t<10?"0" + String(t)+ ":00":String(t)  + ":00");
    last_timer = t;
  }
  

}

void displayConfigCicle(int t){

  if(t != last_cicles){
    tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
    tft.setTextSize(15);
    tft.setTextColor(TFT_ORANGE, TFT_RED);
    tft.setTextSize(15);
    tft.setCursor(114, 98);
    tft.print( cicles_choose<10? "0" + String(cicles_choose): ""+ String(cicles_choose));
    last_cicles = t;
  }
  

}

void selectAnimation(int i){
  if(i == 2){
    if(item_selected != last_item_selected){
      tft.setTextSize(1.9);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.fillRoundRect(11, 193, 99, 29, 5.5,  TFT_WHITE);
      tft.setCursor(34, 204);
      tft.print("< Back");

      tft.setTextSize(1.9);
      tft.fillRoundRect(209.5, 193, 99, 29, 5.5,  TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(242, 204);
      tft.print("Next >");

      last_item_selected = item_selected;
    }

    tft.setTextSize(15);
    tft.setTextColor(TFT_ORANGE, TFT_RED);
    tft.setTextSize(15);
    tft.setCursor(55, 98);
   
    if(interface == 3){
      tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
       tft.setCursor(110, 98);
      tft.print( cicles_choose<10? "0" + String(cicles_choose): ""+ String(cicles_choose));
    } else{
      tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
    }
    

    delay(200);

    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.setTextSize(15);
    
    if(interface == 3){
      tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
      tft.setCursor(110, 98);
      tft.print( cicles_choose<10? "0" + String(cicles_choose): ""+ String(cicles_choose));
    } else{
      tft.setCursor(55, 98);
      tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
    }


  } else if(i == 1){
      tft.setTextSize(1.9);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.fillRoundRect(11, 193, 99, 29, 5.5,  TFT_ORANGE);
      tft.setCursor(34, 204);
      tft.print("< Back");

      delay(200);
      
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.fillRoundRect(11, 193, 99, 29, 5.5,  TFT_WHITE);
      tft.setCursor(34, 204);
      tft.print("< Back");

      if(item_selected != last_item_selected){
        tft.setTextSize(15);
        tft.setTextColor(TFT_WHITE, TFT_RED);
        tft.setTextSize(15);
        
        
        if(interface == 3){
          tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
          tft.setCursor(110, 98);
        tft.print( cicles_choose<10? "0" + String(cicles_choose): ""+ String(cicles_choose));
        } else{
          tft.setCursor(55, 98);
          tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
        }

        tft.setTextSize(1.9);
        tft.fillRoundRect(209.5, 193, 99, 29, 5.5,  TFT_WHITE);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setCursor(242, 204);
        tft.print("Next >");

        last_item_selected = item_selected;
      }
  
    
  } else if( i == 3){
    if(item_selected != last_item_selected){
        tft.setTextSize(15);
        tft.setTextColor(TFT_WHITE, TFT_RED);
        tft.setTextSize(15);
        if(interface == 3){
          tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
          tft.setCursor(110, 98);
          tft.print( cicles_choose<10? "0" + String(cicles_choose): ""+ String(cicles_choose));
        } else{
          tft.setCursor(55, 98);
          tft.print(timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
        }

        tft.setTextSize(1.9);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.fillRoundRect(11, 193, 99, 29, 5.5,  TFT_WHITE);
        tft.setCursor(34, 204);
        tft.print("< Back");


        last_item_selected = item_selected;
      }

      tft.setTextSize(1.9);
      tft.fillRoundRect(209.5, 193, 99, 29, 5.5,  TFT_ORANGE);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.setCursor(242, 204);
      tft.print("Next >");

      delay(200);

      tft.setTextSize(1.9);
      tft.fillRoundRect(209.5, 193, 99, 29, 5.5,  TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(242, 204);
      tft.print("Next >");


  }

}

void pomodoroUI(){
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(5);
  tft.setCursor(40, 100);
  tft.print("Pomodoro");
}

int configStudy(){
  return 1;
}
int configBreack(){
  return 2;
}
int configCicles(){
  return 3;
}

int configPomodoro(){
  return 4;
}

void UIControl(int id){
  switch(id){
    case 1:
      configStudyUI();
      while(!confirm()){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 2:
      configBreackUI();
      while(true){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 3:
      configCiclesUI();
      while(!confirm()){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 4:
      pomodoroUI();
      Pomodoro pomodoro(study_time, breack_time, cicles, 9);
      currentMillis = millis();
      myTime = ((millis() - currentMillis) / 1000.0) / 60.0;
      while(myTime < pomodoro.getTotalTime()){
        myTime = ((millis() - currentMillis) / 1000.0) / 60.0;
        Serial.println(pomodoro.getTimer(myTime));
        delay(1000);
      }
      // while(myTime < totalTime){
      //   myTime = ((millis() - currentMillis) / 1000) /60;
      //   Serial.println("Timer: "+  pomodoro.getTimer(myTime)+ ", Tempo decorrido: " + String(myTime) + "min");
      // }
      //pomodoro.timer();
      Serial.print("Chegou");
      break;
        
  }

}

bool confirm(){
  return false;
}

void confirmUI(int item, int ui){

  int button_selected = 2;
  int last_button_selected = 2;
  bool click = false;

  tft.setTextSize(1.9);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  tft.fillRect(0, 0 , 320 , 240 , TFT_RED);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);
  tft.fillRoundRect(54, 45 , 214 , 150.5 , 5, TFT_DARKCYAN);

  tft.fillRoundRect(64.5, 138, 88, 29,5, TFT_WHITE);
  tft.setCursor(100, 149);
  tft.print("No");

  tft.fillRoundRect(167,138, 88, 29,5, TFT_WHITE);
  tft.setCursor(202, 149);
  tft.print("Yes");

  tft.setTextColor(TFT_BLACK, TFT_DARKCYAN);
  tft.setCursor(129, 70);
  tft.print("CONFIRM?");


  tft.setTextColor(TFT_WHITE, TFT_DARKCYAN);
  tft.setCursor(64.5, 94);
  tft.print((ui==1)?"Do you want to set the study":(ui==2)?"Do you want to set the break":"Do you want to set ");
  tft.setCursor(64.5, 102);
  if(ui<=2){
    tft.println("session duration to " + String(timer) + " minutes?");
  } else{
    tft.println("the number of cicles to"+ String(cicles_choose) + "?");
  }
  

  while(!click){
    
    button_selected = selection(item); 
    Serial.println(button_selected);

    
    if(button_selected == 2){
      if(last_button_selected != button_selected){
        tft.fillRoundRect(64.5, 138, 88, 29,5, TFT_WHITE);
        tft.setCursor(100, 149);
        tft.print("No");
        last_button_selected = button_selected;
      }
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.fillRoundRect(167,138, 88, 29,5, TFT_WHITE);
      tft.setCursor(202, 149);
      tft.print("Yes");

      delay(200); 

      tft.fillRoundRect(167,138, 88, 29,5, TFT_ORANGE);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.setCursor(202, 149);
      tft.print("Yes");
    } else if(button_selected == 1){
      if(last_button_selected != button_selected){
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.fillRoundRect(167,138, 88, 29,5, TFT_WHITE);
        tft.setCursor(202, 149);
        tft.print("Yes");

        last_button_selected = button_selected;
      }
      tft.fillRoundRect(64.5, 138, 88, 29,5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(100, 149);
      tft.print("No");

      delay(200);

      tft.fillRoundRect(64.5, 138, 88, 29,5, TFT_ORANGE);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.setCursor(100, 149);
      tft.print("No");
    }

    click = digitalRead(20)==0?true:false;
  }

  click = 0;

  if(button_selected == 2){
    switch (ui){
      case 1: 
        interface = 2;
        study_time = timer;
        timer = 0;
        UIControl(configBreack());
        break;
      case 2:
        interface = 3;
        breack_time = timer;
        timer = 0;
        UIControl(configCicles());
        break;
      case 3: 
        interface = 4;
        cicles = cicles_choose;
        cicles_choose = 0;
        UIControl(configPomodoro());
        break;
    }
  } else if(button_selected == 1){
    interface = interface;
    UIControl(ui);
  }
} 



