//library
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <DHT.h>
#include <ESPAsyncWebServer.h>

// WebSocket server port
#define WEBSOCKET_PORT 81

// define for CO sensor
#define LED 2
#define SENSOR A4
#define DELAY 5000

int COValue = 0;  // variable to store the value coming from the sensor

// define for PM sensor
#define LENG 31   // 0x42 + 31 bytes equal to 32 bytes
unsigned char buf[LENG];

float PM2_5Value = 0; // define PM2.5 value of the air detector module

// define for DHT11 sensor
#define DHT_SENSOR_PIN  26 // ESP32 pin GIOP21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

WebSocketsServer webSocket(WEBSOCKET_PORT); // Create a WebSocket server instance
AsyncWebServer server1(80);
//wifi


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial2.setTimeout(1500);
  Serial.println("Hello Coding Crew");
  dht_sensor.begin();
  pinMode(LED, OUTPUT);

  // Mount SPIFFS file system
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  
  // Open the root directory
  File root = SPIFFS.open("/");
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  
  // List all files in the root directory
  File file = root.openNextFile();
  while (file) {
    Serial.print("File: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }

  WiFi.begin("AdeKUS-StudentSpace", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  
// Serve index.html
server1.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");
});

server1.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");
});

server1.on("/about.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/about.html", "text/html");
});

// Serve CO.html
server1.on("/CO.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/CO.html")) {
    request->send(SPIFFS, "/CO.html", "text/html");
    Serial.println("CO.html exists");
  } else {
    request->send(404);
    Serial.println("CO.html does not exist");
  }
});


// Serve contact.html
server1.on("/contact.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/contact.html")) {
    request->send(SPIFFS, "/contact.html", "text/html");
    Serial.println("contact.html exists");
  } else {
    request->send(404);
    Serial.println("contact.html does not exist");
  }
});

// Serve Humidity.html
server1.on("/Humidity.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/Humidity.html")) {
    request->send(SPIFFS, "/Humidity.html", "text/html");
    Serial.println("Humidity.html exists");
  } else {
    request->send(404);
    Serial.println("Humidity.html does not exist");
  }
});

// Serve PM25.html
server1.on("/PM25.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/PM25.html")) {
    request->send(SPIFFS, "/PM25.html", "text/html");
    Serial.println("PM25.html exists");
  } else {
    request->send(404);
    Serial.println("PM25.html does not exist");
  }
});

// Serve services.html
server1.on("/services.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/services.html")) {
    request->send(SPIFFS, "/services.html", "text/html");
    Serial.println("services.html exists");
  } else {
    request->send(404);
    Serial.println("services.html does not exist");
  }
});

// Serve Temperature.html
server1.on("/Temperature.html", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/Temperature.html")) {
    request->send(SPIFFS, "/Temperature.html", "text/html");
    Serial.println("Temperature.html exists");
  } else {
    request->send(404);
    Serial.println("Temperature.html does not exist");
  }
});

// Serve background.css
server1.on("/background.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/background.css")) {
    request->send(SPIFFS, "/background.css", "text/css");
    Serial.println("background.css exists");
  } else {
    request->send(404);
    Serial.println("background.css does not exist");
  }
});

// Serve circles.css
server1.on("/circles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/circles.css")) {
    request->send(SPIFFS, "/circles.css", "text/css");
    Serial.println("circles.css exists");
  } else {
    request->send(404);
    Serial.println("circles.css does not exist");
  }
});

// Serve content.css
server1.on("/content.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/content.css")) {
    request->send(SPIFFS, "/content.css", "text/css");
    Serial.println("content.css exists");
  } else {
    request->send(404);
    Serial.println("content.css does not exist");
  }
});

// Serve styles_temp.css
server1.on("/styles_temp.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/styles_temp.css")) {
    request->send(SPIFFS, "/styles_temp.css", "text/css");
    Serial.println("styles_temp.css exists");
  } else {
    request->send(404);
    Serial.println("styles_temp.css does not exist");
  }
});

