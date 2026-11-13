@ =========================================================
@ PETALBURG GYM: Mom's house. Room trainers guard the stairs,
@ Mom and Misty wait in the salon, Norman in the Littleroot arena.
@ =========================================================
PetalburgCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_Gym_OnTransition
	.byte 0

PetalburgCity_Gym_OnTransition:
	call_if_lt VAR_PETALBURG_GYM_STATE, 2, PetalburgCity_Gym_EventScript_InitializeGymState
	end

PetalburgCity_Gym_EventScript_InitializeGymState::
	setvar VAR_PETALBURG_GYM_STATE, 2
	return

PetalburgCity_Gym_EventScript_GymGuide::
	msgbox PetalburgCity_Gym_Text_GymGuide, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_FINISHED_HAUS_BATTLE, PetalburgCity_Gym_EventScript_MomAfterWin
	goto_if_lt VAR_PETALBURG_GYM_STATE, 6, PetalburgCity_Gym_EventScript_MomNoBadges
	msgbox PetalburgCity_Gym_Text_MomWelcome, MSGBOX_DEFAULT
	closemessage
	msgbox PetalburgCity_Gym_Text_MistyInterrupts, MSGBOX_DEFAULT
	closemessage
	trainerbattle_two_trainers TRAINER_NORMAN_1, PetalburgCity_Gym_Text_MomDefeat, TRAINER_MISTY, PetalburgCity_Gym_Text_MistyDefeat
	setflag FLAG_FINISHED_HAUS_BATTLE
	msgbox PetalburgCity_Gym_Text_MomRewardSpeech, MSGBOX_DEFAULT
	giveitem ITEM_TM01
	msgbox PetalburgCity_Gym_Text_MistyGivesStone, MSGBOX_DEFAULT
	giveitem ITEM_BLASTOISINITE
	msgbox PetalburgCity_Gym_Text_MistyExplainStone, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_SendToNorman

PetalburgCity_Gym_EventScript_MomNoBadges:
	msgbox PetalburgCity_Gym_Text_DadNoBadges, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_MomAfterWin:
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_MomPostBattle
	msgbox PetalburgCity_Gym_Text_MomAskTeleport, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_SendToNorman
	release
	end

PetalburgCity_Gym_EventScript_MomPostBattle:
	msgbox PetalburgCity_Gym_Text_MomPostBattle, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_SendToNorman::
	msgbox PetalburgCity_Gym_Text_MomNormanWaits, MSGBOX_DEFAULT
	closemessage
	playse SE_WARP_IN
	warp MAP_LITTLEROOT_ARENA, 4, 12
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_Mary::
	trainerbattle_single TRAINER_MARY, PetalburgCity_Gym_Text_MaryIntro, PetalburgCity_Gym_Text_MaryDefeat
	msgbox PetalburgCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL, PetalburgCity_Gym_Text_RandallIntro, PetalburgCity_Gym_Text_RandallDefeat
	msgbox PetalburgCity_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_Parker::
	trainerbattle_single TRAINER_PARKER, PetalburgCity_Gym_Text_ParkerIntro, PetalburgCity_Gym_Text_ParkerDefeat
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_Jody::
	trainerbattle_single TRAINER_JODY, PetalburgCity_Gym_Text_JodyIntro, PetalburgCity_Gym_Text_JodyDefeat
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_George::
	trainerbattle_single TRAINER_GEORGE, PetalburgCity_Gym_Text_GeorgeIntro, PetalburgCity_Gym_Text_GeorgeDefeat
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_Alexia::
	trainerbattle_single TRAINER_ALEXIA, PetalburgCity_Gym_Text_AlexiaIntro, PetalburgCity_Gym_Text_AlexiaDefeat
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE, PetalburgCity_Gym_Text_BerkeIntro, PetalburgCity_Gym_Text_BerkeDefeat
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

@ --- TEXTE ---
PetalburgCity_Gym_Text_GymGuide:
	.string "Willkommen im Haus von Mom!\p"
	.string "Jedes Zimmer hat einen Bewohner, der\n"
	.string "dich an der Treppe herausfordert.\p"
	.string "Ganz oben im Salon warten Mom und\n"
	.string "Misty auf dich. Viel Glueck!$"

PetalburgCity_Gym_Text_MistyGivesStone:
	.string "MISTY: Ich gebe mich geschlagen.\n"
	.string "Nimm diesen Stein von mir!$"

