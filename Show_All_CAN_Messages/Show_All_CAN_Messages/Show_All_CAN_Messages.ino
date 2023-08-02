
#include <mcp_can.h>
#include <SPI.h>

unsigned long Time;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                          // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
  if(CAN0.begin(MCP_STDEXT, CAN_250KBPS, MCP_16MHZ) == CAN_OK) Serial.print("MCP2515 Init Okay!!\r\n");
  else Serial.print("MCP2515 Init Failed!!\r\n");
  
  pinMode(2, INPUT_PULLUP);                       // Setting pin 2 for /INT input
  
  Serial.println("MCP2515 Library Mask & Filter Example...");
  CAN0.setMode(MCP_NORMAL);                // Change to normal mode to allow messages to be transmitted
delay(10000);
}

void loop()
{
    if(digitalRead(2) == LOW)                    // If pin 2 is low, read receive buffer
    {
      Time = millis();
      
      CAN0.readMsgBuf(&rxId, &len, rxBuf); // Read data: len = data length, buf = data byte(s)
      
      Serial.print(Time);
      Serial.print("; ");
      Serial.print("ID;");
      Serial.print(rxId, HEX);
      Serial.print(" Data;");
      for(int i = 0; i<len; i++)           // Print each byte of the data
      {
        Serial.print(rxBuf[i], DEC);
        Serial.print(";");
      }
      
  Serial.println();
  
    }

}

/*********************************************************************************************************
END FILE
*********************************************************************************************************/
