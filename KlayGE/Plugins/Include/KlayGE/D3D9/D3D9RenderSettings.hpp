#ifndef _D3D9RENDERSETTINGS_HPP
#define _D3D9RENDERSETTINGS_HPP

#include <d3d9.h>
#include <KlayGE/RenderSettings.hpp>

#pragma comment(lib, "KlayGE_RenderEngine_D3D9.lib")

namespace KlayGE
{
	// 建立渲染窗口的设置
	/////////////////////////////////////////////////////////////////////////////////
	struct D3D9RenderSettings : public RenderSettings
	{
		D3D9RenderSettings()
			: multiSample(0)
			{ }
		virtual ~D3D9RenderSettings()
			{ }

		U32 multiSample;

		bool ConfirmDevice(const D3DCAPS9& caps, U32 behavior, D3DFORMAT format) const
		{
			if (caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
			{
				return false;
			}
			return this->DoConfirmDevice(caps, behavior, format);
		}

	private:
		virtual bool DoConfirmDevice(const D3DCAPS9& /*caps*/, U32 /*behavior*/, D3DFORMAT /*format*/) const
			{ return true; }
	};
}

#endif			// _D3D9RENDERSETTINGS_HPP
