#include "DXUT.h"
#include "SoundManager.h"

void SoundManager::Play_Bg(wstring path)
{
	// mcisendstring���� �����ϰ� ������� �ҷ��´�.
	auto route = L"open " + path + L" type mpegvideo alias A";
	
	mciSendString(route.c_str(), NULL, NULL, NULL);
	
	// �׸��� ���ѹݺ� ���
	mciSendString(L"play A notify repeat", NULL, NULL, NULL);
}

void SoundManager::Play_Ef(wstring path)
{
	//// ȿ���� ������ ����Ѵ�.
	sndPlaySound(path.c_str(), SND_ASYNC);
}