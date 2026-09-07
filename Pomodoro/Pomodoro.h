#ifndef Pomodoro_h
#define Pomodoro_h

#include <vector> 
#include "Arduino.h"

class Pomodoro{
  public:
    Pomodoro(int study, int breack, int cicles, const int BUZZER_PIN);
    void timer();
    String getTimer(float tt);
    int getTotalTime();
    String getState();
  private:
    int studyTime;
    int breackTime;
    int cycles;

    unsigned long currentMillis;
    int currentRep;
    unsigned long myTime;
    int buzzer;

    String studyTimeS;
    String breackTimeS;
    String cyclesS;

    void playAlarm();
    void studyTimer();
    void breackTimer();


    String time;
    unsigned long timePassed;
    float cc;
    std::vector<int> timeConfig;
    String state;

    void setState(int b);

};

#endif