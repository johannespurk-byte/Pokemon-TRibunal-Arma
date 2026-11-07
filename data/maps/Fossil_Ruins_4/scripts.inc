Fossil_Ruins_4_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Fossil_Ruins_4_OnResume
	.byte 0

Fossil_Ruins_4_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Fossil_Ruins_4_EventScript_TryRemoveGiratina
	end

@ A caught Giratina leaves right away, not only when the map is loaded again
Fossil_Ruins_4_EventScript_TryRemoveGiratina::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_FOSSIL_RUINS_4_GIRATINA
	return

Fossil_Ruins_4_EventScript_Giratina::
	lockall
	msgbox Fossil_Ruins_4_Text_Giratina, MSGBOX_DEFAULT
	playbgm MUS_PL_GIRATINA_APPEARS_1, FALSE
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_GIRATINA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_FOSSIL_RUINS_4_GIRATINA
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Fossil_Ruins_4_EventScript_RanFromGiratina
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Fossil_Ruins_4_EventScript_RanFromGiratina
	setflag FLAG_HIDE_FOSSIL_RUINS_4_GIRATINA
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Fossil_Ruins_4_EventScript_FadeGiratina
	releaseall
	end

Fossil_Ruins_4_EventScript_FadeGiratina::
	setvar VAR_0x8004, SPECIES_GIRATINA
	goto Common_EventScript_LegendaryFlewAway
	end

@ It comes back when the map is loaded again
Fossil_Ruins_4_EventScript_RanFromGiratina::
	setvar VAR_0x8004, SPECIES_GIRATINA
	goto Common_EventScript_LegendaryFlewAway
	end

Fossil_Ruins_4_Text_Giratina:
	.string "Something enormous is watching from\n"
	.string "the far side of this broken world...$"
