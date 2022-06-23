#include "RE/A/Actor.h"

#include "RE/A/AIProcess.h"
#include "RE/B/BGSAttackData.h"
#include "RE/B/BGSColorForm.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSAnimationGraphManager.h"
#include "RE/B/BSFaceGenAnimationData.h"
#include "RE/B/BSFaceGenNiNode.h"
#include "RE/B/BShkbAnimationGraph.h"
#include "RE/B/bhkCharacterController.h"
#include "RE/E/ExtraCanTalkToPlayer.h"
#include "RE/E/ExtraFactionChanges.h"
#include "RE/F/FormTraits.h"
#include "RE/H/HighProcessData.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/M/MiddleHighProcessData.h"
#include "RE/M/Misc.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiMath.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/ProcessLists.h"
#include "RE/T/TESFaction.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESObjectMISC.h"
#include "RE/T/TESRace.h"
#include "RE/T/TESWorldSpace.h"

namespace RE
{
	NiPointer<Actor> Actor::LookupByHandle(RefHandle a_refHandle)
	{
		NiPointer<Actor> ref;
		LookupReferenceByHandle(a_refHandle, ref);
		return ref;
	}

	bool Actor::LookupByHandle(RefHandle a_refHandle, NiPointer<Actor>& a_refrOut)
	{
		return LookupReferenceByHandle(a_refHandle, a_refrOut);
	}

