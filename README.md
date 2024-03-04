# ESP32 WebServer for Servo Control

This repository hosts the code for a web server designed for the ESP32 controller, enabling the control of a servo motor via web interface buttons. The web interface is enhanced using HTMX and Bootstrap for a responsive and intuitive user experience.

## Features

- **ESP32 Compatibility**: Specifically designed for the ESP32 microcontroller.
- **Servo Motor Control**: Control a servo motor directly through your web browser.
- **HTMX Integration**: Utilizes HTMX for dynamic content updates without needing to refresh the page.
- **Bootstrap Framework**: Ensures a mobile-responsive layout that looks great on any device.

## Getting Started

To get started with this project, follow these steps:

1. **Clone the Repository**:


2. **Install Dependencies**:
- Ensure you have the ESP32 development environment set up.
- Install any required libraries
    ```
    #include <WiFi.h>
    #include <WebServer.h>
    #include <ESP32Servo.h>
    ```


3. **Upload to ESP32**:
- Follow the instructions to upload the code to your ESP32 device.

4. **Connect to the Web Server**:
- Once the ESP32 is running, connect to the web server using the IP address found in your router/firewall.

## Usage

After setting up the project and connecting to the web server, you will see two buttons on the webpage. Use these buttons to control the direction and angle of the servo motor.

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

## License

This project is licensed under the GNU General Public License v2.0 - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the ESP32 community for the invaluable resources and support.
- HTMX for making web interactions a breeze.
- Bootstrap team for the responsive framework.

## Contact

If you have any questions or feedback, please open an issue in the GitHub repository.

---

Happy Coding!

<img src="https://github.com/Muxoid/esp32-webserver-htmx/assets/17557003/f49f10bc-b36a-4847-b6ad-417eb7d7eccc" width="300" height="600">


