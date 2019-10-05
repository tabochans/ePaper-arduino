#include "epaper.h"
#include "buffer.h"
#include "bluetooth.h"

Bluetooth g_bluetooth;
ePaper g_paper;
Buffer g_buffer;


void Command_Initialize() {
	g_bluetooth.Flush();
	g_buffer.ClearBuffer();
	g_paper.Init_ePaper();
}

void Command_Load() {
  	g_paper.LoadCheckerBoard(8);
  	g_bluetooth.Flush();
  	g_buffer.ClearBuffer();
}

void Command_Next() {
	g_bluetooth.Flush();
  	g_buffer.ClearBuffer();
}

void Command_Show() {
  	g_paper.ShowImage();
  	g_bluetooth.Flush();
  	g_buffer.ClearBuffer();
}

bool mainLoop() {
	
	if(!g_bluetooth.is_BluetoothON()) {
		return false;
	}
	g_bluetooth.Update();

	if(!g_bluetooth.is_BluetoothConnect()) {
		return false;
	}


	while(!g_bluetooth.Available()) {
		delay(2);
	}

	g_buffer.ClearBuffer();

	while(g_bluetooth.Available()) {
		g_buffer.WriteByte(g_bluetooth.Read() & 0xff);
	}
	Serial.println();

	const uint8_t mode = g_buffer.Read_Byte();

	switch(mode) {
		case 'I' :
			Command_Initialize();
		break;
		
		case 'L' :
			Command_Load();
		break;

		case 'N' :
			Command_Next();
		break;

		case 'S' :
			Command_Show();
		break;

		default:
			Serial.println("Unknown Command \n");
		break;

	};

	g_bluetooth.Write("Ok!");

	delay(1);
	return true;
}



void setup() {
  Serial.begin(115200);
  delay(10);
  
  g_paper.Init_SPI();

  delay(100);

  g_bluetooth.Setup();
}

void loop() {
	mainLoop();
}
