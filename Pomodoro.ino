String studyTimeS = String(0);
String usermessage = String(0);
String breackTimeS = String(0);
int studyTime = 0;
int breackTime = 0;
int cycles = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  config();
  
}

void loop() {
  
  

}

void config(){
  Serial.println("----------- [POMODORO] ----------");
  studyConfig();
  breackConfig();

}

void studyConfig(){
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
  }else{
    usermessage = String(0);
    studyConfig();
  }
}

void breackConfig(){
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
    breackTimeS = breackTimeS.toInt();
  }else{
    usermessage = String(0);
    breackConfig();
  }
}