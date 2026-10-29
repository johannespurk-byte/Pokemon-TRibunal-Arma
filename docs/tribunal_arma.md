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

### Menüs

Team, Beutel und Pokédex haben dasselbe Schema: marineblaue Flächen, goldene Kanten und goldene Schrift.

| Datei | Änderung |
|---|---|
| `graphics/interface/std_menu.pal` | Index 1 Marineblau, 2 Gold, 3 Bronze: Kontextmenüs und Ja/Nein auf allen Bildschirmen |
| `graphics/interface/option_menu_text.pal`, `sOptionMenuBg_Pal` in `src/option_menu.c` | Optionsmenü: Titelleiste Bronze, Karte Marineblau, Namen Gold, Werte Hellgold, Pfeile und Hilfetext Dunkelgold |
| `graphics/bag/swsh/tiles.png` | Gelbe Fläche wird Marineblau, orange Balken werden Gold, die Taschenleiste wird Schieferblau. In Palette 1 steht die Schrift (1 Gold, 3 Bronze; das gewählte Item hat 2 Hellgold und 4 Bronze, weil sein Balken schwarz ist) |
| `graphics/bag/swsh/*.png` (Sprites) | Index 8, das rechte Ende des Balkens unter dem gewählten Item, wird Gold |
| `graphics/party_menu/swsh/tiles.png` | Rote und lila Hälfte werden Marineblau und Schieferblau, die Pokéball-Linien Gold. Zeilen 1–6 sind die Zustände der Team-Plätze (Index 1 Fläche, 3 Schrift, 2 Schatten). Der Platz unter dem Cursor ist golden mit marineblauer Schrift |
| `graphics/pokedex/bg_*.pal`, `search_results_bg.pal` | Alter Pokédex: weiße, graue und gelbe Flächen und grüne Streifen werden Marineblau, Konturen und Titel Gold |
| `graphics/pokedex/hgss/palette_default.pal`, `palette_national.pal`, `palette_search_results.pal` | HGSS-Pokédex: Zeile 0 ist der Rahmen (1 Fläche, 4 Gitter und Beschriftung, 6 Buchstaben auf den Balken, 7–9 Balken und Kanten, 15 Schrift `TEXT_DYNAMIC_COLOR_6` und Konturen in Gold) |
| `PrintMonInfo` in `src/pokedex_plus_hgss.c` | Der Pokédex-Eintrag nimmt mit `GetFontIdToFit` die schmalere Schrift, wenn er sonst über den Rahmen ragt |

| `graphics/battle_interface/text.pal` (Index 8–10), `B_WIN_YESNO` in `src/battle_message.c` | Ja/Nein im Kampf: Fläche Marineblau, Schrift Gold, Schatten Bronze. Vorher war die Fläche weiß und die Cursor-Spalte im Rahmen marineblau |
| `message_box.png`, `name_box.png` (Index 4–9, 14, 15) | Rot, Grün und Blau sind aufgehellt, damit farbiger Text auf Marineblau lesbar bleibt (z. B. die Stimmfarben der NPCs in FireRed/LeafGreen). 14/15 sind Hellgold mit Bronze-Schatten |
| `sTrainerCardTextColors`, `sTrainerCardStatColors` in `src/trainer_card.c` | Trainerkarte: Die Karte bleibt platinfarben, die Schrift ist dunkle Bronze (Index 15 der Dialogbox-Palette) mit Goldschatten. Werte auf der Rückseite sind Bronze statt Rot |
| `graphics/shop/menu.png` | Laden: Itemliste mit marineblauen Streifen und goldenem Rand statt Pfirsich und Grün; Beschreibungs- und Item-Box marineblau statt weiß |
| `ShowSaveInfoWindow` in `src/start_menu.c` | Speichermenü: Ort und Werte in Hellgold (Index 14) statt Grün bzw. Blau/Rot je nach Geschlecht |

Text mit `TEXT_COLOR_WHITE` auf Palette 15 ist jetzt marineblau, weil Index 1 die Boxfläche ist.
`palette_search_menu.pal` (Suchmaske) und die `_dark`-Paletten sind unverändert.

## Erweiterter Pokédex

In `include/config/pokedex_plus_hgss.h` ist `POKEDEX_PLUS_HGSS` auf `TRUE` gesetzt.
Der Pokédex im HGSS-Stil zeigt Werte, Entwicklungen, Formen und Attacken.
Alle Generationen 1–9 sind eingeschaltet, der National-Dex reicht bis Nr. 1025.
`NewGameInitData` in `src/new_game.c` ruft `EnableNationalPokedex()` auf, damit ist der National-Dex ab Spielbeginn aktiv.
Den Pokédex selbst bekommt man weiterhin von Birch bzw. Eich, danach zeigt er sofort alle 1025 Pokémon.
Das spätere Upgrade durch Birch bzw. Eich läuft trotzdem ab, ändert aber nichts mehr.

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
