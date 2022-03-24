#include "DXUT.h"
#include "Include.h"

void GameScene::Init()
{
	SoundManager::GetInstance()->Play_Bg(L"res/BGM2.mp3");

	_score = 0;
	D3DXCreateFont(DXUTGetD3D9Device(), 50, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"System", &_font);

	Logo = new Sprite();
	Logo->SetTexture(L"Tetris/Logo.png");
	Logo->_isUI = false;
	Logo->_position = { 1200,300 };

	GameOver = new Sprite();
	GameOver->SetTexture(L"Tetris/GameOver.png");
	GameOver->_isUI = true;
	GameOver->_layer = 3;
	GameOver->_visible = false;
	GameOver->_position = { ScreenWidth/2,ScreenHeigth/2 };
	
	for (int heith = 0; heith < STAGE_HEITH; heith++)
	{
		for (int width = 0; width < STAGE_WIDTH; width++)
		{
			sprTile[heith][width] = new Sprite();
			sprTile[heith][width]->SetTexture(L"Tetris/Tile.png");
			sprTile[heith][width]->_position.x = 0 + width * 50;
			sprTile[heith][width]->_position.y = 0 + heith * 50;
			sprTile[heith][width]->_isUI = false;
		}
	}

	for (int heith = 0; heith < 4; heith++)
	{
		for (int width = 0; width < 5; width++)
		{
			holdTile[heith][width] = new Sprite();
			holdTile[heith][width]->SetTexture(L"Tetris/Tile.png");
			holdTile[heith][width]->_position.x = 600 + width * 50;
			holdTile[heith][width]->_position.y = 400 + heith * 50;
			holdTile[heith][width]->_isUI = false;
		}
	}

	for (int j = 0; j < STAGE_HEITH; j++)
		for (int i = 0; i < STAGE_WIDTH; i++)
			Tile[j][i] = 0;

	Camera::GetInstance()->setScale(1.5);
	camPos = { ScreenWidth / 2 + 200, ScreenHeigth / 2  + 120};

	_holdShape = -1;
	_holdcolor = COLOR(255, 255, 255, 255);
	_isHold = true;
	_curShape = new Shape();
	_curShape->SetMino();
	_curShape->SetPos(vec2(4, 0));
	ShapeMNG::GetInstance()->v_Shapes.push_back(_curShape);

	GameSpeed = 0.5;
	tick = 0;
	
	Game = true;
}

