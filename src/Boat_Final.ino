// 보트블루투스(수신)
#include <SoftwareSerial.h>
#include <DHT.h>    // 적외선 센서를 위한 헤더파일
#include<AFMotor.h>  // dc모터를 위한 헤더파일
#include <Servo.h>  // 서보모터를 위한 헤더파일

const int irDetectPin = 40; // 적외선센서 출력핀 설정
AF_DCMotor motor1(1);   // 모터쉴드 dc1번모터
AF_DCMotor motor2(2);   // 모터쉴드 dc2번모터
Servo servo;             // 서보모터
#define SPEED 70
#define DELAY 30

void setup()  
{ 
  pinMode(irDetectPin, INPUT); // 적외선센서핀을 입력으로 설정
  servo.attach(9);
  Serial.begin(9600);
  Serial1.begin(9600);
  motor1.setSpeed(SPEED);
  motor2.setSpeed(SPEED);
}

int speed1 = 70;
int speed2 = 70;
int i;
void loop()
{
  // 조이스틱의 x값을 읽어들임
  int x_Value = Serial1.parseInt();
  delay(10);
  // 조이스틱의 y값을 읽어들임
  int y_Value = Serial1.parseInt();
  delay(10);
  // 버튼의 상태를 읽어들임
  char cmd = Serial1.read();
  delay(10);

  // x,y 좌표와 버튼의 상태를 출력
  Serial.print("\n   X =  ");
  Serial.print( x_Value,DEC);
  delay(5);
  Serial.print("   Y =  ");
  Serial.print(y_Value,DEC);
  delay(5);
  Serial.print("   cmd =  ");
  Serial.print(cmd,DEC);
  delay(5);
  Serial.print("\n");
  
  if(y_Value > 750){
    // 조이스틱 모듈을 좌측 상단으로 움직였다면
    if (x_Value < 350) { 
      // 프로세싱에 L 데이터를 전송합니다.
      Serial.write('L');
      // 서보모터 좌측으로 약간 움직임
      servo.write(70);
      delay(DELAY);
    } 
    
      // 조이스틱 모듈을 우측 상단으로 움직였다면
      else if (x_Value > 750) { 
        // 프로세싱에 2 데이터를 전송합니다. 
      Serial.write('2');
      // 서보모터 우측으로 약간 움직임
      servo.write(115);
      delay(DELAY);
      } 
    
      // 조이스틱 모듈을 위로 움직였다면
      else { 
      // 프로세싱에 1 데이터를 전송합니다. 
      Serial.write('1');
      // 서보모터 정면
      servo.write(90);
      delay(DELAY);
      }   
    }

  else if(y_Value < 350){
    // 조이스틱 모듈을 좌측 하단으로 움직였다면
    if (x_Value < 350) { 
      // 프로세싱에 7 데이터를 전송합니다.
      Serial.write('7');
      // 서보모터 좌측으로 많이 움직임
      servo.write(40);
          delay(DELAY);
      } 
      // 조이스틱 모듈을 우측 하단으로 움직였다면
      else if (x_Value > 750) { 
          // 프로세싱에 5 데이터를 전송합니다. 
          Serial.write('5');
          // 서보모터 우측으로 약간 움직임
          servo.write(130);
          delay(DELAY);
      } 
    
    // 조이스틱 모듈을 아래로 움직였다면
      else{
        // 프로세싱에 6 데이터를 전송합니다. 
        Serial.write('6');
        // 서보모터 정면
        servo.write(90);
        delay(DELAY);      
      }
  }

  else{
    // 조이스틱 모듈을 왼쪽으로 움직였다면
      if (x_Value < 350) { 
        // 프로세싱에 9 데이터를 전송합니다. 
          Serial.write('9');
          // 서보모터 왼쪽으로 움직임
          servo.write(60);
          delay(DELAY);
      } 
      
      // 조이스틱 모듈을 오른쪽으로 움직였다면
      else if (x_Value > 750) { 
        // 프로세싱에 3 데이터를 전송합니다.
          Serial.write('3'); 
          // 서보모터 오른쪽으로 많이 움직임
          servo.write(140);
          delay(DELAY);
      }
    
    // 조이스틱 모듈이 정중앙에 위치한다면
      else{
        // 프로세싱에 0 데이터를 전송합니다. 
          Serial.write('0');
          // 서보모터 정면
          servo.write(90);
          delay(DELAY);
      }
  }

  // A Button이 눌렸다면
  switch(cmd) {
  case 'A' :  // dc모터 감속
    // 프로세싱에 A 데이터를 전송합니다. 
      Serial.write('A');
      if(speed1>29){
      motor1.setSpeed(speed1-=8);
      motor2.setSpeed(speed2-=8);
      }
      delay(DELAY);
      break;
      
  case 'B' :  //dc모터 정지
    // 프로세싱에 B 데이터를 전송합니다. 
      Serial.write('B'); 
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      delay(DELAY);
      break;

  case 'C' :  //dc모터 가속
      // 프로세싱에 C 데이터를 전송합니다.
      Serial.write('C');
      if(speed1<234){
      motor1.setSpeed(speed1+=10);
      motor2.setSpeed(speed2+=10);
      }
      delay(DELAY);
      break;

  case 'D' :  //dc모터 작동
    // 프로세싱에 D 데이터를 전송합니다.
      Serial.write('D');
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(SPEED);
      motor2.setSpeed(SPEED);
      delay(DELAY);
      break;
  }
  
  int noDetect = digitalRead(irDetectPin); //적외선센서 상태 읽어오기
  if(noDetect) //적외선센서가 HIGH이면 즉, 감지 안되었다면
  {
    Serial.println("Good");
    Serial1.println("1"); // 1이라는 데이터를 조이스틱으로 보냄
    delay(20);
  }
  else  //LOW 즉, 감지 되었다면
  {
    Serial.println("DANGER!!!");
    Serial1.println("2"); // 2라는 데이터를 조이스틱으로 보냄
   delay(20);
 }
 
  delay(DELAY);
}
