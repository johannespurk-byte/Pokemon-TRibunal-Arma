#ifndef GUARD_NUZLOCKE_H
#define GUARD_NUZLOCKE_H

bool32 Nuzlocke_IsActive(void);
void Nuzlocke_OnBattleStart(void);
bool32 Nuzlocke_IsCatchBlocked(void);
void Nuzlocke_MarkFaintedPartyMonsDead(void);
void Nuzlocke_MarkMonDead(struct Pokemon *mon);
bool32 Nuzlocke_ShouldSkipHeal(struct BoxPokemon *boxMon);
bool32 Nuzlocke_IsItemBlocked(struct Pokemon *mon);

#endif // GUARD_NUZLOCKE_H
