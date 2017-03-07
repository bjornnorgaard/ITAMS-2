#include "gsm.h"
#include "usart.h"

GsmDriver::GsmDriver()
{

}

GsmDriver::~GsmDriver()
{

}

void GsmDriver::sendMessage(unsigned char* phonenumber, unsigned char* message)
{
	setTextMode();
	sendString((unsigned char*)SEND_MESSAGE);
	sendString(phonenumber);
	sendString((unsigned char*)ENTER);
	sendString(message);
	sendByte(CTRL_Z);
}

unsigned char* GsmDriver::getMessage()
{
	return NULL;
}

void GsmDriver::getAllMessages()
{
	sendString((unsigned char*)GET_ALL_MESSAGES);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::setTextMode()
{
	sendString((unsigned char*)SET_TEXT_MODE);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::enableEcho()
{
	sendString((unsigned char*)ENABLE_ECHO);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::disableEcho()
{
	sendString((unsigned char*)DISABLE_ECHO);
	sendString((unsigned char*)ENTER);
}

void GsmDriver::waitForMessageReady()
{
	for (unsigned int i = 0; i < DATA_SIZE; i++)
	{
		if(data[i] == '>')
		return 1;
	}
	return 0;
}
