//
//  PortScanner.cpp
//  PortScanner
//
//  Created by Jonathan Ginsburg on 8/26/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#ifndef __Port_Scanner___
#define __Port_Scanner___

#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <string>

struct NetFile {
    std::string protocol;
    std::string command;
    std::string host;
    std::string port;
    std::string status;
};

#define BUFFER_SIZE 1000
class PortScanner {
private:
    std::string getLsofOutput() {
        std::string retVal;
        FILE * file = popen("lsof -i -n -P -F", "r");
        char currentCharacter = 'a';
        while ((currentCharacter = getc(file)) != EOF) {
            retVal += currentCharacter;
        }
        return retVal;
    }
    void clearNetFile(NetFile * netFileToClear) {
        netFileToClear->protocol = "";
        netFileToClear->command = "";
        netFileToClear->host = "";
        netFileToClear->port = "";
        netFileToClear->status = "";
    }
    std::vector<NetFile> parseLsofOutput(std::string lsofOutput) {
        std::vector<NetFile> retVal;
        std::string currentToken;
        char tokenType = 0;
        bool inToken = false;
        NetFile currentNetFile;
        for (int i = 0; i < lsofOutput.size(); ++i) {
            if (!inToken) {
                tokenType = lsofOutput[i];
                inToken = true;
            }
            else {
                if (lsofOutput[i] == '\n') { /*finish token*/
                    inToken = false;
                    if (tokenType == 'p'/*close last token, if exists, and add NetFile to retVal*/) {
                        retVal.push_back(currentNetFile);
                        clearNetFile(&currentNetFile);
                    }
                    else {
                        switch (tokenType) {
                            case 'P':
                                currentNetFile.protocol = currentToken;
                                break;
                            case 'c':
                                currentNetFile.command = currentToken;
                                break;
                            case 'n':
                            {
                                unsigned long positionOfArrow = currentToken.find("->");
                                if (positionOfArrow != std::string::npos) { /*simple case host:port*/
                                    currentToken = currentToken.substr(0, positionOfArrow);
                                }
                                unsigned long positionOfColon = currentToken.find(":");
                                currentNetFile.host = currentToken.substr(0, positionOfColon);
                                currentNetFile.port = currentToken.substr(positionOfColon + 1);
                            }
                                break;
                            case 'T':
                                if (currentToken.substr(0, 3) == "ST=") {
                                    currentNetFile.status = currentToken.substr(3);
                                }
                                break;
                            default:
                                //Do nothing
                                break;
                        }
                    }
                    currentToken = "";
                }
                else {
                    currentToken += lsofOutput[i];
                }
            }
        }
        if (retVal.size() > 0) {
            retVal.erase(retVal.begin());
        }
        return retVal;
    }
public:
    static unsigned int _referenceCount;
    void * operator new(std::size_t size) {
        ++_referenceCount;
        return malloc(size);
    }
    void operator delete(void * p)
    {
        --_referenceCount;
        free(p);
    }
    std::vector<NetFile> getListeningPorts() {
        std::vector<unsigned int> retVal;
        return parseLsofOutput(getLsofOutput());
    }
    bool isUsedPort(std::string portToTest) {
        std::vector<NetFile> ports = getListeningPorts();
        for (int i = 0; i < ports.size(); ++i) {
            if (ports[i].port == portToTest) {
                return true;
            }
        }
        return false;
    }
};
unsigned int PortScanner::_referenceCount = 0;

#endif
