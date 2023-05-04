
// definitions

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <unistd.h> // for usleep()
#include <fcntl.h>  // for open(), close(), read(), write()
#include <termios.h>
#include <datatypes.h>

using namespace std;

static int fd;

extern vector<pair<UChar *, int>> commandCodesPtr;
extern vector<vector<UChar>> commandCodes;

UChar *ProcessCommand(int command, bool isValueSet = false, UChar value = 0, int valueIndex = 0);
UChar calculateChecksum(UChar *data, int length);
int SerialPortOpen();
void ConfigureSerialPort(int fd);
void PopulateCommandCodes();
void DeleteCommandCodes();

#endif
