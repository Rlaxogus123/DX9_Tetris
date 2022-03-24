#include "DXUT.h"
#include "Include.h"

Shape::Shape()
{
	_shape = 0;
	_pattern = 0;
	_curline = 0;

	_pivot = {0,0};

	_active = false;
	_direction = 0;
	_Gameover = true;
	_deathBlock = false;
	_cooldown = 0;
	_hit = false;
}

Shape::~Shape()
{
}
void Shape::SetMino(int shape)
{
	if (shape == -1)
	{
		float MinoStack = 0;

		for (int i = 0; i < 7; i++)
			if (ShapeMNG::GetInstance()->randomMino[i] == 1)
				MinoStack++;

		if (MinoStack == 7)
			for (int i = 0; i < 7; i++)
				ShapeMNG::GetInstance()->randomMino[i] = 0;

		do _shape = rand() % 7;
		while (ShapeMNG::GetInstance()->randomMino[_shape] != 0);

		ShapeMNG::GetInstance()->randomMino[_shape] = 1;

		int r = rand() % 5;
		switch (r)
		{
		case 0:
			sndPlaySound(L"res/hit1.wav", SND_ASYNC);
			break;
		case 1:
			sndPlaySound(L"res/hit2.wav", SND_ASYNC);
			break;
		case 2:
			sndPlaySound(L"res/hit3.wav", SND_ASYNC);
			break;
		case 3:
			sndPlaySound(L"res/hit4.wav", SND_ASYNC);
			break;
		case 4:
			sndPlaySound(L"res/hit5.wav", SND_ASYNC);
			break;
		}
	}
	else
	{
		_shape = shape;
	}

	_pattern = 0;
	_curline = 0;
	_active = true;
	_color = COLOR(255, 0, 0, 255);

	switch (_shape)
	{
	case 0:
		_color = COLOR(255, 255, 0, 255);
		break;
	case 1:
		_color = COLOR(0, 255, 255, 255);
		break;
	case 2:
		_color = COLOR(0, 255, 0, 255);
		break;
	case 3:
		_color = COLOR(255, 0, 0, 255);
		break;
	case 4:
		_color = COLOR(255, 0, 255, 255);
		break;
	case 5:
		_color = COLOR(1, 0.5f, 0, 255);
		break;
	case 6:
		_color = COLOR(0, 0, 255, 255);
		break;
	}
}

void Shape::AddRotation()
{
	_pattern++;
	if (_pattern == 4) _pattern = 0;
}

void Shape::SubTractRotation()
{
	_pattern--;
	if (_pattern < 0) _pattern = 3;
}
