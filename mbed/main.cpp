/**
 * Mbed program for launching HTTP server and listening for "Big Deal" alerts from Salesforce
 * @author James Loghry (@dancinllama on twitter)
 * 12/8/2013
 *
 */
#include "mbed.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "C12832_lcd.h"
#include "BigDealHandler.h"
   
//object for interacting with LCD on mbed application board
C12832_LCD lcd;

EthernetInterface eth;

//Main function for doing pretty much everything
int main() {
    //Instanciate HTTP server for listening for requests
    HTTPServer svr;
    
    //Add Big Deal handler to look for anything matching http://<youripaddress>/bigdeal
    svr.addHandler<HTTPBigDealRequestHandler>("/bigdeal");
    svr.start();
     
    //Display mbed's IP address on the LCD while the action happens
    C12832_LCD lcd;
    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("Server started.\nListening for requests.\nIP Address: %s\n",eth.getIPAddress());

    //Continuously poll and blink LED1 on and off, indicating we are awaiting requests
    DigitalOut led1(LED1);
    while(1){
        wait(0.5);
        led1=!led1;
        svr.poll();
    }
    
    return 0;
}