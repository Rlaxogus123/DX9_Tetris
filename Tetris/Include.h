#pragma once

#include "DXUT.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <list>
#include <string>

using namespace std;

typedef D3DXVECTOR3 vec3;
typedef D3DXVECTOR2 vec2;
typedef D3DXCOLOR COLOR;

#define ScreenWidth 1280
#define ScreenHeigth 720

#define STAGE_WIDTH 10
#define STAGE_HEITH 20

extern int Tile[STAGE_HEITH][STAGE_WIDTH];

#include "Scene.h"
#include "Singleton.h"
#include "Director.h"
#include "Node.h"
#include "Texture.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Camera.h"
#include "SoundManager.h"

#include "Shape.h"

#include "GameScene.h"
