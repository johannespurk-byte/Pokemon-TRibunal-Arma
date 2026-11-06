Fossil_Ruins_3_MapScripts::
	.byte 0

@ Back-to-back fight: MAXIE first, then GIOVANNI steps forward. The trigger sits on the
@ only way into the goal room, so nobody reaches the ladder without beating both.
Fossil_Ruins_3_EventScript_Showdown::
	lockall
	goto_if_not_defeated TRAINER_MAXIE_FOSSIL_RUINS, Fossil_Ruins_3_EventScript_Maxie
	goto_if_not_defeated TRAINER_GIOVANNI_FOSSIL_RUINS, Fossil_Ruins_3_EventScript_Giovanni
	setvar VAR_TEMP_1, 1
	releaseall
	end

Fossil_Ruins_3_EventScript_Maxie::
	turnobject LOCALID_PLAYER, DIR_WEST
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox Fossil_Ruins_3_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_FOSSIL_RUINS, Fossil_Ruins_3_Text_MaxieDefeat
	msgbox Fossil_Ruins_3_Text_MaxieAfterBattle, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_FOSSIL_RUINS_3_MAXIE
	removeobject LOCALID_FOSSIL_RUINS_3_MAXIE
	goto Fossil_Ruins_3_EventScript_Giovanni
	end

Fossil_Ruins_3_EventScript_Giovanni::
	applymovement LOCALID_FOSSIL_RUINS_3_GIOVANNI, Fossil_Ruins_3_Movement_GiovanniStepForward
	waitmovement 0
	turnobject LOCALID_FOSSIL_RUINS_3_GIOVANNI, DIR_EAST
	turnobject LOCALID_PLAYER, DIR_WEST
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	msgbox Fossil_Ruins_3_Text_GiovanniIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GIOVANNI_FOSSIL_RUINS, Fossil_Ruins_3_Text_GiovanniDefeat
	msgbox Fossil_Ruins_3_Text_GiovanniAfterBattle, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_FOSSIL_RUINS_3_GIOVANNI
	removeobject LOCALID_FOSSIL_RUINS_3_GIOVANNI
	fadescreen FADE_FROM_BLACK
	setvar VAR_TEMP_1, 1
	releaseall
	end

Fossil_Ruins_3_Movement_GiovanniStepForward:
	walk_down
	step_end

Fossil_Ruins_3_Text_MaxieIntro:
	.string "MAXIE: So you slid your way through\n"
	.string "the ice to reach us.\p"
	.string "TEAM MAGMA and TEAM ROCKET have\n"
	.string "business in these ruins.\p"
	.string "Interfere, and I will bury you\n"
	.string "beneath them!$"

Fossil_Ruins_3_Text_MaxieDefeat:
	.string "Hmph…\n"
	.string "You are stronger than I expected.$"

Fossil_Ruins_3_Text_MaxieAfterBattle:
	.string "MAXIE: Do not celebrate yet.\p"
	.string "GIOVANNI, this one is yours.\n"
	.string "I will not stand in your way.$"

Fossil_Ruins_3_Text_GiovanniIntro:
	.string "GIOVANNI: You beat MAXIE, so you\n"
	.string "have earned my attention.\p"
	.string "Your POKéMON are rested. Good.\n"
	.string "I want no excuses when you fall!$"

Fossil_Ruins_3_Text_GiovanniDefeat:
	.string "Impressive…\n"
	.string "I underestimated you.$"

Fossil_Ruins_3_Text_GiovanniAfterBattle:
	.string "GIOVANNI: Remember this. Our alliance\n"
	.string "does not end in these ruins.\p"
	.string "We will meet again!$"
