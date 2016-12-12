/* 
  조이스틱 센서 쉴드 핀 구성
  조이스틱 센서 쉴드는 쉴드 형태의 보드이므로, 오렌지보드 결합 후 아래 소자 사용 시 정해진 핀을 사용하셔야 합니다.
    - Joystick X : A0
    - Joystick Y : A1
    - Joystick Button : D10
    - A Button : A2
    - B Button : A3 
    - C Button : D8
    - D Button : D9
    - Left Button : D4
    - Right Button : D5
    - Dial Variable Resistor : A4
    - Piezo Buzzer : D6 
    - Vibration Motor : D7
    - Photoresistor : A5
    - LED 1 : D2
    - LED 2 : D3 
    - LED 3 : D11 
    - LED 4 : D12
    - LED 5 : D13
*/

#include <SoftwareSerial.h>
// 조이스틱코드

// Joystick X를 A0으로 설정합니다.
const int joyStickX = A0;
// Joystick Y를 A1으로 설정합니다. 
const int joyStickY = A1;
// A Button을 A2으로 설정합니다. 
const int AButton = A2;
// B Button을 A3으로 설정합니다. 
const int BButton = A3;
// C Button을 D8으로 설정합니다.
const int CButton = 8;
// D Button을 D9으로 설정합니다. 
const int DButton = 9;
// left Button을 D4로 설정합니다. 
const int leftButton = 4; 
// right Button을 D5로 설정합니다. 
const int rightButton = 5;
// 부저를 D6으로 설정합니다.
const int piezo = 6;
// led의 핀을 설정합니다.
const int led1 = 2;
const int led2 = 3;
const int led3 = 11;
const int led4 = 12;
const int led5 = 13;
// 톤 배열 수
int numTones = 8;
// 음계 표준 주파수(4옥타브) : 도, 레, 미, 파, 솔, 라, 시, 도
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};
int ledset[] = {2,3,11,12,13};
#define DELAY 50
  
void setup(){
  // 시리얼 통신을 위해 통신 속도를 9600 bps로 설정합니다.
  Serial.begin(9600); 
  Serial1.begin(9600);
  // leftButton을 입력 핀으로 설정합니다.
  // INPUT_PULLUP은 내부에 있는 pullup저항을 쓰겠다는 말
  pinMode(leftButton, INPUT_PULLUP);
  // rightButton을 입력 핀으로 설정합니다. 
  pinMode(rightButton, INPUT_PULLUP);
  // C Button을 입력 핀으로 설정합니다.
  pinMode(CButton, INPUT_PULLUP);
  // D Button을 입력 핀으로 설정합니다.
  pinMode(DButton, INPUT_PULLUP );
  pinMode(piezo, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

}
void loop(){
  // Joystick X에서 읽어온 값을 x_Value에 저장합니다.
  int x_Value = analogRead(joyStickX);
  delay(1);
  // Joystick Y에서 읽어온 값을 y_Value에 저장합니다. 
  int y_Value = analogRead(joyStickY);
  delay(1);
  int num = Serial1.parseInt();   // 적외선 센서의 상태를 읽어와 num에 저장(1이면 물체감지X, 2이면 물체감지)
  delay(1);

  Serial1.print("   X =  ");
  Serial1.print( x_Value,DEC);  // DEC = 10진수 형태로 출력
  delay(5);
  Serial1.print("   Y =  ");
  Serial1.print(y_Value,DEC);
  delay(5);
if (analogRead(AButton) == LOW) {
  Serial1.println('A');
  delay(DELAY);
}
if (analogRead(BButton) == LOW) {
  Serial1.println('B');
  delay(DELAY);
}
if (digitalRead(CButton) == LOW) {
  Serial1.println('C');
  delay(DELAY);
}
if (digitalRead(DButton) == LOW) {
  Serial1.println('D');
  delay(DELAY);
}
  // 적외선센서 switch
  switch(num) {
  case 1 :  // 장애물 감지X
      Serial.println("Good");
      delay(50);
      break;
      
  case 2 :  // 장애물 감지
      Serial.println("Danger!!!");
      tone(piezo, tones[6]);  //'시'에 해당하는 음 출력
      for(int i=0; i<5; i++)  // 조이스틱의 led 출력
        digitalWrite(ledset[i], HIGH);
      delay(50);
      noTone(piezo);  // 소리 정지
      for(int i=0; i<5; i++)  // led 정지
        digitalWrite(ledset[i], LOW);
      break;
  }
  delay(500);
}
