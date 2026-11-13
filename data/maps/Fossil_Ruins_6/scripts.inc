@ =========================================================
@ FOSSIL RUINS 6: a galaxy of floating asteroids.
@ GIOVANNI, MAXIE and ARCHIE fight back to back; afterwards
@ the player may take ONE of six legendaries from the altar.
@ =========================================================
Fossil_Ruins_6_MapScripts::
	.byte 0

Fossil_Ruins_6_EventScript_Showdown::
	lockall
	setrespawn HEAL_LOCATION_FOSSIL_RUINS_6
	turnobject LOCALID_PLAYER, DIR_NORTH
	goto_if_not_defeated TRAINER_GIOVANNI_FOSSIL_RUINS_6, Fossil_Ruins_6_EventScript_Giovanni
	goto_if_not_defeated TRAINER_MAXIE_FOSSIL_RUINS_6, Fossil_Ruins_6_EventScript_Maxie
	goto_if_not_defeated TRAINER_ARCHIE_FOSSIL_RUINS_6, Fossil_Ruins_6_EventScript_Archie
	setvar VAR_TEMP_1, 1
	releaseall
	end

Fossil_Ruins_6_EventScript_Giovanni::
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	msgbox Fossil_Ruins_6_Text_GiovanniIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GIOVANNI_FOSSIL_RUINS_6, Fossil_Ruins_6_Text_GiovanniDefeat
	msgbox Fossil_Ruins_6_Text_GiovanniAfterBattle, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_FOSSIL_RUINS_6_GIOVANNI
	removeobject LOCALID_FOSSIL_RUINS_6_GIOVANNI
	goto Fossil_Ruins_6_EventScript_Maxie
	end

Fossil_Ruins_6_EventScript_Maxie::
	applymovement LOCALID_FOSSIL_RUINS_6_MAXIE, Fossil_Ruins_6_Movement_StepRight
	waitmovement 0
	turnobject LOCALID_FOSSIL_RUINS_6_MAXIE, DIR_SOUTH
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox Fossil_Ruins_6_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_FOSSIL_RUINS_6, Fossil_Ruins_6_Text_MaxieDefeat
	msgbox Fossil_Ruins_6_Text_MaxieAfterBattle, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_FOSSIL_RUINS_6_MAXIE
	removeobject LOCALID_FOSSIL_RUINS_6_MAXIE
	goto Fossil_Ruins_6_EventScript_Archie
	end

Fossil_Ruins_6_EventScript_Archie::
	applymovement LOCALID_FOSSIL_RUINS_6_ARCHIE, Fossil_Ruins_6_Movement_StepLeft
	waitmovement 0
	turnobject LOCALID_FOSSIL_RUINS_6_ARCHIE, DIR_SOUTH
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox Fossil_Ruins_6_Text_ArchieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHIE_FOSSIL_RUINS_6, Fossil_Ruins_6_Text_ArchieDefeat
	msgbox Fossil_Ruins_6_Text_ArchieAfterBattle, MSGBOX_DEFAULT
	special HealPlayerParty
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_FOSSIL_RUINS_6_ARCHIE
	removeobject LOCALID_FOSSIL_RUINS_6_ARCHIE
	fadescreen FADE_FROM_BLACK
	msgbox Fossil_Ruins_6_Text_AltarOpen, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 1
	releaseall
	end

Fossil_Ruins_6_Movement_StepRight:
	walk_right
	walk_right
	step_end

Fossil_Ruins_6_Movement_StepLeft:
	walk_left
	walk_left
	step_end

