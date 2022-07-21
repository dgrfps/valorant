#pragma once

#include "../serial/Serial.h"

class Mouse {
	public:
		static void Move(int x, int y)
		{
			char com_port[100] = "\\\\.\\COM";

			strcat_s(com_port, std::to_string(Settings::COMPORT).c_str());

			DWORD COM_BAUD_RATE = CBR_9600;

			SimpleSerial serial = SimpleSerial(com_port, COM_BAUD_RATE);
			if (serial.connected_) {
				

				char data[255] = "";

				char bufferX[100];
				sprintf_s(bufferX, "%d", x);

				char bufferY[100];
				sprintf_s(bufferY, "%d", y);

				strcat_s(data, bufferX);
				strcat_s(data, ",");
				strcat_s(data, bufferY);

				serial.WriteSerialPort(data);
				serial.CloseSerialPort();
			}
		}
};