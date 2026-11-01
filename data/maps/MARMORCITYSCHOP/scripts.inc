MARMORCITYSCHOP_MapScripts::
	.byte 0

MARMORCITYSCHOP_EventScript_Nurse::
	lock
	faceplayer
	message MARMORCITYSCHOP_Text_Welcome
	waitmessage
	pokemart MARMORCITYSCHOP_Nurse_Pokemart
	msgbox MARMORCITYSCHOP_Text_Goodbye, MSGBOX_DEFAULT
	release
	end

	.align 2
MARMORCITYSCHOP_Nurse_Pokemart::
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_LUM_BERRY
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_ENERGY_POWDER
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_EXP_ALL
	.2byte ITEM_NONE

MARMORCITYSCHOP_Text_Welcome:
	.string "Hi! How may I serve you today?$"

MARMORCITYSCHOP_Text_Goodbye:
	.string "Please come again!$"
