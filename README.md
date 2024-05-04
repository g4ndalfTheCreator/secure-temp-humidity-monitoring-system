# Secure Temperature/Humidity Measurement System

A comprehensive solution for everyday temperature and humidity logging needs, secure and reliable :) Try this at home!

## Structure

1. [Hardware Requirements](#hardware-requirements)
2. [Architecture](#architecture)
3. [Installation Guide](#installation-guide)
   - [Certificate Generation for Secure Communication](#certificate-generation-for-secure-communication)
   - [ESP8266 Installation and MQTT.ino Modifications](#esp8266-installation-and-mqttino-modifications)
   - [Running the Central Server](#running-the-central-server)
4. [Security Features and Implementations](#security-features-and-implementations)
5. [Security Verification of the Tools and Frameworks](#security-verification-of-the-tools-and-frameworks)

## 1. Hardware Requirements
For running this marvelous system you need following components:
 - DHT11 / DHT22 (or any sensor if you are up for some tinkering and modifying the system)
 - Esp8266 board, Wemos family devices are tested to be working great. (You may bring your own other wifi based boards but again some tinkering is required)
 - A machine that can act as server. A raspberry pi or any linux will do great, but do **NOT** use windows here since they are rubbish.

 That's basically everything you need. Ready for an adventure? 

## 2. Architecture
Following figure presents system's architecture:

![img of the architecture](images/architecture.jpg)


## 3. Installation Guide

### Certificate Generation for Secure Communication
To enable secure communication, follow these steps to generate SSL certificates:


### ESP8266 Installation and MQTT.ino Modifications
NOTE: You have to have working arduino program installed to complete the following steps, if you do not have please install it.


To install ESP8266 and modify MQTT.ino for the system, follow these instructions:

1. Install the ESP8266 board:
   - Open the Arduino IDE.
   - Go to **File > Preferences**.
   - In the "Additional Boards Manager URLs" field, enter the following URL:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Click **OK** to save the preferences.
   - Go to **Tools > Board > Boards Manager**.
   - Search for "esp8266" and install the ESP8266 board.

2. Install dependecies you need:
   - Go through required components and search from arduino store and install

3. Modify MQTT.ino:
   - Open the MQTT.ino file in the Arduino IDE.
   - Update the necessary configurations such as Wi-Fi credentials, MQTT broker address, and topic.
   - Make any other modifications required for your specific setup.

4. Upload the code to the ESP8266 board:
   - Connect the ESP8266 board to your computer.
   - Select the appropriate board and port from the **Tools** menu.
   - Click the **Upload** button to upload the modified code to the ESP8266 board.

### Running the Central Server
 TBD

### BYOP - Bring your own (reverse)proxy

I assume that if you have found your way into this point of the guide and are still alive you know how to setup your own proxy. If you don't here is couple of guides how to do that. And please generate certificates for the grafana GUI to use it over HTTPS otherwise all the hard work of securing the traffic is useless 

- [Google](#https://www.google.com) 

## 4. Security Features and Implementations

The system has many levels of security. Majority of the security relies on the encryption of the data and certificates. The

## 4. Security Features and Implementations
The system has many levels of security. Majority of the security relies on the encryption of the data and certificates. The system implements the following security features:

- **Encryption in MQTT:** All data transmitted over MQTT between the sensors and the central server is encrypted using SSL certificates, ensuring secure communication over TLS 1.2.
- **Authentication:** The system uses authentication mechanisms to verify the identity of the sensors and the central server, preventing unauthorized access.
- **Access Control (Server):** Access to the central server is restricted to authorized users only, ensuring that only authorized personnel can view and manage the collected data. This has been implemented by accessing the central server over VPN only and using only. 
- **Access Control (Grafana):** Access to the Grafana is restricted to authorized and restricted users only, ensuring that only persons with correct priviledges can view the data. 
- **Certificate Generation:** The repository provides a step-by-step guide for generating SSL certificates to enable secure communication on your deployed instace.

The data is being sent over a secure connection:
![img of the secure connection](images/secure_server.jpg)

And it uses our self signed and truested certficate:
![img of the certificate used](images/certificate.jpg)


These security features ensure that the temperature and humidity measurement system is secure and reliable, protecting the integrity and confidentiality of the collected data.

## 5. Security Verification of the Tools and Frameworks
[Discuss the verification process of the tools and frameworks used for development, ensuring they meet security standards.]

This complete guide will assist you in setting up a secure temperature and humidity measurement system for your everyday needs.

## 5. Security Verification of the Tools and Frameworks
[Discuss the verification process of the tools and frameworks used for development, ensuring they meet security standards.]

This complete guide will assist you in setting up a secure temperature and humidity measurement system for your everyday needs.
