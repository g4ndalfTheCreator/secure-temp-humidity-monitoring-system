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
 - DHT11 / DHT22 (or any sensor if you are up for some tinkering and modifying the code)
 - Esp8266 board, Wemos family devices are tested to be working great. (You may bring your own other wifi based boards but again some tinkering is required)
 - A machine that can act as server. A raspberry pi or any linux will do great, but do **NOT** use windows here since they are rubbish.

 That's basically everything you need. Ready for an adventure? 

## 2. Architecture
Following figure presents system's architecture:

![img of the architecture](images/architecture.jpg)


## 3. Installation Guide


#### Generate and self sign root CA for all of your certificates

To generate and self sign the root CA for all of your certificates, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory where you want to generate the root CA certificate.
3. Run the following command to generate the root CA private key:
   ```
   openssl genrsa -out yourRootCAKey.pem 4096
   ```
4. Run the following command to generate the root CA certificate:
   ```
   openssl req -x509 -sha256 -new -nodes -key yourRootCAKey.pem -days 3650 -out yourRootCACert.pem
   ```
   You may adjust the values to your needs
5. Fill in the required information for the root CA certificate, such as country name, state or province name, locality name, organizational unit name, and common name.

6. The root CA certificate will be generated and saved as `yourRootCACert.pem` in the current directory.

#### Generate configuration to easily store your certificate information:
store following in ssl.conf
```
[req]
distinguished_name = req_distinguished_name
req_extensions = v3_req

[req_distinguished_name]
countryName = <your input here>
countryName_default = <your input here>
stateOrProvinceName = <your input here>
stateOrProvinceName_default = <your input here>
localityName = <your input here>
localityName_default = <your input here>
organizationalUnitName = <your input here>
organizationalUnitName_default = <your input here>
commonName = <your input here>
commonName_max = 64

[ v3_req ]
# Extensions to add to a certificate request
basicConstraints = CA:FALSE
keyUsage = nonRepudiation, digitalSignature, keyEncipherment
subjectAltName = @alt_names
[alt_names]
DNS.1   = <your input here>
IP.1 	= <your input here>

```
Note: Make sure to replace `<your input here>` with the actual values for the certificate information.

#### Generate keys for the mosquitto certificate

To generate keys for the mosquitto certificate, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory where you want to generate the mosquitto certificate.
3. Run the following command to generate the private key:
   ```
   openssl genrsa -out mosquitto.key 4096
   ```

4. Run the following command to generate the certificate signing request (CSR) using the provided configuration file:
   ```
   openssl req -out mosquitto.csr -key mosquitto.key -config ssl.conf -new
   ```
5. The private key will be generated and saved as `mosquitto.key` in the current directory, and the CSR will be saved as `mosquitto.csr`.

6. Use the CSR to obtain a signed certificate from a certificate authority (CA) or self-sign the certificate using the root CA generated earlier:
`sudo openssl x509 -req -days 3650 -in mosquitto.csr -CA yourRootCACert.pem -CAkey yourRootCAKey.pem -out mosquitto.crt -extensions v3_req -extfile ssl.conf`

7. Once you have the signed certificate, save it as `mosquitto.crt` in the same directory. These steps can also be applied in granafana certificate creation

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
   - Change your certificate's SHA1 checksum to the field = This enables your sensor to trust the broker
   - Make any other modifications required for your specific setup.

4. Upload the code to the ESP8266 board:
   - Connect the ESP8266 board to your computer.
   - Select the appropriate board and port from the **Tools** menu.
   - Click the **Upload** button to upload the modified code to the ESP8266 board.

### Running the Central Server
This server can be ran on any linux distro, For running the server you need to do the following:
- Update environment variables in .env file

- Install Docker Compose: Docker Compose is included in Docker Desktop for Windows and Mac. For Linux, you can download it from Docker's GitHub repository. You can check if it's installed correctly by running `docker compose --version` in your terminal. 

- Run the docker compose with `docker compose up`

- Test that Gradfan is running at: ``locahost:3000``


### BYOP - Bring your own (reverse)proxy

I assume that if you have found your way into this point of the guide and are still alive you know how to setup your own reverse proxy. If you don't here are couple of tips how to do that. And please generate certificates for the grafana GUI to use it over HTTPS otherwise all the hard work of securing the traffic is useless 

- [Google](#https://www.google.com) For general instructions how to setup a proxy like Nginx
- You can copy the example (and secure) nginx configuration file from the central_server_nginx_config -> /etc/nginx/sites-enabled at the server


## 4. Security Features and Implementations
The system has many levels of security. Majority of the security relies on the encryption of the data and certificates. The system implements the following security features:

- **Encryption in MQTT:** All data transmitted over MQTT between the sensors and the central server is encrypted using SSL and certificates, ensuring secure communication over TLS 1.2.
- **Authentication:** The system uses authentication mechanisms to verify the identity of the sensors and the central server, preventing unauthorized access.
- **Access Control (Server):** Access to the central server is restricted to authorized users only with password protected public-keys, ensuring that only authorized personnel can view and manage the collected data. Usage over internet has been implemented by accessing the central server over VPN (wireguard) only. 
- **Access Control (Grafana):** Access to the Grafana is restricted to authorized and restricted users only, ensuring that only persons with correct priviledges can view the data. No admins or superusers in use
- **Certificate Generation:** The repository provides a step-by-step guide for generating SSL certificates to enable secure communication on your deployed instace.
- **Countermeasures against CSRF and other:** The provided configuration is for setting HTTP response headers to enhance the security of your web application. These headers can help mitigate several types of attacks such as Cross-Site Scripting (XSS), Cross-Site Request Forgery (CSRF), Clickjacking, and others. 
#### Proof of secure implementation.
The data is being sent over a secure connection:
![img of the secure connection](images/secure_server.jpg)

And it uses our self signed and truested certficate:
![img of the certificate used](images/certificate.jpg)


These security features ensure that the temperature and humidity measurement system is secure and reliable, protecting the integrity and confidentiality of your temperature and humidity data from nasty neightbours.


## 5. Security Verification of the Tools and Frameworks
For this project I have been using few frameworks and tools to enchance the deployability and overall quality.

**Below is a security analysis of Docker in project**

Docker security is a critical aspect to consider when deploying containerized application like this. One of the key security features of Docker is container isolation. A pontential attacker cannot access the data or the executions of other containers nor the host system. Another important aspect of Docker security is image security. For that I have ensured that I will use docker images only from reputable sources. In addition, Docker provides secure networking options. I have configured network isolation between containers and only data input container (mosquitto) and exit point (grafana have open ports for external communication) These measures help protect against network-based attacks and eavesdropping. I have also implemented .env file to prevent data leakage throug github via docker containers.In conclusion, Docker can be used to improve overall security.

**Below is a security analysis of Docker in project**

Docker security is a critical aspect to consider when deploying containerized application like this. One of the key security features of Docker is container isolation. A pontential attacker cannot access the data or the executions of other containers nor the host system. Another important aspect of Docker security is image security. For that I have ensured that I will use docker images only from reputable sources. In addition, Docker provides secure networking options. I have configured network isolation between containers and only data input container (mosquitto) and exit point (grafana have open ports for external communication) These measures help protect against network-based attacks and eavesdropping. I have also implemented .env file to prevent data leakage throug github via docker containers.In conclusion, Docker can be used to improve overall security.