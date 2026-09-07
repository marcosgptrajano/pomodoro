#include <TFT_eSPI.h> // Biblioteca do display+// Arquivo com a sua array de pixels
#include "Pomodoro.h"

TFT_eSPI tft = TFT_eSPI();


int item_selected = 2;
int last_item_selected = 2;
int j_x = 0;
int j_y = 0;
bool j_bt = false;

int timer = 1;
int last_timer = 0;
int cycles_choose = 0;
int last_cycles = 0;

int interface = 1;

int study_time = 1;
int break_time = 1;
int cycles = 1;

double myTime;
double currentMillis;

bool skip = false;
bool stop = false;
int state = 0;

float timeStopped = 0;
bool isStopped = false;

#define BUZZER 2

void confirmUI(int item, int ui);
bool confirm();
void UIControl(int id);
void displayConfigTime(int t);
void displayConfigCicle(int t);


void setup() {
  pinMode(20, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
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
  tft.print("Break time");


  //Item03
  tft.fillRoundRect(214, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setCursor(243, 30);
  tft.print("Cycles");

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

void configBreakUI(){
  configStudyUI();

  tft.fillRoundRect(7, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setTextSize(1.9);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(24, 30);
  tft.print("Study time");

  tft.setTextColor(TFT_BLACK, TFT_DARKCYAN);
  tft.fillRoundRect(110, 19, 99, 29, 5.5, TFT_DARKCYAN);
  tft.setCursor(127, 30);
  tft.print("Break time");


}

void configCyclesUI(){
  configBreakUI();

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.fillRoundRect(110, 19, 99, 29, 5.5, TFT_WHITE);
  tft.setCursor(127, 30);
  tft.print("Break time");

  tft.setTextColor(TFT_BLACK, TFT_DARKCYAN);
  tft.fillRoundRect(214, 19, 99, 29, 5.5, TFT_DARKCYAN);
  tft.setCursor(243, 30);
  tft.print("Cycles");

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
        if(timer < 90){
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
    
    } else if(interface == 3){
        while(j_bt){j_bt = digitalRead(20)==0?true:false;}
        tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
        tft.setTextSize(15);
        tft.setTextColor(TFT_ORANGE, TFT_RED);
        tft.setTextSize(15);
        tft.setCursor(114, 98);
        tft.print(  timer<10?"0" + String(cycles_choose):String(timer));
        last_cycles = cycles_choose;
        while(!j_bt){
        j_bt = digitalRead(20)==0?true:false;
        j_y = analogRead(26);
        if(j_y >600){
        if(cycles_choose < 60){
          cycles_choose++;
          delay(100);
        }
        
        } else if( j_y < 400){
          if(cycles_choose > 1){
            cycles_choose--;
            delay(100);
          }
        }
        displayConfigCicle(cycles_choose);
        }
    } else{ 
      while(j_bt){ j_bt = digitalRead(20)==0?true:false; }
      skip = true;
    }
}

  if(item_selected == 3 && j_bt){
    Serial.print("Next");
    item_selected = 2;
    confirmUI(selection(2), interface);
  }

  if(interface > 1 && interface < 4){
    if(interface > 2){
      if(item_selected == 1 && j_bt){
      item_selected = 2;
      interface--;
      timer = break_time;
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
  
  }  else if (interface == 4){
     if(item_selected == 1 && j_bt){
      while(j_bt){ j_bt = digitalRead(20)==0?true:false; }
      isStopped = true;
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

  if(t != last_cycles){
    tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
    tft.setTextSize(15);
    tft.setTextColor(TFT_ORANGE, TFT_RED);
    tft.setTextSize(15);
    tft.setCursor(114, 98);
    tft.print( cycles_choose<10? "0" + String(cycles_choose): ""+ String(cycles_choose));
    last_cycles = t;
  }
  

}

void selectAnimation(int i){
  if (interface < 4){
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
      tft.print( cycles_choose<10? "0" + String(cycles_choose): ""+ String(cycles_choose));
    } else{
      tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");
    }
    

    delay(200);

    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.setTextSize(15);
    
    if(interface == 3){
      tft.fillRect(47.6, 64.5, 225, 105, TFT_RED);
      tft.setCursor(110, 98);
      tft.print( cycles_choose<10? "0" + String(cycles_choose): ""+ String(cycles_choose));
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
        tft.print( cycles_choose<10? "0" + String(cycles_choose): ""+ String(cycles_choose));
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
          tft.print( cycles_choose<10? "0" + String(cycles_choose): "" + String(cycles_choose));
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
  } else{
    if(i == 2){
      if(item_selected != last_item_selected){
        tft.setTextSize(2);
        tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
        tft.setCursor(43, 180.6);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.print("Pause");
      }
      tft.setTextSize(2);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.fillRoundRect(191.8, 172.2, 99.4, 28.9, 5.5, TFT_ORANGE);
      tft.setCursor(218, 180.6);
      tft.print("Skip");

      
    } else if( i == 1){
      if(item_selected != last_item_selected){
      tft.setTextSize(2);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.fillRoundRect(191.8, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
      tft.setCursor(218, 180.6);
      tft.print("Skip");
      }

      tft.setTextSize(2);
      tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_ORANGE);
      tft.setCursor(43, 180.6);
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.print("Pause");

    }
  }
}

void pomodoroUI(){
  tft.fillScreen(TFT_RED);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_RED);
  tft.setTextSize(3);
  tft.setCursor(72.3, 45);
  tft.print("Study Time");

  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setCursor(55, 90);
  tft.setTextSize(8);
  tft.print(study_time>=10?String(study_time) + ":00":"0"+ String(study_time) + ":00");

  tft.setTextSize(2);
  tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
  tft.setCursor(43, 180.6);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.print("Pause");

  tft.fillRoundRect(191.8, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
  tft.setCursor(218, 180.6);
  tft.print("Skip");

}

void breakUI(){
  tft.fillScreen(TFT_DARKCYAN);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);
  tft.setTextColor(TFT_ORANGE, TFT_DARKCYAN);
  tft.setTextSize(3);
  tft.setCursor(72.3, 45);
  tft.print("Break Time");

  tft.setTextColor(TFT_WHITE, TFT_DARKCYAN);
  tft.setCursor(55, 90);
  tft.setTextSize(8);
  tft.print(break_time>=10?String(break_time) + ":00":"0"+ String(break_time) + ":00");

  tft.setTextSize(2);
  tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
  tft.setCursor(43, 180.6);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.print("Pause");

  tft.fillRoundRect(191.8, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
  tft.setCursor(218, 180.6);
  tft.print("Skip");

}

void transitionUI(){
  tft.fillScreen(TFT_ORANGE);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_ORANGE);
  tft.setTextSize(3);
  tft.setCursor(72.3, 45);
  tft.print("Start in...");

  tft.setTextColor(TFT_WHITE, TFT_ORANGE);
  tft.setCursor(55, 100);
  tft.setTextSize(8);
  tft.print("00:05");
  playAlarm();

}

void finishUI(){

  tft.fillScreen(TFT_RED);
  tft.drawRect(5, 12, 310, 216, TFT_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setCursor(29.6, 67.6);
  tft.print("Congrulations");
  tft.setCursor(29.6, 104.5);
  
  tft.print("do you finish!");

  tft.setTextSize(2);
  tft.setCursor(98.8, 150.6);
  tft.setTextColor(TFT_ORANGE, TFT_RED);
  tft.print("Click to reset");

  playAlarm();

  while(!j_bt){
  j_bt = digitalRead(20) == 0 ? true : false; 
  }

  UIControl(configStudy());



}

int configStudy(){
  return 1;
}
int configBreak(){
  return 2;
}
int configCycles(){
  return 3;
}

int configPomodoro(){
  return 4;
}

void UIControl(int id){
  switch(id){
    case 1:
      interface = 1;
      study_time = 1;
      break_time = 1;
      cycles = 1;
      timer = 1;
      cycles_choose = 1;
      configStudyUI();
      while(!confirm()){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 2:
      configBreakUI();
      while(true){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 3:
      configCyclesUI();
      while(!confirm()){
        selection(3);
        interact();
        selectAnimation(item_selected);
      }
      break;
    case 4:
      transitionUI();
      Pomodoro pomodoro(study_time, break_time, cycles);
      timeStopped = 0;
      currentMillis = millis();
      
      myTime = (((millis() - currentMillis) / 1000.0 / 60.0) - timeStopped) ; 
      state = 0;
      int lastState = state;
      
      
      while(myTime + pomodoro.getSkip() < pomodoro.getTotalTime()){

        String currentTimerStr = pomodoro.getTimer(myTime);
        Serial.println(currentTimerStr);

        if(pomodoro.getState() == "Trasition"){
          state = 0;
        } else if(pomodoro.getState() == "Study Time"){ 
          state = 1;
        } else {
          state = 2;
        }

        if(state == 1 || state == 2){
          selection(2);
          interact();
          if(skip == true){
            pomodoro.Skip();
            skip = false;
          }
          if(isStopped == true){
            tft.setTextSize(2);
            tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_ORANGE);
            tft.setCursor(43, 180.6);
            tft.setTextColor(TFT_BLACK, TFT_ORANGE);
            tft.print("Resume");
            
            float start = myTime;
            float end;
            while(!j_bt){
              j_bt = digitalRead(20) == 0 ? true : false;
              end = (((millis() - currentMillis) / 1000.0) / 60.0); 
            }

            timeStopped += (end - start);
            isStopped = false; 
            
            tft.setTextSize(2);
            tft.fillRoundRect(24, 172.2, 99.4, 28.9, 5.5, TFT_WHITE);
            tft.setCursor(43, 180.6);
            tft.setTextColor(TFT_BLACK, TFT_WHITE); 
            tft.print("Pause");
          }
            
          selectAnimation(item_selected);
        }

        // 3. Atualiza o tempo decorrido para a próxima iteração
        myTime = (((millis() - currentMillis) / 1000.0) / 60.0) - timeStopped;
        
        if(state == 0){
          tft.setTextColor(TFT_WHITE, TFT_ORANGE);
        } else if(state == 1){
          tft.setTextColor(TFT_WHITE, TFT_RED);
        } else{
          tft.setTextColor(TFT_WHITE, TFT_DARKCYAN);
        }
        
        if(state == 0){
          tft.setCursor(55, 100);
        } else{
          tft.setCursor(55, 90);
        }
        
        tft.setTextSize(8);
        tft.print(currentTimerStr);

        if(state == 0){
          tft.setTextColor(TFT_WHITE, TFT_ORANGE);
        } else if (state == 1){
          tft.setTextColor(TFT_ORANGE, TFT_RED);
        } else{
          tft.setTextColor(TFT_ORANGE, TFT_DARKCYAN);
        }
        tft.setTextSize(3);
        tft.setCursor(72.3, 45);
        tft.print(pomodoro.getState());

        if(state != lastState){
          if(state == 0){
            transitionUI();
          } else if (state == 1){
            pomodoroUI();
          } else{
            breakUI();
          }
        }

        lastState = state;
        delay(1000);
      }

      finishUI();
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
    tft.println("the number of cycles to"+ String(cycles_choose) + "?");
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
        timer = 1;
        UIControl(configBreak());
        break;
      case 2:
        interface = 3;
        break_time = timer;
        timer = 1;
        UIControl(configCycles());
        break;
      case 3: 
        interface = 4;
        cycles = cycles_choose;
        cycles_choose = 1;
        UIControl(configPomodoro());
        break;
    }
  } else if(button_selected == 1){
    interface = interface;
    UIControl(ui);
  }
} 


void playAlarm(){

  for(int c = 0; c <= 3; c++){
    tone(BUZZER, 200);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(BUZZER, 400);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(BUZZER, 600);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(BUZZER, 800);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(BUZZER, 1000);
    delay(100); // Wait for 1000 millisecond(s)
    
    noTone(BUZZER);
    delay(1000);
  }
}

