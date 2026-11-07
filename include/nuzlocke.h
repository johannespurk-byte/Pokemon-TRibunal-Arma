#ifndef GUARD_NUZLOCKE_H
#define GUARD_NUZLOCKE_H

// Route 104 und 112 sind je eine Karte, aber zwei getrennte Stücke. Das obere Stück hat ein eigenes Bit,
// ganz am Ende, damit neue MAPSECs es nicht verschieben.
#define NUZLOCKE_AREA_ROUTE_104_NORTH 255
#define NUZLOCKE_AREA_ROUTE_112_NORTH 254

bool32 Nuzlocke_IsActive(void);
bool32 Nuzlocke_IsAreaUsed(u32 area);
u32 Nuzlocke_GetEncounterArea(void);
void Nuzlocke_OnBattleStart(void);
bool32 Nuzlocke_IsCatchBlocked(void);
void Nuzlocke_MarkFaintedPartyMonsDead(void);
void Nuzlocke_MarkMonDead(struct Pokemon *mon);
bool32 Nuzlocke_ShouldSkipHeal(struct BoxPokemon *boxMon);
bool32 Nuzlocke_IsItemBlocked(struct Pokemon *mon);

#endif // GUARD_NUZLOCKE_H
