#include "DXUT.h"
#include "Include.h"

Node::Node()
{
	_position = { 0,0 };
	_scale = { 1,1 };
	_pivot = { 0.5f,0.5f };
	_v = {0,0};

	_rotation = 0;

	_visible = true;
	_isUI = false;

	_color = COLOR(255,255,255,255);

	_layer = 0;
}

D3DXMATRIX Node::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTransformation2D(&m, nullptr, 0, &_scale, nullptr, _rotation, &_position);
	return m;
}
