Route111_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_PokemonCenter_1F_OnTransition
	.byte 0

Route111_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_ROUTE_111
	end

Route111_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_ROUTE111_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
