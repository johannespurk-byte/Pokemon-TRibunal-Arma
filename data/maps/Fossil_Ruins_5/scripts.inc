Fossil_Ruins_5_MapScripts::
	.byte 0

@ Back-to-back fight like in Fossil Ruins 3: ARCHIE first, then GIOVANNI steps forward.
@ The trigger sits at the top of the only stairs into the hall.
Fossil_Ruins_5_EventScript_Showdown::
	lockall
	setrespawn HEAL_LOCATION_FOSSIL_RUINS_5
	goto_if_not_defeated TRAINER_ARCHIE_FOSSIL_RUINS, Fossil_Ruins_5_EventScript_Archie
	goto_if_not_defeated TRAINER_GIOVANNI_FOSSIL_RUINS_5, Fossil_Ruins_5_EventScript_Giovanni
	goto Fossil_Ruins_5_EventScript_Rift
	end

Fossil_Ruins_5_EventScript_Archie::
	turnobject LOCALID_PLAYER, DIR_WEST
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox Fossil_Ruins_5_Text_ArchieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHIE_FOSSIL_RUINS, Fossil_Ruins_5_Text_ArchieDefeat
	msgbox Fossil_Ruins_5_Text_ArchieAfterBattle, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_FOSSIL_RUINS_5_ARCHIE
	removeobject LOCALID_FOSSIL_RUINS_5_ARCHIE
	goto Fossil_Ruins_5_EventScript_Giovanni
	end

Fossil_Ruins_5_EventScript_Giovanni::
	applymovement LOCALID_FOSSIL_RUINS_5_GIOVANNI, Fossil_Ruins_5_Movement_GiovanniStepForward
	waitmovement 0
	turnobject LOCALID_FOSSIL_RUINS_5_GIOVANNI, DIR_EAST
	turnobject LOCALID_PLAYER, DIR_WEST
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	msgbox Fossil_Ruins_5_Text_GiovanniIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GIOVANNI_FOSSIL_RUINS_5, Fossil_Ruins_5_Text_GiovanniDefeat
	msgbox Fossil_Ruins_5_Text_GiovanniAfterBattle, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_FOSSIL_RUINS_5_GIOVANNI
	removeobject LOCALID_FOSSIL_RUINS_5_GIOVANNI
	fadescreen FADE_FROM_BLACK
	goto Fossil_Ruins_5_EventScript_Rift
	end

@ After GIOVANNI a rift in space opens in the hall and pulls the player into Fossil Ruins 6
Fossil_Ruins_5_EventScript_Rift::
	msgbox Fossil_Ruins_5_Text_Rift, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fossil_Ruins_5_EventScript_RiftNo
	closemessage
	playse SE_WARP_IN
	warp MAP_FOSSIL_RUINS_6, 5, 21
	waitstate
	releaseall
	end

Fossil_Ruins_5_EventScript_RiftNo::
	setvar VAR_TEMP_1, 1
	releaseall
	end

Fossil_Ruins_5_Text_Rift:
	.string "Where GIOVANNI stood, a rift full of\n"
	.string "stars tears open in the air…\p"
	.string "Step into the rift?$"

Fossil_Ruins_5_Movement_GiovanniStepForward:
	walk_down
	step_end

Fossil_Ruins_5_Text_ArchieIntro:
	.string "ARCHIE: Bwahahaha! You crossed the\n"
	.string "dark water to find us down here?\p"
	.string "MAXIE failed in the ice. I won't.\n"
	.string "The sea will swallow these ruins,\l"
	.string "and you with them!$"

Fossil_Ruins_5_Text_ArchieDefeat:
	.string "Washed out…\n"
	.string "Like a wave on the rocks.$"

Fossil_Ruins_5_Text_ArchieAfterBattle:
	.string "ARCHIE: Tch… You're the real deal.\p"
	.string "GIOVANNI, the stage is yours.\n"
	.string "Show this kid what the TRIBUNAL is.$"

Fossil_Ruins_5_Text_GiovanniIntro:
	.string "GIOVANNI: We meet again.\p"
	.string "Last time I held back.\n"
	.string "Not anymore.\p"
	.string "Your POKéMON are rested.\n"
	.string "Now face the full power of\l"
	.string "TEAM ROCKET!$"

Fossil_Ruins_5_Text_GiovanniDefeat:
	.string "Again…?\n"
	.string "You are a true menace.$"

Fossil_Ruins_5_Text_GiovanniAfterBattle:
	.string "GIOVANNI: This changes nothing.\p"
	.string "The TRIBUNAL has more than one\n"
	.string "hand to play. Until next time!$"

@ Two Aqua grunts block the stairs to the hall and fight together as a double battle.
Fossil_Ruins_5_EventScript_Grunts::
	lockall
	goto_if_set FLAG_HIDE_FOSSIL_RUINS_5_GRUNTS, Fossil_Ruins_5_EventScript_GruntsDone
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox Fossil_Ruins_5_Text_GruntsIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_two_trainers TRAINER_AQUA_GRUNT_FOSSIL_RUINS_5_A, Fossil_Ruins_5_Text_GruntADefeat, TRAINER_AQUA_GRUNT_FOSSIL_RUINS_5_B, Fossil_Ruins_5_Text_GruntBDefeat
	msgbox Fossil_Ruins_5_Text_GruntsAfterBattle, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_FOSSIL_RUINS_5_GRUNTS
	removeobject LOCALID_FOSSIL_RUINS_5_GRUNT_A
	removeobject LOCALID_FOSSIL_RUINS_5_GRUNT_B
	fadescreen FADE_FROM_BLACK
	setvar VAR_TEMP_2, 1
	releaseall
	end

