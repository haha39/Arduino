const int Red = 9;
const int Green = 10;
const int Blue = 11;
 
#define FADESPEED 5     // SPEED

#define BUTTON 2        // BUTTON
 
void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

  pinMode(BUTTON, INPUT);

  Serial.begin(9600);  //開始輸出訊息到監控視窗
}
 
void loop() {
  int sensorValue = analogRead(A0);  //讀取A0的值
  Serial.println(sensorValue);       //在監控視窗顯示讀取的值
  
  int r, g, b;
  if(sensorValue > 500) {
    // 由藍到紫
    for (r = 0; r < 256; r++) { 
      analogWrite(Red, r);
      delay(FADESPEED);
    } 
    // 由紫到紅
    for (b = 255; b > 0; b--) { 
      analogWrite(Blue, b);
      delay(FADESPEED);
    } 
    // 由紅到黃
    for (g = 0; g < 256; g++) { 
      analogWrite(Green, g);
      delay(FADESPEED);
    } 
    // 由黃到綠
    for (r = 255; r > 0; r--) { 
      analogWrite(Red, r);
      delay(FADESPEED);
    } 
    // 由綠到藍綠色
    for (b = 0; b < 256; b++) { 
      analogWrite(Blue, b);
      delay(FADESPEED);
    } 
    // 由藍綠色到藍色
    for (g = 255; g > 0; g--) { 
      analogWrite(Green, g);
      delay(FADESPEED);
    }
  }
  else {
    //stop & prtoct my eyes
    analogWrite(Red, 0);
    analogWrite(Blue, 0);
    analogWrite(Green, 0);
  }

  //delay(2000);
  
}
