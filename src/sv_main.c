#include "server.h"

typedef void (*Huff_Decompress_t)( msg_t *mbuf, int offset );
Huff_Decompress_t Huff_Decompress = (Huff_Decompress_t)0x8076C31;

void SV_ConnectionlessPacket( netadr_t from, msg_t *msg )
{
	printf("####### SV_ConnectionlessPacket \n");

	char* s;
	char* c;
	
	MSG_BeginReading(msg);
	MSG_ReadLong(msg);
	
	void (*SV_Netchan_AddOOBProfilePacket)(int);
	*(int*)&SV_Netchan_AddOOBProfilePacket = 0x8094928;
	SV_Netchan_AddOOBProfilePacket(msg->cursize);
	
	if ( !Q_strncmp( "connect", (char*)&msg->data[4], 7 ) )
		Huff_Decompress( msg, 12 );
	
	s = MSG_ReadStringLine(msg);
	Cmd_TokenizeString(s);
	c = Cmd_Argv(0);
	
	if ( !Q_stricmp( c,"getstatus" ) )
	{
		printf("####### getstatus \n");

		void (*SVC_Status)(netadr_t);
		*(int*)&SVC_Status = 0x80880d0;
		SVC_Status(from);
	}
	else if ( !Q_stricmp( c,"getinfo" ) )
	{
		printf("####### getinfo \n");

		void (*SVC_Info)(netadr_t);
		*(int*)&SVC_Info = 0x8092a74;
		SVC_Info(from);
	}
	else if ( !Q_stricmp( c,"getchallenge" ) )
	{
		printf("####### getchallenge \n");

		void (*SV_GetChallenge)(netadr_t);
		*(int*)&SV_GetChallenge = 0x80889d0;
		SV_GetChallenge(from);
	}
	else if ( !Q_stricmp( c,"connect" ) )
	{
		printf("####### connect \n");
		
		void (*SV_DirectConnect)(netadr_t);
		*(int*)&SV_DirectConnect = 0x8089e7e;
		SV_DirectConnect(from);
	}
	else if ( !Q_stricmp( c,"ipAuthorize" ) )
	{
		printf("####### ipAuthorize \n");

		SV_AuthorizeIpPacket( from );
	}
	else if ( !Q_stricmp( c, "rcon" ) )
	{
		printf("####### rcon \n");

		((void (*)(netadr_t,msg_t*))0x80930D0)(from, msg);
	}
	else if ( !Q_stricmp( c, "disconnect" ) )
	{
		printf("####### disconnect \n");

		// if a client starts up a local server, we may see some spurious
		// server disconnect messages when their new server sees our final
		// sequenced messages to the old client*/
	}
	else
	{
		Com_DPrintf( "bad connectionless packet '%s' from %s.\n", s, NET_AdrToString( from ));
	}
}