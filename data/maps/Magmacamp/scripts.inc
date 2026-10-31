Magmacamp_MapScripts::
	.byte 0
Magmacamp_Grunt_1_Gamma::
	trainerbattle_double TRAINER_GRUNT_MAGMACAMP_1, Magmacamp_Text_GammaIntro, Magmacamp_Text_GammaDefeated, Magmacamp_Text_GammaNotEnoughMons
	msgbox Magmacamp_Text_GammaPostBattle, MSGBOX_AUTOCLOSE
	end

Magmacamp_Grunt_2_Alpha::
	trainerbattle_double TRAINER_GRUNT_MAGMACAMP_2, Magmacamp_Text_AlphaIntro, Magmacamp_Text_AlphaDefeated, Magmacamp_Text_AlphaNotEnoughMons
	msgbox Magmacamp_Text_AlphaPostBattle, MSGBOX_AUTOCLOSE
	end

@ =========================================================================
@ TEXTE FÜR GRUNT 1 (GAMMA)
@ =========================================================================
Magmacamp_Text_GammaIntro:
	.string "We want to test our new strength again.\n"
	.string "We will not lose this time!$"	

Magmacamp_Text_GammaDefeated:
	.string "Arrgh, I lost the battle...\n"
	.string "I should have trained mine more.$"

Magmacamp_Text_GammaNotEnoughMons:
	.string "Humph... You don't even have two\n"
	.string "Pokemon with you.$"

Magmacamp_Text_GammaPostBattle:
	.string "Listen, you. If you're strong for me,\n"
	.string "We need to talk to our admins.!$"

@ =========================================================================
@ TEXTE FÜR GRUNT 2 (ALPHA)
@ =========================================================================
Magmacamp_Text_AlphaIntro:
	.string "We want to test our new strength again.\n"
	.string "We will not lose this time!$"	

Magmacamp_Text_AlphaDefeated:
	.string "Arrgh, I lost the battle...\n"
	.string "I should have trained mine more.$"

Magmacamp_Text_AlphaNotEnoughMons:
	.string "Hey, a double battle requires two\n"
	.string "Pokemon! Come back later.$"

Magmacamp_Text_AlphaPostBattle:
	.string "Listen, you. If you're strong for me,\n"
	.string "We need to talk to our admins.!$"
