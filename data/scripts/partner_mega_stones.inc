@ Gym partners hand over every Mega Stone of their type (legendary ones excluded);
@ the signature stone comes first with giveitem, the rest is added here.
@ Stones the player already has (dual types, earlier gifts) are skipped.
	.macro addmegaonce item:req
	checkitem \item
	goto_if_eq VAR_RESULT, TRUE, 1f
	additem \item
1:
	.endm

PartnerMega_EventScript_Fire::
	msgbox PartnerMega_Text_MoreFire, MSGBOX_DEFAULT
	addmegaonce ITEM_CHARIZARDITE_X
	addmegaonce ITEM_HOUNDOOMINITE
	addmegaonce ITEM_BLAZIKENITE
	addmegaonce ITEM_CAMERUPTITE
	addmegaonce ITEM_EMBOARITE
	addmegaonce ITEM_CHANDELURITE
	addmegaonce ITEM_DELPHOXITE
	addmegaonce ITEM_PYROARITE
	addmegaonce ITEM_SCOVILLAINITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotFire
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreFire:
	.string "Nimm auch alle anderen\n"
	.string "Feuer-Megasteine mit!$"

PartnerMega_Text_GotFire:
	.string "{PLAYER} erhaelt alle\n"
	.string "Feuer-Megasteine!$"

PartnerMega_EventScript_Ice::
	msgbox PartnerMega_Text_MoreIce, MSGBOX_DEFAULT
	addmegaonce ITEM_FROSLASSITE
	addmegaonce ITEM_ABOMASITE
	addmegaonce ITEM_CRABOMINITE
	addmegaonce ITEM_BAXCALIBRITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotIce
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreIce:
	.string "Nimm auch alle anderen\n"
	.string "Eis-Megasteine mit!$"

PartnerMega_Text_GotIce:
	.string "{PLAYER} erhaelt alle\n"
	.string "Eis-Megasteine!$"

PartnerMega_EventScript_Psychic::
	msgbox PartnerMega_Text_MorePsychic, MSGBOX_DEFAULT
	addmegaonce ITEM_SLOWBRONITE
	addmegaonce ITEM_STARMINITE
	addmegaonce ITEM_GARDEVOIRITE
	addmegaonce ITEM_GALLADITE
	addmegaonce ITEM_MEDICHAMITE
	addmegaonce ITEM_CHIMECHITE
	addmegaonce ITEM_METAGROSSITE
	addmegaonce ITEM_DELPHOXITE
	addmegaonce ITEM_MEOWSTICITE
	addmegaonce ITEM_MALAMARITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotPsychic
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MorePsychic:
	.string "Nimm auch alle anderen\n"
	.string "Psycho-Megasteine mit!$"

PartnerMega_Text_GotPsychic:
	.string "{PLAYER} erhaelt alle\n"
	.string "Psycho-Megasteine!$"

PartnerMega_EventScript_Water::
	msgbox PartnerMega_Text_MoreWater, MSGBOX_DEFAULT
	addmegaonce ITEM_SLOWBRONITE
	addmegaonce ITEM_STARMINITE
	addmegaonce ITEM_GYARADOSITE
	addmegaonce ITEM_FERALIGITE
	addmegaonce ITEM_SWAMPERTITE
	addmegaonce ITEM_SHARPEDONITE
	addmegaonce ITEM_GRENINJITE
	addmegaonce ITEM_TATSUGIRINITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotWater
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreWater:
	.string "Nimm auch alle anderen\n"
	.string "Wasser-Megasteine mit!$"

PartnerMega_Text_GotWater:
	.string "{PLAYER} erhaelt alle\n"
	.string "Wasser-Megasteine!$"

PartnerMega_EventScript_Poison::
	msgbox PartnerMega_Text_MorePoison, MSGBOX_DEFAULT
	addmegaonce ITEM_VENUSAURITE
	addmegaonce ITEM_BEEDRILLITE
	addmegaonce ITEM_VICTREEBELITE
	addmegaonce ITEM_SCOLIPITE
	addmegaonce ITEM_DRAGALGITE
	addmegaonce ITEM_GLIMMORANITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotPoison
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MorePoison:
	.string "Nimm auch alle anderen\n"
	.string "Gift-Megasteine mit!$"

PartnerMega_Text_GotPoison:
	.string "{PLAYER} erhaelt alle\n"
	.string "Gift-Megasteine!$"

PartnerMega_EventScript_Rock::
	msgbox PartnerMega_Text_MoreRock, MSGBOX_DEFAULT
	addmegaonce ITEM_TYRANITARITE
	addmegaonce ITEM_BARBARACITE
	addmegaonce ITEM_GLIMMORANITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotRock
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreRock:
	.string "Nimm auch alle anderen\n"
	.string "Gestein-Megasteine mit!$"

PartnerMega_Text_GotRock:
	.string "{PLAYER} erhaelt alle\n"
	.string "Gestein-Megasteine!$"

PartnerMega_EventScript_Ghost::
	msgbox PartnerMega_Text_MoreGhost, MSGBOX_DEFAULT
	addmegaonce ITEM_GENGARITE
	addmegaonce ITEM_SABLENITE
	addmegaonce ITEM_ABSOLITE_Z
	addmegaonce ITEM_FROSLASSITE
	addmegaonce ITEM_CHANDELURITE
	addmegaonce ITEM_GOLURKITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotGhost
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreGhost:
	.string "Nimm auch alle anderen\n"
	.string "Geist-Megasteine mit!$"

PartnerMega_Text_GotGhost:
	.string "{PLAYER} erhaelt alle\n"
	.string "Geist-Megasteine!$"

PartnerMega_EventScript_Grass::
	msgbox PartnerMega_Text_MoreGrass, MSGBOX_DEFAULT
	addmegaonce ITEM_VENUSAURITE
	addmegaonce ITEM_VICTREEBELITE
	addmegaonce ITEM_MEGANIUMITE
	addmegaonce ITEM_ABOMASITE
	addmegaonce ITEM_CHESNAUGHTITE
	addmegaonce ITEM_SCOVILLAINITE
	playfanfare MUS_OBTAIN_ITEM
	message PartnerMega_Text_GotGrass
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	return

PartnerMega_Text_MoreGrass:
	.string "Nimm auch alle anderen\n"
	.string "Pflanzen-Megasteine mit!$"

PartnerMega_Text_GotGrass:
	.string "{PLAYER} erhaelt alle\n"
	.string "Pflanzen-Megasteine!$"
