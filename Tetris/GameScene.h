#pragma once

class GameScene : public Scene
{
public:
	virtual void Init();
	virtual void Update();
	virtual void OnExit();

	void CreateShape();

	Sprite* sprTile[STAGE_HEITH][STAGE_WIDTH];
	Sprite* holdTile[4][5];
	int Tile[STAGE_HEITH + 1][STAGE_WIDTH];

	Sprite* Logo;
	Sprite* GameOver;

	Shape* _curShape;

	vec2 camPos;
	vec2 tetrisPos;

	float GameSpeed;
	float tick;

	int _holdShape;
	COLOR _holdcolor;
	bool _isHold;

	int _score;
	LPD3DXFONT _font;

	bool Game;
};

