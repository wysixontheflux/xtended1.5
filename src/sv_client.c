#include "server.h"
#include <sys/time.h>

typedef struct
{
	char        *name;
	void ( *func )( client_t *cl );
} ucmd_t;

static ucmd_t* ucmds = (ucmd_t*)0x80ee680;
/*
static ucmd_t ucmds[] =
{
	{"userinfo", (void*)0x8087B28},
	{"disconnect", (void*)0x8087AF8},
	{"cp", (void*)0x808674C},//SV_VerifyPaks_f},
	{"vdr", (void*)0x8087B14},
	{"download", SV_BeginDownload},
	{"nextdl", (void*)0x8086168},
	{"stopdl", (void*)0x8087960},
	{"donedl", (void*)0x80879FC},
	{"retransdl", (void*)0x8087A2C},
	{NULL, NULL}
};
*/

client_t **clients = (client_t**)svsclients_ptr;

getuserinfo_t getuserinfo = (getuserinfo_t)0x808B25C;
setuserinfo_t setuserinfo = (setuserinfo_t)0x808B1D0;
SV_DropClient_t SV_DropClient = (SV_DropClient_t)0x8085CF4;

void (*SV_FreeClient_o)(client_t*) = (void(*)(client_t*))0x808D34C;

void SV_FreeClient(client_t *cl)
{
	SV_FreeClient_o(cl);
}

bool is_good_string(char* str) {
	int i;
	for(i = 0; i < strlen(str); i++)
		if(str[i] < 32 || str[i] > 126)
			return 0;
	return 1;
}

void SV_AuthorizeIpPacket( netadr_t from )
{
	return; //auth srv nty
}

static time_t connect_t = 0;

