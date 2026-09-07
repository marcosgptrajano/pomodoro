#include "Arduino.h"
#include "Pomodoro.h"
#include <vector> 

Pomodoro::Pomodoro(int study, int breack, int cicles){
  studyTime = study;
  breackTime = breack;
  cycles = cicles;

  currentMillis = 0;
  currentRep = 0;
  time = "";
  timePassed = 0;
  cc = 0;
  state = "Trasition";

  skip = 0;
  tempoRestanteBloco = 0;


  if(cicles > 1 ){
    // 2 blocos para o 1º ciclo (T, S) + 4 blocos para cada ciclo adicional (T, B, T, S)
    int totalBlocks = 2 + (cicles - 1) * 4;
    timeConfig.resize(totalBlocks);
    
    int index = 0;
    // 1º Ciclo: Transição e Estudo inicial
    timeConfig[index++] = 0.11; 
    timeConfig[index++] = studyTime; 
    
    // Demais ciclos: Transição -> Pausa -> Transição -> Estudo
    for(int i = 1; i < cicles; i++){
      timeConfig[index++] = 0.11;       // Transição para a pausa
      timeConfig[index++] = breackTime; // Pausa
      timeConfig[index++] = 0.11;       // Transição para o próximo estudo
      timeConfig[index++] = studyTime;  // Estudo
    }
  }else{
    timeConfig.resize(2);
    timeConfig[0] = 0.11;
    timeConfig[1] = studyTime;
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
    tempoRestanteBloco = 0;
    int blocoAtual = 0;
    float timeWithSkip = tt + skip;

    while (blocoAtual < timeConfig.size() && timeWithSkip >= timeConfig[blocoAtual]) {
        timeWithSkip -= timeConfig[blocoAtual]; 
        blocoAtual++;
    }

    if (blocoAtual >= timeConfig.size()) {
        return "00:00";
    }

    tempoRestanteBloco = timeConfig[blocoAtual] - timeWithSkip;

    int minutos = int(tempoRestanteBloco);
    int segundos = int((tempoRestanteBloco - minutos) * 60);

    // Cria a string dos segundos com zero à esquerda se for menor que 10
    String secStr = (segundos < 10) ? "0" + String(segundos) : String(segundos);
    
    // Cria a string dos minutos com zero à esquerda se for menor que 10
    String minStr = (minutos < 10) ? "0" + String(minutos) : String(minutos);

    setState(blocoAtual);
    
    // Junta as duas partes perfeitamente: "45:59", "09:05", etc.
    return minStr + ":" + secStr; 
}

float Pomodoro::getTotalTime(){
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

void Pomodoro::Skip(){
  if(state == "Study Time" || state == "Break Time"){
    // Aplica o pulo do bloco atual e ajusta o relógio de atalho
    skip += tempoRestanteBloco;
  }
}

float Pomodoro::getSkip(){
  return skip;
}



