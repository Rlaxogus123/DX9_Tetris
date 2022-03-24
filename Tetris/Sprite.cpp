#include "DXUT.h"
#include "Include.h"

Sprite::Sprite()
{
	_sprite = nullptr;
	_texture = nullptr;
	D3DXCreateSprite(DXUTGetD3D9Device(), &_sprite);
}

Sprite::~Sprite()
{
	Renderer::GetInstance()->DeleteRenderTarget(this);
}

void Sprite::SetTexture(wstring path)
{
	_texture = TextureManager::GetInstance()->LoadTexture(path);
	AddRenderTarget();
}

void Sprite::AddRenderTarget()
{
	Renderer::GetInstance()->AddRenderTarget(this);
}

RECT Sprite::GetRect()
{
	RECT r;
	r.right		= _position.x + (_texture->_info.Width / 2 * _scale.x);
	r.left		= _position.x - (_texture->_info.Width / 2 * _scale.x);
	r.bottom	= _position.y + (_texture->_info.Height / 2 * _scale.y);
	r.top		= _position.y - (_texture->_info.Height / 2 * _scale.y);
	return r;
}

void Sprite::Draw()
{
	if (!_visible) return;
	if (_texture == nullptr) return;

	_isUI ? _sprite->Begin(D3DXSPRITE_ALPHABLEND) : _sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	_sprite->SetTransform(&GetMatrix());
	vec3 centor = { _pivot.x * _texture->_info.Width, _pivot.y * _texture->_info.Height,0 };
	_sprite->Draw(_texture->_texture, nullptr, &centor, nullptr, _color);
	_sprite->End();
}