	bool Actor::AddAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const
	{
		BSAnimationGraphManagerPtr graphManager;
		GetAnimationGraphManager(graphManager);
		if (graphManager) {
			bool sinked = false;
			for (const auto& animationGraph : graphManager->graphs) {
				if (sinked) {
					break;
				}
				const auto eventSource = animationGraph->GetEventSource<BSAnimationGraphEvent>();
				for (const auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						sinked = true;
						break;
					}
				}
			}
			if (!sinked) {
				graphManager->graphs.front()->GetEventSource<BSAnimationGraphEvent>()->AddEventSink(a_sink);
				return true;
			}
		}
		return false;
	}

	bool Actor::AddSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::AddSpell);
		REL::Relocation<func_t> func{ Offset::Actor::AddSpell };
		return func(this, a_spell);
	}

	void Actor::AddToFaction(TESFaction* a_faction, std::int8_t a_rank)
	{
		using func_t = decltype(&Actor::AddToFaction);
		REL::Relocation<func_t> func{ RELOCATION_ID(36678, 37686) };
		return func(this, a_faction, a_rank);
	}

	void Actor::AllowBleedoutDialogue(bool a_canTalk)
	{
		if (a_canTalk) {
			boolFlags.set(BOOL_FLAGS::kCanSpeakToEssentialDown);
		} else {
			boolFlags.reset(BOOL_FLAGS::kCanSpeakToEssentialDown);
		}
	}

	void Actor::AllowPCDialogue(bool a_talk)
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (!xTalk) {
			xTalk = new ExtraCanTalkToPlayer();
			extraList.Add(xTalk);
		}

		xTalk->talk = a_talk;
	}

	bool Actor::CanAttackActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::CanAttackActor);
		REL::Relocation<func_t> func{ RELOCATION_ID(36532, 37532) };
		return func(this, a_actor);
	}

	bool Actor::CanFlyHere() const
	{
		const auto* worldSpace = GetWorldspace();
		return worldSpace && worldSpace->HasMaxHeightData();
	}

	bool Actor::CanOfferServices() const
	{
		const auto* vendorFac = GetVendorFaction();
		return vendorFac ? vendorFac->OffersServices() : false;
	}

	bool Actor::CanPickpocket() const
	{
		if (!race) {
			return false;
		}

		return race->AllowsPickpocket() && !IsPlayerTeammate();
	}

	bool Actor::CanTalkToPlayer() const
	{
		auto xTalk = extraList.GetByType<ExtraCanTalkToPlayer>();
		if (xTalk) {
			return xTalk->talk;
		} else {
			return race != nullptr && race->AllowsPCDialogue();
		}
	}

	void Actor::ClearArrested()
	{
		if (currentProcess && currentProcess->IsArrested()) {
			currentProcess->SetArrested(false);
			EvaluatePackage(false, false);
			auto procManager = ProcessLists::GetSingleton();
			if (procManager) {
				procManager->StopCombatAndAlarmOnActor(this, true);
			}
		}
	}

	void Actor::ClearExpressionOverride()
	{
		auto faceGen = GetFaceGenAnimationData();
		if (faceGen) {
			faceGen->ClearExpressionOverride();
		}
	}

	ActorHandle Actor::CreateRefHandle()
	{
		return GetHandle();
	}

	bool Actor::Decapitate()
	{
		using func_t = decltype(&Actor::Decapitate);
		REL::Relocation<func_t> func{ RELOCATION_ID(36631, 37639) };
		return func(this);
	}

	void Actor::DeselectSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::DeselectSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37820, 38769) };
		return func(this, a_spell);
	}

	void Actor::DispelWornItemEnchantments()
	{
		using func_t = decltype(&Actor::DispelWornItemEnchantments);
		REL::Relocation<func_t> func{ Offset::Actor::DispelWornItemEnchantments };
		return func(this);
	}

	void Actor::DoReset3D(bool a_updateWeight)
	{
		using func_t = decltype(&Actor::DoReset3D);
		REL::Relocation<func_t> func{ Offset::Actor::DoReset3D };
		return func(this, a_updateWeight);
	}

	void Actor::EnableAI(bool a_enable)
	{
		if (a_enable) {
			boolBits.set(BOOL_BITS::kProcessMe);
		} else {
			boolBits.reset(BOOL_BITS::kProcessMe);
			if (const auto controller = GetCharController()) {
				controller->SetLinearVelocityImpl(0.0f);
			}
		}
	}

	void Actor::EvaluatePackage(bool a_immediate, bool a_resetAI)
	{
		using func_t = decltype(&Actor::EvaluatePackage);
		REL::Relocation<func_t> func{ RELOCATION_ID(36407, 37401) };
		return func(this, a_immediate, a_resetAI);
	}

	TESNPC* Actor::GetActorBase()
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	const TESNPC* Actor::GetActorBase() const
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	float Actor::GetActorValueModifier(ACTOR_VALUE_MODIFIER a_modifier, ActorValue a_value) const
	{
		using func_t = decltype(&Actor::GetActorValueModifier);
		REL::Relocation<func_t> func{ RELOCATION_ID(37524, 38469) };
		return func(this, a_modifier, a_value);
	}

	InventoryEntryData* Actor::GetAttackingWeapon()
	{
		if (!currentProcess || !currentProcess->high || !currentProcess->high->attackData || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = currentProcess->high->attackData;
		auto proc = currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	const InventoryEntryData* Actor::GetAttackingWeapon() const
	{
		if (!currentProcess || !currentProcess->high || !currentProcess->high->attackData || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto attackData = currentProcess->high->attackData;
		auto proc = currentProcess->middleHigh;

		return attackData->IsLeftAttack() ? proc->leftHand : proc->rightHand;
	}

	bhkCharacterController* Actor::GetCharController() const
	{
		return currentProcess ? currentProcess->GetCharController() : nullptr;
	}

	uint32_t Actor::GetCollisionFilterInfo(uint32_t& a_outCollisionFilterInfo)
	{
		using func_t = decltype(&Actor::GetCollisionFilterInfo);
		REL::Relocation<func_t> func{ RELOCATION_ID(36559, 37560) };
		return func(this, a_outCollisionFilterInfo);
	}

	NiPointer<Actor> Actor::GetCommandingActor() const
	{
		return currentProcess ? currentProcess->GetCommandingActor().get() : NiPointer<Actor>{};
	}

	TESFaction* Actor::GetCrimeFaction()
	{
		return GetCrimeFactionImpl();
	}

	const TESFaction* Actor::GetCrimeFaction() const
	{
		return GetCrimeFactionImpl();
	}

	InventoryEntryData* Actor::GetEquippedEntryData(bool a_leftHand) const
	{
		if (!currentProcess || !currentProcess->middleHigh) {
			return nullptr;
		}

		auto proc = currentProcess->middleHigh;
		return a_leftHand ? proc->leftHand : proc->rightHand;
	}

	TESForm* Actor::GetEquippedObject(bool a_leftHand) const
	{
		if (currentProcess) {
			if (a_leftHand) {
				return currentProcess->GetEquippedLeftHand();
			} else {
				return currentProcess->GetEquippedRightHand();
			}
		} else {
			return nullptr;
		}
	}

	std::int32_t Actor::GetGoldAmount()
	{
		const auto inv = GetInventory([](TESBoundObject& a_object) -> bool {
			return a_object.IsGold();
		});

		const auto dobj = BGSDefaultObjectManager::GetSingleton();
		if (!dobj) {
			return 0;
		}

		const auto gold = dobj->GetObject<TESObjectMISC>(DEFAULT_OBJECT::kGold);
		const auto it = inv.find(gold);
		return it != inv.end() ? it->second.first : 0;
	}

	ActorHandle Actor::GetHandle()
	{
		return ActorHandle(this);
	}

	NiAVObject* Actor::GetHeadPartObject(BGSHeadPart::HeadPartType a_type)
	{
		const auto actorBase = GetActorBase();
		const auto faceNode = GetFaceNodeSkinned();
		const auto facePart = actorBase ? actorBase->GetCurrentHeadPartByType(a_type) : nullptr;
		return faceNode && facePart ? faceNode->GetObjectByName(facePart->formEditorID) : nullptr;
	}

	float Actor::GetHeight()
	{
		const auto min = GetBoundMin();
		const auto max = GetBoundMax();
		const auto diff = max.z - min.z;
		const auto height = GetBaseHeight() * diff;

		if (!currentProcess || !currentProcess->InHighProcess()) {
			return height;
		}

		const auto cachedHeight = currentProcess->GetCachedHeight();
		if (cachedHeight == 0.0) {
			currentProcess->SetCachedHeight(height);
			return height;
		} else {
			return cachedHeight;
		}
	}

	Actor* Actor::GetKiller() const
	{
		if (IsDead(false)) {
			return nullptr;
		}

		return myKiller.get().get();
	}

	std::uint16_t Actor::GetLevel() const
	{
		using func_t = decltype(&Actor::GetLevel);
		REL::Relocation<func_t> func{ Offset::Actor::GetLevel };
		return func(this);
	}

	bool Actor::GetMount(NiPointer<Actor>& a_outMount)
	{
		using func_t = decltype(&Actor::GetMount);
		REL::Relocation<func_t> func{ RELOCATION_ID(37757, 38702) };
		return func(this, a_outMount);
	}

	bool Actor::GetMountedBy(NiPointer<Actor>& a_outRider)
	{
		using func_t = decltype(&Actor::GetMountedBy);
		REL::Relocation<func_t> func{ RELOCATION_ID(37758, 38703) };
		return func(this, a_outRider);
	}

	ObjectRefHandle Actor::GetOccupiedFurniture() const
	{
		if (currentProcess) {
			return currentProcess->GetOccupiedFurniture();
		} else {
			return {};
		}
	}

	TESRace* Actor::GetRace() const
	{
		auto base = GetActorBase();
		return base ? base->race : nullptr;
	}

	bool Actor::GetRider(NiPointer<Actor>& a_outRider)
	{
		using func_t = decltype(&Actor::GetRider);
		REL::Relocation<func_t> func{ RELOCATION_ID(37758, 38703) };
		return func(this, a_outRider);
	}

	TESObjectARMO* Actor::GetSkin() const
	{
		if (const auto base = GetActorBase(); base && base->skin) {
			return base->skin;
		} else if (const auto aRace = GetRace(); aRace && aRace->skin) {
			return aRace->skin;
		}
		return nullptr;
	}

	TESObjectARMO* Actor::GetSkin(BGSBipedObjectForm::BipedObjectSlot a_slot)
	{
		if (const auto worn = GetWornArmor(a_slot); worn) {
			return worn;
		}
		return GetSkin();
	}

	SOUL_LEVEL Actor::GetSoulSize() const
	{
		using func_t = decltype(&Actor::GetSoulSize);
		REL::Relocation<func_t> func{ RELOCATION_ID(37862, 38817) };
		return func(this);
	}

	TESFaction* Actor::GetVendorFaction()
	{
		if (!vendorFaction) {
			CalculateCurrentVendorFaction();
		}
		return vendorFaction;
	}

	const TESFaction* Actor::GetVendorFaction() const
	{
		if (!vendorFaction) {
			CalculateCurrentVendorFaction();
		}
		return vendorFaction;
	}

	TESObjectARMO* Actor::GetWornArmor(BGSBipedObjectForm::BipedObjectSlot a_slot)
	{
		const auto inv = GetInventory([](TESBoundObject& a_object) {
			return a_object.IsArmor();
		});

		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count > 0 && entry->IsWorn()) {
				const auto armor = item->As<TESObjectARMO>();
				if (armor && armor->HasPartOf(a_slot)) {
					return armor;
				}
			}
		}

		return nullptr;
	}

	TESObjectARMO* Actor::GetWornArmor(FormID a_formID)
	{
		const auto inv = GetInventory([=](TESBoundObject& a_object) {
			return a_object.IsArmor() && a_object.GetFormID() == a_formID;
		});

		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count > 0 && entry->IsWorn()) {
				return item->As<TESObjectARMO>();
			}
		}

		return nullptr;
	}

	bool Actor::HasKeywordString(std::string_view a_formEditorID)
	{
		const auto base = GetActorBase();
		return base && base->HasApplicableKeywordString(a_formEditorID);
	}

	bool Actor::HasLineOfSight(TESObjectREFR* a_ref, bool& a_arg2)
	{
		using func_t = decltype(&Actor::HasLineOfSight);
		REL::Relocation<func_t> func{ RELOCATION_ID(53029, 53829) };
		return func(this, a_ref, a_arg2);
	}

	bool Actor::HasPerk(BGSPerk* a_perk) const
	{
		using func_t = decltype(&Actor::HasPerk);
		REL::Relocation<func_t> func{ Offset::Actor::HasPerk };
		return func(this, a_perk);
	}

	bool Actor::HasSpell(SpellItem* a_spell) const
	{
		using func_t = decltype(&Actor::HasSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37828, 38782) };
		return func(this, a_spell);
	}

	void Actor::InterruptCast(bool a_restoreMagicka) const
	{
		using func_t = decltype(&Actor::InterruptCast);
		REL::Relocation<func_t> func{ RELOCATION_ID(37808, 38757) };
		return func(this, a_restoreMagicka);
	}

	bool Actor::IsAIEnabled() const
	{
		return boolBits.all(BOOL_BITS::kProcessMe);
	}

	bool Actor::IsAMount() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsAMount);
	}

	bool Actor::IsAnimationDriven() const
	{
		bool result = false;
		return GetGraphVariableBool("bAnimationDriven", result) && result;
	}

	bool Actor::IsBeingRidden() const
	{
		return IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsBlocking() const
	{
		using func_t = decltype(&Actor::IsBlocking);
		REL::Relocation<func_t> func{ RELOCATION_ID(36927, 37952) };
		return func(this);
	}

	bool Actor::IsCasting(MagicItem* a_spell) const
	{
		using func_t = decltype(&Actor::IsCasting);
		REL::Relocation<func_t> func{ RELOCATION_ID(37810, 38759) };
		return func(this, a_spell);
	}

	bool Actor::IsCommandedActor() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsCommandedActor);
	}

	bool Actor::IsEssential() const
	{
		return boolFlags.all(BOOL_FLAGS::kEssential);
	}

	bool Actor::IsFactionInCrimeGroup(const TESFaction* a_faction) const
	{
		auto crimFac = GetCrimeFaction();
		if (!crimFac) {
			return false;
		}

		if (crimFac == a_faction) {
			return true;
		} else {
			return crimFac->IsFactionInCrimeGroup(a_faction);
		}
	}

	bool Actor::IsGhost() const
	{
		using func_t = decltype(&Actor::IsGhost);
		REL::Relocation<func_t> func{ Offset::Actor::GetGhost };
		return func(this);
	}

	bool Actor::IsGuard() const
	{
		return boolBits.all(BOOL_BITS::kGuard);
	}

	bool Actor::IsHostileToActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::IsHostileToActor);
		REL::Relocation<func_t> func{ Offset::Actor::GetHostileToActor };
		return func(this, a_actor);
	}

	bool Actor::IsLimbGone(std::uint32_t a_limb)
	{
		using func_t = decltype(&Actor::IsLimbGone);
		REL::Relocation<func_t> func{ RELOCATION_ID(19338, 19765) };
		return func(this, a_limb);
	}

	bool Actor::IsInMidair() const
	{
		using func_t = decltype(&Actor::IsInMidair);
		REL::Relocation<func_t> func{ RELOCATION_ID(36259, 37243) };
		return func(this);
	}

	bool Actor::IsInRagdollState() const
	{
		using func_t = decltype(&Actor::IsInRagdollState);
		REL::Relocation<func_t> func{ RELOCATION_ID(36492, 37491) };
		return func(this);
	}

	bool Actor::IsOnMount() const
	{
		return !IsAMount() && extraList.HasType(ExtraDataType::kInteraction);
	}

	bool Actor::IsOverEncumbered() const
	{
		using func_t = decltype(&Actor::IsOverEncumbered);
		REL::Relocation<func_t> func{ RELOCATION_ID(36457, 37453) };
		return func(this);
	}

	bool Actor::IsPlayerTeammate() const
	{
		return boolBits.all(BOOL_BITS::kPlayerTeammate);
	}

	float Actor::IsPointDeepUnderWater(float a_zPos, TESObjectCELL* a_cell)
	{
		auto waterHeight = !a_cell || a_cell == parentCell ? GetWaterHeight() : a_cell->GetExteriorWaterHeight();

		if (waterHeight == -NI_INFINITY && a_cell) {
			waterHeight = a_cell->GetExteriorWaterHeight();
		}

		if (waterHeight <= a_zPos) {
			return 0.0f;
		}

		return std::fminf((waterHeight - a_zPos) / GetHeight(), 1.0f);
	}

	bool Actor::IsRunning() const
	{
		using func_t = decltype(&Actor::IsRunning);
		REL::Relocation<func_t> func{ Offset::Actor::IsRunning };
		return func(this);
	}

	bool Actor::IsSneaking() const
	{
		if (!ActorState::IsSneaking()) {
			return false;
		}

		if (ActorState::IsSwimming()) {
			return false;
		}

		if (IsOnMount()) {
			return false;
		}

		return true;
	}

	bool Actor::IsPointSubmergedMoreThan(const NiPoint3& a_pos, TESObjectCELL* a_cell, const float a_waterLevel)
	{
		return IsPointDeepUnderWater(a_pos.z, a_cell) >= a_waterLevel;
	}

	bool Actor::IsSummoned() const noexcept
	{
		return currentProcess && currentProcess->GetIsSummonedCreature();
	}

	bool Actor::IsTrespassing() const
	{
		return boolFlags.all(BOOL_FLAGS::kIsTrespassing);
	}

	void Actor::KillImmediate()
	{
		using func_t = decltype(&Actor::KillImmediate);
		REL::Relocation<func_t> func{ RELOCATION_ID(36723, 37735) };
		return func(this);
	}

	void Actor::RemoveAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const
	{
		BSAnimationGraphManagerPtr graphManager;
		GetAnimationGraphManager(graphManager);
		if (graphManager) {
			bool sinked = true;
			for (const auto& animationGraph : graphManager->graphs) {
				if (!sinked) {
					break;
				}
				const auto eventSource = animationGraph->GetEventSource<BSAnimationGraphEvent>();
				for (const auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						eventSource->RemoveEventSink(a_sink);
						sinked = false;
						break;
					}
				}
			}
		}
	}

	void Actor::RemoveExtraArrows3D()
	{
		extraList.RemoveByType(ExtraDataType::kAttachedArrows3D);
	}

	bool Actor::RemoveSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::RemoveSpell);
		REL::Relocation<func_t> func{ RELOCATION_ID(37772, 38717) };
		return func(this, a_spell);
	}

	std::int32_t Actor::RequestDetectionLevel(Actor* a_target, DETECTION_PRIORITY a_priority)
	{
		using func_t = decltype(&Actor::RequestDetectionLevel);
		REL::Relocation<func_t> func{ Offset::Actor::RequestDetectionLevel };
		return func(this, a_target, a_priority);
	}

	void Actor::SetRotationX(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationX);
		REL::Relocation<func_t> func{ RELOCATION_ID(36602, 37610) };
		return func(this, a_angle);
	}

	void Actor::SetRotationZ(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationZ);
		REL::Relocation<func_t> func{ RELOCATION_ID(36248, 37230) };
		return func(this, a_angle);
	}

	void Actor::SetLifeState(ACTOR_LIFE_STATE a_lifeState)
	{
		using func_t = decltype(&Actor::SetLifeState);
		REL::Relocation<func_t> func{ RELOCATION_ID(36604, 37612) };
		return func(this, a_lifeState);
	}

	void Actor::StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner, bool a_allowWarning)
	{
		using func_t = decltype(&Actor::StealAlarm);
		REL::Relocation<func_t> func{ RELOCATION_ID(36427, 37422) };
		return func(this, a_ref, a_object, a_num, a_total, a_owner, a_allowWarning);
	}

	void Actor::StopInteractingQuick(bool a_unk02)
	{
		using func_t = decltype(&Actor::StopInteractingQuick);
		REL::Relocation<func_t> func{ RELOCATION_ID(37752, 38697) };
		return func(this, a_unk02);
	}

	void Actor::StopMoving(float a_delta)
	{
		using func_t = decltype(&Actor::StopMoving);
		REL::Relocation<func_t> func{ RELOCATION_ID(36801, 37817) };
		return func(this, a_delta);
	}

	void Actor::SwitchRace(TESRace* a_race, bool a_player)
	{
		using func_t = decltype(&Actor::SwitchRace);
		REL::Relocation<func_t> func{ Offset::Actor::SwitchRace };
		return func(this, a_race, a_player);
	}

	void Actor::UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData)
	{
		using func_t = decltype(&Actor::UpdateArmorAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateArmorAbility };
		return func(this, a_armor, a_extraData);
	}

	void Actor::Update3DModel()
	{
		if (currentProcess) {
			currentProcess->Update3DModel(this);
		}
	}

	void Actor::UpdateHairColor()
	{
		auto npc = GetActorBase();
		if (npc && npc->headRelatedData) {
			const auto hairColor = npc->headRelatedData->hairColor;
			if (hairColor) {
				NiColor color;
				color.red = static_cast<float>(hairColor->color.red) / static_cast<float>(128.0);
				color.green = static_cast<float>(hairColor->color.green) / static_cast<float>(128.0);
				color.blue = static_cast<float>(hairColor->color.blue) / static_cast<float>(128.0);

				auto model = Get3D(false);
				if (model) {
					model->UpdateHairColor(color);
				}
			}
		}
	}

	void Actor::UpdateSkinColor()
	{
		const auto* npc = GetActorBase();
		if (npc) {
			NiColor color;
			color.red = static_cast<float>(npc->bodyTintColor.red) / static_cast<float>(255.0);
			color.green = static_cast<float>(npc->bodyTintColor.green) / static_cast<float>(255.0);
			color.blue = static_cast<float>(npc->bodyTintColor.blue) / static_cast<float>(255.0);

			auto thirdPerson = Get3D(false);
			if (thirdPerson) {
				thirdPerson->UpdateBodyTint(color);
			}

			auto firstPerson = Get3D(true);
			if (firstPerson) {
				firstPerson->UpdateBodyTint(color);
			}
		}
	}

	void Actor::UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand)
	{
		using func_t = decltype(&Actor::UpdateWeaponAbility);
		REL::Relocation<func_t> func{ Offset::Actor::UpdateWeaponAbility };
		return func(this, a_weapon, a_extraData, a_leftHand);
	}

	void Actor::VisitArmorAddon(TESObjectARMO* a_armor, TESObjectARMA* a_arma, std::function<void(bool a_firstPerson, NiAVObject& a_obj)> a_visitor)
	{
		enum
		{
			k3rd,
			k1st,
			kTotal
		};

		char addonString[WinAPI::MAX_PATH]{ '\0' };
		a_arma->GetNodeName(addonString, this, a_armor, -1);
		std::array<NiAVObject*, kTotal> skeletonRoot = { Get3D(k3rd), Get3D(k1st) };
		if (skeletonRoot[k1st] == skeletonRoot[k3rd]) {
			skeletonRoot[k1st] = nullptr;
		}
		for (std::size_t i = 0; i < skeletonRoot.size(); ++i) {
			if (skeletonRoot[i]) {
				const auto obj = skeletonRoot[i]->GetObjectByName(addonString);
				if (obj) {
					a_visitor(i == k1st, *obj);
				}
			}
		}
	}

	bool Actor::VisitFactions(std::function<bool(TESFaction* a_faction, std::int8_t a_rank)> a_visitor)
	{
		auto base = GetActorBase();
		if (base) {
			for (auto& factionInfo : base->factions) {
				if (a_visitor(factionInfo.faction, factionInfo.rank)) {
					return true;
				}
			}

			auto factionChanges = extraList.GetByType<ExtraFactionChanges>();
			if (factionChanges) {
				for (auto& change : factionChanges->factionChanges) {
					if (a_visitor(change.faction, change.rank)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool Actor::WouldBeStealing(const TESObjectREFR* a_target) const
	{
		return a_target != nullptr && !a_target->IsAnOwner(this, true, false);
	}

	void Actor::CalculateCurrentVendorFaction() const
	{
		using func_t = decltype(&Actor::CalculateCurrentVendorFaction);
		REL::Relocation<func_t> func{ RELOCATION_ID(36392, 37383) };
		return func(this);
	}

	TESFaction* Actor::GetCrimeFactionImpl() const
	{
		if (IsCommandedActor()) {
			return nullptr;
		}

		auto xFac = extraList.GetByType<ExtraFactionChanges>();
		if (xFac && (xFac->crimeFaction || xFac->removeCrimeFaction)) {
			return xFac->crimeFaction;
		}

		auto base = GetActorBase();
		return base ? base->crimeFaction : nullptr;
	}
}
