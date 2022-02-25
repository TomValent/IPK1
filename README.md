# IPK Projekt 1
Projekt bol zameraný na vývoj jednoduchej TCP siete pomocou 
socketov a protokolu HTTP. Pre implemetáciu som si zvolil  jazyk C.

## Prerekvizity
Program je odporúčané spúšťať na *Linuxe Ubuntu 20.04*, na 
ktorom bol aj vyvíjaný.

* GCC - preklad zdrojového kódu, ak nie je
* Linux terminál - preloženie, spustenie alebo pripojenie 
    sa na server
* Webový prehliadač - umožnuje sa pripojiť aj takto


## Spustenie a používanie
Priložený Makefile daný zdrojový kód preloží v príkazovom riadku
príkazom:
````
make
````
v danom adresári. Následne treba server spustiť príkazom:
```
./hinfosvc port
```

kde *port* je číslo portu na ktorom bude server bežať.
Teraz keď je server spustený a klient sa môže naň pripojiť
pomocou webového prehliadača:
```
http://loacalhost:port
```
alebo z príkazového riadka:
```
curl http://loacalhost:port
wget http://loacalhost:port
```

Server má ďalej 3 ďalšie funkcie. Ak spustíme server rovnakou
adresou a pridáme */cpu-name* server vypíše informácie o CPU,
ak ho spustíme s */hostname* server vypíše doménové meno a
ak ho spustíme s */load* server vypočíťa a vypíše aktuálnu
záťaž procesoru.

### Ostatné
Makefile okrem prekladania obsahuje funkcie na zmazanie
zbytočných súborov po ukončení práce so serverom príkazom ***make
clean*** v terminále a zipovanie zdrojových súborov pomocou
***make zip***.

### Zdroje
[Zdroj 1](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa) <br/>
[Zdroj 2](https://www.binarytides.com/socket-programming-c-linux-tutorial/) <br/>
[Zdroj 3](https://www.youtube.com/watch?v=LtXEMwSG5-8&t=1079s) <br/>

Autor: Tomas Valent (xvalen27)