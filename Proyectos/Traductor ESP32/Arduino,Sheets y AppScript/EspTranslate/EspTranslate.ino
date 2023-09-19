#include <WiFi.h>
#include <HTTPClient.h>

const char * ssid = "CUARTOP";
const char * password = "leonardosussanxenia123";
String GOOGLE_SCRIPT_ID = "AKfycbxZ45hEwmwPEO9F6n2eVm3eXKyUK4gyVLyIYfUMeUxH6CvZxLA6GX2gtix6NB9X0uSF";

WiFiClientSecure client;
void setup() {
  Serial.begin(115200);
  delay(2000); // Pause for 2 seconds
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Iniciado");
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado");
}

void loop() {
  //
  if(Serial.available()){
    String texto = urlencode(Serial.readStringUntil('\n'));
    escribirApp(texto);
    delay(3000);
    leerApp();
  }
}

void leerApp(void) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read";
//   Serial.print(url);
  Serial.println("Traduciendo...");
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  String payload;
    if (httpCode > 0) { //Check for the returning code
        payload = http.getString();
        //Serial.println(httpCode);
        Serial.println(payload);
      }
    else {
      Serial.println("Error haciendo la petición");
    }
  http.end();
}

void escribirApp(String texto){
      //Serial.println(texto);
      HTTPClient http;
      String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?texto="+texto;
      //Serial.println(url);
      //Serial.println("Traduciendo");
      http.begin(url.c_str()); //Specify the URL and certificate
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET();
      String payload;
      if (httpCode > 0) { //Check for the returning code
          payload = http.getString();
          //Serial.println(httpCode);
          Serial.println(payload);
      }
      else {
          Serial.println("Error haciendo la petición");
      }
      http.end();
}

////////
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
    char code2;
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
        code2='\0';
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