void Info_RemoveKey_Big( char *s, const char *key )
{
	char    *start;
	char pkey[BIG_INFO_KEY];
	char value[BIG_INFO_VALUE];
	char    *o;

	if ( strlen( s ) >= BIG_INFO_STRING ) {
		Com_Error( ERR_DROP, "Info_RemoveKey_Big: oversize infostring [%s] [%s]", s, key );
	}

	if ( strchr( key, '\\' ) ) {
		return;
	}

	while ( 1 )
	{
		start = s;
		if ( *s == '\\' ) {
			s++;
		}
		o = pkey;
		while ( *s != '\\' )
		{
			if ( !*s ) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;
		while ( *s != '\\' && *s )
		{
			if ( !*s ) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;

		if ( !Q_stricmp( key, pkey ) ) {
			strcpy( start, s );  // remove this part
			return;
		}

		if ( !*s ) {
			return;
		}
	}

}
void Info_SetValueForKey_Big( char *s, const char *key, const char *value ) {
	char newi[BIG_INFO_STRING];

	if ( strlen( s ) >= BIG_INFO_STRING ) {
		Com_Error( ERR_DROP, "Info_SetValueForKey: oversize infostring [%s] [%s] [%s]", s, key, value );
	}

	if ( strchr( key, '\\' ) || strchr( value, '\\' ) ) {
		Com_Printf( "Can't use keys or values with a \\\n" );
		return;
	}

	if ( strchr( key, ';' ) || strchr( value, ';' ) ) {
		Com_Printf( "Can't use keys or values with a semicolon\n" );
		return;
	}

	if ( strchr( key, '\"' ) || strchr( value, '\"' ) ) {
		Com_Printf( "Can't use keys or values with a \"\n" );
		return;
	}

	Info_RemoveKey_Big( s, key );
	if ( !value || !strlen( value ) ) {
		return;
	}

	Com_sprintf( newi, sizeof( newi ), "\\%s\\%s", key, value );

	if ( strlen( newi ) + strlen( s ) > BIG_INFO_STRING ) {
		Com_Printf( "BIG Info string length exceeded\n" );
		return;
	}

	strcat( s, newi );
}

int get_client_number(client_t* cl);

int QDECL SV_ClientCommand(client_t *cl, msg_t *msg)
{
	//printf("####### SV_ClientCommand \n");

	int seq;
	const char *s;
	char *cmd;

	qboolean clientOk = qtrue;
	qboolean floodprotect = qtrue;

	seq = MSG_ReadLong(msg);
	s = MSG_ReadString(msg);

	if (cl->lastClientCommand >= seq)
		return qtrue;

	if (!strstr(s, "nextdl"))
	{
		Com_DPrintf( "clientCommand: %s : %i : %s\n", cl->name, seq, s );
	}

	if (seq > cl->lastClientCommand + 1)
	{
		Com_Printf( "Client %s lost %i clientCommands\n", cl->name, seq - cl->lastClientCommand + 1 );
		SV_DropClient( cl, "EXE_LOSTRELIABLECOMMANDS" );
		return qfalse;
	}

	//printf("####### PASS1 \n");

	if (!strncmp("team", s, 4) || !strncmp("score", s, 5) || !strncmp("mr", s, 2))
		floodprotect = qfalse;

	if (cl->state >= CS_ACTIVE && svs_time < *(int*)(&cl->state + 68632) && floodprotect)
		clientOk = qfalse;

	if (floodprotect)
		*(int*)((int)&cl->state + 68632) = svs_time + 800;

	//printf("####### PASS2 \n");

	ucmd_t *u;
	qboolean bProcessed = qfalse;
	Cmd_TokenizeString(s);
	cmd = Cmd_Argv(0);

	for ( u = ucmds; u->name; u++)
	{
		if (!strcmp(cmd, u->name))
		{
			u->func(cl);
			bProcessed = qtrue;
			break;
		}
	}

	//printf("####### PASS3 \n");

	if (clientOk)
	{
		//printf("####### clientOk \n");
		if (!u->name && *(int*)0x836b820 == 2)
		{
			if (!Q_stricmp(cmd, "follownext") || !Q_stricmp(cmd, "followprev") || !Q_stricmp(cmd, "gc"))
				goto skip_vm_call;

			printf("####### VM_Call \n");
			VM_Call(*(int*)0x80EE804, 6, get_client_number( cl ));
		}
	}

	//printf("####### PASS4 \n");

	skip_vm_call:
	cl->lastClientCommand = seq;
	//printf("####### PASS5 \n");
	Com_sprintf(cl->lastClientCommandString, sizeof(cl->lastClientCommandString), "%s", s);
	//printf("####### cl->lastClientCommandString = %s \n", cl->lastClientCommandString);
	//printf("####### PASS6 \n");
	return 1;
}

#if 0
void custom_SV_ExecuteClientMessage(client_t *cl, msg_t *msg)
{
	//cprintf(PRINT_UNDERLINE | PRINT_DEBUG, "##### custom_SV_ExecuteClientMessage \n");

	int* cl_serverId = (int*)((int)cl + 371084);
	int* sv_serverId = (int*)0x80EE800;
	int* cl_messageAcknowledge = (int*)((int)cl + 67096);

	void (*MSG_Init)(msg_t*, byte*, int) = (void(*)(msg_t*, byte*, int))0x807F928;
	int (*MSG_ReadBitsCompress)(msg_t*, byte*, int) = (int(*)(msg_t*, byte*, int))0x807FC6F;
	int (*MSG_ReadBits)(msg_t*, int) = (int(*)(msg_t*, int))0x807FB40;
	//qboolean (*SV_ClientCommand)(client_t*, msg_t*) = (void(*)(client_t*, msg_t*))0x808c858;
	//void (*SV_ClientEnterWorld)(client_t*, usercmd_t*) = (void(*)(client_t*, usercmd_t*))0x80877d8;
	void (*SV_SendClientGameState)(client_t*) = (void(*)(client_t*))0x808AE44;
	void (*SV_UserMove)(client_t*, msg_t*, qboolean) = (void(*)(client_t*, msg_t*, qboolean))0x808CADE;

	byte msgBuf[16384];
	msg_t decompressMsg;
	int c;

	MSG_Init(&decompressMsg, msgBuf, sizeof(msgBuf));
	decompressMsg.cursize = MSG_ReadBitsCompress(&msg->data[msg->readcount], msgBuf, msg->cursize - msg->readcount);

	if (*cl_serverId == *sv_serverId || cl->downloadName[0])
	{
		while (1)
		{
			c = MSG_ReadBits(&decompressMsg, 2);
			if (c != 2)
			{
				break;
			}
			if (!SV_ClientCommand(cl, &decompressMsg) || cl->state == CS_ZOMBIE)
			{
				return;
			}
		}
		
		/*
		int* sv_pure = ((int*)0x83CCD58) + 32;
		if (sv_pure->integer && cl->pureAuthentic == 2)
		{
			cl->nextSnapshotTime = -1;
			SV_DropClient(cl, "EXE_UNPURECLIENTDETECTED");
			cl->state = CS_ACTIVE;
			SV_SendClientSnapshot(cl);
			cl->state = CS_ZOMBIE;
		}
		*/
		
		if (c)
		{
			if (c == 1)
			{
				SV_UserMove(cl, &decompressMsg, 0);
			}
			else if (c != 3)
			{
				Com_DPrintf("WARNING: bad command byte %i for client %i\n", c, get_client_number(cl));
			}
		}
		else
		{
			SV_UserMove(cl, &decompressMsg, 1);
		}
	}
	else if (*cl_messageAcknowledge > cl->gamestateMessageNum)
	{
		if (((*cl_serverId & 0xF0) == (*sv_serverId & 0xF0)) && cl->state == CS_PRIMED)
		{
			cprintf(PRINT_UNDERLINE | PRINT_WARN, "##### STUCK ISSUE OCCURRING \n");
		}
		Com_DPrintf("%s : dropped gamestate, resending\n", cl->name);
		SV_SendClientGameState(cl);
	}
}
#endif

client_t* getclient(int num)
{
    client_t *cl = (client_t*)(*(int*)clients+num*clientsize);
	return cl;
}
int get_client_number(client_t* cl)
{
	return (((int)&cl->state - *(int*)svsclients_ptr) / clientsize);
}