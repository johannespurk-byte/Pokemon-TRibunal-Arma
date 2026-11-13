@ Shared scripts for the service NPCs in every Pokemon Center and Mart.
@ Regional form trader: trades any party Pokemon for a regional form.
@ VAR_0x8004 = party slot, VAR_0x8005 = chosen species,
@ VAR_0x8006 = level of the new Pokemon, VAR_0x8007 = level cap.

Common_EventScript_RegionalTrader::
	lock
	faceplayer
	msgbox Common_Text_RegionalTraderIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_RegionalTraderDecline
Common_EventScript_RegionalTraderChooseRegion::
	message Common_Text_RegionalTraderWhichRegion
	waitmessage
	dynmultichoice 18, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_RegionAlola, Common_Text_RegionGalar, Common_Text_RegionHisui, Common_Text_RegionPaldea, gText_Exit
	switch VAR_RESULT
	case 0, Common_EventScript_RegionalTraderAlola
	case 1, Common_EventScript_RegionalTraderGalar
	case 2, Common_EventScript_RegionalTraderHisui
	case 3, Common_EventScript_RegionalTraderPaldea
	goto Common_EventScript_RegionalTraderDecline

Common_EventScript_RegionalTraderAlola::
	message Common_Text_RegionalTraderWhichMon
	waitmessage
	dynmultichoice 16, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_Rf_RATTATA_ALOLA, Common_Text_Rf_RATICATE_ALOLA, Common_Text_Rf_RAICHU_ALOLA, Common_Text_Rf_SANDSHREW_ALOLA, Common_Text_Rf_SANDSLASH_ALOLA, Common_Text_Rf_VULPIX_ALOLA, Common_Text_Rf_NINETALES_ALOLA, Common_Text_Rf_DIGLETT_ALOLA, Common_Text_Rf_DUGTRIO_ALOLA, Common_Text_Rf_MEOWTH_ALOLA, Common_Text_Rf_PERSIAN_ALOLA, Common_Text_Rf_GEODUDE_ALOLA, Common_Text_Rf_GRAVELER_ALOLA, Common_Text_Rf_GOLEM_ALOLA, Common_Text_Rf_GRIMER_ALOLA, Common_Text_Rf_MUK_ALOLA, Common_Text_Rf_EXEGGUTOR_ALOLA, Common_Text_Rf_MAROWAK_ALOLA, gText_Exit
	switch VAR_RESULT
	case 0, Common_EventScript_RegionalTraderPick_RATTATA_ALOLA
	case 1, Common_EventScript_RegionalTraderPick_RATICATE_ALOLA
	case 2, Common_EventScript_RegionalTraderPick_RAICHU_ALOLA
	case 3, Common_EventScript_RegionalTraderPick_SANDSHREW_ALOLA
	case 4, Common_EventScript_RegionalTraderPick_SANDSLASH_ALOLA
	case 5, Common_EventScript_RegionalTraderPick_VULPIX_ALOLA
	case 6, Common_EventScript_RegionalTraderPick_NINETALES_ALOLA
	case 7, Common_EventScript_RegionalTraderPick_DIGLETT_ALOLA
	case 8, Common_EventScript_RegionalTraderPick_DUGTRIO_ALOLA
	case 9, Common_EventScript_RegionalTraderPick_MEOWTH_ALOLA
	case 10, Common_EventScript_RegionalTraderPick_PERSIAN_ALOLA
	case 11, Common_EventScript_RegionalTraderPick_GEODUDE_ALOLA
	case 12, Common_EventScript_RegionalTraderPick_GRAVELER_ALOLA
	case 13, Common_EventScript_RegionalTraderPick_GOLEM_ALOLA
	case 14, Common_EventScript_RegionalTraderPick_GRIMER_ALOLA
	case 15, Common_EventScript_RegionalTraderPick_MUK_ALOLA
	case 16, Common_EventScript_RegionalTraderPick_EXEGGUTOR_ALOLA
	case 17, Common_EventScript_RegionalTraderPick_MAROWAK_ALOLA
	goto Common_EventScript_RegionalTraderChooseRegion

