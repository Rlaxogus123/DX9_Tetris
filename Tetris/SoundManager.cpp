#include "DXUT.h"
#include "SoundManager.h"

void SoundManager::Play_Bg(wstring path)
{
	// mcisendstring으로 간단하게 배경음을 불러온다.
	auto route = L"open " + path + L" type mpegvideo alias A";
	
	mciSendString(route.c_str(), NULL, NULL, NULL);
	
	// 그리고 무한반복 재생
	mciSendString(L"play A notify repeat", NULL, NULL, NULL);
}

void SoundManager::Play_Ef(wstring path)
{
	//// 효과음 파일을 재생한다.
	sndPlaySound(path.c_str(), SND_ASYNC);
}