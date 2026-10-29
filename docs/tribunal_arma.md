# Pokémon Tribunal ARMA – Änderungen

Diese Seite beschreibt Änderungen an Pokémon Tribunal ARMA, die nicht aus pokeemerald-expansion stammen.
Alle drei ROMs werden so gebaut, Emerald zuletzt, weil alle dieselbe `Pokemon_Tribunal_ARMA.gba` schreiben:

```bash
make firered -j$(nproc) UNUSED_ERROR=1 DEPRECATED_ERROR=1
make leafgreen -j$(nproc) UNUSED_ERROR=1 DEPRECATED_ERROR=1
make -j$(nproc) UNUSED_ERROR=1 DEPRECATED_ERROR=1
```

## Titelbild

Die Schriftzüge „TRIBUNAL ARMA“, „PRESS START“ und „©2026 WARGUN“ sind in einer gemeinsamen, handgezeichneten Blockschrift gezeichnet.
Die Buchstaben sind 5 Pixel hoch und haben 2 Pixel breite Striche und eine schwarze Kontur von 1 Pixel.
Der Pokémon-Schriftzug ist unverändert.

| Datei | Inhalt |
|---|---|
| `graphics/title_screen/tribunal_arma_0.png` … `_3.png` | „TRIBUNAL ARMA“, 4 Sprites à 32×8 bei y = 64 |
| `graphics/title_screen/tribunal_arma_logo.pal` | Goldpalette für „TRIBUNAL ARMA“ |
| `graphics/title_screen/press_start.png` | Kacheln 1–20: PRESS START (gold), Kacheln 21–40: Copyright (silber) |

## Goldene Schrift in Textboxen

Dialogtexte und die Rahmen der Menüfenster in der Spielwelt sind golden auf dunklem Marineblau.
Der GBA zeichnet jeden Buchstaben mit genau zwei Farben: Füllfarbe und Schatten.
Mehr Farbstufen als Gold mit Bronze-Schatten sind deshalb nicht möglich.

| Datei | Index | Farbe | Verwendung |
|---|---|---|---|
| `graphics/text_window/message_box.png`, `name_box.png` | 1, 13, 14 | 20,28,64 Marineblau | Hintergrund der Dialogbox |
| | 2 | 248,208,72 Gold | Schrift |
| | 3 | 112,64,8 Bronze | Schriftschatten |
| | 10 / 11 / 12 | dunkle Kontur / Goldkante / dunkles Blau | Kante der Box |
| `graphics/text_window/1.png` (Standard-Fensterrahmen) | 1–8, 15 | Goldtöne | Rahmen von Startmenü, Ja/Nein und Auswahlmenüs |
| | 14 | Marineblau | Innenkante des Rahmens |

Die Palette der Dialogbox (`gMessageBox_Pal`) laden auch Menüfenster mit Palette 15.
Darum wird die Schrift dort ebenfalls golden.
Der Fußabdruck im Pokédex nutzt Index 2 dieser Palette und ist jetzt ebenfalls golden.

`graphics/interface/std_menu.pal` ist unverändert.
Diese Palette nutzen Bildschirme mit hellem Hintergrund (Team, Beutel, Pokédex), auf denen Gold schlecht lesbar wäre.

## Rocket-Versteck (nur FireRed/LeafGreen)

Alle elf Rüpel (`TRAINER_TEAM_ROCKET_GRUNT_8` … `_18`) und Giovanni (`TRAINER_BOSS_GIOVANNI`) haben 6 Pokémon mit 31 DVs, EVs, Wesen, Item und passender Fähigkeit.
Die KI ist `Smart Trainer / Prediction`.
Jedes Team hat genau einen Nutzer pro Gimmick: Mega, Dynamax, Tera und Z-Attacke.
Die Teams stehen in `src/data/trainers_frlg.party`.

### Level

In `src/data/level_scaling_rules.h` kämpfen alle zwölf mit `LEVEL_SCALING_TO_LEVEL_CAP`, also immer auf der aktuellen Level-Grenze aus `src/caps.c`.
Die Regeln stehen in `#if IS_FRLG`.

| Orden | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|---|
| Level-Grenze | 18 | 36 | 50 | 60 | 68 | 74 | 80 | 90 | 100 |

### Teams

| Trainer | Mega | Dynamax | Tera | Z-Attacke |
|---|---|---|---|---|
| Rüpel 8 | Bibor | Iksbat | Arbok (Boden) | Alola-Sleimok (Tenebrium Z) |
| Rüpel 9 | Kangama | Gaunux | Alola-Snobilikat (Unlicht) | Alola-Rattikarl (Normium Z) |
| Rüpel 10 | Zobiris | Deponitox (Gigadynamax) | Aggrostella (Stahl) | Schlukwech (Toxium Z) |
| Rüpel 11 | Flunkifer | Mimigma | Kryppuk (Fee) | Zoroark (Tenebrium Z) |
| Rüpel 12 | Hundemon | Piondragi | Hypno (Psycho) | Skuntank (Toxium Z) |
| Rüpel 13 | Tohaido | Krebutack | Calamanero (Kampf) | Tentoxa (Aquium Z) |
| Rüpel 14 | Simsala | Bronzong | Morbitesse (Fee) | Rossana (Glacium Z) |
| Rüpel 15 | Meditalis | Machomei (Gigadynamax) | Kapoera (Geist) | Meistagrif (Fightium Z) |
| Rüpel 16 | Banette | Sandamer | Hippoterus (Wasser) | Stalobor (Terrium Z) |
| Rüpel 17 | Garados | Aerodactyl | Nidoking (Boden) | Despotar (Petrium Z) |
| Rüpel 18 | Gengar | Riffex (Gigadynamax) | Porygon2 (Geist) | Relaxo (Relaxonium Z) |
| Giovanni | Stahlos | Rihornior | Nidoqueen (Fee) | Nidoking (Terrium Z) |

Giovannis übrige Pokémon sind Digdri (Fokusgurt, Ausweglos) und Snobilikat (Leben-Orb, Techniker).

Im Emerald-Build haben die Rüpel 8–18 dieselben IDs wie Walter 3–5, die Top Vier und vier Arenaleiter.
Das Rocket-Versteck ist deshalb nur in FireRed/LeafGreen korrekt.

### Giovannis Text

Nach dem Kampf verspricht Giovanni weitere Begegnungen und verrät das Bündnis mit Team Magma und Team Aqua.
Er finanziert Marc (Magma) und Adrian (Aqua) und hält sie für „nützliche Narren“.
Dafür führen sie ihn zu den Legenden von Hoenn.
Der Text steht in `data/maps/RocketHideout_B4F_Frlg/scripts.inc`.

### Geplant

- Giovanni in der Silph Co. bleibt unverändert.
- Die Arena von Vertania wird ein eigenes Custom-Event.