Common_EventScript_RegionalTraderPick_RATTATA_ALOLA::
	setvar VAR_0x8005, SPECIES_RATTATA_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_RATICATE_ALOLA::
	setvar VAR_0x8005, SPECIES_RATICATE_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_RAICHU_ALOLA::
	setvar VAR_0x8005, SPECIES_RAICHU_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SANDSHREW_ALOLA::
	setvar VAR_0x8005, SPECIES_SANDSHREW_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SANDSLASH_ALOLA::
	setvar VAR_0x8005, SPECIES_SANDSLASH_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_VULPIX_ALOLA::
	setvar VAR_0x8005, SPECIES_VULPIX_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_NINETALES_ALOLA::
	setvar VAR_0x8005, SPECIES_NINETALES_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_DIGLETT_ALOLA::
	setvar VAR_0x8005, SPECIES_DIGLETT_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_DUGTRIO_ALOLA::
	setvar VAR_0x8005, SPECIES_DUGTRIO_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_MEOWTH_ALOLA::
	setvar VAR_0x8005, SPECIES_MEOWTH_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_PERSIAN_ALOLA::
	setvar VAR_0x8005, SPECIES_PERSIAN_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_GEODUDE_ALOLA::
	setvar VAR_0x8005, SPECIES_GEODUDE_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_GRAVELER_ALOLA::
	setvar VAR_0x8005, SPECIES_GRAVELER_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_GOLEM_ALOLA::
	setvar VAR_0x8005, SPECIES_GOLEM_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_GRIMER_ALOLA::
	setvar VAR_0x8005, SPECIES_GRIMER_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_MUK_ALOLA::
	setvar VAR_0x8005, SPECIES_MUK_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_EXEGGUTOR_ALOLA::
	setvar VAR_0x8005, SPECIES_EXEGGUTOR_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_MAROWAK_ALOLA::
	setvar VAR_0x8005, SPECIES_MAROWAK_ALOLA
	goto Common_EventScript_RegionalTraderChooseMon

Common_EventScript_RegionalTraderGalar::
	message Common_Text_RegionalTraderWhichMon
	waitmessage
	dynmultichoice 16, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_Rf_MEOWTH_GALAR, Common_Text_Rf_PONYTA_GALAR, Common_Text_Rf_RAPIDASH_GALAR, Common_Text_Rf_SLOWPOKE_GALAR, Common_Text_Rf_SLOWBRO_GALAR, Common_Text_Rf_SLOWKING_GALAR, Common_Text_Rf_FARFETCHD_GALAR, Common_Text_Rf_WEEZING_GALAR, Common_Text_Rf_MR_MIME_GALAR, Common_Text_Rf_CORSOLA_GALAR, Common_Text_Rf_ZIGZAGOON_GALAR, Common_Text_Rf_LINOONE_GALAR, Common_Text_Rf_DARUMAKA_GALAR, Common_Text_Rf_DARMANITAN_GALAR_STANDARD, Common_Text_Rf_YAMASK_GALAR, Common_Text_Rf_STUNFISK_GALAR, Common_Text_Rf_ARTICUNO_GALAR, Common_Text_Rf_ZAPDOS_GALAR, Common_Text_Rf_MOLTRES_GALAR, gText_Exit
	switch VAR_RESULT
	case 0, Common_EventScript_RegionalTraderPick_MEOWTH_GALAR
	case 1, Common_EventScript_RegionalTraderPick_PONYTA_GALAR
	case 2, Common_EventScript_RegionalTraderPick_RAPIDASH_GALAR
	case 3, Common_EventScript_RegionalTraderPick_SLOWPOKE_GALAR
	case 4, Common_EventScript_RegionalTraderPick_SLOWBRO_GALAR
	case 5, Common_EventScript_RegionalTraderPick_SLOWKING_GALAR
	case 6, Common_EventScript_RegionalTraderPick_FARFETCHD_GALAR
	case 7, Common_EventScript_RegionalTraderPick_WEEZING_GALAR
	case 8, Common_EventScript_RegionalTraderPick_MR_MIME_GALAR
	case 9, Common_EventScript_RegionalTraderPick_CORSOLA_GALAR
	case 10, Common_EventScript_RegionalTraderPick_ZIGZAGOON_GALAR
	case 11, Common_EventScript_RegionalTraderPick_LINOONE_GALAR
	case 12, Common_EventScript_RegionalTraderPick_DARUMAKA_GALAR
	case 13, Common_EventScript_RegionalTraderPick_DARMANITAN_GALAR_STANDARD
	case 14, Common_EventScript_RegionalTraderPick_YAMASK_GALAR
	case 15, Common_EventScript_RegionalTraderPick_STUNFISK_GALAR
	case 16, Common_EventScript_RegionalTraderPick_ARTICUNO_GALAR
	case 17, Common_EventScript_RegionalTraderPick_ZAPDOS_GALAR
	case 18, Common_EventScript_RegionalTraderPick_MOLTRES_GALAR
	goto Common_EventScript_RegionalTraderChooseRegion

