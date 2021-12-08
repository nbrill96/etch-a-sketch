
const int numReadingsX = 10;
const int numReadingsY = 10;
int readingsX[numReadingsX];      // the readings from the analog input
int readingsY[numReadingsY];
int readIndexOfX = 0;              // the index of the current reading
int readIndexOfY = 0; 
int totalX = 0;                  // the running total
int totalY = 0; 
int averageX = 0; 
int averageY = 0; 

const int potPin = A0;
const int potPin2 = A1;
int potVal = 0;
int potVal2 = 0;
int inByte = 0;

void setup() {

  pinMode(potPin, INPUT);
  pinMode(potPin2, INPUT);
  
  Serial.begin(9600);

  for (int thisReading = 0; thisReading < numReadingsX; thisReading++) {
    readingsX[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numReadingsY; thisReading++) {
    readingsY[thisReading] = 0;
  }

//  establishContact();

}

void loop() {

//if (Serial.available() > 0){
  inByte = Serial.read();
  potVal = analogRead(potPin);
  potVal2 = analogRead(potPin2);

  potVal = map(potVal, 0, 1023, 0, 600);
  potVal2 = map(potVal2, 0, 1023,0,600);

//smoothing for X
  totalX = totalX - readingsX[readIndexOfX];
  readingsX[readIndexOfX] = potVal;
  totalX = totalX + readingsX[readIndexOfX];
  readIndexOfX = readIndexOfX + 1;
  if (readIndexOfX >= numReadingsX) {
    readIndexOfX = 0;
  }
  averageX = totalX / numReadingsX;

//smoothing for Y
totalY = totalY - readingsY[readIndexOfY];
  readingsY[readIndexOfY] = potVal2;
  totalY = totalY + readingsY[readIndexOfY];
  readIndexOfY = readIndexOfY + 1;
  if (readIndexOfY >= numReadingsY) {
    readIndexOfY = 0;
  }
  averageY = totalY / numReadingsY;

//sensor values
  Serial.print(averageX);
  Serial.print(",");
  Serial.println(averageY);
  delay(50);
  



//}
}

//void establishContact(){
//  while(Serial.available() <= 0){
//    Serial.println("0,0");
//    delay(300);
//  }
//}
