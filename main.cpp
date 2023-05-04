
#include <iostream>
#include <functions.h> // All Definitions are declared.
#include <definitions.h>
using namespace std;

// ########################## DRIVER CODE ###############################

int main()

{

    PopulateCommandCodes();

    cout << "########################   START  #######################" << endl;
    int fd = 0;
    fd = SerialPortOpen();
    ConfigureSerialPort(fd);
    int check = 0;

    while (!check)
    {
        cout << "********************   START_MENU  *********************" << endl;

        cout << "'1' 2D/3D Toggle" << endl;
        cout << "'2' Display Brightness Value" << endl;
        cout << "'3' Set Brightness" << endl;
        cout << "'4' Display Image Intensity Value " << endl;
        cout << "'5' Set Image Intensity" << endl;
        cout << "'6' Display Shapness Value" << endl;
        cout << "'7' Set Shapness Value" << endl;
        cout << "'Q' To Exit" << endl;

        cout << "********************   END_MENU  *********************" << endl;
        cout << "\n\n";
        char input;
        cin >> input;
        switch (input)
        {
        case '1':
        {
            auto t2d3dStatus = ProcessCommand(TOGGLE_2D_3D_SELECT_STATUS);
            if (t2d3dStatus[4] == 0x01) // 2D command response for 0x01
            {
                cout << "Switching from 2D to 3D...\n";
                auto swith2D = ProcessCommand(TOGGLE_2D_3D_SELECT_2D);
                bool flag = true;
                while (flag)
                {
                    cout << ".";
                    sleep(2);
                    auto t2d3dStatus1 = ProcessCommand(TOGGLE_2D_3D_SELECT_STATUS);
                    if (t2d3dStatus1[4] == 0x02)
                    {
                        flag = false;
                    }
                }
            }
            else if (t2d3dStatus[4] == 0x02) // 3D command response for 0x02
            {
                cout << "Switching from 3D to 2D...\n";
                auto swith3D = ProcessCommand(TOGGLE_2D_3D_SELECT_3D);
                bool flag = true;
                while (flag)
                {
                    cout << ".";
                    sleep(2);
                    auto t2d3dStatus2 = ProcessCommand(TOGGLE_2D_3D_SELECT_STATUS);
                    if (t2d3dStatus2[4] == 0x01)
                    {
                        flag = false;
                    }
                }
            }
            break;
        }
        case '2':
        {
            auto t2d3dStatus = ProcessCommand(BRIGHTNESS_SETTING_STATUS);
            printf("Current Brightness value : %d\n", t2d3dStatus[4]);
        }
        break;
        case '3':
        {
            bool flag = false;
            while (!flag)
            {
                int value;
                cout << "Enter Brightness value (1-100) : " << endl;
                cin >> value;
                if (value >= 0 && value <= 100)
                {
                    auto t2d3dStatus = ProcessCommand(BRIGHTNESS_SETTING, true, value, 5);
                    flag = true;
                }
                else
                {
                    cout << "Invalid  Brightness value,Please enter in the range of (1-100) " << endl;
                }
            }
        }
        break;
        case '4':
        {
            auto imageIntensity = ProcessCommand(IMAGE_INTENSITY_STATUS);
            printf("Current Image Intensity Value : %d\n", imageIntensity[4]);
        }
        break;
        case '5':
        {
            bool flag = false;
            while (!flag)
            {
                int value;
                cout << "Enter Image Intensity (1-100) : " << endl;
                cin >> value;
                if (value >= 1 && value <= 100)
                {
                    auto imageIntensity = ProcessCommand(IMAGE_INTENSITY, true, value, 5);
                    flag = true;
                }
                else
                {
                    cout << "Invalid Image Intensity, Please enter in the range of (1-100) " << endl;
                }
            }
        }
        break;
        case '6':
        {
            auto sharpnessValue = ProcessCommand(IMAGE_SHARPNESS_STATUS);
            printf("Current Sharpness Value : %d\n", sharpnessValue[4]);
        }
        break;
        case '7':
        {
            bool flag = false;
            while (!flag)
            {
                int value;
                cout << "Enter Sharpness (1-20)" << endl;
                cin >> value;
                if (value >= 1 && value <= 20)
                {
                    auto sharpnessValue = ProcessCommand(IMAGE_SHARPNESS, true, value, 5);
                    flag = true;
                }
                else
                {
                    cout << " Invalid Sharpness, Please enter in the range of (1-20)" << endl;
                }
            }
        }
        break;
        case 'Q':
        {
            check = 1;
            cout << "Quitting application\n";
        }
        break;
        default:
            cout << "Invalid request\n";
        }
        sleep(0.5);
        cout << "\n\n";
    }
    cout << "########################   END  #######################" << endl;

    DeleteCommandCodes();
    close(fd);
    return 0;
}