Common_EventScript_RegionalTraderPick_MEOWTH_GALAR::
	setvar VAR_0x8005, SPECIES_MEOWTH_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_PONYTA_GALAR::
	setvar VAR_0x8005, SPECIES_PONYTA_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_RAPIDASH_GALAR::
	setvar VAR_0x8005, SPECIES_RAPIDASH_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SLOWPOKE_GALAR::
	setvar VAR_0x8005, SPECIES_SLOWPOKE_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SLOWBRO_GALAR::
	setvar VAR_0x8005, SPECIES_SLOWBRO_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SLOWKING_GALAR::
	setvar VAR_0x8005, SPECIES_SLOWKING_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_FARFETCHD_GALAR::
	setvar VAR_0x8005, SPECIES_FARFETCHD_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_WEEZING_GALAR::
	setvar VAR_0x8005, SPECIES_WEEZING_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_MR_MIME_GALAR::
	setvar VAR_0x8005, SPECIES_MR_MIME_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_CORSOLA_GALAR::
	setvar VAR_0x8005, SPECIES_CORSOLA_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ZIGZAGOON_GALAR::
	setvar VAR_0x8005, SPECIES_ZIGZAGOON_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_LINOONE_GALAR::
	setvar VAR_0x8005, SPECIES_LINOONE_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_DARUMAKA_GALAR::
	setvar VAR_0x8005, SPECIES_DARUMAKA_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_DARMANITAN_GALAR_STANDARD::
	setvar VAR_0x8005, SPECIES_DARMANITAN_GALAR_STANDARD
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_YAMASK_GALAR::
	setvar VAR_0x8005, SPECIES_YAMASK_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_STUNFISK_GALAR::
	setvar VAR_0x8005, SPECIES_STUNFISK_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ARTICUNO_GALAR::
	setvar VAR_0x8005, SPECIES_ARTICUNO_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ZAPDOS_GALAR::
	setvar VAR_0x8005, SPECIES_ZAPDOS_GALAR
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_MOLTRES_GALAR::
	setvar VAR_0x8005, SPECIES_MOLTRES_GALAR
	goto Common_EventScript_RegionalTraderChooseMon

