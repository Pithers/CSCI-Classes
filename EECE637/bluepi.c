//bluepi.c
//EECE 637
//Brandon Smith & Nathan Massey

#include "bluepi.h"

int bluepi_channel_add(uint8_t rfcomm_channel)
{
	//Code taken and slightly altered from sdptool.c sourcecode
	//----------------SDP channel add stuff--------------------------
	svc_info_t st;

	//Define svc_info_t structure
	memset(&st, 0, sizeof(st));
	st.handle = 0xffffffff;
	st.name = "SP";
	st.channel = rfcomm_channel;

	//Set up variables
	svc_info_t* si = &st;	
	sdp_list_t *svclass_id, *apseq, *proto[2], *profiles, *root, *aproto;
	uuid_t root_uuid, sp_uuid, l2cap, rfcomm;
	sdp_profile_desc_t profile;
	sdp_record_t record;
	uint8_t u8 = si->channel ? si->channel : 1;
	sdp_data_t *channel;
	int ret = 0;

	bdaddr_t interface;
	bacpy(&interface, BDADDR_ANY);

	memset(&record, 0, sizeof(sdp_record_t));
	record.handle = si->handle;

	//add public browsing to list
	sdp_uuid16_create(&root_uuid, PUBLIC_BROWSE_GROUP);
	root = sdp_list_append(0, &root_uuid);
	sdp_set_browse_groups(&record, root);
	sdp_list_free(root, 0);

	//add serial port to list
	sdp_uuid16_create(&sp_uuid, SERIAL_PORT_SVCLASS_ID);
	svclass_id = sdp_list_append(0, &sp_uuid);
	sdp_set_service_classes(&record, svclass_id);
	sdp_list_free(svclass_id, 0);

	//add serial port id to list
	sdp_uuid16_create(&profile.uuid, SERIAL_PORT_PROFILE_ID);
	profile.version = 0x0100;
	profiles = sdp_list_append(0, &profile);
	sdp_set_profile_descs(&record, profiles);
	sdp_list_free(profiles, 0);

	//add l2cap to list
	sdp_uuid16_create(&l2cap, L2CAP_UUID);
	proto[0] = sdp_list_append(0, &l2cap);
	apseq = sdp_list_append(0, proto[0]);

	//add rfcomm to list
	sdp_uuid16_create(&rfcomm, RFCOMM_UUID);
	proto[1] = sdp_list_append(0, &rfcomm);
	channel = sdp_data_alloc(SDP_UINT8, &u8);
	proto[1] = sdp_list_append(proto[1], channel);
	apseq = sdp_list_append(apseq, proto[1]);

	aproto = sdp_list_append(0, apseq);
	sdp_set_access_protos(&record, aproto);

	//set data into record
	sdp_set_info_attr(&record, "Serial Port", "BlueZ", "COM Port");
	sdp_set_url_attr(&record, "http://www.bluez.org/", "http://www.bluez.org/", "http://www.bluez.org/");

	sdp_set_service_id(&record, sp_uuid);
	sdp_set_service_ttl(&record, 0xffff);
	sdp_set_service_avail(&record, 0xff);
	sdp_set_record_state(&record, 0x00001234);

	//connect to local sdp server, register the service
	sdp_session_t *session;
	session = sdp_connect(&interface /*BDADDR_ANY*/, BDADDR_LOCAL, SDP_RETRY_IF_BUSY);
	if(!session)
	{
		perror("couldn't connect to local sdp channel\n");
		ret = -1;
	}

	if (sdp_device_record_register(session, &interface, &record, SDP_RECORD_PERSIST) < 0) 
	{
		printf("service record registration failed\n");
		ret = -1;
	}
	else
	{
		//printf("Serial Port service registered on channel %i\n", rfcomm_channel);
	}

	sdp_data_free(channel);
	sdp_list_free(proto[0], 0);
	sdp_list_free(proto[1], 0);
	sdp_list_free(apseq, 0);
	sdp_list_free(aproto, 0);
	
	sdp_close(session);

	return ret;
}

int bluepi_service(uint8_t channel)
{
	//-------------Initialize variables-----------
	FILE* fp;
	int sock, client, alen;
	struct sockaddr_rc addr;
	char b_addr[19] = {0};
	char buff[1024] = {0};
	int device_secure = 0;
	int bytes_read = 0;
	int status = 0;
	char msg_snd_buff[20] = "--------------------";
	char msg_rcv_buff[10] = {0};
	char* token = 0;

	//-------------Create sdp channel-------------
	if((bluepi_channel_add(channel)) < 0)
	{
		perror("couldn't add channel\n");
		return -1;
	}

	//-------------Create socket-------------------
	if((sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0)
	{
		perror("couldn't create socket\n");
		return -2;
	}

	//-------------Setup socket stuff--------------
	addr.rc_family = AF_BLUETOOTH;
	bacpy(&addr.rc_bdaddr, BDADDR_ANY);
	addr.rc_channel = htobs(channel);		//connect to channel setup by bluepi_channel_add
	alen = sizeof(addr);

	//-------------Bind socket---------------------
	if(bind(sock, (struct sockaddr *)&addr, alen) < 0)
	{
		perror("couldn't bind socket");
		return -3;
	}

	//-------------Start Listening-----------------
	listen(sock,10);
  	//printf("Waiting for connections...\n");

	//-------------Accept connections--------------
  	while(client = accept(sock, (struct sockaddr *)&addr, &alen))
    	{
      		ba2str(&addr.rc_bdaddr, b_addr);
      		//printf("Got a connection attempt!\n");
      		//printf("From: %s \n", b_addr);

      		//------------------------Reading ID file----------------------
        	//now read file and compare found devices with list
        	fp = fopen("./bluetooth_ids", "r");
		if(fp == NULL)
        	{
                	perror("couldn't open bluetooth_ids file\n");
                	return -4;
        	}

		//Scan bluetooth_ids file until the end or the address matches the connecting address
		while(fgets(buff, sizeof(buff), fp) && device_secure == 0)
		{		
			//ignore lines starting with '#', ' ', or '\n' character
			if(buff[0] == '#' || buff[0] == ' ' || buff[0] == '\n')
			{
				continue;
			}
			
			//Only grab the bluetooth address, ignore whitespace, hastags, and newlines
			token = strtok(buff, " #\n");
			if(token != 0)
			{
				strcpy(buff,token);
			}		

			//if buff and address of device trying to connect are equal (only compare the 17 characters)
			if(strncmp(buff, b_addr, 17) == 0 )
			{
				//printf("BT address: %s found on list!\n", b_addr);
                        	//printf("R/W enabled with client: %s\n", b_addr);
				device_secure = 1;
			}
		}
		fclose(fp);

		if(device_secure == 0)
		{
			//printf("BT address: %s NOT found on list!\n", b_addr);
			//printf("Closing connection with client: %s\n", b_addr);
			close(client);
		}
		else
		{
			//Client connection established, security verified. Return the client socket descriptor
			close(sock);
			return client;
		}
    	}

}

