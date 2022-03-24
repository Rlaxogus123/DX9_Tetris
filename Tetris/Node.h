#pragma once
class Node
{
public:
	Node();
	virtual ~Node() {};

	D3DXMATRIX GetMatrix();
	virtual void Draw() {};
	virtual void Update() {};

	vec2 _position;
	vec2 _scale;
	vec2 _pivot;
	vec2 _v;

	float _rotation;

	bool _visible;
	bool _isUI;

	COLOR _color;

	int _layer;
};

