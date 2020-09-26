
int pinDP = 8;
int pinB = 7;
int pinC = 6;
int pinD = 5;
int pinE = 4;
int pinF = 3;
int pb = 2;
int pinG = 1;
int pinA = 0;
int D1 = 12;
int D2 = 11;
int D3 = 10;
int D4 = 9;
volatile int state = LOW;



int dig1 = 0;
int dig2 = 0;
int dig3 = 0;
int dig4 = 0;



void setup() {
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
  pinMode(pinD,OUTPUT);
  pinMode(pinE,OUTPUT);
  pinMode(pinF,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinDP,OUTPUT);
  pinMode(pb,INPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);

  

  cli();//stops all interupts
  TCCR1A = 0;//set TCCR1A register = 0
  TCCR1B = 0;//set TCCR1B register = 0
  TCNT1  = 0;//starting counter value
  OCR1A = 624;// time when the timer interupt is tripped
  TCCR1B |= (1 << WGM12);//timer1 turn on CTC (compare match)
  TCCR1B |= (1 << CS12);//prescaler of 256
  TIMSK1 |= (1 << OCIE1A);//enable timer compare interrupt
  sei();//allows for interupts again

  
  attachInterrupt(0,stateChange,FALLING);
  
}


void loop() {

  if(dig1!=0){
    selectDig(1);
    dispNum(dig1);
    digitalWrite(pinDP, HIGH);
    delay(1);
  }

  selectDig(2);
  dispNum(dig2);
  digitalWrite(pinDP, LOW);
  delay(1);

  
  selectDig(3);
  dispNum(dig3);
  digitalWrite(pinDP, HIGH);
  delay(1);
  
  selectDig(4);
  dispNum(dig4);
  digitalWrite(pinDP, HIGH);
  delay(1);
  

}


void selectDig(int dig){

  switch (dig) {
    case 1:
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    break;

    case 2:
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    break;

    case 3:
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    break;

    case 4:
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    break;

    default:
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    break;
    
  }
}


void dispNum (int num) {

  switch (num) {
    case 1:
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
    break;
    
    case 2:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, LOW);
    break;

    case 3:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, LOW);
    break;

    case 4:
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
    break;

    case 5:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
    break;

    case 6:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
    break;

    case 7:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
    break;

    case 8:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
    break;

    case 9:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
    break;

    case 0:
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, HIGH);
    break;
    
    default:
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
    break;
  }
}


void stateChange(){
  delay(20);
  state = !state;
}


ISR(TIMER1_COMPA_vect) {

  if(state==HIGH){

    dig4++;
    
    if (dig4>9){
      
      dig3++;
      dig4=0;
      
      if(dig3>9){
        
        dig2++;
        dig3=0;
        
        if (dig2>9){
          
          dig1++;
          dig2=0;
          
        }
      }
    }
  }
}
