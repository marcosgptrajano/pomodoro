#include "Arduino.h"
#include "Pomodoro.h"
#include <vector> 

Pomodoro::Pomodoro(int study, int breack, int cicles, int BUZZER_PIN){

  pinMode(BUZZER_PIN, OUTPUT);
  buzzer = BUZZER_PIN;
  studyTime = study;
  breackTime = breack;
  cycles = cicles;

  currentMillis = 0;
  currentRep = 0;
  time = "";
  timePassed = 0;
  cc = 0;
  state = "Trasition";

  if(cicles > 1 ){
    timeConfig.resize(cicles + (cicles -1) + (cicles+1));
    timeConfig[0] = 0.11;
    for( int cc = 2; cc<=(cicles*2)+1; cc+=2){
    timeConfig[cc] = 0.11;
    }
    for(int cc = 1; cc <= (cicles*2)+1 ; cc+=4){
    timeConfig[cc] = studyTime;
    }
    for(int cc = 3; cc <= (cicles*2)+1  ; cc+=4){
    timeConfig[cc] = breackTime;
    }
  }else{
    timeConfig.resize(cicles + 1);
    timeConfig[0] = 0.11;
    timeConfig[1] = studyTime;
  }


}

void Pomodoro::playAlarm(){
  for(int c = 0; c <= 3; c++){
    tone(buzzer, 200);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(buzzer, 400);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(buzzer, 600);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(buzzer, 800);
    delay(100); // Wait for 1000 millisecond(s)
    
    tone(buzzer, 1000);
    delay(100); // Wait for 1000 millisecond(s)
    
    noTone(buzzer);
    delay(1000);
  }
}

void Pomodoro::timer(){
  Serial.println("-------------------------------");
  Serial.println("Iniciando o timer....");
  playAlarm();
  for(currentRep = 1 ; currentRep <= cycles ; currentRep++){
    studyTimer();
    playAlarm();
    if(currentRep < cycles){
      breackTimer();
      playAlarm();
    }
  }
  Serial.println("------ YOU FINISH -------");
}

void Pomodoro::studyTimer(){
  Serial.println("["+ String(currentRep)  + "/"+ String(cycles) + "]"+ "ESTUDO - " + String(studyTime)+ ":00");
  currentMillis = millis();
  myTime = (millis() - currentMillis) / 1000;
  int lastSecond = -1;
  while(myTime < studyTime * 60){
    myTime = (millis() - currentMillis) / 1000;

    if (myTime >= studyTime * 60) break;

    if(myTime != lastSecond){ 
      lastSecond = myTime;
      int nowMinutes = (studyTime - 1) - myTime / 60;
      int nowSeconds = 59 - (myTime % 60);
    
      Serial.print("Timer:");
      
      time = String(nowMinutes) + ":" + String(nowSeconds);
      Serial.println(time);
    }
  }
}

void Pomodoro::breackTimer(){
  Serial.println("["+ String(currentRep)  + "/"+ String(cycles - 1) + " ]"+ "PAUSA - " + String(breackTime)+":00");
  currentMillis = millis();
  myTime = (millis() - currentMillis) / 1000;

  int lastSecond = myTime;
  while(myTime < breackTime * 60){
    myTime = (millis() - currentMillis) / 1000;


    if (myTime >= breackTime * 60) break;

    if(myTime != lastSecond){ 
      lastSecond = myTime;
      int nowMinutes = (breackTime - 1) - myTime / 60;
      int nowSeconds = 59 - (myTime % 60);
      
      time = String(nowMinutes) + ":" + String(nowSeconds); 
      Serial.print("Timer:");
      Serial.println(time);
    }
  }
}


String Pomodoro::getTimer(float tt){
  float tempoRestanteBloco = 0;
    int blocoAtual = 0;

    while (blocoAtual < timeConfig.size() && tt >= timeConfig[blocoAtual]) {
        tt -= timeConfig[blocoAtual]; 
        blocoAtual++;
    }

    if (blocoAtual >= timeConfig.size()) {
        return "0:00";
    }

    tempoRestanteBloco = timeConfig[blocoAtual] - tt;

    int minutos = int(tempoRestanteBloco);
    int segundos = int((tempoRestanteBloco - minutos) * 60);

    String secStr = (segundos < 10) ? "0" + String(segundos) : String(segundos);

    setState(blocoAtual);
    
    return minutos>=10?String(minutos):"0"+String(minutos) + ":" + secStr; 
  // cc = float(tt);
  // totalTime = (studyTime * cycles) + (breackTime * (cycles - 1));
  // int neededTime = totalTime - timePassed;

  // cc = cc - studyTime;
  // while(cc > 0){
  //   cc = cc - studyTime;
  //   if(cc > 0){
  //     cc = cc- breackTime;
  //     if( cc == 0){
  //       cc = cc - studyTime;
  //     }
  //   } else if (cc == 0){
  //      cc = cc - breackTime;
  //   }
  //}

  // String minutes = String(int(-cc));
  // String seconds = String (((-cc) - int(-cc)) * 60);
  // return minutes + ":" + seconds;
  
}

int Pomodoro::getTotalTime(){
  float total = 0;
  for(float t : timeConfig){
    total += t;
  }
  return total;
}

void Pomodoro::setState(int b){
  if(b%2 == 0){
    state = "Trasition";
  } else if(b%4 == 1){
    state = "Study Time";
  } else if(b%4 == 3){
    state = "Break Time";
  }
  
}

String Pomodoro::getState(){
  return state;
}

