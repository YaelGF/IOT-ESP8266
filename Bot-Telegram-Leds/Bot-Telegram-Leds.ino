#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

//min37
// Replace with your network credentials
const char* ssid = "IZZI-38CA";
const char* password = "8871B1CA38CA";

// Initialize Telegram BOT
#define BOTtoken "1664474817:AAGupW8hcshFjAATUhK6u06t830tfde4xdU"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1173370204"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin1 = 2;
const int ledPin2 = 14;
const int ledPin3 = 12;
bool ledState1 = LOW;
bool ledState2 = LOW;
bool ledState3 = LOW;


// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on_green to turn Led green ON \n";
      welcome += "/led_off_green to turn Led green OFF \n";
      welcome += "/led_on_yellow to turn Led yellow ON \n";
      welcome += "/led_off_yellow to turn Led yellow OFF \n";
      welcome += "/led_on_red to turn Led red ON \n";
      welcome += "/led_off_red to turn led red OFF \n";
      welcome += "/leds_on to turn leds ON \n";
      welcome += "/leds_off to turn leds OFF \n";
      
      bot.sendMessage(chat_id, welcome, "");
    }
      if (text == "/led_on_green"){
      bot.sendMessage(chat_id, "LED green ON", "");
      ledState1 = HIGH;
      digitalWrite(ledPin1, ledState1);
    }
    if (text == "/led_off_green"){
      bot.sendMessage(chat_id, "LED green OFF", "");
      ledState1 = LOW;
      digitalWrite(ledPin1, ledState1);
    }
    if (text == "/led_on_yellow") {
      bot.sendMessage(chat_id, "LED yellow ON", "");
      ledState2 = HIGH;
      digitalWrite(ledPin2, ledState2);
    }
    
    if (text == "/led_off_yellow") {
      bot.sendMessage(chat_id, "LED yellow OFF", "");
      ledState2 = LOW;
      digitalWrite(ledPin2, ledState2);
    }
      
  
    if (text == "/led_on_red"){
      bot.sendMessage(chat_id, "LED red ON", "");
      ledState3 = HIGH;
      digitalWrite(ledPin3, ledState3);     
    }
    if (text == "/led_off_red"){
      bot.sendMessage(chat_id, "LED red OFF", "");
      ledState3 = LOW;
      digitalWrite(ledPin3, ledState3);     
    }
    if (text == "/leds_on"){
      bot.sendMessage(chat_id, "LEDS ON", "");
      ledState1 = HIGH;
      ledState2 = HIGH;
      ledState3 = HIGH;
      digitalWrite(ledPin1, ledState1);
      digitalWrite(ledPin2, ledState2);
      digitalWrite(ledPin3, ledState3); 
    }
    if (text == "/leds_off"){
      bot.sendMessage(chat_id, "LEDS OFF", "");
      ledState1 = LOW;
      ledState2 = LOW;
      ledState3 = LOW;
      digitalWrite(ledPin1, ledState1);
      digitalWrite(ledPin2, ledState2);
      digitalWrite(ledPin3, ledState3);   
  }
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    client.setInsecure();
  #endif

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, ledState1);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, ledState2);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, ledState3);
  
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
