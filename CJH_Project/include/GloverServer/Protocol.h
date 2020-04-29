#pragma once


#include"TMath.h"

#define PACKET_HEADER_SIZE 10
#define PACKET_MAX_MSGSZ 2048

#define PACKET_MAX_SIZE PACKET_MAX_MSGSZ+PACKET_HEADER_SIZE

#pragma pack(push,1)

struct PACKETHEADER
{
	uint16_t        iotype;	// ��Ŷ ����� ����
	uint16_t    	len;	// msg ����Ʈ ũ��
	uint16_t    	type;	// � ��Ŷ�̴�.	
	uint32_t        time;   // ��Ŷ ���� �ð� 
};

struct UPACKET
{
	PACKETHEADER ph;
	char Msg[PACKET_MAX_SIZE];
};


typedef struct {
	int   iID;
	char  name[10];
}USER_INFO;

typedef struct {
	//DWORD    dwID;
	TCHAR    dwID[10] = {0};
	FVector  vPos;
	FVector  vVelocity;
	FRotator  vRotation;
	float	 fHealth;
	int      iType;
	bool     bAlive;
}JPACKET_CHARACTER_INFO;


#pragma pack(pop)



static std::ostream& operator <<(std::ostream& stream, PACKETHEADER& h)
{
	stream.write(reinterpret_cast<char*>(&h), sizeof(PACKETHEADER));
	return stream;
}

static std::ostream& operator <<(std::ostream& stream, JPACKET_CHARACTER_INFO& c_Info)
{
	stream.write(reinterpret_cast<char*>(&c_Info), sizeof(JPACKET_CHARACTER_INFO));
	return stream;
}

static std::ostream& operator <<(std::ostream& stream, USER_INFO& u_Info)
{
	stream.write(reinterpret_cast<char*>(&u_Info), sizeof(USER_INFO));
	return stream;
}



template<typename T>
std::istream & tBlockRead(std::istream& stream, T& value)
{
	return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}
template<typename T>
std::ostream & tBlockWrite(std::ostream& stream, T& value)
{
	return stream.write(reinterpret_cast<char*>(&value), sizeof(T));
}

static std::stringstream MakePacket( int iType,std::stringstream& Data)
{
	std::stringstream sstream;
	PACKETHEADER Pheader;
	Pheader.iotype = 777;
	Pheader.type = iType;
	Pheader.len = (uint16_t)(PACKET_HEADER_SIZE + Data.str().length());

	sstream << Pheader << Data.str().c_str();

	return move(sstream);
}

enum Character
{
	ROCK_MAN=0,
	MEGA_MAN,
};
enum JPACKET_TYPE
{


	//ä��
	PACKET_CHAT_MSG = 1000,
	//�α���
	PACKET_LOGIN_MSG = 2000,
	PACKET_GAME_START=2001,
	//�÷��̾� �ൿ
	PACKET_PLAYER_MOVE=3000,
	PACKET_PLAYER_ATTACK=3001,
	PACKET_PLAYER_JUMP=3002,

	PACKET_HIT_CHARACTER = 4000, // �ɸ��� �ǰ� ����
	PACKET_HIT_NPC, // NPC �ǰ� ����
	PACKET_ATTACK_CHARACTER, // �ɸ��� ���� ����
	PACKET_ATTACK_NPC, // NPC ���� ����
	PACKET_DEAD_CHARACTER, // �ɸ��� ����
	PACKET_DEAD_NPC, // NPC ����
	PACKET_DAMAGE_CHARACTER, // �ɸ��� ������ ����
	PACKET_DAMAGE_NPC, // NPC ������ ����
	PACKET_SPAWN_CHARACTER, // �ɸ��� ����
	PACKET_SPAWN_NPC, // NPC ����
	PACKET_SPAWN_NPC_LIST, // 
	PACKET_SYNC_CHARACTER, // �ɸ��� ����ȭ
	PACKET_SYNC_NPC_LIST, // NPC ����ȭ	
	PACKET_NPC_TARGETMOVE,  // NPC Ÿ���̵�

	//
	PACKET_SELECT_CHARACTER_REQ = 5000,
	PACKET_SELECT_CHARACTER_ACK = 5001,



	//���� 
	PACKET_ZONE_ENTRY_REQ = 6000,//������ ���� ��û
	PACKET_ZONE_ENTRY_ACK, // ���� �� ���� ����
	PACKET_ZONE_NEW_PLAYER, // ���� �� ���� �ɸ��� ���� ����
	PACKET_ZONE_PLAYERS_INFO, // ���� ���� ������ �������� �÷��� �ɸ��� ���� ���� 
	PACKET_ZONE_USER_INFO,// ������ ��������Ʈ ����(�÷��̾�+��Ÿ(������ ��))
	PACKET_ZONE_TARGET_REQ, // �� Ÿ�� ��ġ ��û  
	PACKET_ZONE_TARGET_ACK, // �� Ÿ�� ��ġ ����
};
