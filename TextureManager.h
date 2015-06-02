#pragma once
#include "dx2dxMacros.h"
#include <vector>

NS_DX2DX
{
	class TextureManager final
	{
		struct TextureInfo
		{
			std::wstring fileDir;
			LPDIRECT3DTEXTURE9 texture;
		};

	private:
		SINGLETONE(TextureManager)

	private:
		std::vector<TextureInfo> _TexturePool;

	public:
		LPDIRECT3DTEXTURE9 GetTexture(LPCWSTR fileDir);
				
		void DeleteTexture(LPCWSTR fileDir);
		void DeleteTexture(LPDIRECT3DTEXTURE9 texture);

		void DeleteAllTexture();
	};
}