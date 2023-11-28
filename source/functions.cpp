

// ##################### METHOD DEFINITIONS #############################

#include <functions.h>
using namespace std;

int SerialPortOpen()
{
  
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        cout << "Failed to open serial port." << endl;
    }
    else
    {
        cout << "serial port is opened" << endl;
    }
    return fd;
}

void ConfigureSerialPort(int fd)

{
    if (fd != -1)
    {
        // configure serial port
        struct termios options;
        tcgetattr(fd, &options);
        cfsetispeed(&options, B115200);
        cfsetospeed(&options, B115200);
        options.c_cflag |= (CLOCAL | CREAD);
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        tcsetattr(fd, TCSANOW, &options);
        cout << "configuration done" << endl;
    }
    else
    {
        cout << "Failed to configure serial port" << endl;
    }
}

UChar *ProcessCommand(int command, bool isValueSet, UChar value, int valueIndex)

{
    UChar *result;
    if (command >= 0 && command < commandCodesPtr.size())
    {

        UChar cmd[commandCodesPtr[command].second];
        for (int i = 0; i < commandCodesPtr[command].second; ++i)
        {
            if (isValueSet && i == valueIndex)
            {
                cmd[valueIndex] = value;
            }
            else
            {
                cmd[i] = commandCodesPtr[command].first[i];
            }
        }

        cmd[commandCodesPtr[command].second - 1] = calculateChecksum(cmd, sizeof(cmd) - 1);

        size_t cmdLength = sizeof(cmd);
        UChar response[6];
        size_t responseLength = sizeof(response);
        int bytesWritten, bytesRead;

        // clear buffer
        memset(response, 0, responseLength);

        // cout << "write command" << endl;
        // write command
        bytesWritten = write(fd, cmd, cmdLength);

        // cout<<"bytes written"<<bytesWritten<<endl;

        if (bytesWritten != cmdLength)
        {
            cerr << "Failed to send command." << endl;
            return 0;
        }

        // cout << "wait for response" << endl;
        // wait for response#include ".h"
        sleep(5); // 5 ms

        // cout << "read response" << endl;
        bytesRead = read(fd, response, responseLength);
        // cout << "after read response" << bytesRead <<endl;

        // for(int i = 0;i<responseLength;i++)
        // {
        //     printf("%02x",response[i]);
        // }

        if (bytesRead != responseLength)
        {
            cerr << "Failed to read response." << endl;
            return result;
        }
        result = response;
        // cout << "end of send command" << endl;
    }
    else
    {
        cout << " command unknown" << endl;
    }
    return result;
}

UChar calculateChecksum(UChar *data, int length)

{
    // cout << "enter in check sum" << endl;

    UChar checksum = 0;

    for (int i = 0; i < length; i++)
    {
        checksum += data[i];
    }

    return checksum;
}

void PopulateCommandCodes()

{
    int cnt = 0;
    for (auto &vec : commandCodes)
    {
        auto item = new UChar[vec.size()];
        std::copy(vec.begin(), vec.end(), item); // copy elements from vector to UChar*

        commandCodesPtr.push_back(make_pair(item, vec.size()));
    }
}

void DeleteCommandCodes()

{
    for (int i = 0; i < commandCodesPtr.size(); ++i)
    {
        delete[] commandCodesPtr[i].first;
    }
}
