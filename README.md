# MSW_Undefined
## Alap RPG játék
## A Program működése
A program CLI-ből indítható, 1 darab fájlt vár bemenetként. A fájlban egy hero és egy monsters kulccsal lehet megadni az 1 darab hőst és az 1 vagy több monstert.
### Pl:
```
{
    "hero" : "Dark_Wanderer.json",
    "monsters" : " Fallen.json  Fallen.json  Zombie.json  Fallen.json  Fallen.json  Zombie.json  Fallen.json  Blood_Raven.json "
}
```
Ezek a fájlok ugyanilyen felépítésű json fileok
### Pl. 
```
{
    "name" : "Prince Aidan of Khanduras",
    "base_health_points" : 30,
    "base_damage" : 3,
    "base_attack_cooldown" : 1.1,
    "experience_per_level" : 20,
    "health_point_bonus_per_level" : 5,
    "damage_bonus_per_level" : 1,
    "cooldown_multiplier_per_level": 0.9
}

```

A program a következő kulccsokat fogadja el:
*name*, *health_points , *damage, *attack cooldown, experience_per_level, health_point_bonus_per_level,
damage_bonus_per_level, cooldown_multiplier_per_level, lore, additional_info, race
## Indítás:

```./a.out scenario1.json ```

Ezek után a program lejátsza a karakterek közötti csatát, ahol minden karakter a hp-jából az ellenfél dmg-jének megfelelő sebzést szenved el, ha a cooldown lejárt, ameddig az egyik meg nem hal. Emellett a Hero rendelkezik levelup képességgel is.
