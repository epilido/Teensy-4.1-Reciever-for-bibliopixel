#include <SPI.h>        
#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <FastLED.h>
#include "global.h"

CRGB * _fastLEDs;
CRGB * _fastLEDs1;
CLEDController * pLed = NULL;
CLEDController * pLed1 = NULL;
uint16_t numLEDs = 681;
uint8_t bytesPerPixel = 3;
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

unsigned int UdpPort = 8888;      // local port to listen on
unsigned int UdpPort1 = 8889;

EthernetUDP Udp;  // An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp1;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(UdpPort);
  Udp1.begin(UdpPort1);
          
      _fastLEDs = (CRGB*)malloc(sizeof(CRGB)*numLEDs);
  memset(_fastLEDs, 0, sizeof(CRGB)*numLEDs);
  _fastLEDs1 = (CRGB*)malloc(sizeof(CRGB)*numLEDs);
  memset(_fastLEDs1, 0, sizeof(CRGB)*numLEDs);
         pLed = new APA102Controller<11, 10, BGR, 8950000>();
          pLed1 = new APA102Controller<26, 0, BGR, 8950000>();
  
    
       FastLED.addLeds(pLed, _fastLEDs, numLEDs);
        FastLED.addLeds(pLed1, _fastLEDs1, numLEDs);
      
}
#define EMPTYMAX 100
void getData()
{
  int packetSize = Udp.parsePacket();
  
  if(packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");

    // read the packet into packetBufffer
    static char cmd = 0;
    static uint16_t size = 0;
    static uint16_t count = 0;
    static uint8_t emptyCount = 0;
    static size_t c = 0;
    static uint16_t packetSize = numLEDs * bytesPerPixel;
   
    cmd = Udp.read();
    size = 0;
    Udp.read((char*)&size, 2);

    if (cmd == CMDTYPE::PIXEL_DATA)

    {
      count = 0;
      emptyCount = 0;

      if (size == packetSize)
      {
        while (count < packetSize)
        {
          c = Udp.read(((char*)_fastLEDs) + count, packetSize - count);
          
          
          if (c == 0)
          {
            emptyCount++;
            if(emptyCount > EMPTYMAX) break;
          }
          else
          {
            emptyCount = 0;
          }

          count += c;
        }
      }

      //uint8_t resp = RETURN_CODES::SUCCESS;
      if (count == packetSize)
      {
        FastLED.show();
        
      }

      else if (cmd == CMDTYPE::BRIGHTNESS)
    {
      uint8_t result = RETURN_CODES::SUCCESS;
      if (size != 1)
        result = RETURN_CODES::ERROR_SIZE;
      else
      {
        uint8_t brightness = 255;
        size_t read = Udp.read((char*)&brightness, 1);
        if (read != size)
          result = RETURN_CODES::ERROR_SIZE;
        else
        {
          FastLED.setBrightness(brightness);
        }
      }
      //else
        //resp = RETURN_CODES::ERROR_SIZE;

      //Serial.write(resp);
    

   
    }
    }
  }
    }
    void getData1()
    {
     
  int packetSize1 = Udp1.parsePacket();
  
  if(packetSize1) {

    // read the packet into packetBufffer
    static char cmd = 0;
    static uint16_t size = 0;
    static uint16_t count = 0;
    static uint8_t emptyCount = 0;
    static size_t c = 0;
    static uint16_t packetSize1 = numLEDs * bytesPerPixel;
   
    cmd = Udp1.read();
    size = 0;
    Udp1.read((char*)&size, 2);

    if (cmd == CMDTYPE::PIXEL_DATA)

    {
      count = 0;
      emptyCount = 0;

      if (size == packetSize1)
      {
        while (count < packetSize1)
        {
          c = Udp1.read(((char*)_fastLEDs1) + count, packetSize1 - count);
          
          
          if (c == 0)
          {
            emptyCount++;
            if(emptyCount > EMPTYMAX) break;
          }
          else
          {
            emptyCount = 0;
          }

          count += c;
        }
      }

      //uint8_t resp = RETURN_CODES::SUCCESS;
      if (count == packetSize1)
      {
        FastLED.show();
        
      }

      else if (cmd == CMDTYPE::BRIGHTNESS)
    {
      uint8_t result = RETURN_CODES::SUCCESS;
      if (size != 1)
        result = RETURN_CODES::ERROR_SIZE;
      else
      {
        uint8_t brightness = 255;
        size_t read = Udp1.read((char*)&brightness, 1);
        if (read != size)
          result = RETURN_CODES::ERROR_SIZE;
        else
        {
          FastLED.setBrightness(brightness);
        }
      }
      //else
        //resp = RETURN_CODES::ERROR_SIZE;

      //Serial.write(resp);
    

   
    }
    }
    }
    }
void loop() {
getData();
getData1();

}

 
