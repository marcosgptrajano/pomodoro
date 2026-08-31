#include <TFT_eSPI.h> // Biblioteca do display+// Arquivo com a sua array de pixels

TFT_eSPI tft = TFT_eSPI();

int item_selected = 2;
int last_item_selected = 2;
int j_x = 0;
int j_y = 0;
bool j_bt = false;

int timer = 0;
int last_timer = 0;

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
  start();
}

void loop() {

  joystick();
  select(item_selected);

}

void start(){
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

void joystick(){
  j_x = analogRead(27);
  j_bt = digitalRead(20)==0?true:false;
  
  //Serial.println("x: " + String(j_x)+ "y: " + String(j_y) + "bt: " + String(j_bt));
  

  if(j_x > 600){
    if(item_selected < 3) {
      item_selected++;
    } 
  } else if(j_x < 400) {
    if(item_selected > 1){
      item_selected--;
    } 
  }

  if(item_selected == 2 && j_bt){
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
  }

  Serial.println("item_selected: " + String(item_selected) + " button state: " + String(j_bt) +" Timer: " + String(timer));
  delay(200);
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

void select(int i){
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
    tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");

    delay(200);

    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.setTextSize(15);
    tft.setCursor(55, 98);
    tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");


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
        tft.setCursor(55, 98);
        tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");

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
        tft.setCursor(55, 98);
        tft.print( timer<10?"0" + String(timer)+ ":00":String(timer)  + ":00");

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


