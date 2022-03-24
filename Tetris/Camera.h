#pragma once
class Camera : public Singleton<Camera>
{
private:
	D3DXMATRIX OM;
	D3DXMATRIX IM;
	D3DXMATRIX VM;
	vec2 _camPos;
	float _camSize;

public:
	void CameraInit();
	void CameraUpdate();

	void setPosition(vec2 v) { _camPos.x = v.x, _camPos.y = v.y; };
	vec2 getPosition() { return _camPos; };
	void setScale(float f) { _camSize = f; };
	float getScale() { return _camSize; };
};

