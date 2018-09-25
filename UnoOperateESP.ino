#include<SoftwareSerial.h>
SoftwareSerial espSerial(2,3);//RX,TX
void setup() {
   Serial.begin(9600);
   while(!Serial){;};
   espSerial.begin(115200);// esp8266 01波特率
   while(!espSerial){;};
   // espSerial.write("AT\r\n"); 
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CWMODE_DEF=1","OK");
    Serial.write("cwmode");
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CWJAP_DEF=\"mi6x\",\"qiuyuhan\"","OK");
    Serial.write("wifi");
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CIPSTART=\"TCP\",\"www.swcvc.net.cn\",80","OK");
    Serial.write("jap");
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CIPMODE=1","OK");
    Serial.write("cipmode");
    espSerial.write("AT+CIPSEND\r\n");
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CIPSEND","OK");
    espSerial.write("GET http://www.swcvc.net.cn/index.htm \r\n");
    waitAndReadToend(&espSerial);
    espSerial.write("+++");//END TouChuan

    Serial.write("\r\ndata send success\r\n");
    delay(10000);
    WriteCmdAndreadSerialUntil(&espSerial,"AT+CIPCLOSE","OK");
    //delay(1000);
    //espSerial.write("+++");
    //delay(1000);
    //espSerial.write("+++");
    //delay(1000);
    //espSerial.write("AT+CIPCLOSE");
    Serial.write("conn succ\r\n");
}

void loop() 
{
  
   if(Serial.available())
   {
    espSerial.write(Serial.read());
   }
   if(espSerial.available())
   {
     Serial.write(espSerial.read());   
   }
  
}
void waitAndReadToend(SoftwareSerial * serial)
{
  delay(1000);
  while(!(serial->available()))
  {;};
  while(serial->available())
  {
    delay(100);
    Serial.write(serial->read());
  }
}
void  WriteCmdAndreadSerialUntil(SoftwareSerial * serial,String cmd,char * untilstr)
{
  int itimeout=0;
  serial->print(cmd+"\r\n");
  while(1)
  {
    delay(500);
    itimeout+=500;
     while(serial->available())
     {
       delay(500);
       itimeout+=500;
      if(serial->find(untilstr))   
       return;
     }
    if(itimeout>15000)return WriteCmdAndreadSerialUntil(serial,cmd,untilstr);
   
  }
 
}
