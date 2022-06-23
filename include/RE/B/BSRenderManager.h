#pragma once

#include "RE/N/NiTexture.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView1;
struct ID3D11ShaderResourceView1;

namespace RE
{
	class BSRenderManager
	{
	public:
		[[nodiscard]] static BSRenderManager* GetSingleton() noexcept
		{
			REL::Relocation<BSRenderManager**> singleton{ RELOCATION_ID(524907, 411393) };
			return *singleton;
		}

		[[nodiscard]] NiTexture::RendererData* CreateRenderTexture(std::uint32_t a_width, std::uint32_t a_height)
		{
			using func_t = decltype(&BSRenderManager::CreateRenderTexture);
			REL::Relocation<func_t> func{ RELOCATION_ID(75507, 77299) };
			return func(this, a_width, a_height);
		}

		std::uint64_t                  unk00[0x48 >> 3];             // 0000
		ID3D11Device*                  forwarder;                    // 0048
		ID3D11DeviceContext*           context;                      // 0050
		std::uint64_t                  unk58;                        // 0058
		std::uint64_t                  unk60;                        // 0060
		std::uint64_t                  unk68;                        // 0068
		IDXGISwapChain*                swapChain;                    // 0070
		std::uint64_t                  unk78;                        // 0078
		std::uint64_t                  unk80;                        // 0080
		ID3D11RenderTargetView1*       renderView;                   // 0088
		ID3D11ShaderResourceView1*     resourceView;                 // 0090
		std::uint64_t                  unk98[(0x2788 - 0x90) >> 3];  // 0098
		SKSE::WinAPI::CRITICAL_SECTION lock;                         // 2790
	};
	static_assert(sizeof(BSRenderManager) == 0x27B8);
}
