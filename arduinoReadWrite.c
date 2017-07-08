#include <windows.h>
#include <stdio.h>
#include <conio.h>

/**

* @file ArduinoReadWrite.c

* @author C Squad

* @brief Serial communication

* @version 1.0

* @date May 24, 2016

*/

int openSerial(HANDLE *hComm)
{
    DCB dcbSerialParams = { 0 }; // Initializing DCB structure
    int Status = 0, continuer = 1;
    *hComm = CreateFile("COM5", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    Status = GetCommState(*hComm, &dcbSerialParams);

    dcbSerialParams.BaudRate = CBR_9600;  // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;  // Setting Parity = None

    SetCommState(*hComm, &dcbSerialParams);


    if (*hComm == INVALID_HANDLE_VALUE)
        return 0;
    else
        return 1;

    //CloseHandle(*hComm);   //Closing the Serial Port

}


int arduinoWrite(HANDLE *hComm)
{
    char lpBuffer = 'A';
    int Status = 0;
    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
    dNoOFBytestoWrite = sizeof(lpBuffer);

    Status = WriteFile(hComm,        // Handle to the Serial port
                       &lpBuffer,     // Data to be written to the port
                       dNoOFBytestoWrite,  //No of bytes to write
                       &dNoOfBytesWritten, //Bytes written
                       NULL);

}
