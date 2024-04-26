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

![img of the architecture](#resources/architecture.png)

## 3. Installation Guide

### Certificate Generation for Secure Communication
[Step-by-step guide for generating SSL certificates for secure communication.]

### ESP8266 Installation and MQTT.ino Modifications
[Instructions on installing ESP8266 and modifying MQTT.ino for the system.]

### Running the Central Server
[Guide on setting up and running the central server for data collection and management.]

### BYOP - Bring your own (reverse)proxy

I assume that if you have found your way into this point of the guide and are still alive you know how to setup your own proxy. If you don't here is couple of guides how to do that. And please generate certificates for the grafana GUI to use it over HTTPS otherwise all the hard work of securing the traffic is useless 

- [Google](#https://www.google.com) 

## 4. Security Features and Implementations
[Detail the security features implemented in the system, such as encryption, authentication, etc.]

## 5. Security Verification of the Tools and Frameworks
[Discuss the verification process of the tools and frameworks used for development, ensuring they meet security standards.]

This complete guide will assist you in setting up a secure temperature and humidity measurement system for your everyday needs.
