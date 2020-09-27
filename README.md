# MSW_Undefined
## Alap RPG játék
## A Program működése
A program CLI-ből indítható, jelenleg 2 heroval. A 2 hero adatait 2 fileban kell megadni json formátumba, name, hp, dmg sorrendben. Ezután ezeket a fileokat kell beadni argumentumként.
### Pl:
```
{
"name":"Valaki",
"hp":50,
"dmg":30
} 
```
## Indítás:

```./a.out 1.json 2.json ```

Ezek után a program lejátsza a 2 karakter közötti csatát, ahol minden karakter a hp-jából az ellenfél dmg-jének megfelelő sebzést szenved el, ameddig az egyik meg nem hal.