void GameScene::Update()
{
	if (DXUTIsKeyDown('W')) camPos.y--;
	if (DXUTIsKeyDown('S')) camPos.y++;
	if (DXUTIsKeyDown('A')) camPos.x--;
	if (DXUTIsKeyDown('D')) camPos.x++;

	if (DXUTWasKeyPressed('Q')) Camera::GetInstance()->setScale(Camera::GetInstance()->getScale() + 0.1);
	if (DXUTWasKeyPressed('E')) Camera::GetInstance()->setScale(Camera::GetInstance()->getScale() - 0.1);

	if (DXUTWasKeyPressed('R')) if (!Game) Director::GetInstance()->ChangeScene(new GameScene);

	if (DXUTWasKeyPressed('1')) _curShape->SetMino(0);
	if (DXUTWasKeyPressed('2')) _curShape->SetMino(1);
	if (DXUTWasKeyPressed('3')) _curShape->SetMino(2);
	if (DXUTWasKeyPressed('4')) _curShape->SetMino(3);
	if (DXUTWasKeyPressed('5')) _curShape->SetMino(4);
	if (DXUTWasKeyPressed('6')) _curShape->SetMino(5);
	if (DXUTWasKeyPressed('7')) _curShape->SetMino(6);

	RECT rt;
	SetRect(&rt, 500, 500, 0, 0);
	char _strscore[100];
	sprintf(_strscore, "Score : %d", _score);
	_font->DrawTextA(NULL, _strscore, -1, &rt, DT_NOCLIP, COLOR(1, 1, 1, 1));
	if (DXUTWasKeyPressed(VK_SPACE) && _isHold)
	{
		if (_holdShape == -1)
		{
			_holdShape = (int)_curShape->_shape;
			_holdcolor = _curShape->_color;

			_curShape->SetMino();
			_curShape->SetPos(vec2(4, 0));

			_isHold = false;

			return;
		}
		if (_holdShape != -1)
		{
			int temp = (int)_curShape->_shape;
			COLOR temp2 = _curShape->_color;

			_curShape->SetMino(_holdShape);
			_curShape->SetPos(vec2(4, 0));

			_holdShape = temp;
			_holdcolor = temp2;

			_isHold = false;

			return;
		}
	}

	Camera::GetInstance()->setPosition(camPos);

	// ▼ Game

	if (!Game) return;

	static float downTick = 0;
	downTick += GLOBAL::deltaTime;
	if (DXUTIsKeyDown(VK_DOWN))
	{
		if (downTick > 0.075)
		{
			_curShape->SetPos(_curShape->_pivot + vec2(0, 1));
			_curShape->_direction = 2;
			_curShape->_Gameover = false;
			_curShape->_cooldown = 0;
			downTick = 0; tick = 0;
		}
	}

	static float leftTick = 0;
	leftTick += GLOBAL::deltaTime;
	if (DXUTIsKeyDown(VK_LEFT))
	{
		if (leftTick > 0.1)
		{
			_curShape->SetPos(_curShape->GetPos() + vec2(-1, 0));
			_curShape->_direction = 0;
			_curShape->_Gameover = false;
			_curShape->_cooldown = 0;
			leftTick = 0;
		}
	}

	static float rightTick = 0;
	rightTick += GLOBAL::deltaTime;
	if (DXUTIsKeyDown(VK_RIGHT))
	{
		if (rightTick > 0.1)
		{
			_curShape->SetPos(_curShape->GetPos() + vec2(1, 0));
			_curShape->_direction = 1;
			_curShape->_Gameover = false;
			_curShape->_cooldown = 0;
			rightTick = 0;
		}
	}

	if (DXUTWasKeyPressed('Z'))
	{
		_curShape->AddRotation();
		_curShape->_cooldown = 0;
	}
	if (DXUTWasKeyPressed('X'))
	{
		_curShape->SubTractRotation();
		_curShape->_cooldown = 0;
	}

	tick += GLOBAL::deltaTime;
	if (_curShape->_hit) _curShape->_cooldown += GLOBAL::deltaTime;

	// 게임스피드에 따라서 내려오는속도가 빨라짐.
	if (tick > GameSpeed)
	{
		if (_curShape != nullptr)
		{
			_curShape->SetPos(_curShape->GetPos() + vec2(0, 1));
			_curShape->_direction = 2;
			_curShape->_Gameover = false;
			tick = 0;
		}
	}

	// Cliiping
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (_curShape->tetriminos[_curShape->_shape][_curShape->_pattern][j][i])
			{
				while (Tile[j + (int)_curShape->GetPos().y][i + (int)_curShape->GetPos().x] == 2)
				{
					if (_curShape->_direction == 0) _curShape->SetPos(_curShape->GetPos() + vec2(1, 0));
					else if (_curShape->_direction == 1) _curShape->SetPos(_curShape->GetPos() + vec2(-1, 0));
					else if (_curShape->_direction == 2) _curShape->SetPos(_curShape->GetPos() + vec2(0, -1));
				}

				Tile[j + (int)_curShape->GetPos().y][i + (int)_curShape->GetPos().x] = _curShape->tetriminos[_curShape->_shape][_curShape->_pattern][j][i];

				while (i + (int)_curShape->GetPos().x >= STAGE_WIDTH)	_curShape->SetPos(_curShape->GetPos() + vec2(-1, 0));
				while (i + (int)_curShape->GetPos().x < 0)				_curShape->SetPos(_curShape->GetPos() + vec2(1, 0));
				while (j + (int)_curShape->GetPos().y >= STAGE_HEITH)	_curShape->SetPos(_curShape->GetPos() + vec2(0, -1));
			}
		}
	}

	for (auto it : ShapeMNG::GetInstance()->v_Shapes)
	{
		if (it->_active) _curShape = it;
		else
		{
			// 맨 윗줄에서 블럭이 죽으면 게임오버
			if (it->GetPos().y == 0)
			{
				Game = false;
				GameOver->_visible = true;
			}
			// 죽은 조각의 위치정보를 Tile에 전송
			if (!it->_deathBlock)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						if (it->tetriminos[it->_shape][it->_pattern][j][i])
						{
							if (j + (int)it->GetPos().y >= STAGE_HEITH) break;
							Tile[j + (int)it->GetPos().y][i + (int)it->GetPos().x] = it->tetriminos[it->_shape][it->_pattern][j][i];
							sprTile[j + (int)it->GetPos().y][i + (int)it->GetPos().x]->_color = it->_color;
							if (Tile[j + (int)it->GetPos().y][i + (int)it->GetPos().x] == 1)
							{
								Tile[j + (int)it->GetPos().y][i + (int)it->GetPos().x]++;
								it->_deathBlock = true;
							}
						}
					}
				}
			}
		}
	}

	// 현재 조각의 잔상없애기
	for (int j = 0; j < STAGE_HEITH; j++)
		for (int i = 0; i < STAGE_WIDTH; i++)
			if (Tile[j][i] == 1) Tile[j][i] = 0;

	// 현재 조각의 위치정보를 Tile에 전송
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (_curShape->tetriminos[_curShape->_shape][_curShape->_pattern][j][i])
			{
				Tile[j + (int)_curShape->GetPos().y][i + (int)_curShape->GetPos().x] = _curShape->tetriminos[_curShape->_shape][_curShape->_pattern][j][i];
				sprTile[j + (int)_curShape->GetPos().y][i + (int)_curShape->GetPos().x]->_color = _curShape->_color;
				if (j + (int)_curShape->GetPos().y == STAGE_HEITH - 1)
				{
					_curShape->_hit = true;
					if (_curShape->_cooldown > 0.5) CreateShape();
				}
				if (Tile[(int)_curShape->GetPos().y + 1 + j][(int)_curShape->GetPos().x + i] == 2)
				{
					_curShape->_hit = true;
					if (_curShape->_cooldown > 0.5) CreateShape();
				}
			}
		}
	}

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 5; i++)
				holdTile[j][i]->_color = COLOR(255,255,255,255);

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if(_holdShape != -1)
				if (_curShape->tetriminos[_holdShape][0][j][i])
					holdTile[j + 1][i + 1]->_color = _holdcolor;



	// 한 줄이 인식되면 한줄 지우고 스왑.
	int lineStack = 0;
	for (int j = 0; j < STAGE_HEITH; j++)
	{
		for (int i = 0; i < STAGE_WIDTH; i++)
		{
			if (Tile[j][i] == 2) lineStack++;
			if (lineStack == STAGE_WIDTH)
			{
				cout << "줄 지워짐" << endl;
				_score += 50;
				for (int z = 0; z < STAGE_WIDTH; z++)
					Tile[j][z] = 0;

				for (int q = j - 1; q > 0; q--)
				{
					for (int a = 0; a < STAGE_WIDTH; a++)
					{
						int temp = Tile[q + 1][a];
						Tile[q + 1][a] = Tile[q][a];
						Tile[q][a] = temp;
						
						COLOR temp2 = sprTile[q + 1][a]->_color;
						sprTile[q + 1][a]->_color = sprTile[q][a]->_color;
						sprTile[q][a]->_color = temp2;
					}
				}
			}
		}
		lineStack = 0;
	}

	// Tile 흰색 초기화
	for (int j = 0; j < STAGE_HEITH; j++)
		for (int i = 0; i < STAGE_WIDTH; i++)
			if (Tile[j][i] == 0) sprTile[j][i]->_color = COLOR(255, 255, 255, 255);
}

void GameScene::OnExit()
{
	delete Logo;
	delete GameOver;

	for (int j = 0; j < STAGE_HEITH; j++)
	{
		for (int i = 0; i < STAGE_WIDTH; i++)
		{
			Tile[j][i] = 0;
			delete sprTile[j][i];
		}
	}
	
	for (auto it : ShapeMNG::GetInstance()->v_Shapes)
	{
		if(!it->_active)
			delete it;
	}
	ShapeMNG::GetInstance()->v_Shapes.clear();
}

void GameScene::CreateShape()
{
	_curShape->_active = false;

	if (_curShape->_Gameover) Game = false;
	if (!Game) return;

	_curShape = new Shape();
	_curShape->SetMino();
	_curShape->SetPos(vec2(4, 0));
	ShapeMNG::GetInstance()->v_Shapes.push_back(_curShape);
	_isHold = true;
}
