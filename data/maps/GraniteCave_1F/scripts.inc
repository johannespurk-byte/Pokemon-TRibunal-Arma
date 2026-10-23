GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	trainerbattle_single TRAINER_AQUACAMP_GRUNT_2, RusturfTunnel_Text_MikeIntro, RusturfTunnel_Text_MikeDefeat
	msgbox RusturfTunnel_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

