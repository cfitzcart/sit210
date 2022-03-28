// ------------
// LED MORSE CODE NAME
// ------------

/*-------------
March 2022
C. Fitzgerald-Carter
ID: 218447197

This program will blink an led on and off to spell the name "Cat" in morse code.
It blinks the D7 LED on a Particle device as well as an LED wired to D0 simultaneously.

Morse code is made up of dots and dashes:
> A dot is ONE unit and a dash is THREE units
> The space between the parts of a letter is ONE unit
> The space between letters is THREE units
> The space between words is SEVEN units

-------------*/


int led1 = D0; // Instead of writing D0 over and over again, we'll write led1


int led2 = D7; // Instead of writing D7 over and over again, we'll write led2


void setup() {

  // Declare LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}


void loop() {
  // Spells the letters C-A-T in a loop

  // letter "c" 
  write_c();
  
  // space between letters : THREE units
  delay(600);
  
  write_a();
  
  // space between letters : THREE units
  delay(600);
  
  write_t();
  
  // space between words : SEVEN units
  delay(1400);
}

void write_a(){

  // "a" is .-

  //short flash : ONE UNIT
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  
  delay(200);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  delay(200);
  
  // long flash : THREE units
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  delay(600);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void write_c(){

  // "C" is -.-.
  //long flash : THREE UNITS
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  delay(600);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  delay(200);
  
  //short flash : ONE UNIT
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  
  delay(200);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  delay(200);

 //long flash : THREE UNITS
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  delay(600);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  delay(200);
  
  //short flash : ONE UNIT
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  
  delay(200);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void write_t(){

  // "t" is -
  // long flash : THREE units
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  delay(600);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}
