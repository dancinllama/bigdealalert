/* BigDealHandler.h */
#ifndef __BIGDEALHANDLER_H__
#define __BIGDEALHANDLER_H__

#include "mbed.h"
#include "HTTPRequestHandler.h"

class HTTPBigDealRequestHandler : public HTTPRequestHandler
{
        std::string m_rootPath;
        std::string m_localPath;

    public:
        /** constructor for HTTPBigDealRequestHandler object and stores the request related data locally. 
        * the request handling will be initiated from within the constructor.
        * @param rootPath : The path under which the handler was registered.
        * @param localPath : The path which is relative to the registered file system root.
        * @param Msg : Message request information that comes with the request.
        * @param Tcp : The socket connection for communicating with the client.
        */
        HTTPBigDealRequestHandler(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& Msg, TCPSocketConnection& Tcp);
        
        /** Destructor 
        */
        virtual ~HTTPBigDealRequestHandler();
  
        /** static creation function for this object.
        */
        static inline HTTPRequestHandler* create(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& msg, TCPSocketConnection& tcp) { return new HTTPBigDealRequestHandler(rootPath, localPath, msg, tcp); }
              
        /** Handler function to serve GET requests
        */
        virtual int handleGetRequest();
        
        /** Handler function to serve PUT requests
        */
        virtual int handlePutRequest();
        
        /** Handler function to serve POST requests
        */
        virtual int handlePostRequest();

        /** Parse a uri string for uri file name and argument:value pairs
        */
//        int parseUriArgs(string uri, string map<string, string>& args);
};
#endif //   __BIGDEALHANDLER_H__