Fossil_Ruins_6_EventScript_Dialga::
	setvar VAR_0x8004, SPECIES_DIALGA
	setvar VAR_0x8005, ITEM_ADAMANT_CRYSTAL
	setvar VAR_0x8008, ITEM_ADAMANT_ORB
	setvar VAR_0x8009, ITEM_NONE
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_Palkia::
	setvar VAR_0x8004, SPECIES_PALKIA
	setvar VAR_0x8005, ITEM_LUSTROUS_GLOBE
	setvar VAR_0x8008, ITEM_LUSTROUS_ORB
	setvar VAR_0x8009, ITEM_NONE
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_Solgaleo::
	setvar VAR_0x8004, SPECIES_SOLGALEO
	setvar VAR_0x8005, ITEM_SOLGANIUM_Z
	setvar VAR_0x8008, ITEM_NONE
	setvar VAR_0x8009, ITEM_NONE
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_Lunala::
	setvar VAR_0x8004, SPECIES_LUNALA
	setvar VAR_0x8005, ITEM_LUNALIUM_Z
	setvar VAR_0x8008, ITEM_NONE
	setvar VAR_0x8009, ITEM_NONE
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_Necrozma::
	setvar VAR_0x8004, SPECIES_NECROZMA
	setvar VAR_0x8005, ITEM_ULTRANECROZIUM_Z
	setvar VAR_0x8008, ITEM_N_SOLARIZER
	setvar VAR_0x8009, ITEM_N_LUNARIZER
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_Deoxys::
	setvar VAR_0x8004, SPECIES_DEOXYS_NORMAL
	setvar VAR_0x8005, ITEM_NONE
	setvar VAR_0x8008, ITEM_METEORITE
	setvar VAR_0x8009, ITEM_NONE
	goto Fossil_Ruins_6_EventScript_ChooseLegend
	end

Fossil_Ruins_6_EventScript_ChooseLegend::
	lock
	faceplayer
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox Fossil_Ruins_6_Text_TakeLegend, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fossil_Ruins_6_EventScript_Release
	specialvar VAR_0x8006, GetLevelCapForScript
	givemon VAR_0x8004, VAR_0x8006, VAR_0x8005
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Fossil_Ruins_6_EventScript_NoRoom
	copyvar VAR_0x8007, VAR_RESULT
	playfanfare MUS_OBTAIN_ITEM
	message Fossil_Ruins_6_Text_ReceivedLegend
	waitmessage
	waitfanfare
	call_if_ne VAR_0x8007, MON_GIVEN_TO_PARTY, Fossil_Ruins_6_EventScript_SentToPC
	setflag FLAG_FOSSIL_RUINS_6_LEGEND_CHOSEN
	call Fossil_Ruins_6_EventScript_GiveExtras
	msgbox Fossil_Ruins_6_Text_OthersVanish, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_FOSSIL_RUINS_6_DIALGA
	removeobject LOCALID_FOSSIL_RUINS_6_PALKIA
	removeobject LOCALID_FOSSIL_RUINS_6_SOLGALEO
	removeobject LOCALID_FOSSIL_RUINS_6_LUNALA
	removeobject LOCALID_FOSSIL_RUINS_6_NECROZMA
	removeobject LOCALID_FOSSIL_RUINS_6_DEOXYS
	fadescreen FADE_FROM_BLACK
	release
	end

@ The legendary's other items go into the bag; Z crystals need a Z-Ring
Fossil_Ruins_6_EventScript_GiveExtras::
	call_if_ne VAR_0x8008, ITEM_NONE, Fossil_Ruins_6_EventScript_GiveExtra1
	call_if_ne VAR_0x8009, ITEM_NONE, Fossil_Ruins_6_EventScript_GiveExtra2
	call_if_eq VAR_0x8005, ITEM_SOLGANIUM_Z, Fossil_Ruins_6_EventScript_GiveZRing
	call_if_eq VAR_0x8005, ITEM_LUNALIUM_Z, Fossil_Ruins_6_EventScript_GiveZRing
	call_if_eq VAR_0x8005, ITEM_ULTRANECROZIUM_Z, Fossil_Ruins_6_EventScript_GiveZRing
	return

Fossil_Ruins_6_EventScript_GiveExtra1::
	checkitem VAR_0x8008
	goto_if_eq VAR_RESULT, TRUE, Fossil_Ruins_6_EventScript_Return
	giveitem VAR_0x8008
	return

