

#include "CAN.hpp"
#include "CAN_OBD.hpp"
#include <STM32_board.h>

// Comment only one of these two lines to include CAN trasceiver only or 
// both CAN trasceiver and Modem

#define INCLUDE_MODEM 
//#undef  INCLUDE_MODEM 

//Serial to Modem
HardwareSerial ATSerial(USART4);

void setup() 
{
  delay(4000);
  Serial.print("CAN Example ....! \n");
  
  Serial.begin(115200);

  bool ret = CANInit(CAN_500KBPS);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9

  if (!ret) 
  {
    Serial.print("CANInit(.) returned FALSE");
    while(true);
  }

#ifdef INCLUDE_MODEM

  Serial.print("Initialize Modem ....! \n");
  //Initialize Modem
  // Modem PIN
  pinMode(PB15,OUTPUT);

  //First power on the Modem
  digitalWrite(PB15, HIGH);
  delay(500);
  digitalWrite(PB15, LOW);

  delay(5000);

  Serial.print("Power On Modem completed....! \n");
  Serial.println("\r\Setting Modem UART...");

  // set the data rate for the ATSerial port
  pinModeAF(PA0, GPIO_AF4_USART4);
  pinModeAF(PA1, GPIO_AF4_USART4);

  ATSerial.begin(115200);
  while (!ATSerial) ;
  ATSerial.println("Modem USART Serial Done .....");

  Serial.println("Exit Initlization.....");

  #endif
}

void loop() 
{

#ifdef INCLUDE_MODEM
  //ATI
  sendATcommand("ATE1");
  sendATcommand("ATI");
  delay(1000);

  loopModem(); 

  #endif

  loopCAN();
}

void loopCAN() 
{
  String RawData;
  float Value1, Value2, Value3, Value4, Value5;
  Value1 = Value2 = Value3 = Value4 = Value5 = -1; 

  uint32_t supportedpids;

  CAN_msg_t CAN_RX_msg;

  Serial.println ("\r\n\r\n\r\n");

  //	OBD standards this vehicle conforms to
  Serial.println("OBD standards this vehicle conforms to"); 
  SendOBDMessage(0x01,0x1C);

  if(CANMsgAvail()) 
  {
    CANReceive(&CAN_RX_msg);

    Serial.print("OBD Supported: ");
    unsigned int OBD_Type = CAN_RX_msg.data[3];          
    Serial.println(OBD_TYPE[OBD_Type]);    
  }

  Serial.println ("");
  
  //	PIDs supported
  Serial.println("PIDs supported");     
  SendOBDMessage(0x01,0x00);

  if(CANMsgAvail()) 
  {
    CANReceive(&CAN_RX_msg);   

    Serial.print("Supported PIDs: 0x");

    supportedpids = (((uint32_t)CAN_RX_msg.data[3]) << 24);
    supportedpids |= (((uint32_t)CAN_RX_msg.data[4]) << 16);
    supportedpids |= (((uint32_t)CAN_RX_msg.data[5]) << 8);
    supportedpids |= CAN_RX_msg.data[6];
    
    Serial.println(supportedpids, HEX);  
  }

  Serial.println ("");

  if(((1<<(32-0x05)) & supportedpids) != 0) //engine coolant temp.
  {
    Serial.println("Engine Coolant Temp - YES");
    SendOBDMessage(0x01,0x05);

    if(CANMsgAvail()) 
    {
      CANReceive(&CAN_RX_msg);

      if (ReadPID(0x05, CAN_RX_msg.data, &Value1, &Value2, &Value3, &Value4, &Value5))
      {
        Serial.print("Display Value: ");
        Serial.println(Value1); 
      }
      else
      {
        Serial.println("Engine Coolant Temp - Fail");
      }
    }
  }
  else
  {
    Serial.println("Engine Coolant Temp - NO");
  }

  Serial.println ("");


  if(((1<<(32-0x0C)) & supportedpids)!=0) //Engine Speed (RPM)
  {
    Serial.println("Engine Speed (RPM) - YES");
    SendOBDMessage(0x01,0x0C);

    if(CANMsgAvail()) 
    {
      CANReceive(&CAN_RX_msg);
    
      if (ReadPID(0x0C, CAN_RX_msg.data, &Value1, &Value2, &Value3, &Value4, &Value5))
      {
        Serial.print("Display Value: ");
        Serial.println(Value1); 
      }
      else
      {
        Serial.println("Engine Speed (RPM) - Fail");
      }
    }
  }
  else
  {
    Serial.println("Engine Speed (RPM) - NO");
  }

  Serial.println ("");

  if(((1<<(32-0x0D)) & supportedpids)!=0) //Vehicle Speed
  {
    Serial.println("Vehicle Speed (Km/h) - YES");
    SendOBDMessage(0x01,0x0D);

    if(CANMsgAvail()) 
    {
      CANReceive(&CAN_RX_msg);
              
      if (ReadPID(0x0D, CAN_RX_msg.data, &Value1, &Value2, &Value3, &Value4, &Value5))
      {
        Serial.print("Display Value: ");
        Serial.println(Value1); 
      }
      else
      {
        Serial.println("Vehicle Speed (Km/h) - Fail");
      }
    }
  }
  else
  {
    Serial.println("Vehicle Speed (Km/h) - NO");
  }

  Serial.println ("");

  if(((1<<(32-0x10)) & supportedpids)!=0) //Mass Air Flow
  {
    Serial.println("Mass Air Flow - YES");
    SendOBDMessage(0x01,0x10);
    
    if(CANMsgAvail()) 
    {
      CANReceive(&CAN_RX_msg);

      if (ReadPID(0x10, CAN_RX_msg.data, &Value1, &Value2, &Value3, &Value4, &Value5))
      {
        Serial.print("Display Value: ");
        Serial.println(Value1); 
      }
      else
      {
        Serial.println("Mass Air Flow - Fail");
      }
    }
  }
  else
  {
    Serial.println("Mass Air Flow - NO");
  }

  Serial.println ("");
       
  if(((1<<(32-0x11)) & supportedpids)!=0) //Throttle Position
  {
    Serial.println("Throttle Position - YES");
    SendOBDMessage(0x01,0x11);
    
    if(CANMsgAvail()) 
    {
      CANReceive(&CAN_RX_msg);

      if (ReadPID(0x11, CAN_RX_msg.data, &Value1, &Value2, &Value3, &Value4, &Value5))
      {
        Serial.print("Display Value: ");
        Serial.println(Value1); 
      }
      else
      {
        Serial.println("Throttle Postion - Fail");
      } 
    }
  }
  else
  {
    Serial.println("Throttle Postion - NO");
  }
}  


void loopModem() 
{ 
  while (ATSerial.available()) 
  {
    char at = ATSerial.read();
    Serial.write(at);
  }

  while (Serial.available()) 
  {
    char d = Serial.read();
    ATSerial.write(d);
    Serial.write(d);
  }
}


bool sendATcommand(const char *command) 
{
  while (ATSerial.read() >= 0)
    ;

  int cmd_len = strlen(command);
  int send_bytes = ATSerial.write(command);

  Serial.print("\r\n");
  Serial.print(command);
  Serial.print("\r\n");

  if (send_bytes != cmd_len) 
  {
    Serial.print("\r\n Error in AT Command");
    return false;
  }

  ATSerial.write("\r\n");
  return true;
}