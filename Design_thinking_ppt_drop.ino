
#include "HUSKYLENS.h" //허스키 렌즈 관련 헤더파일 추가
#include "SoftwareSerial.h" //시리얼 통신 관련 헤더파일 추가 
#include<Keyboard.h> //키보드 명령 관련 헤더파일 추가 (아두이노 레오나르도 모델에서만 작동)

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);  


void setup() {
    Serial.begin(115200);
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }

}

void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      Keyboard.release(KEY_DOWN_ARROW);
      Keyboard.release(KEY_UP_ARROW);
      }
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
         }
        }    
      }


void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
 
 int num1 = map(result.xCenter,0,320,0,180);
 int num2 = map(result.yCenter,0,240,0,180);
 
if(result.ID == 1){
  if(num1 >= 130) {
    Keyboard.press(KEY_RIGHT_ARROW);  //키보드 프레스라는 명령어는, 괄호 안에 있는 키를 누르도록 명령함.
    delay(1000);
  }
  else if(num1 <= 50) {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(1000);
  }
  else{
    Keyboard.release(KEY_LEFT_ARROW); //키보드 릴리스라는 명령어는, 괄호 안에 있는 키를 떼도록 명령함.
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  Serial.println(num1);
  Serial.println(num2);
  
}
    }

  } 

    