Common_EventScript_RegionalTraderHisui::
	message Common_Text_RegionalTraderWhichMon
	waitmessage
	dynmultichoice 16, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_Rf_GROWLITHE_HISUI, Common_Text_Rf_ARCANINE_HISUI, Common_Text_Rf_VOLTORB_HISUI, Common_Text_Rf_ELECTRODE_HISUI, Common_Text_Rf_TYPHLOSION_HISUI, Common_Text_Rf_QWILFISH_HISUI, Common_Text_Rf_SNEASEL_HISUI, Common_Text_Rf_SAMUROTT_HISUI, Common_Text_Rf_LILLIGANT_HISUI, Common_Text_Rf_ZORUA_HISUI, Common_Text_Rf_ZOROARK_HISUI, Common_Text_Rf_BRAVIARY_HISUI, Common_Text_Rf_SLIGGOO_HISUI, Common_Text_Rf_GOODRA_HISUI, Common_Text_Rf_AVALUGG_HISUI, Common_Text_Rf_DECIDUEYE_HISUI, gText_Exit
	switch VAR_RESULT
	case 0, Common_EventScript_RegionalTraderPick_GROWLITHE_HISUI
	case 1, Common_EventScript_RegionalTraderPick_ARCANINE_HISUI
	case 2, Common_EventScript_RegionalTraderPick_VOLTORB_HISUI
	case 3, Common_EventScript_RegionalTraderPick_ELECTRODE_HISUI
	case 4, Common_EventScript_RegionalTraderPick_TYPHLOSION_HISUI
	case 5, Common_EventScript_RegionalTraderPick_QWILFISH_HISUI
	case 6, Common_EventScript_RegionalTraderPick_SNEASEL_HISUI
	case 7, Common_EventScript_RegionalTraderPick_SAMUROTT_HISUI
	case 8, Common_EventScript_RegionalTraderPick_LILLIGANT_HISUI
	case 9, Common_EventScript_RegionalTraderPick_ZORUA_HISUI
	case 10, Common_EventScript_RegionalTraderPick_ZOROARK_HISUI
	case 11, Common_EventScript_RegionalTraderPick_BRAVIARY_HISUI
	case 12, Common_EventScript_RegionalTraderPick_SLIGGOO_HISUI
	case 13, Common_EventScript_RegionalTraderPick_GOODRA_HISUI
	case 14, Common_EventScript_RegionalTraderPick_AVALUGG_HISUI
	case 15, Common_EventScript_RegionalTraderPick_DECIDUEYE_HISUI
	goto Common_EventScript_RegionalTraderChooseRegion

Common_EventScript_RegionalTraderPick_GROWLITHE_HISUI::
	setvar VAR_0x8005, SPECIES_GROWLITHE_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ARCANINE_HISUI::
	setvar VAR_0x8005, SPECIES_ARCANINE_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_VOLTORB_HISUI::
	setvar VAR_0x8005, SPECIES_VOLTORB_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ELECTRODE_HISUI::
	setvar VAR_0x8005, SPECIES_ELECTRODE_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_TYPHLOSION_HISUI::
	setvar VAR_0x8005, SPECIES_TYPHLOSION_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_QWILFISH_HISUI::
	setvar VAR_0x8005, SPECIES_QWILFISH_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SNEASEL_HISUI::
	setvar VAR_0x8005, SPECIES_SNEASEL_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SAMUROTT_HISUI::
	setvar VAR_0x8005, SPECIES_SAMUROTT_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_LILLIGANT_HISUI::
	setvar VAR_0x8005, SPECIES_LILLIGANT_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ZORUA_HISUI::
	setvar VAR_0x8005, SPECIES_ZORUA_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_ZOROARK_HISUI::
	setvar VAR_0x8005, SPECIES_ZOROARK_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_BRAVIARY_HISUI::
	setvar VAR_0x8005, SPECIES_BRAVIARY_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_SLIGGOO_HISUI::
	setvar VAR_0x8005, SPECIES_SLIGGOO_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_GOODRA_HISUI::
	setvar VAR_0x8005, SPECIES_GOODRA_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_AVALUGG_HISUI::
	setvar VAR_0x8005, SPECIES_AVALUGG_HISUI
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_DECIDUEYE_HISUI::
	setvar VAR_0x8005, SPECIES_DECIDUEYE_HISUI
	goto Common_EventScript_RegionalTraderChooseMon

Common_EventScript_RegionalTraderPaldea::
	message Common_Text_RegionalTraderWhichMon
	waitmessage
	dynmultichoice 16, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_Rf_WOOPER_PALDEA, Common_Text_Rf_TAUROS_PALDEA_COMBAT, Common_Text_Rf_TAUROS_PALDEA_BLAZE, Common_Text_Rf_TAUROS_PALDEA_AQUA, gText_Exit
	switch VAR_RESULT
	case 0, Common_EventScript_RegionalTraderPick_WOOPER_PALDEA
	case 1, Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_COMBAT
	case 2, Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_BLAZE
	case 3, Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_AQUA
	goto Common_EventScript_RegionalTraderChooseRegion

