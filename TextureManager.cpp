#include "DXUT.h"
#include "TextureManager.h"

USING_NS_DX2DX;

SINGLETONE_INSTANCE_INIT(TextureManager, nullptr);

TextureManager::TextureManager()
{
	_TexturePool.reserve(50);
}


TextureManager::~TextureManager()
{
	DeleteAllTexture();
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(LPCWSTR fileDir)
{
	for (auto tex : _TexturePool)
	{
		if (tex.fileDir == fileDir)
		{
			return tex.texture;
		}
	}

	LPDIRECT3DTEXTURE9 texture = nullptr;

	D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), fileDir,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		NULL, NULL, NULL, &texture);



	_TexturePool.push_back(TextureInfo{fileDir, texture});

	return texture;
}

void TextureManager::DeleteTexture(LPCWSTR fileDir)
{
	for (auto iter = _TexturePool.begin(); iter != _TexturePool.end(); iter++)
	{
		auto tex = *iter;
		if (tex.fileDir == fileDir)
		{
			tex.texture->Release();
			_TexturePool.erase(iter);
			return;
		}
	}
	LOG("TexturePool::DeleteTexture(LPCWSTR)에서 제거대상을 찾지못함.\n");
}

void TextureManager::DeleteTexture(LPDIRECT3DTEXTURE9 texture)
{
	for (auto iter = _TexturePool.begin(); iter != _TexturePool.end(); iter++)
	{
		auto tex = *iter;
		if (tex.texture == texture)
		{
			tex.texture->Release();
			_TexturePool.erase(iter);
			return;
		}
	}
	LOG("TexturePool::DeleteTexture(LPDIRECT3DTEXTURE9)에서 제거대상을 찾지못함.\n");
}

void TextureManager::DeleteAllTexture()
{
	for (auto tex : _TexturePool)
	{
		tex.texture->Release();
	}

	_TexturePool.erase(_TexturePool.begin(), _TexturePool.end());
}