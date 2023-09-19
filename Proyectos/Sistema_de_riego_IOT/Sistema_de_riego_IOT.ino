//Incluimos las librerias

#include "DHTesp.h"
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
#include <ESP32Time.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Conexiones WiFi
const char* ssid = "CUARTOP";
const char* password = "leonardosussanxenia123";
String GOOGLE_SCRIPT_ID = "AKfycbxS4h1q_-kvKbYD3TnCls4VW8_dqt8o6G7go9eVXMPnNvIMUOuT9Kgoha7H1LPY3RHG1g";
//Conexion de Tiempo
const char* ntpServer="pool.ntp.org";
const long gmtOffset_sec=-5*3600;
const int daylightOffset_sec=0;

//Declaramos el variable que almacena el pin a conectar el DHT11
int pinDHT = 15;
DHTesp dht;
TempAndHumidity data;
WiFiClientSecure client;
ESP32Time rtc;
TaskHandle_t Tarea0;
TaskHandle_t Tarea1;
TaskHandle_t Tarea2;
String modo="...";
String hora="";
String fecha="";

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(loop0,"Tarea0",2000,NULL,1,&Tarea0,1);
  xTaskCreatePinnedToCore(loop1,"Tarea1",6000,NULL,1,&Tarea1,0);
  xTaskCreatePinnedToCore(loop2,"Tarea2",6000,NULL,1,&Tarea2,0);
  //Inicializamos el dht
  dht.setup(pinDHT, DHTesp::DHT11);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0); 
  display.println("Connecting to WiFi...");
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    display.clearDisplay();
  }
  Serial.println("Conectado");

  //Configuración de tiempo
  configTime(gmtOffset_sec,daylightOffset_sec,ntpServer);
  struct tm timeinfo;
  if(getLocalTime(&timeinfo)){
    rtc.setTimeStruct(timeinfo);
  }
  delay(5000);
}
//loop de lectura de sensores
void loop() {
  data = dht.getTempAndHumidity();
  mostrar_pantalla(modo,String(data.temperature, 2),String(data.humidity, 1));
}
//loop de control de hora
void loop0(void *parameter){
  //Revisa la hora
  while(1==1){
    Serial.println(rtc.getTime("%d/%m/%y %H:%M:%S"));
    hora=urlencode(rtc.getTime("%H:%M:%S"));
    fecha=urlencode(rtc.getTime("%d/%m/%y"));
    delay(1000);
  }
}

//loop de lectura
void loop1(void *parameter){
  //Hace las peticiones de lectura
  while(1==1){
    HTTPClient http;
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read";
    //   Serial.print(url);
    Serial.println("Leyendo...");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    String payload;
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      //Serial.println(httpCode);
      modo=payload;
      Serial.println(payload);
    }
    else {
      Serial.println("Error haciendo la petición");
    }
    http.end();
    delay(3000);
  }
}
//loop de escritura
void loop2(void *parameter){
  while(1==1){
    HTTPClient http;
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?fecha="+fecha+"&hora="+hora+"&temperatura="+String(data.humidity, 1)+"&humedad="+String(data.temperature, 2);
    //   Serial.print(url);
    Serial.println("Escribiendo...");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    String payload;
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      //Serial.println(httpCode);
      Serial.println(url);
      Serial.println(payload);
    }
    else {
      Serial.println("Error haciendo la petición");
      Serial.println(url);
    }
    http.end();
    delay(3000);
  }
}
//Funciones Extra
void mostrar_pantalla(String modo,String temperatura,String humedad){
  display.clearDisplay();
  display.setCursor(0,0); 
  display.println("Modo: ");
  display.print(modo);
  display.println("");
  display.println("");
  display.println("Temperatura: ");
  display.print(temperatura+" ");
  display.cp437(true);
  display.write(167);
  display.println("C");
  display.println("");
  display.println("Humedad: ");
  display.print(humedad+" %");
  display.println("");
  display.display();
}

void printCenter(const String buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
  display.setCursor((x - w / 2) + (128 / 2), y);
  display.print(buf);
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