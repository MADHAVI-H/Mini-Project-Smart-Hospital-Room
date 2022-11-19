#include <ESP8266WiFi.h>
 
const char* ssid = "October WIFi";
const char* password = "9844787378";

int ledPin1 =5;  //D1(GPIO 05)
int ledPin2 =4;  //D2(GPIO 04)

int ledPin16 =16; //D0 INDICATION (GPIO 16)(active low)

String value1 = "OFF";
String value2 = "OFF";

WiFiServer server(80);

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
delay(10);
 
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin16, OUTPUT);

 digitalWrite(ledPin1, LOW);
 digitalWrite(ledPin2, LOW);
 digitalWrite(ledPin16, HIGH);// negation

 // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) 
 {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(ledPin16, LOW);// wifi connected indication


  // Start the server
  server.begin();//main 1
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //main 2
  Serial.println("/");
 
}

void loop() {
  // put your main code here, to run repeatedly:

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


// Match the request
 
  //////Pin D1 code///  
  if (request.indexOf("/LED1=ON") != -1) 
  {
    digitalWrite(ledPin1, HIGH);
    value1 = "ON";
  }
  if (request.indexOf("/LED1=OFF") != -1) 
  {
    digitalWrite(ledPin1, LOW);
    value1 = "OFF";
  }

  ////Pin D2 code//
   if (request.indexOf("/LED2=ON") != -1) 
  {
    digitalWrite(ledPin2, HIGH);
    value2 = "ON";
  }
  if (request.indexOf("/LED2=OFF") != -1) 
  {
    digitalWrite(ledPin2, LOW);
    value2 = "OFF";
  }

    // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  //pin D1 led on/off
  client.println("<br><br>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off 1 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On 1</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin1 is now: ");
 
  client.print(value1);

  //pin D2 led on/off
  client.println("<br><br>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off 2 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On 2</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin2 is now: ");
 
  client.print(value2);
}