Fossil_Ruins_6_EventScript_GiveExtra2::
	checkitem VAR_0x8009
	goto_if_eq VAR_RESULT, TRUE, Fossil_Ruins_6_EventScript_Return
	giveitem VAR_0x8009
	return

Fossil_Ruins_6_EventScript_GiveZRing::
	checkitem ITEM_Z_POWER_RING
	goto_if_eq VAR_RESULT, TRUE, Fossil_Ruins_6_EventScript_Return
	giveitem ITEM_Z_POWER_RING
	return

Fossil_Ruins_6_EventScript_Return::
	return

Fossil_Ruins_6_EventScript_SentToPC::
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8004
	call Common_EventScript_TransferredToPC
	return

Fossil_Ruins_6_EventScript_NoRoom::
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	release
	end

Fossil_Ruins_6_EventScript_Release::
	release
	end

@ The portal on the altar leads to Route 118, east of Mauville City
Fossil_Ruins_6_EventScript_Portal::
	lockall
	msgbox Fossil_Ruins_6_Text_Portal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fossil_Ruins_6_EventScript_PortalNo
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_WARP_IN
	@ Route 118 east of Mauville City, on the shore where the player has to surf on
	@ (16,9): next to the water, outside the sight line of DALTON at (17,11)
	warp MAP_ROUTE118, 16, 9
	waitstate
	releaseall
	end

Fossil_Ruins_6_EventScript_PortalNo::
	releaseall
	end

Fossil_Ruins_6_Text_GiovanniIntro:
	.string "GIOVANNI: So you followed me through\n"
	.string "the rift. Look around you…\p"
	.string "Stars, planets, endless space. Whoever\n"
	.string "rules this place rules everything.\p"
	.string "MAXIE and ARCHIE stand with me.\n"
	.string "You will not pass all three of us!$"

Fossil_Ruins_6_Text_GiovanniDefeat:
	.string "GIOVANNI: Hmph… Even here, among the\n"
	.string "stars, you defy me.$"

Fossil_Ruins_6_Text_GiovanniAfterBattle:
	.string "GIOVANNI: MAXIE! Your turn.\n"
	.string "Let the child feel the heat of the land.$"

Fossil_Ruins_6_Text_MaxieIntro:
	.string "MAXIE: Fufufu… Land is born from the\n"
	.string "fire of a thousand suns.\p"
	.string "GROUDON's power shines even in space!$"

Fossil_Ruins_6_Text_MaxieDefeat:
	.string "MAXIE: The flames… went out?$"

Fossil_Ruins_6_Text_MaxieAfterBattle:
	.string "MAXIE: ARCHIE! Don't you dare lose\n"
	.string "as well!$"

Fossil_Ruins_6_Text_ArchieIntro:
	.string "ARCHIE: Bwahahaha! Even the stars come\n"
	.string "from the great ocean of space!\p"
	.string "KYOGRE will wash you away!$"

Fossil_Ruins_6_Text_ArchieDefeat:
	.string "ARCHIE: Washed up… by a kid…$"

Fossil_Ruins_6_Text_ArchieAfterBattle:
	.string "ARCHIE: Fine! The altar is yours.\n"
	.string "But only one of them will follow you!$"

Fossil_Ruins_6_Text_AltarOpen:
	.string "The three leaders vanished into the\n"
	.string "rift. The way to the altar is free.$"

Fossil_Ruins_6_Text_TakeLegend:
	.string "{STR_VAR_1} looks at you calmly.\p"
	.string "Only one of the six can come with\n"
	.string "you. Choose {STR_VAR_1}?$"

Fossil_Ruins_6_Text_ReceivedLegend:
	.string "{PLAYER} obtained {STR_VAR_1}!$"

Fossil_Ruins_6_Text_OthersVanish:
	.string "The other legendary POKéMON fade\n"
	.string "back into the stars…$"

Fossil_Ruins_6_Text_Portal:
	.string "A portal of starlight. It leads to\n"
	.string "ROUTE 118, east of MAUVILLE CITY.\p"
	.string "Step through?$"
