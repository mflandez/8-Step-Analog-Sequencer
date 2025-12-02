// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>



// pin Mode
Button mode = Button();
int buttonPinMode=12;
bool ModeState=LOW;

// pin Reset
Button reset = Button();
int buttonPinReset=13;
bool ResetState=LOW;

//Impulsion, Horloge Externe
Button impulse = Button();
int jackPinImpulse = 7;
bool ImpulseState=LOW;


// pot Bpm
int potInBpm = A1;
int valeurBPM = 500;
float B =120;
float constraint=0;

// pot longueur
int potInLongueur = A2;
int valeurLongueur=8;
int nombrePas = 8;

// Timing
unsigned long eventInterval = 0;
unsigned long previousTime = 0;

unsigned long eventIntervalImpulse = 30;
unsigned long previousImpulseTime = 0;
 

// compteur dans la sequence
int sequencePas = 1;

// selecteur du multiplexeur
int pin_Out_S0=8;
int pin_Out_S1=9;
int pin_Out_S2=10;

// trig somme out
int pin_Out_TRIG=4;

//millis



void setup() {
  // put your setup code here, to run once:
  //Mode
    mode.attach(buttonPinMode, INPUT);
    mode.interval(10);
    mode.setPressedState(LOW);

  //Reset
    reset.attach(buttonPinReset, INPUT);
    reset.interval(10);
    reset.setPressedState(LOW);

  //Impulse
    impulse.attach(jackPinImpulse, INPUT);
    impulse.interval(10);
    impulse.setPressedState(LOW);

  //Bpm
  //Longueur  
  //Selecteur du multiplexeur
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  pinMode(pin_Out_TRIG, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long currentImpulseTime = millis();
//digitalWrite(pin_Out_TRIG, LOW);

  // Bouton de selection de mode digital en entrée D12
    // antirrebonds
    // maitre ou esclave
  // Mode
  //ModeState = 0 Master; ModeState=1 Slave
    mode.update();
    if (mode.pressed()) {
      ModeState = !ModeState;
      Serial.print("change1");
      Serial.println(ModeState);
    }

  // Bouton de RESET digital en entrée D13
    // Si actionné, on met le compteur dans le sequence a 1
    // antirrebonds
  // Reset  
    reset.update();
    if (reset.pressed()) {
      ResetState = !ResetState;
      Serial.print("flippper");
      Serial.println(ResetState);
   // sequence mis a zero
      sequencePas=-1;

    }

  // Imuplsion pour faire avancer la sequence en entree A0
  // Si superieur a 3.3 V (calcule a faire) fait +1 sur le compteur
  // Antirrebonds 10 ms


  // Horloge interne
  // Potentiomentre pour choisir le delay de temps 
  // Entrée A1
  //  180 bpm = 0.3333; 
  //  120 bpm = 500
  //  60 bpm = 1; 
  //  Dans un variable delai
  // Lorsque delai == temps actuel-temps precedent, on fait augmenter le compteur de sequence


  // Bpm
  valeurBPM = analogRead(potInBpm);
  //B = valeurBPM *(180.f/1023.f);
  constraint = map(valeurBPM, 0, 1023, 60, 180);
  eventInterval=60000UL/constraint;
//   Serial.println(constraint);
//Serial.println(eventInterval);


  // potentionmetre pour choisir la longueur de la sequence en entrée A2
  // 1 jusuq'a 8 pas  
  // attends jusqu'a l'impulsion suivante
  //Longueur
  valeurLongueur = analogRead(potInLongueur);
  nombrePas = map(valeurLongueur, 0, 1023, 0, 7);
  // Serial.println(nombrePas+1);

  // Si mode master (0) utilise millis()
if ( ModeState == LOW){  
 unsigned long currentTime = millis();
 
 if(currentTime - previousTime >= eventInterval){
    digitalWrite(pin_Out_TRIG, HIGH);
    Serial.println(eventInterval);
    //Serial.println(currentTime);
    Serial.println("rapido");
    previousTime = currentTime;
    // Si mode externe utilise impulsion
    advanceSequence();
    }
} else if (ModeState == HIGH){
  // Impulsion  
    impulse.update();
    if (impulse.pressed()){
      ImpulseState = !ImpulseState;
      digitalWrite(pin_Out_TRIG, HIGH);
      Serial.print("blabla");
      Serial.println(ImpulseState);
      advanceSequence();
    }
}

  if(currentImpulseTime - previousImpulseTime >= eventIntervalImpulse){
    digitalWrite(pin_Out_TRIG, LOW);
    previousImpulseTime = currentImpulseTime;
  } 
 
    
  switchSequence();
 }


 //ROUTINES

 
 void advanceSequence(){
    if((sequencePas<nombrePas)){
    sequencePas++;
  } else if((sequencePas == nombrePas) || (sequencePas>nombrePas)) {
    sequencePas=0;
    } 
 }

 void switchSequence(){
     // do something different depending on the range value:
  switch (sequencePas) {
    case 0:    // step 1
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
     // Serial.println("S1");
      break;
    case 1:    // step 2
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S2");
      break;
    case 2:    // step 3
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S3");
      break;
    case 3:    // step 4
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S4");
      break;
    case 4:    // step 5
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S5");
      break;   
    case 5:    // step 6
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S6");
      break;     
    case 6:    // step 7
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
      //Serial.println("S7");
      break;
    case 7:    // step 8
    digitalWrite(pin_Out_S0, HIGH && (sequencePas & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (sequencePas & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (sequencePas & B00000100));
     // Serial.println("S8");
      break;                
  }
  delay(1);        // delay in between reads for stability

  }
