#include "JH_Character.h"



JH_Character::JH_Character()
{
}


JH_Character::~JH_Character()
{
}
std::ostream& operator<<(std::ostream&stream, JH_Character& C_Info)
{
	stream << C_Info.m_Character;
	return stream;
 }