Fossil_Ruins_5_EventScript_GruntsDone::
	setvar VAR_TEMP_2, 1
	releaseall
	end

Fossil_Ruins_5_Text_GruntsIntro:
	.string "GRUNT: Hey! Nobody goes up there!\p"
	.string "The BOSS is busy with GIOVANNI.\n"
	.string "The two of us will wash you away!$"

Fossil_Ruins_5_Text_GruntADefeat:
	.string "No way…\n"
	.string "We got swept away!$"

Fossil_Ruins_5_Text_GruntBDefeat:
	.string "Ugh… Even together\n"
	.string "we couldn't stop you!$"

Fossil_Ruins_5_Text_GruntsAfterBattle:
	.string "GRUNT: Fine, go on up!\n"
	.string "ARCHIE will sink you for good!$"

@ =========================================================
@ EXPERTIN UNDINE: hands out the Z-Ring and the Waterium Z
@ =========================================================
Fossil_Ruins_5_EventScript_Undine::
	trainerbattle_single TRAINER_UNDINE, Fossil_Ruins_5_Text_UndineIntro, Fossil_Ruins_5_Text_UndineDefeated, Fossil_Ruins_5_EventScript_UndineDefeated
	@ Already beaten: hand over what the player is still missing
	checkitem ITEM_Z_POWER_RING
	goto_if_eq VAR_RESULT, FALSE, Fossil_Ruins_5_EventScript_UndineGiveLater
	checkitem ITEM_WATERIUM_Z
	goto_if_eq VAR_RESULT, FALSE, Fossil_Ruins_5_EventScript_UndineGiveLater
	msgbox Fossil_Ruins_5_Text_UndinePostBattle, MSGBOX_AUTOCLOSE
	end

Fossil_Ruins_5_EventScript_UndineGiveLater::
	lock
	faceplayer
	msgbox Fossil_Ruins_5_Text_UndineReward, MSGBOX_DEFAULT
	checkitem ITEM_Z_POWER_RING
	call_if_eq VAR_RESULT, FALSE, Fossil_Ruins_5_EventScript_UndineGiveRing
	checkitem ITEM_WATERIUM_Z
	call_if_eq VAR_RESULT, FALSE, Fossil_Ruins_5_EventScript_UndineGiveCrystal
	release
	end

Fossil_Ruins_5_EventScript_UndineDefeated::
	lock
	faceplayer
	msgbox Fossil_Ruins_5_Text_UndineReward, MSGBOX_DEFAULT
	checkitem ITEM_Z_POWER_RING
	call_if_eq VAR_RESULT, FALSE, Fossil_Ruins_5_EventScript_UndineGiveRing
	call Fossil_Ruins_5_EventScript_UndineGiveCrystal
	release
	end

Fossil_Ruins_5_EventScript_UndineGiveRing::
	giveitem ITEM_Z_POWER_RING
	msgbox Fossil_Ruins_5_Text_UndineExplainRing, MSGBOX_DEFAULT
	return

Fossil_Ruins_5_EventScript_UndineGiveCrystal::
	giveitem ITEM_WATERIUM_Z
	msgbox Fossil_Ruins_5_Text_UndineExplainCrystal, MSGBOX_DEFAULT
	return

Fossil_Ruins_5_Text_UndineIntro::
	.string "Niemand findet den Weg auf meine Insel.\n"
	.string "Du bist bis hierher gesurft? Respekt!\p"
	.string "Aber gegen meine Flut im Dunkeln\n"
	.string "hast du keine Chance!$"

Fossil_Ruins_5_Text_UndineDefeated::
	.string "Meine Flut... einfach versiegt!$"

Fossil_Ruins_5_Text_UndineReward::
	.string "Du beherrschst sogar das dunkle Wasser.\n"
	.string "Nimm diesen Schatz aus dem See.$"

Fossil_Ruins_5_Text_UndineExplainRing::
	.string "Das ist ein Z-Ring. Ohne ihn kann\n"
	.string "kein Pokemon eine Z-Attacke einsetzen.$"

Fossil_Ruins_5_Text_UndineExplainCrystal::
	.string "Und das ist das Aquarium Z.\n"
	.string "Lass ein Wasser-Pokemon es tragen, um\l"
	.string "eine gewaltige Z-Attacke zu entfesseln!$"

Fossil_Ruins_5_Text_UndinePostBattle::
	.string "Hier unten ist das Wasser so still...\n"
	.string "Aber du hast es zum Kochen gebracht!$"

@ Used after a whiteout when the last respawn point was a boss hall in Fossil Ruins 5 or 6
EventScript_AfterWhiteOutFossilRuins::
	lockall
	msgbox Fossil_Ruins_5_Text_WhiteOutRecovered, MSGBOX_DEFAULT
	fadedefaultbgm
	releaseall
	end

Fossil_Ruins_5_Text_WhiteOutRecovered:
	.string "Your POKéMON have recovered.\n"
	.string "The fight is still waiting ahead!$"
