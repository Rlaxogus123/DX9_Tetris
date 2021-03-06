#include "DXUT.h"
#include "Include.h"

Texture* TextureManager::LoadTexture(wstring path)
{
	for (auto it : _texturelist)
	{
		if (it->_filename == path)
			return it;
	}

	auto route = L"res/" + path;
	Texture* texture = new Texture();
	texture->_filename = path;

	auto isFail = D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), route.c_str(), -2, -2, 1, 0, D3DFORMAT::D3DFMT_A8B8G8R8,
		D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &texture->_info, nullptr, &texture->_texture);

	if (FAILED(isFail))
	{
		wcout << "FAIL!!" << route << endl;
		delete texture;
		return nullptr;
	}
	else
	{
		wcout << "LOAD!!" << route << endl;
		_texturelist.push_back(texture);
		return texture;
	}
}
