Fossil_Ruins_2_MapScripts::
	.byte 0

@ =========================================================
@ TRAINER 1: STONER (Gibt das Dynamax-Band / Z-Ring & Kristall)
@ =========================================================
Fossil_Ruins_2_Eventscript_Stoner::
	trainerbattle_single TRAINER_STONER, Fossil_Ruins_2_Text_StonerIntro, Fossil_Ruins_2_Text_StonerDefeated, Fossil_Ruins_2_EventScript_StonerDefeatedScript
	msgbox Fossil_Ruins_2_Text_StonerPostBattle, MSGBOX_AUTOCLOSE
	end

Fossil_Ruins_2_EventScript_StonerDefeatedScript::
	lock
	faceplayer
	msgbox Fossil_Ruins_2_Text_StonerExplainReward, MSGBOX_DEFAULT
	giveitem ITEM_Z_POWER_RING
	msgbox Fossil_Ruins_2_Text_ExplainZRing, MSGBOX_DEFAULT
	giveitem ITEM_ROCKIUM_Z
	msgbox Fossil_Ruins_2_Text_ExplainZCrystal, MSGBOX_DEFAULT
	release
	end

Fossil_Ruins_2_Text_StonerIntro::
	.string "Willkommen in den Tiefen der Ruinen!\n"
	.string "Meine Gesteins-Festung wird dich zerquetschen!$"	

Fossil_Ruins_2_Text_StonerDefeated::
	.string "Unmoeglich... Meine Verteidigung wurde\n"
	.string "wie Glas zertruemmert!$"

Fossil_Ruins_2_Text_StonerExplainReward::
	.string "Du hast eine unbaendige Kraft bewiesen.\n"
	.string "Nimm diese Relikte, die wir hier ausgegraben haben.$"

Fossil_Ruins_2_Text_ExplainZRing::
	.string "Das ist ein Z-Ring.\n"
	.string "Er kanalisiert den Willen des Trainers.$"

Fossil_Ruins_2_Text_ExplainZCrystal::
	.string "Und das hier ist das Petraium Z.\n"
	.string "Lass ein Gesteins-Pokemon es tragen, um eine\n"
	.string "Z-Attacke von gigantischer Macht zu entfesseln!$"

Fossil_Ruins_2_Text_StonerPostBattle::
	.string "Ein wahrer Kampfrausch... Wenn du noch mehr\n"
	.string "Herausforderungen suchst, fordere die anderen heraus.$"


@ =========================================================
@ TRAINER 2: RINO (Gesteins-Trainer)
@ =========================================================
Fossil_Ruins_2_Eventscript_Rino::
	trainerbattle_single TRAINER_RINO, Fossil_Ruins_2_Text_RinoIntro, Fossil_Ruins_2_Text_RinoDefeated
	msgbox Fossil_Ruins_2_Text_RinoPostBattle, MSGBOX_AUTOCLOSE
	end

Fossil_Ruins_2_Text_RinoIntro::
	.string "Stoner mag die Schaetze bewachen, aber ich\n"
	.string "bewache den Weg nach draussen! Kaempfen wir!$"

Fossil_Ruins_2_Text_RinoDefeated::
	.string "Auch meine Fossilien konnten deiner\n"
	.string "Offensive nicht standhalten...$"

Fossil_Ruins_2_Text_RinoPostBattle::
	.string "Hast du die Gesteins-Z-Attacke schon\n"
	.string "ausprobiert? Sie laesst den Boden erbeben!$"


@ =========================================================
@ TRAINER 3: BERT (Fossilien-Sammler)
@ =========================================================
Fossil_Ruins_2_Eventscript_Bert::
	trainerbattle_single TRAINER_BERT, Fossil_Ruins_2_Text_BertIntro, Fossil_Ruins_2_Text_BertDefeated
	msgbox Fossil_Ruins_2_Text_BertPostBattle, MSGBOX_AUTOCLOSE
	end

Fossil_Ruins_2_Text_BertIntro::
	.string "Diese alten Fossilien schlafen seit Aeonen.\n"
	.string "Spuere ihre urzeitliche Wut!$"

Fossil_Ruins_2_Text_BertDefeated::
	.string "Wieder zurueck in den ewigen Schlaf...$"

Fossil_Ruins_2_Text_BertPostBattle::
	.string "Es gibt hier noch so viel zu erforschen.\n"
	.string "Vielleicht finden wir noch mehr Kristalle.$"
