# bluepi_service- Bluetooth Pairing Service for Raspberry Pi

## Functions:
	#include <bluepi.h>
	int bluepi_service(uint8_t channel);

## Description:
bluepi_service() creates an sdp channel and binds to an rfcomm socket.
The function blocks until it recieves a verified connection. On a connection request from another bluetooth 
device it searches through the file "bluetooth_ids" and compares the connecting device's bluetooth address
to those in the file. If the connecting address is located in the file then a socket is esablished
between the devices and a socket descriptor is returned. If the connecting device is not in
"bluetooth_ids" the connection to the connecting device is terminated and the service continues
to wait for another connection.

## Parameters:
uint8_t channel
see http://www.spectrumwiki.com/wiki/DisplayEntry.aspx?DisplyId=127 for a list of acceptable channel numbers (0 to 78)
Each channel operates at a different frequency in the 2.4 GHz band.
	
## Return Value:
On success, a socket descriptor to a servicable device is returned.
On failure, a negative number is returned as follows:
	-1: Failed to create sdp channel
	-2: Failed to create bluetooth socket
	-3: Failed to bind bluetooth socket
	-4: Failed to open "bluetooth_ids" file

## Notes:
Connecting to multiple devices may be problematic. Creating multiple sdp channels and sockets
does not seem to allow multiple devices to connect. 
When compiling, you must use the -lbluetooth option to link to the bluetooth library.

## Examples:

'''#include "bluepi.h"

int main()
{
	char msg_snd_buff[10] = "You sent: ";
	char msg_rcv_buff[10] = {0};

	int s = bluepi_service(15);					//create service

	if(s < 0)
	{
		printf("error\n");
		return 1;
	}
	
	while(1)							//echo messages back to client forever
	{
		memset(msg_rcv_buff, ' ', sizeof(msg_rcv_buff));	//clear buffer contents

		if(read(s, msg_rcv_buff, sizeof(msg_rcv_buff)) < 0)
		{
			printf("Connection terminated by client\n");
			close(s);
			return 1;
		}
		else
		{
			printf("%s\n", msg_rcv_buff);
		}
	
		if(write(s, msg_snd_buff, sizeof(msg_snd_buff)) < 0)
		{
			printf("Connection terminated by server\n");
			close(s);
			return 1;
		}
		else
		{
			printf("%s%s\n", msg_snd_buff, msg_rcv_buff);
		}
	}

	close(s);

return 0;
}'''
