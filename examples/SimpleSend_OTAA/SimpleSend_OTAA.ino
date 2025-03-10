/*******************************************************************************
* SMW_SX1262M0 Simple Send - OTAA (v1.0)
* 
* Simple program to test sending a message with OTAA.
* This program uses the ATmega to communicate with the LoRaWAN module.
* 
* Copyright 2022 RoboCore.
* Written by Francois (07/06/2022).
* 
* 
* This file is part of the SMW_SX1262M0 library ("SMW_SX1262M0-lib").
* 
* "SMW_SX1262M0-lib" is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* "SMW_SX1262M0-lib" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with "SMW_SX1262M0-lib". If not, see <https://www.gnu.org/licenses/>
*******************************************************************************/

// --------------------------------------------------
// Libraries

#include <SMW_SX1262M0.h>

#include <SoftwareSerial.h>

// --------------------------------------------------
// Variables

SoftwareSerial ss(10,11);
SMW_SX1262M0 lorawan(ss);

CommandResponse response;

const char APPEUI[] = "0000000000000000";
const char APPKEY[] = "00000000000000000000000000000000";

const unsigned long PAUSE_TIME = 300000; // [ms] (5 min)
unsigned long timeout;
bool joined = false;
int count = 0;

// --------------------------------------------------
// --------------------------------------------------

void setup() {
  // Start the UART for debugging
  Serial.begin(9600);
  Serial.println(F("--- SMW_SX1262M0 Uplink (OTAA) ---"));

  // start the UART for the LoRaWAN module
  ss.begin(9600);

  // reset the module
  lorawan.reset();

  // set join mode to OTAA
  response = lorawan.set_JoinMode(SMW_SX1262M0_JOIN_MODE_OTAA);
  if(response == CommandResponse::OK){
    Serial.println(F("Mode set to OTAA"));
  } else {
    Serial.println(F("Error setting the join mode"));
  }

  // read the Device EUI
  char deveui[16];
  response = lorawan.get_DevEUI(deveui);
  if(response == CommandResponse::OK){
    Serial.print(F("DevEUI: "));
    Serial.write(deveui, 16);
    Serial.println();
  } else {
    Serial.println(F("Error getting the Device EUI"));
  }

  // set the Application EUI
  response = lorawan.set_AppEUI(APPEUI);
  if(response == CommandResponse::OK){
    Serial.print(F("Application EUI set ("));
    Serial.write(APPEUI, 16);
    Serial.println(')');
  } else {
    Serial.println(F("Error setting the Application EUI"));
  }

  // set the Application Key
  response = lorawan.set_AppKey(APPKEY);
  if(response == CommandResponse::OK){
    Serial.print(F("Application Key set ("));
    Serial.write(APPKEY, 32);
    Serial.println(')');
  } else {
    Serial.println(F("Error setting the Application Key"));
  }

  // save the current configuration (optional)
  response = lorawan.save();
  if(response == CommandResponse::OK){
    Serial.println(F("Settings saved"));
  } else {
    Serial.println(F("Error on saving"));
  }

  // join the network
  Serial.println(F("Joining the network"));
  lorawan.join();
}

// --------------------------------------------------
// --------------------------------------------------

void loop() {
  if(timeout < millis()){
    // send a message
    if(lorawan.isConnected()){
      // print the "joined" message
      if(!joined){
        Serial.println(F("Joined"));
        joined = true; // set
      }
      
      // update the counter
      count++;
      if(count > 255){
        count = 0; // reset
      }
  
      // convert to HEX
      char data[] = { '0', '0', 0};
      data[0] += (count / 16);
      if(data[0] > '9'){
        data[0] += 7;
      }
      data[1] += (count % 16);
      if(data[1] > '9'){
        data[1] += 7;
      }
  
      // send the message
      Serial.print(F("Data: "));
      Serial.println(data);
      response = lorawan.sendX(1, data);
  
      // update the timeout
      timeout = millis() + PAUSE_TIME;
    } else {
      // show some activity
      Serial.println('.');
    
      // update the timeout
      timeout = millis() + 5000; // 5 s
    }
  }
}

// --------------------------------------------------
// --------------------------------------------------