// Serve script.js
server1.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/script.js")) {
    request->send(SPIFFS, "/script.js", "text/javascript");
    Serial.println("script.js exists");
  } else {
    request->send(404);
    Serial.println("script.js does not exist");
  }
});

// Serve background.js
server1.on("/background.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  if (SPIFFS.exists("/background.js")) {
    request->send(SPIFFS, "/background.js", "text/javascript");
    Serial.println("background.js exists");
  } else {
    request->send(404);
    Serial.println("background.js does not exist");
  }
});


server1.begin();

}


// Function prototypes
void readDustParticles();
void readHumidTemp();
void readCO();

void loop() {
  Serial.println("--------------------------------------------------------------");
  readCO();
  readHumidTemp();
//  readDustParticles();
  
 
  delay(DELAY);

  // Check for WebSocket events
  webSocket.loop();
}

// ### PM2.5 Functions ###

// Read PM2.5 sensor data
void readDustParticles() {
  if (Serial2.find(0x42)) {  // start to read when detect 0x42
    Serial2.readBytes(buf, LENG);

    if (buf[0] == 0x4d) {
      if (checkValuePM_25(buf, LENG)) {
        PM2_5Value = transmitPM2_5(buf); // count PM2.5 value of the air detector module
      }
    }
  }

  static unsigned long OledTimer = millis();
  if (millis() - OledTimer >= 1000) {
    OledTimer = millis();
    Serial.print("PM2.5: ");
    Serial.print(PM2_5Value);
    Serial.println("  ug/m3");

    // Send PM2.5 value to WebSocket clients
    String pmData = String(PM2_5Value);
    webSocket.broadcastTXT(pmData);
  }
}

// Check the validity of PM2.5 data
char checkValuePM_25(unsigned char *thebuf, char leng) {
  char receiveflag = 0;
  int receiveSum = 0;

  for (int i = 0; i < (leng - 2); i++) {
    receiveSum = receiveSum + thebuf[i];
  }
  receiveSum = receiveSum + 0x42;

  if (receiveSum == ((thebuf[leng - 2] << 8) + thebuf[leng - 1])) // check the serial data
  {
    receiveSum = 0;
    receiveflag = 1;
  }

  return receiveflag;
}

// Extract PM2.5 value from received data
int transmitPM2_5(unsigned char *thebuf) {
  int PM2_5Val;
  PM2_5Val = ((thebuf[5] << 8) + thebuf[6]); // count PM2.5 value of the air detector module
  return PM2_5Val;
}

// Read humidity and temperature from DHT11 sensor
void readHumidTemp() {
  // Read humidity
  float humi  = dht_sensor.readHumidity();
  // Read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // Read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  // Check whether the reading is successful or not
  if (isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.println("%");

    //Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println("°C");
   // Serial.print("°C  ~  ");
    //Serial.print(tempF);
   // Serial.println("°F");

    // Send humidity and temperature values to WebSocket clients
    String data1 = String(humi) ;
    String humidityJsonData = "{\"type\":\"sensor_data\",\"sensor\":\"humidity\",\"value\":" + data1 + "}";
     webSocket.broadcastTXT(humidityJsonData);
      String data2 = String(tempC);
      String temperatureJsonData = "{\"type\":\"sensor_data\",\"sensor\":\"temperature\",\"value\":" + data2 + "}";
    webSocket.broadcastTXT(temperatureJsonData);

  }

  // Wait 2 seconds between readings
  //delay(2000);
}

// Read CO sensor data
void readCO() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second

  // Read the value from the sensor
  COValue = analogRead(SENSOR);
  Serial.print("CO Value: ");
  Serial.print(COValue);
  Serial.println(" ppm");

  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500);

  String coData = String(COValue);
  String coJsonData = "{\"type\":\"sensor_data\",\"sensor\":\"co\",\"value\":" + coData + "}";
  webSocket.broadcastTXT(coJsonData);
  
}

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      break;
    }
    case WStype_DISCONNECTED: {
      Serial.printf("[%u] Disconnected\n", num);
      break;
    }
    case WStype_TEXT: {
      Serial.printf("[%u] Received payload: %s\n", num, payload);

      // Handle incoming messages here

      break;
    }
  }
}
