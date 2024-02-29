#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>



#define SERVO_PIN 18 // Change to your servo's connected pin
#define MAX_DEGREE 180 // Maximum degree for servo
#define MIN_US 500 // Minimum pulse width for servo in microseconds
#define MAX_US 2400 // Maximum pulse width for servo in microseconds

const char* ssid = "Wifi_SSID";
const char* password = "Wifi Password";

WebServer server(80);
Servo myServo;
int currentPosition = 0;
// Initial value for demonstration
int value = 0;

void setup() {
 Serial.begin(115200);
  WiFi.begin(ssid, password);

  

  // After connecting to WiFi
  myServo.attach(SERVO_PIN, MIN_US, MAX_US);

  moveServo(0);
  int servoPin = 18; // GPIO pin connected to the servo motor
  
  
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  

  Serial.println("Connected to the WiFi network");

  server.on("/", HTTP_GET, []() {
    sendMainPage();
  });

  server.on("/increment", HTTP_GET, []() {
    
    if (value < 60){
      value++; // Increment the value
      server.send(200, "text/html", "Volume: " + String(value)); // Send back only the updated value
      moveServo(3);
    }
  });

  server.on("/decrement", HTTP_GET, []() {
    if (value > 0){
      value--; // Decrement the value
      server.send(200, "text/html", "Volume: " + String(value)); // Send back only the updated value
      moveServo(-3);
    }

  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void sendMainPage() {
  // Dynamic part for the value display
  String valueDisplay = "<span id='value-display'>Volume: " + String(value) + "</span>";

  String html =
  "<!DOCTYPE html><html>"
  "<head>"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<link rel='icon' href='data:,'>"
  "<script src='https://unpkg.com/htmx.org'></script>"
  "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">"
  "<style>"
  "html, body { "
  "  height: 100%; " // Ensure the body takes full viewport height
  "  margin: 0; "
  "  display: flex; "
  "  justify-content: center; "
  "  align-items: center; "
  "  background-image: url('https://background.com'); " // Replace with your image URL
  "  background-size: cover; "
  "  background-position: center; "
  "}"
  ".container { "
  "  background-color: rgba(255, 255, 255, 0.8); "
  "  border-radius: 10px; "
  "  padding: 20px; "
  "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); "
  "}"
  ".btn { margin: 5px; }"
  "</style>"
  "</head>"
  "<body>"
  "<div class=\"container my-5 bg-dark text-white\">"
  "  <div class=\"row justify-content-center\">"
  "    <div class=\"col-12 col-md-8 text-center\">"
  "      <h1>Volume Control</h1>"
  "      <div id=\"control-panel\" class=\"my-4\">"
  "        <button class=\"btn btn-success\" hx-get=\"/increment\" hx-target=\"#value-display\" hx-swap=\"innerHTML\">Up</button>"
  "        <span id=\"value-display\" class=\"d-block my-3\">Volume: "+ String(value) +"</span>"
  "        <button class=\"btn btn-danger\" hx-get=\"/decrement\" hx-target=\"#value-display\" hx-swap=\"innerHTML\">Down</button>"
  "      </div>"
  "    </div>"
  "  </div>"
  "</div>"
  "</body></html>";



  server.send(200, "text/html", html);
}

void moveServo(int delta) {
    // Update currentPosition based on the input delta
    currentPosition += delta;
    
    // Clamp the currentPosition to ensure it's within 0 to MAX_DEGREE degrees
    currentPosition = max(0, min(currentPosition, MAX_DEGREE));
    
    // Move the servo to the new currentPosition
    myServo.write(currentPosition);
    
    Serial.print("Moving servo to ");
    Serial.println(currentPosition);
}
