Fossil_Ruins_5_MapScripts::
	.byte 0

@ Back-to-back fight like in Fossil Ruins 3: ARCHIE first, then GIOVANNI steps forward.
@ The trigger sits at the top of the only stairs into the hall.
Fossil_Ruins_5_EventScript_Showdown::
	lockall
	goto_if_not_defeated TRAINER_ARCHIE_FOSSIL_RUINS, Fossil_Ruins_5_EventScript_Archie
	goto_if_not_defeated TRAINER_GIOVANNI_FOSSIL_RUINS_5, Fossil_Ruins_5_EventScript_Giovanni
	setvar VAR_TEMP_1, 1
	releaseall
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
	setvar VAR_TEMP_1, 1
	releaseall
	end

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
