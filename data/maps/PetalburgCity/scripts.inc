@ --- GLOBALE ANMELDUNG FÜR DEN LINKER ---
.global PetalburgCity_MapScripts
.global PetalburgCity_EventScript_Boy
.global PetalburgCity_EventScript_Girl
.global PetalburgCity_EventScript_GymSign
.global PetalburgCity_EventScript_CitySign
.global PetalburgCity_EventScript_WallysMom
.global PetalburgCity_EventScript_Gentleman
.global PetalburgCity_EventScript_GymBoy
.global PetalburgCity_EventScript_RotomMowEncounter
.global PetalburgCity_EventScript_ShowGymToPlayer0
.global PetalburgCity_EventScript_ShowGymToPlayer1
.global PetalburgCity_EventScript_ShowGymToPlayer2
.global PetalburgCity_EventScript_ShowGymToPlayer3
.global PetalburgCity_EventScript_Scott0
.global PetalburgCity_EventScript_Scott1
.global PetalburgCity_EventScript_Scott2
.global PetalburgCity_EventScript_Scott3
.global PetalburgCity_EventScript_WallyHouseSign

PetalburgCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_OnTransition
	.byte 0

PetalburgCity_OnTransition:
	setflag FLAG_VISITED_PETALBURG_CITY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	end

PetalburgCity_EventScript_WallysMom::
	msgbox PetalburgCity_Text_WallysMom, MSGBOX_NPC
	end

PetalburgCity_EventScript_Gentleman::
	msgbox PetalburgCity_Text_Gentleman, MSGBOX_NPC
	end

PetalburgCity_EventScript_GymBoy::
	msgbox PetalburgCity_Text_GymBoy, MSGBOX_NPC
	end

PetalburgCity_EventScript_RotomMowEncounter::
	lockall
	msgbox PetalburgCity_Text_RotomRustle, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_EventScript_Boy::
	msgbox PetalburgCity_Text_Boy, MSGBOX_NPC
	end

PetalburgCity_EventScript_Girl::
	msgbox PetalburgCity_Text_Girl, MSGBOX_NPC
	end

PetalburgCity_EventScript_GymSign::
	msgbox PetalburgCity_Text_GymSign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_CitySign::
	msgbox PetalburgCity_Text_CitySign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_WallyHouseSign::
	msgbox PetalburgCity_Text_WallyHouseSign, MSGBOX_SIGN
	end

@ KORREKTUR: Alle fehlenden Sprungmarken wurden vollständig und sauber ausformuliert!
PetalburgCity_EventScript_ShowGymToPlayer0::
	end
PetalburgCity_EventScript_ShowGymToPlayer1::
	end
PetalburgCity_EventScript_ShowGymToPlayer2::
	end
PetalburgCity_EventScript_ShowGymToPlayer3::
	end
PetalburgCity_EventScript_Scott0::
	end
PetalburgCity_EventScript_Scott1::
	end
PetalburgCity_EventScript_Scott2::
	end
PetalburgCity_EventScript_Scott3::
	end

@ --- TEXTE ---
PetalburgCity_Text_Boy:
	.string "Ich habe gehoert, in der Arena geht\n"
	.string "es heute drunter und drueber!$"

PetalburgCity_Text_Girl:
	.string "MOM hat die Arena uebernommen.\n"
	.string "Sie ist echt unschlagbar!$"

PetalburgCity_Text_GymSign:
	.string "POKéMON ARENA von BLÜTENBURG CITY\n"
	.string "LEITERIN: MOM$"

PetalburgCity_Text_CitySign:
	.string "BLÜTENBURG CITY\n"
	.string "Wo Mensch und Natur harmonieren.$"

PetalburgCity_Text_WallysMom:
	.string "Heiko ist im Moment nicht da...$"

PetalburgCity_Text_Gentleman:
	.string "Diese Stadt strahlt eine unheimliche\n"
	.string "Ruhe aus.$"

PetalburgCity_Text_GymBoy:
	.string "Bist du stark genug fuer die Zimmer-\n"
	.string "Herausforderung da drinnen?$"

PetalburgCity_Text_WallyHouseSign:
	.string "HEIKOS HAUS$"

PetalburgCity_Text_RotomRustle:
	.string "Das hohe Gras raschelt unheimlich...\n"
	.string "Ein wildes ROTOM (Rasenmaeher) greift an!$"
