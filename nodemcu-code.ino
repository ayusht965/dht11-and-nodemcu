
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Redmi";
const char* password = "12345678";
String serverName = "https://adc-project.herokuapp.com/";
unsigned long lastTime = 0;
// Timer set to 1 minutes (60000)
unsigned long timerDelay = 40000;

char a[20];//input array from arduino
int i, value,temp,hum;//

void setup() {
  Serial.begin(115200); 

  
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  delay(2000);
}

void loop() {
  //Send an HTTP POST request every 10 minutes
if(Serial.available()>0)
  {
    i=0;
    while(0<Serial.available()){
      a[i] = Serial.read();
      i++;
      }
  }
  String s = String(a);
    value = s.toInt();
  temp = value/100;
  
  hum = value%100;
 
    String humS = String(hum);
    String tempS = String(temp);
  
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "/data";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      // Set contenxt-type to send a post request with json payload
      http.addHeader("Content-Type", "application/json");
      
      // Send HTTP GET request
      int httpResponseCode = http.POST("{\"temperature\":" + tempS + ", \"humidity\":" +  humS+"}");
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  
  }
}
