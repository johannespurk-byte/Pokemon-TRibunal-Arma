OldaleTown_Mart_MapScripts::
	.byte 0

OldaleTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIBeserveYou
	waitmessage
	pokemart OldaleTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart:
	.2byte ITEM_MASTER_BALL
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_NUGGET
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_NONE

OldaleTown_Mart_EventScript_Woman::
	lock
	faceplayer
	msgbox OldaleTown_Mart_Text_Woman, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy::
	lock
	faceplayer
	msgbox OldaleTown_Mart_Text_Boy, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_Text_Woman:
	.string "Dieser Supermarkt hat neuerdings ganz\nverrueckte Luxus-Gegenstaende!$"

OldaleTown_Mart_Text_Boy:
	.string "Hast du auch so viel Geld auf der\nhohen Kante wie dieser neue Trainer?$"

gText_HowMayIBeserveYou::
	.string "Welcome!\n"
	.string "How may I serve you?$"
