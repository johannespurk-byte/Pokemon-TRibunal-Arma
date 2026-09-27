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
.2byte ITEM_TM_WATER_PULSE   // TM Aquawelle (Adrian)
.2byte ITEM_TM_ROCK_TOMB     // TM Felsgrab (Giovanni)
.2byte ITEM_TM_SECRET_POWER  // TM Geheimpower (Giovanni)
.2byte ITEM_TM_SHOCK_WAVE    // TM Schockwelle (Marc)
.2byte ITEM_TM_THIEF         // TM Raub (Marc - Ersatz für Fake Out, funktioniert garantiert!)
.2byte ITEM_SITRUS_BERRY     // Sitrusbeere
.2byte ITEM_SILK_SCARF       // Seidenschal
.2byte ITEM_CHOICE_BAND      // Wahlband
.2byte ITEM_SOOTHE_BELL      // Sanftglocke
.2byte ITEM_NONE             // Schließt das Verkaufsregal sicher ab


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
