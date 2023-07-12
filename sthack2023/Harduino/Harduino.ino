#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "MyAccessPoint";       
int keyIndex = 0;              

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

 // Web server IP 
  WiFi.config(IPAddress(192, 168, 4, 42));

  char pass[] = "Z7cX_Ud-3A5E'1m)=?cJU664";

  // Reversing the key, but this is deadcode
  size_t l = strlen(pass);
  char rev[l];
  int j = 0;
  rev[l] = '\0';
  for(int i = l-1; i >= 0; i--){
    rev[j++] = pass[i];
  }

  int checksum = 0; // Unused checksum as "dead code " 
  char tmp;
  char f[l];
  for(int k = 0; k < l; k++)
  {
    tmp = pass[k] ^ k;
    
    if(tmp <= 32){
      tmp += 31;
    }
    if(tmp >= 126){
      tmp -= 125;
    }

    f[k] = tmp;
    checksum = checksum + (int)rev[k]; // Checksum as dead code

  }
  f[l] = '\0';


  // Wif iAP setup with ssid and passphrase
  status = WiFi.beginAP(ssid, f);
  Serial.println("AP setup OK");
  
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

}


void loop() {
  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }
  
  WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("new client");           
    String currentLine = "";               
    while (client.connected()) {           
      delayMicroseconds(10);               
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("");
            client.print("Welcome to the flag provider <br \>");
            client.print("The flag is: STHACK{H@rdU1n0_107_MuCh_FuN}");
            client.println();
            break;
          }
          else {      
            currentLine = "";
          }
        }
        else if (c != '\r') {   
          currentLine += c;      
        }
      }
    }
    client.stop();
  }
}
