@ =========================================================
@ LITTLEROOT ARENA: Norman with Koga as his backup.
@ Norman gives the Balance Badge, Koga the Gengarite.
@ =========================================================
LittlerootArena_MapScripts::
	.byte 0

LittlerootArena_EventScript_Leaders::
	lock
	faceplayer
	goto_if_set FLAG_BADGE05_GET, LittlerootArena_EventScript_PostBattle
	msgbox LittlerootArena_Text_Intro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_two_trainers TRAINER_NORMAN_ARENA, LittlerootArena_Text_NormanDefeat, TRAINER_KOGA_ARENA, LittlerootArena_Text_KogaDefeat
	message LittlerootArena_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LittlerootArena_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setvar VAR_PETALBURG_GYM_STATE, 7
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	giveitem ITEM_TM_FACADE
	setflag FLAG_RECEIVED_TM_FACADE
	msgbox LittlerootArena_Text_KogaGivesStone, MSGBOX_DEFAULT
	giveitem ITEM_GENGARITE
	msgbox LittlerootArena_Text_KogaExplainStone, MSGBOX_DEFAULT
	@ NORMAN hands over SURF himself (instead of WALLY's dad) and sends the player to Fossil Ruins 5
	msgbox LittlerootArena_Text_NormanGivesSurf, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	setvar VAR_PETALBURG_CITY_STATE, 5
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	msgbox LittlerootArena_Text_NormanSendToRuins, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	playse SE_WARP_IN
	warp MAP_FOSSIL_RUINS_5, 14, 34
	waitstate
	release
	end

LittlerootArena_EventScript_PostBattle:
	msgbox LittlerootArena_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

LittlerootArena_Text_Intro:
	.string "NORMAN: Du hast Mom und Misty\n"
	.string "besiegt? Ich bin stolz auf dich!\p"
	.string "KOGA: Doch hier endet dein Weg.\n"
	.string "Norman und ich kaempfen gemeinsam!\p"
	.string "NORMAN: Zeig uns, was du kannst!$"

LittlerootArena_Text_NormanDefeat:
	.string "NORMAN: Du bist wirklich stark\n"
	.string "geworden...$"

LittlerootArena_Text_KogaDefeat:
	.string "KOGA: Selbst mein Gift konnte dich\n"
	.string "nicht aufhalten!$"

LittlerootArena_Text_ReceivedBalanceBadge:
	.string "{PLAYER} erhaelt den Balanceorden\n"
	.string "von Norman!$"

LittlerootArena_Text_ExplainBadge:
	.string "NORMAN: Der Balanceorden zeigt, dass\n"
	.string "du deine Pokemon im Griff hast.\p"
	.string "Nimm auch diese TM. Fassade wird\n"
	.string "staerker, wenn dein Pokemon\l"
	.string "vergiftet, gelaehmt oder verbrannt\l"
	.string "ist.$"

LittlerootArena_Text_KogaGivesStone:
	.string "KOGA: Ein Ninja erkennt wahre\n"
	.string "Staerke. Nimm diesen Stein!$"

LittlerootArena_Text_KogaExplainStone:
	.string "KOGA: Das Gengarnit. Damit kann\n"
	.string "Gengar Mega-evolvieren!$"

LittlerootArena_Text_NormanGivesSurf:
	.string "NORMAN: Wallys Vater hat mir das\n"
	.string "hier fuer dich mitgegeben.\p"
	.string "Damit kommst du uebers Wasser!$"

LittlerootArena_Text_NormanSendToRuins:
	.string "NORMAN: Team Aqua und Giovanni sind\n"
	.string "in den Fossilruinen gesehen worden.\p"
	.string "Ich schicke dich direkt hin.\n"
	.string "Pass auf dich auf!$"

LittlerootArena_Text_PostBattle:
	.string "NORMAN: Du hast das Zeug zu einem\n"
	.string "Champion. Zieh weiter voran!$"
