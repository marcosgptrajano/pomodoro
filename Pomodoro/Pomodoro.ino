
String studyTimeS = String(0);
String usermessage = String(0);
String breackTimeS = String(0);
String cyclesS = String(0);
String totalTimeS = String(0);

int studyTime = 0;
int breackTime = 0;
int cycles = 0;
int totalTime = 0;

unsigned long currentMillis = 0;
int currentRep = 0;
unsigned long myTime;

const int buzzer = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  config();
  currentMillis = millis();
  
}

void loop() {

  pomodoro();


}

void config(){
  while (!Serial) {
    delay(10); 
  }
  Serial.println(R"rawliteral(

                                                                      
       ▒                                                          
  ▒▒   ▒    ▒                                                     
   ▒▒▓▓▒▓▓▒▒     ____                           _                 
 ▓▓▓ ▒▒▒▒▒ ▓▓▓   | _ \ ___  _ __ ___   ___   __| | ___  _ __ ___  
▓             ▓  ||_) / _ \| '_ ` _ \ / _ \ / _` |/ _ \| '__/ _ \ 
▓             ▓  | __/ (_) | | | | | | (_) | (_| | (_) | | | (_) |
▓▓▓▓       ▓▓▓▓  ||   \___/|_| |_| |_|\___/ \__,_|\___/|_|  \___/ 
    ▓▓▓▓▓▓▓               

    Desenvolvido por :Marcos Trajano
                                                                                
════════════════════════════════════════════════════════════════════════════════)rawliteral");
  Config();

}

void studyConfig(){
  while(true){
  Serial.println("De quanto tempo vai ser o periodo de estudos (Em minutos):");

  while(Serial.available() == 0){}

  studyTimeS = Serial.readString();
  studyTimeS.trim();

  Serial.println("Quer estudar por: " + studyTimeS + " Minutos? [Y/N]");

  while((Serial.available() == 0)){}

  usermessage = Serial.readString();
  usermessage.trim();

  if(usermessage.equalsIgnoreCase("Y")){
    usermessage = String(0);
    studyTime = studyTimeS.toInt();
    break;
  }
 }
}

void breackConfig(){
  while(true){ 
  Serial.println("Digite o tempo de suas pausas (Em minutos):");

  while(Serial.available() == 0){}

  breackTimeS = Serial.readString();
  breackTimeS.trim();

  Serial.println("Suas pausas vão ter: " + breackTimeS + " Minutos? [Y/N]");

  while((Serial.available() == 0)){}

  usermessage = Serial.readString();
  usermessage.trim();

  if(usermessage.equalsIgnoreCase("Y")){
    usermessage = String(0);
    breackTime = breackTimeS.toInt();
    break;
  }

  }
}

void cicleConfig(){
  while(true){
  Serial.println("Quantos repetições quer fazer?");

  while(Serial.available() ==0){}A
  cyclesS = Serial.readString();

  cyclesS.trim();
  Serial.println("Quer fazer: " + cyclesS + " repetições [Y/N]");

  while(Serial.available() == 0){}

  usermessage = Serial.readString();
  usermessage.trim();

  if(usermessage.equalsIgnoreCase("Y")){
    usermessage = String(0);
    cycles = cyclesS.toInt();
    break;
  } 

 }
}

void confirmConfig(){
  while(true){ 
  totalTime = ((float)(studyTime * cycles) + (breackTime * (cycles - 1)));
  int horas = totalTime /60;
  int minutos = totalTime % 60;
  totalTimeS = String(totalTime);

  Serial.println(" Então sua configuração é: ");
  Serial.println( studyTimeS + ", minutos para estudo, ");
  Serial.println( breackTimeS + " minutos para as pausas, ");
  Serial.println("com: " + cyclesS + " ciclos, ");
  Serial.println("totalizando : " + String(horas) + " horas e " + String(minutos) + " minutos de estudo [Y/N]");

  while(Serial.available() == 0){}

  usermessage = Serial.readString();
  usermessage.trim();

  if(usermessage.equalsIgnoreCase("Y")){
    usermessage = String(0);
    break;
  } 
  
  }

}

void Config(){
  pinMode(buzzer, OUTPUT);
  studyConfig();
  breackConfig();
  cicleConfig();
  confirmConfig();
}

void studyTimer(){
  
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
      
      Serial.println(String(nowMinutes) + ":" + String(nowSeconds) );
    }
  }
}

void breackTimer(){


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
      
      Serial.print("Timer:");
      Serial.println(String(nowMinutes) + ":" + String(nowSeconds) );
    }
  }

}

void pomodoro(){
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
  while(true);
}

void playAlarm(){

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