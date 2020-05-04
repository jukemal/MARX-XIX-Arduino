#include <Arduino.h>
#include <Wire.h>
#include <StringSplitter.h>

#define ADDRESS 8

bool isProcessing = false;

int slots[4] = {0};

void receiveEvent(int howMany)
{
  String str;

  while (Wire.available())
  {
    char c = Wire.read();
    str += c;
  }

  for (size_t i = 0; i < 4; i++)
  {
    slots[i] = 0;
  }

  StringSplitter *splitterStar = new StringSplitter(str, '*', 4);
  unsigned int starCount = splitterStar->getItemCount();

  for (size_t i = 0; i < starCount; i++)
  {
    String itemStar = splitterStar->getItemAtIndex(i);

    StringSplitter *splitterUnderScore = new StringSplitter(itemStar, '_', 2);

    String slot_num = splitterUnderScore->getItemAtIndex(1);

    slots[i] = slot_num.toInt();
  }

  for (size_t i = 0; i < 4; i++)
  {
    if (slots[i] > 0)
    {
      Serial.println(slots[i]);
    }
  }

  isProcessing = true;
  Serial.println("Progress Started.");
}

void sendEvent()
{
  if (isProcessing)
  {
    Wire.write("proc");
  }
  else
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
    Serial.println("Progress Running...");
    i++;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  if (!isProcessing)
  {
    Serial.println("Arduino is Running...");
  }
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