Common_EventScript_RegionalTraderPick_WOOPER_PALDEA::
	setvar VAR_0x8005, SPECIES_WOOPER_PALDEA
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_COMBAT::
	setvar VAR_0x8005, SPECIES_TAUROS_PALDEA_COMBAT
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_BLAZE::
	setvar VAR_0x8005, SPECIES_TAUROS_PALDEA_BLAZE
	goto Common_EventScript_RegionalTraderChooseMon
Common_EventScript_RegionalTraderPick_TAUROS_PALDEA_AQUA::
	setvar VAR_0x8005, SPECIES_TAUROS_PALDEA_AQUA
	goto Common_EventScript_RegionalTraderChooseMon

Common_EventScript_RegionalTraderChooseMon::
	bufferspeciesname STR_VAR_2, VAR_0x8005
	msgbox Common_Text_RegionalTraderGiveWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	special RegionalTrade_CheckPartyMon
	goto_if_eq VAR_RESULT, 2, Common_EventScript_RegionalTraderChooseRegion
	goto_if_eq VAR_RESULT, 1, Common_EventScript_RegionalTraderEgg
	bufferspeciesname STR_VAR_2, VAR_0x8005
	msgbox Common_Text_RegionalTraderConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_RegionalTraderChooseRegion
	specialvar VAR_0x8007, GetLevelCapForScript
	goto_if_eq VAR_0x8006, VAR_0x8007, Common_EventScript_RegionalTraderDoTrade
	buffernumberstring STR_VAR_1, VAR_0x8006
	buffernumberstring STR_VAR_3, VAR_0x8007
	message Common_Text_RegionalTraderWhichLevel
	waitmessage
	dynmultichoice 17, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, Common_Text_RegionalTraderSameLevel, Common_Text_RegionalTraderLevelCap
	goto_if_eq VAR_RESULT, 0, Common_EventScript_RegionalTraderDoTrade
	copyvar VAR_0x8006, VAR_0x8007
Common_EventScript_RegionalTraderDoTrade::
	special RegionalTrade_RemovePartyMon
	givemon VAR_0x8005, VAR_0x8006
	bufferspeciesname STR_VAR_2, VAR_0x8005
	buffernumberstring STR_VAR_1, VAR_0x8006
	playfanfare MUS_OBTAIN_ITEM
	message Common_Text_RegionalTraderReceived
	waitmessage
	waitfanfare
	msgbox Common_Text_RegionalTraderThanks, MSGBOX_DEFAULT
	release
	end

Common_EventScript_RegionalTraderEgg::
	msgbox Common_Text_RegionalTraderNoEggs, MSGBOX_DEFAULT
	goto Common_EventScript_RegionalTraderChooseRegion

Common_EventScript_RegionalTraderDecline::
	msgbox Common_Text_RegionalTraderDecline, MSGBOX_DEFAULT
	release
	end

@ Item refiller: shows the bag, then tops up the chosen item.
@ Consumables are filled up to 99, held items get one more copy.
Common_EventScript_ItemRefiller::
	lock
	faceplayer
	msgbox Common_Text_ItemRefillerIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_ItemRefillerDecline
Common_EventScript_ItemRefillerChoose::
	msgbox Common_Text_ItemRefillerShowMe, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_RESULT, 0
	special Script_QuizLadyOpenBagMenu
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ItemRefillerDecline
	special ItemRefill_TryRefill
	bufferitemname STR_VAR_1, VAR_ITEM_ID
	goto_if_eq VAR_RESULT, 1, Common_EventScript_ItemRefillerNotAllowed
	goto_if_eq VAR_RESULT, 2, Common_EventScript_ItemRefillerFull
	buffernumberstring STR_VAR_2, VAR_0x8005
	playfanfare MUS_OBTAIN_ITEM
	message Common_Text_ItemRefillerDone
	waitmessage
	waitfanfare
	goto Common_EventScript_ItemRefillerAgain

Common_EventScript_ItemRefillerNotAllowed::
	msgbox Common_Text_ItemRefillerNotAllowed, MSGBOX_DEFAULT
	goto Common_EventScript_ItemRefillerAgain

Common_EventScript_ItemRefillerFull::
	msgbox Common_Text_ItemRefillerFull, MSGBOX_DEFAULT
