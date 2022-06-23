#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiFrustum.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSCullingProcess;
	class BSLight;
	class BSShaderAccumulator;
	class NiCamera;
	class NiNode;
	class ShadowSceneNode;
	class TESImageSpaceModifier;

	enum class INTERFACE_LIGHT_SCHEME
	{
		kJournal = 0,
		kInventory,
		kInventoryMagic,
		kBook,
		kLoading,
		kUnk05,
		kStats,
		kLockpicking,

		kTotal = 8
	};

	class UI3DSceneManager : public BSTSingletonSDM<UI3DSceneManager>
	{
	public:
		struct MenuLight
		{
		public:
			// members
			NiColor            color;         // 00
			NiPoint3           translate;     // 0C
			float              radius;        // 18
			float              fade;          // 1C
			bool               castsShadows;  // 20
			NiPointer<BSLight> light;         // 28
			MenuLight*         last;          // 30
		};
		static_assert(sizeof(MenuLight) == 0x38);

		static UI3DSceneManager* GetSingleton()
		{
			REL::Relocation<UI3DSceneManager**> singleton{ RELOCATION_ID(517052, 403560) };
			return *singleton;
		}

		// members
		std::uint8_t                               pad01;               // 01
		std::uint16_t                              pad02;               // 02
		std::uint32_t                              pad04;               // 04
		BSCullingProcess*                          cullingProcess;      // 08
		NiPointer<BSShaderAccumulator>             unk10;               // 10
		NiPointer<BSShaderAccumulator>             unk18;               // 18
		NiPointer<NiCamera>                        camera;              // 20
		mutable BSSpinLock                         lock;                // 28
		ShadowSceneNode*                           shadowSceneNode;     // 30
		NiPointer<NiNode>                          menuObjects[8];      // 38
		BSTArray<MenuLight*>                       menuLights;          // 78
		INTERFACE_LIGHT_SCHEME                     currentlightScheme;  // 90
		std::uint32_t                              pad94;               // 94
		BSTArray<INTERFACE_LIGHT_SCHEME>           lightSchemes;        // 98
		BSTArray<NiPointer<TESImageSpaceModifier>> ImageSpaceMods;      // B0
		NiPoint3                                   cachedCameraPos;     // C8
		NiMatrix3                                  cachedCameraRot;     // D0
		NiFrustum                                  viewFrustum;         // F8
	};
	static_assert(sizeof(UI3DSceneManager) == 0x118);
}
