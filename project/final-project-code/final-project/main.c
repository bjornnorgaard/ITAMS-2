#define SMS_META_SIZE 75
#define SMS_DATA_SIZE 50
#define F_CPU 3686400
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "gsm/gsm.h"
#include "uart/uart.h"
#include "bmp085/bmp085.h"
#include "led/led.h"

void clearSmsData(char* meta, char* data);

int main(void)
{
	sei();
	ledInit();
	uartInit();
	gsmInit();
	bmpInit();
	gsmCommandDeleteArrayOfSms(10);

	_delay_ms(5000); // ensure 5 sec. delay
	struct gsmStatus stats;
	char meta[75] = {0};
	char data[50] = {0};
	char phoneNumber[11] = {0};

	gsmCommandGetStatus(&stats);
	clearSmsData(meta, data);
	volatile unsigned char stopHere = 0;
	
	while(1)
	{
		ledReadyForRequest();
		gsmCommandGetStatus(&stats);

		if (stats.newMessage == 1)
		{
			ledMessageReceived();
			gsmCommandReadSms(meta, data, phoneNumber);
			gsmExecuteSmsRequest(data, phoneNumber);
			gsmCommandDeleteSms();
			clearSmsData(meta, data);
		}
		_delay_ms(500);
	}
}

void clearSmsData(char* meta, char* data)
{
	for(int i = 0; i < SMS_META_SIZE; i++)
	{
		meta[i] = 0;
	}

	for(int i = 0; i < SMS_DATA_SIZE; i++)
	{
		data[i] = 0;
	}
}