Common_EventScript_ItemRefillerAgain::
	msgbox Common_Text_ItemRefillerAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Common_EventScript_ItemRefillerChoose
Common_EventScript_ItemRefillerDecline::
	msgbox Common_Text_ItemRefillerBye, MSGBOX_DEFAULT
	release
	end

Common_Text_RegionalTraderIntro:
	.string "I study POKéMON from far-off regions.\p"
	.string "Give me any POKéMON you like and\n"
	.string "I'll trade you a regional form!\p"
	.string "Want to make a trade?$"

Common_Text_RegionalTraderWhichRegion:
	.string "Which region interests you?$"

Common_Text_RegionalTraderWhichMon:
	.string "Which POKéMON would you like?$"

Common_Text_RegionalTraderGiveWhich:
	.string "{STR_VAR_2}, good choice!\n"
	.string "Which POKéMON will you give me?$"

Common_Text_RegionalTraderConfirm:
	.string "You'll trade your {STR_VAR_1}\n"
	.string "for {STR_VAR_2}. Is that okay?$"

Common_Text_RegionalTraderWhichLevel:
	.string "Should it keep your POKéMON's level,\n"
	.string "Lv. {STR_VAR_1}, or the cap, Lv. {STR_VAR_3}?$"

Common_Text_RegionalTraderSameLevel:
	.string "SAME LEVEL$"

Common_Text_RegionalTraderLevelCap:
	.string "LEVEL CAP$"

Common_Text_RegionalTraderReceived:
	.string "{PLAYER} received {STR_VAR_2}\n"
	.string "at Lv. {STR_VAR_1}!$"

Common_Text_RegionalTraderThanks:
	.string "Take good care of it!\n"
	.string "Come back for another trade anytime.$"

Common_Text_RegionalTraderNoEggs:
	.string "Sorry, I can't take an EGG.$"

Common_Text_RegionalTraderDecline:
	.string "Come back if you change your mind!$"

Common_Text_RegionAlola:
	.string "ALOLA$"

Common_Text_RegionGalar:
	.string "GALAR$"

Common_Text_RegionHisui:
	.string "HISUI$"

Common_Text_RegionPaldea:
	.string "PALDEA$"

Common_Text_Rf_RATTATA_ALOLA:
	.string "Rattata$"

Common_Text_Rf_RATICATE_ALOLA:
	.string "Raticate$"

Common_Text_Rf_RAICHU_ALOLA:
	.string "Raichu$"

Common_Text_Rf_SANDSHREW_ALOLA:
	.string "Sandshrew$"

Common_Text_Rf_SANDSLASH_ALOLA:
	.string "Sandslash$"

Common_Text_Rf_VULPIX_ALOLA:
	.string "Vulpix$"

Common_Text_Rf_NINETALES_ALOLA:
	.string "Ninetales$"

Common_Text_Rf_DIGLETT_ALOLA:
	.string "Diglett$"

Common_Text_Rf_DUGTRIO_ALOLA:
	.string "Dugtrio$"

Common_Text_Rf_MEOWTH_ALOLA:
	.string "Meowth$"

Common_Text_Rf_PERSIAN_ALOLA:
	.string "Persian$"

Common_Text_Rf_GEODUDE_ALOLA:
	.string "Geodude$"

Common_Text_Rf_GRAVELER_ALOLA:
	.string "Graveler$"

Common_Text_Rf_GOLEM_ALOLA:
	.string "Golem$"

Common_Text_Rf_GRIMER_ALOLA:
	.string "Grimer$"

Common_Text_Rf_MUK_ALOLA:
	.string "Muk$"

Common_Text_Rf_EXEGGUTOR_ALOLA:
	.string "Exeggutor$"

Common_Text_Rf_MAROWAK_ALOLA:
	.string "Marowak$"

Common_Text_Rf_MEOWTH_GALAR:
	.string "Meowth$"

Common_Text_Rf_PONYTA_GALAR:
	.string "Ponyta$"

Common_Text_Rf_RAPIDASH_GALAR:
	.string "Rapidash$"

Common_Text_Rf_SLOWPOKE_GALAR:
	.string "Slowpoke$"

