
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFi.h>

#define WIFI_SSID "CUARTOP"
#define WIFI_PASSWORD "leonardosussanxenia123"

int LED=4;
int PULSADOR=2;
String GOOGLE_SCRIPT_ID = "AKfycbyZ0xeN-WQLH2hXrxvUzyulStdTpMKZSbWhV72EkZDMP-3seMAcM-sWOjY9AcrIgWUr";

void setup(void) {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println(" Connected!");
}

int presionado=0;

void loop() {
  while (!Serial.available()); // Wait for input
  String texto = Serial.readStringUntil('\n');
  Serial.println(texto);
  enviar(texto);
  delay(10);
}

void enviar(String dato){
  //Revisa la hora
  while(1==1){
        HTTPClient http;
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?datos="+urlencode(dato);
    http.begin(url.c_str()); //Specify the URL and certificate
    Serial.println(url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    String payload;
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      //Serial.println(httpCode);
      //modo=payload;
      //Serial.println(payload);
    }
    else {
      Serial.println("Error haciendo la petición");
    }
    http.end();
    delay(3000);
  }
}


String urldecode(String str)
{
    
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';  
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{
        
        encodedString+=c;  
      }
      
      yield();
    }
    
   return encodedString;
}

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    //char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        //code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
    
}

unsigned char h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}