PetalburgCity_Gym_Text_MistyExplainStone:
	.string "MISTY: Das ist das Turtoksit. Damit\n"
	.string "kann Turtok Mega-evolvieren!$"

PetalburgCity_Gym_Text_MomNormanWaits:
	.string "MOM: Dein Vater erwartet dich in\n"
	.string "seiner Arena in Wurzelheim.\p"
	.string "Ich bringe dich direkt zu ihm!$"

PetalburgCity_Gym_Text_MomAskTeleport:
	.string "MOM: Norman wartet in Wurzelheim\n"
	.string "auf dich. Soll ich dich hinbringen?$"

PetalburgCity_Gym_Text_DadNoBadges:
	.string "MOM: Besiege erst alle Mitbewohner!$"

PetalburgCity_Gym_Text_MomWelcome:
	.string "MOM: Testen wir dein Team! Ich kaempfe aber nicht allein...$"

PetalburgCity_Gym_Text_MistyInterrupts:
	.string "MISTY: Huhu! Ich helfe dir, Mom!$"

PetalburgCity_Gym_Text_MomDefeat:
	.string "MOM: Unglaublich... du hast uns besiegt!$"

PetalburgCity_Gym_Text_MistyDefeat:
	.string "MISTY: Oh nein! Mein Wasser ist verdampft...$"

PetalburgCity_Gym_Text_MomRewardSpeech:
	.string "MOM: Nimm stattdessen diese TM von\n"
	.string "mir!$"

PetalburgCity_Gym_Text_MomPostBattle:
	.string "MOM: Zeig allen, was du gelernt\n"
	.string "hast!$"

PetalburgCity_Gym_Text_BagIsFull:
	.string "MOM: Dein Rucksack ist randvoll!$"

PetalburgCity_Gym_Text_RandallIntro:
	.string "Wer die Kueche betritt, muss\n"
	.string "kaempfen!$"

PetalburgCity_Gym_Text_RandallDefeat:
	.string "Mein Essen brennt an...$"

PetalburgCity_Gym_Text_RandallPostBattle:
	.string "Du darfst weiter ins Bad.$"


PetalburgCity_Gym_Text_MaryIntro:
	.string "Stoer mich nicht beim Faulenzen!$"

PetalburgCity_Gym_Text_MaryDefeat:
	.string "Jetzt habe ich das Finale verpasst!$"

PetalburgCity_Gym_Text_MaryPostBattle:
	.string "Weiter geht es in die Kueche.$"


PetalburgCity_Gym_Text_ParkerIntro:
	.string "Besetzt! Hier kommt keiner ungefragt\n"
	.string "ins Bad!$"

PetalburgCity_Gym_Text_ParkerDefeat:
	.string "Die Zahnpasta ist im Auge gelandet!$"

PetalburgCity_Gym_Text_ParkerPostBattle:
	.string "Der Garten wartet auf dich.$"


PetalburgCity_Gym_Text_AlexiaIntro:
	.string "Ich wollte gerade einen\n"
	.string "Mittagsschlaf machen!$"

PetalburgCity_Gym_Text_AlexiaDefeat:
	.string "Jetzt bin ich hellwach...$"

PetalburgCity_Gym_Text_AlexiaPostBattle:
	.string "Geh hoch auf den Dachboden.$"


PetalburgCity_Gym_Text_GeorgeIntro:
.string "Ich repariere hier unten die\n"
.string "Heizung.$"
PetalburgCity_Gym_Text_GeorgeDefeat:
.string "Die Rohre brechen zusammen!$"
PetalburgCity_Gym_Text_GeorgePostBattle:
	.string "Das Schlafzimmer ist jetzt frei.$"

PetalburgCity_Gym_Text_JodyIntro:
.string "Ich giesse die Pflanzen im Garten.$"
PetalburgCity_Gym_Text_JodyDefeat:
.string "Mein schoener Rasen ist\n"
.string "ueberschwemmt!$"
PetalburgCity_Gym_Text_JodyPostBattle:
	.string "Unten im Keller geht es weiter.$"

PetalburgCity_Gym_Text_BerkeIntro:
	.string "Hier oben auf dem Dachboden weht\n"
	.string "ein scharfer Wind!$"

PetalburgCity_Gym_Text_BerkeDefeat:
	.string "Mein Dachboden ist weggeweht!$"

PetalburgCity_Gym_Text_BerkePostBattle:
	.string "Wahnsinn! Mom wartet im Salon!$"

