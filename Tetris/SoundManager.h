//////////////////////////////////////////////////////////////
///////////////  ���带 ����ϴ� Ŭ����  ///////////////////
//////////////////////////////////////////////////////////////

#pragma once
#include "Include.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager() {};
	~SoundManager() {};

	void Play_Bg(wstring path);
	void Play_Ef(wstring path);
};