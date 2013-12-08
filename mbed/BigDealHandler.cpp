/* BigDealHandler
 * This class implements the HttpRequest handler interface
 * This class listens for the bigdeal URI and handles the alert logic.
 * If request comes in with http://<mbed_ip_address>/bigdeal/?opptyName=<name>&opptyAmount=<amount>
 * Then sit back and watch the magic happen.
 * @author James Loghry
 * @date 12/8/2013
 */
#include "mbed.h"
#include "BigDealHandler.h"
#include "C12832_lcd.h"
#include "hl_debug.h"
#include <map>

#define DEBUG 1
#define NUM_FLASHES 20

//Initialize LEDs for fancy disco party
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

//Initialize mbed application board LCD
C12832_LCD lcd2;

//Variable for retaining arguments from Http GET request
std::map<std::string, std::string> requestArgs;

//Big Deal Alert String to display on LCD when alert comes in
const char* BIG_DEAL_ALERT = "***BIG DEAL ALERT!***\nOpportunity: %s\nAmount: %s\n";

HTTPBigDealRequestHandler::HTTPBigDealRequestHandler(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& Msg, TCPSocketConnection& Tcp)
    : HTTPRequestHandler(Msg, Tcp)
{
    m_rootPath = rootPath;
    m_localPath = localPath;
    requestArgs = Msg.args;
    handleRequest();
}


HTTPBigDealRequestHandler::~HTTPBigDealRequestHandler()
{
}

int HTTPBigDealRequestHandler::handlePutRequest()
{
    return 404;
}

int HTTPBigDealRequestHandler::handlePostRequest()
{
    return 404;
}

void handleBigDeal(string opptyName,string opptyAmount)
{
    lcd2.cls();
    //Reset LEDs
    led1=0;
    led2=0;
    led3=0;
    led4=0;

    //Display Big Deal Message
    lcd2.cls();
    lcd2.locate(0,0);
    lcd2.printf(BIG_DEAL_ALERT,opptyName.c_str(),opptyAmount.c_str());

    //Flash Big Deal Alert LED sequence
    for(int i=0; i < NUM_FLASHES; i++) {
        led1=1;
        wait(0.1);
        led1=0;
        led2=1;
        wait(0.1);
        led2=0;
        led3=1;
        wait(0.1);
        led3=0;
        led4=1;
        wait(0.1);
        led4=0;
        led3=1;
        wait(0.1);
        led3=0;
        led2=1;
        wait(0.1);
        led2=0;
        led1=1;
        wait(0.1);
        led1=0;
    }
    
    //Reset LCD screen
    lcd2.cls();
    lcd2.locate(0,0);
    lcd2.printf("Listening for requests.\n");
    
    return;
}

int HTTPBigDealRequestHandler::handleGetRequest(){
    int err=404;
    
    handleBigDeal(requestArgs["opptyName"],requestArgs["opptyAmount"]);
    err=0;
    //copy str from "const char * of m local path" to "char *" for tokenizing
    /*char * urlPath = new char[m_localPath.size()+1];
    strcpy(urlPath,m_localPath.c_str());
    
    //Tokenize the the local path of the URL from the request
    //and read in oppty name and amount in format of:
    //http://url/bigdeal/{opptyname}/{opptyamount}
    int i=0;
    char * pch = strtok(urlPath,"/");
    char * opptyName;
    char * opptyAmount;  
    while (pch != NULL && i <= 1){
        if(i==0){
            opptyName=pch;
            pch = strtok(NULL,"/");
        }else if(i==1){
            opptyAmount=pch;
        }
        i++;
    }
    
    handleBigDeal(opptyName,opptyAmount);

    err=0;*/
    return err;
}
