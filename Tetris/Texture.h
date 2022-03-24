#pragma once

class Texture
{
public:
	D3DXIMAGE_INFO _info;
	LPDIRECT3DTEXTURE9 _texture;
	wstring _filename;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	list<Texture*> _texturelist;
public:
	Texture* LoadTexture(wstring path);
};