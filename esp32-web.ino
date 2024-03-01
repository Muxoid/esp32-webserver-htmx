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
int currentPosition = 90;
// Initial value for demonstration
int value = 15;
int progressBarWidth;

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
    
    if (value < 30){
      value++; // Increment the value
      
      moveServo(6);
      // Calculate the new width percentage
      progressBarWidth = (value * 100) / 30;

      // Generate the updated progress bar HTML snippet
      String volumeValue = 
      "<div id=\"barCount\">"
        "<div class=\"progress\" role=\"progressbar\"  aria-valuemin=\"0\" aria-valuemax=\"60\" aria-valuenow=\"0\" aria-labelledby=\"pblabel\">"
              "<div id=\"pb\" class=\"progress-bar\" style=\"width:" + String(progressBarWidth) + "%\">" + String(progressBarWidth) + "%</div>"
        "</div>"
       "</div>";

      server.send(200, "text/html", volumeValue );
    }
  });

  



  server.on("/decrement", HTTP_GET, []() {
    if (value > 0){
      value--; // Decrement the value
      //server.send(200, "text/html", "Volume: " + String(value)); // Send back only the updated value
      moveServo(-6);
      // Calculate the new width percentage
      progressBarWidth = (value * 100) / 30;

      // Generate the updated progress bar HTML snippet
      String volumeValue = 
       "<div id=\"barCount\">"
           "<div class=\"progress\" role=\"progressbar\"  aria-valuemin=\"0\" aria-valuemax=\"60\" aria-valuenow=\"0\" aria-labelledby=\"pblabel\">"
              "<div id=\"pb\" class=\"progress-bar\" style=\"width:" + String(progressBarWidth) + "%\">" + String(progressBarWidth) + "%</div>"
            "</div>"
        "</div>";

      server.send(200, "text/html", volumeValue );
    }

  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void sendMainPage() {
  // Dynamic part for the value display
  int progressBarWidth = (value * 100) / 30;

  


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
  ".progress {"
                    "    height: 20px;"
                    "    margin-bottom: 20px;"
                    "    overflow: hidden;"
                    "    background-color: #f5f5f5;"
                    "    border-radius: 4px;"
                    "    box-shadow: inset 0 1px 2px rgba(0,0,0,.1);"
                    "}"
                    ".progress-bar {"
                    "    float: left;"
                    "    width: 0%;"
                    "    height: 100%;"
                    "    font-size: 12px;"
                    "    line-height: 20px;"
                    "    color: #fff;"
                    "    text-align: center;"
                    "    background-color: #337ab7;"
                    "    -webkit-box-shadow: inset 0 -1px 0 rgba(0,0,0,.15);"
                    "    box-shadow: inset 0 -1px 0 rgba(0,0,0,.15);"
                    "    -webkit-transition: width .6s ease;"
                    "    -o-transition: width .6s ease;"
                    "    transition: width .6s ease;"
                    "}"
  "</style>"
  "</head>"
  "<body>"
  "<div class=\"container my-5 bg-dark text-white\">"
  "  <div class=\"row justify-content-center\">"
  "    <div class=\"col-12 col-md-8 text-center\">"
  "      <h1>Volume Control</h1>"
  "      <div id=\"control-panel\" class=\"my-4\">"
  "        <button class=\"btn btn-success\" hx-get=\"/increment\" hx-target=\"#barCount\" hx-swap=\"outerHTML\">Up</button>"
  "        <div id=\"barCount\">"
            "<div class=\"progress\" role=\"progressbar\" hx-target=\"#this\" hx-swap=\"outerHTML\" aria-valuemin=\"0\" aria-valuemax=\"60\" aria-valuenow=\"0\" aria-labelledby=\"pblabel\">"
              "<div id=\"pb\" class=\"progress-bar\" style=\"width:" + String(progressBarWidth) + "%\">" + String(progressBarWidth) + "%</div>"
            "</div>"
           "</div>"
  "        <button class=\"btn btn-danger\" hx-get=\"/decrement\" hx-target=\"#barCount\" hx-swap=\"outerHTML\">Down</button>"
  "      </div>"
  "    </div>"
  "  </div>"
  "</div>"
  "</body></html>";



  server.send(200, "text/html", html);
}

void moveServo(int delta) {
    // Update currentPosition based on the input delta
    currentPosition -= delta;
    
    // Clamp the currentPosition to ensure it's within 0 to MAX_DEGREE degrees
    currentPosition = max(0, min(currentPosition, MAX_DEGREE));
    
    // Move the servo to the new currentPosition
    myServo.write(currentPosition);
    
    Serial.print("Moving servo to ");
    Serial.println(currentPosition);
}
