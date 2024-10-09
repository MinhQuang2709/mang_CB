
#define BLYNK_TEMPLATE_ID "TMPL6C89_2rWx"
#define BLYNK_TEMPLATE_NAME "IOT MangCB"
#define BLYNK_AUTH_TOKEN "02SkNQb6yizyikOxV-b8haYQdbuiq3D7"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <wiFiClient.h>

//wifi
const char* ssid = "8168TKT5";
const char* pass = "tumotdentam";
// config pin sensor
const uint8_t sensor_1 = 32;
const uint8_t sensor_2 = 33;
const uint8_t sensor_3 = 34;
const uint8_t sensor_4 = 35;
const uint8_t Pin_output = 2;
// value read from sensor
uint8_t val_1;
uint8_t val_2;
uint8_t val_3;
uint8_t val_4;

uint8_t button;
WidgetLED LED_ON_APP(V2);

//read val sensor
int read_sensor(int sensor_pin)
{
  int val_analog = analogRead(sensor_pin);
  int val = map(val_analog, 0, 4095, 0, 100);
  return 100 - val;
}
void update_sensor()
{
  val_1 = read_sensor(sensor_1);
  val_2 = read_sensor(sensor_2);
  val_3 = read_sensor(sensor_3);
  val_4 = read_sensor(sensor_4);
}

// on off relay
BLYNK_WRITE(V1)
{
  button = param.asInt();
  if (button == 1)
  {
    digitalWrite(Pin_output, 1);
    LED_ON_APP.on();
  }

  else if (button == 0)
  {
    digitalWrite(Pin_output, 0);
    LED_ON_APP.off();
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(Pin_output, OUTPUT);
  digitalWrite(Pin_output, 0);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() 
{
  Blynk.run();
  
  update_sensor();
  int average_humidity = (val_1 + val_2 + val_3 + val_4) / 4;
  Blynk.virtualWrite(V0, average_humidity);
  delay(1000);
}