Common_Text_Rf_SLOWBRO_GALAR:
	.string "Slowbro$"

Common_Text_Rf_SLOWKING_GALAR:
	.string "Slowking$"

Common_Text_Rf_FARFETCHD_GALAR:
	.string "Farfetch'd$"

Common_Text_Rf_WEEZING_GALAR:
	.string "Weezing$"

Common_Text_Rf_MR_MIME_GALAR:
	.string "Mr. Mime$"

Common_Text_Rf_CORSOLA_GALAR:
	.string "Corsola$"

Common_Text_Rf_ZIGZAGOON_GALAR:
	.string "Zigzagoon$"

Common_Text_Rf_LINOONE_GALAR:
	.string "Linoone$"

Common_Text_Rf_DARUMAKA_GALAR:
	.string "Darumaka$"

Common_Text_Rf_DARMANITAN_GALAR_STANDARD:
	.string "Darmanitan$"

Common_Text_Rf_YAMASK_GALAR:
	.string "Yamask$"

Common_Text_Rf_STUNFISK_GALAR:
	.string "Stunfisk$"

Common_Text_Rf_ARTICUNO_GALAR:
	.string "Articuno$"

Common_Text_Rf_ZAPDOS_GALAR:
	.string "Zapdos$"

Common_Text_Rf_MOLTRES_GALAR:
	.string "Moltres$"

Common_Text_Rf_GROWLITHE_HISUI:
	.string "Growlithe$"

Common_Text_Rf_ARCANINE_HISUI:
	.string "Arcanine$"

Common_Text_Rf_VOLTORB_HISUI:
	.string "Voltorb$"

Common_Text_Rf_ELECTRODE_HISUI:
	.string "Electrode$"

Common_Text_Rf_TYPHLOSION_HISUI:
	.string "Typhlosion$"

Common_Text_Rf_QWILFISH_HISUI:
	.string "Qwilfish$"

Common_Text_Rf_SNEASEL_HISUI:
	.string "Sneasel$"

Common_Text_Rf_SAMUROTT_HISUI:
	.string "Samurott$"

Common_Text_Rf_LILLIGANT_HISUI:
	.string "Lilligant$"

Common_Text_Rf_ZORUA_HISUI:
	.string "Zorua$"

Common_Text_Rf_ZOROARK_HISUI:
	.string "Zoroark$"

Common_Text_Rf_BRAVIARY_HISUI:
	.string "Braviary$"

Common_Text_Rf_SLIGGOO_HISUI:
	.string "Sliggoo$"

Common_Text_Rf_GOODRA_HISUI:
	.string "Goodra$"

Common_Text_Rf_AVALUGG_HISUI:
	.string "Avalugg$"

Common_Text_Rf_DECIDUEYE_HISUI:
	.string "Decidueye$"

Common_Text_Rf_WOOPER_PALDEA:
	.string "Wooper$"

Common_Text_Rf_TAUROS_PALDEA_COMBAT:
	.string "Tauros Combat$"

Common_Text_Rf_TAUROS_PALDEA_BLAZE:
	.string "Tauros Blaze$"

Common_Text_Rf_TAUROS_PALDEA_AQUA:
	.string "Tauros Aqua$"

Common_Text_ItemRefillerIntro:
	.string "I'm the ITEM REFILLER!\p"
	.string "Show me an item from your BAG and\n"
	.string "I'll top it up for free.\p"
	.string "Shall I refill something?$"

Common_Text_ItemRefillerShowMe:
	.string "Go on, show me the item!$"

Common_Text_ItemRefillerDone:
	.string "There you go! You got\n"
	.string "{STR_VAR_2} more {STR_VAR_1}!$"

Common_Text_ItemRefillerNotAllowed:
	.string "Sorry, I can't refill {STR_VAR_1}.\p"
	.string "KEY ITEMS, TMs and MEGA STONES\n"
	.string "are off-limits.$"

Common_Text_ItemRefillerFull:
	.string "You already have plenty of\n"
	.string "{STR_VAR_1}!$"

Common_Text_ItemRefillerAgain:
	.string "Want me to refill another item?$"

Common_Text_ItemRefillerBye:
	.string "Come back when you run low!$"
