# aws-connect-outboundAPI_Blast

The execution of this demo has participants dial a number to add themselves to an emergency callback database. Once added, a remote control car is rammed into a wall which produces an event that executes a callback to all participants.

The remote control car is outfitted with a simple circuit powered by NodeMCU, flashed with the arduino bootloader (can be done using the native LUA if preferred), and an accelerometer. The arduino code includes calls to HTTPS endpoints via the ESP8266 onboard MCU using the ESP8266WiFi.h and WiFiClientSecure.h libraries.

This assembly was attached to the remote control car and rammed into a wall. The voltage generated by the accelerometer was evaluated and if greater than a defined value, an HTTPS GET request to a path created by Amazon API Gateway was made. API Gateway is configured to execute a Lambda function to query a table of phone numbers and dial back every number while preserving the API limits of Amazon Connect's outbound API.

## High level steps to replicate:

1. Create a GET endpoint using Amazon API Gateway. Deploy and and note the URL generated. Update the Arduino code with this value
1. Create a new Amazon Connect instance on aws (aws.amazon.com/connect) and import the two contact flows
1. Create a new DynamoDB table that matches the values within the 2 python functions (set/get)
1. Change the phone numbers and contact flow UUIDs to match the values generated within the Amazon Connect instance


