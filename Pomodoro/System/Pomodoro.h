#ifndef Pomodoro_h
#define Pomodoro_h

#include <vector> 
#include "Arduino.h"

class Pomodoro{
  public:
    Pomodoro(int study, int breack, int cicles);
    void timer();
    String getTimer(float tt);
    float getTotalTime();
    String getState();
    void Skip();
    void Stop();
    float getSkip();
  private:
    int studyTime;
    int breackTime;
    int cycles;

    unsigned long currentMillis;
    int currentRep;
    unsigned long myTime;

    String studyTimeS;
    String breackTimeS;
    String cyclesS;

    void playAlarm();
    void studyTimer();
    void breackTimer();


    String time;
    unsigned long timePassed;
    float cc;
    std::vector<float> timeConfig;
    String state;

    void setState(int b);

    float skip;
    float tempoRestanteBloco;

};

#endif