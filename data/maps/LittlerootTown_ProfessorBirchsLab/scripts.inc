LittlerootTown_ProfessorBirchsLab_MapScripts::
    .byte 0

LittlerootTown_ProfessorBirchsLab_EventScript_Assistant::
    lock
    faceplayer
    msgbox LittlerootTown_ProfessorBirchsLab_Text_AssistantDummy, 4
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
    lock
    faceplayer
    msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchWelcome, 4
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Rival::
    lock
    faceplayer
    msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalDummy, 4
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil::
LittlerootTown_ProfessorBirchsLab_EventScript_Totodile::
LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita::
    lock
    msgbox LittlerootTown_ProfessorBirchsLab_Text_PokemonDummy, 3
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
    lock
    msgbox LittlerootTown_ProfessorBirchsLab_Text_BookshelfDummy, 3
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_PC::
    lock
    msgbox LittlerootTown_ProfessorBirchsLab_Text_PCDummy, 3
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
    lock
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MachineDummy, 3
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_Book::
    lock
    msgbox LittlerootTown_ProfessorBirchsLab_Text_BookDummy, 3
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall::
    bx lr

LittlerootTown_ProfessorBirchsLab_Text_AssistantDummy:
    .string "Ich helfe dem Professor.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchWelcome:
    .string "Willkommen im Labor!$"

LittlerootTown_ProfessorBirchsLab_Text_RivalDummy:
    .string "Viel Erfolg!$"

LittlerootTown_ProfessorBirchsLab_Text_PokemonDummy:
    .string "Ein Ball mit einem Pokemon.$"

LittlerootTown_ProfessorBirchsLab_Text_BookshelfDummy:
    .string "Ein Bücherregal.$"

LittlerootTown_ProfessorBirchsLab_Text_PCDummy:
    .string "Ein Computer.$"

LittlerootTown_ProfessorBirchsLab_Text_MachineDummy:
    .string "Eine Maschine.$"

LittlerootTown_ProfessorBirchsLab_Text_BookDummy:
    .string "Ein Buch.$"
