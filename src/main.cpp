#include <Arduino.h>
#include <Wire.h>

#define ADDRESS 8

bool isProcessing = false;

void receiveEvent(int howMany)
{
  String str;
  while (Wire.available())
  {
    char c = Wire.read();
    str += c;
  }
  Serial.println(str);

  isProcessing = true;
  Serial.println("Progress Started.");
}

void sendEvent()
{
  if (isProcessing)
  {
    Wire.write("proc");
  }else
  {
    Wire.write("done");
  }
  
}

void setup()
{
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);

  Serial.begin(115200);

  Serial.println("Started...");
}

int i = 0;

void loop()
{
  if (isProcessing && i == 10)
  {
    isProcessing = false;
    i = 0;
    Serial.println("Progress Done");
  }

  if (isProcessing)
  {
    i++;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Arduino is Running...");
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

