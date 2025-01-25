#include "mbed.h"
#include <stdio.h>

#define PUSH_BUTTON_1 p5  // Start button
#define PUSH_BUTTON_2 p6      // Stop button
#define SWITCH_1 p7         // Guard Sensor
#define SWITCH_2 p8      // Temp sensor

#define LED_1 p9      // Flash when there is a problem/ Not ready to run
#define LED_2 p10       // Motor is running
#define LED_3 p11      // Fault condition -- guard just opened while running shows for 0.5 s
#define LED_4 p12     // Fault condition -- temp sensor also show for 0.5s
char p = 0;

// Define the Input pins
	DigitalIn pb1(PUSH_BUTTON_1);
	DigitalIn pb2(PUSH_BUTTON_2);
	DigitalIn s1(SWITCH_1);
	DigitalIn s2(SWITCH_2);

//Define the Output pins
	DigitalOut led1(LED_1);
	DigitalOut led2(LED_2);
	DigitalOut led3(LED_3);
	DigitalOut led4(LED_4);

//Define Input/Output buses
	//Write your code here

void ControlLED_DigitalIO ();
void ControlLED_BusIO ();


int main()
{
    while(1) {
        ControlLED_DigitalIO ();
        // ControlLED_BusIO ();
        wait(0.25);
    }
}

void ControlLED_DigitalIO (){
          
          if(pb1 == 1)
          {
                if(s1 != 1)
                {
                     led2 = 1;
                     p = 1;
                }
          }else if(led2 == 1)
          {
                 if(s1 == 1 || pb2 == 1 || s2 == 1)
                 {
                       if(s1 == 1)
                       {
                           led3 = 1;
                           wait(0.5);
                           led3 = 0;
                       }else if(s2 == 1)
                       {
                                led4 = 1;
                                wait(0.5);
                                led4 = 0;
                       }
                       led2 = 0;
                 }
          }
          if(pb2 == 0 && s1 == 0 && s2 == 0 && p == 1 && led2 == 0)
          {
                        led2 = 1;
          }
          if(s1 == 1 || s2 == 1)
          {
                led1 = 1;
          }else{
              led1 = 0;
          }
}

void ControlLED_BusIO (){
    //Write your code here
}