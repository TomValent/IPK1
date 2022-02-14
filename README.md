<h1>IPK Projekt 1</h1>
<p>Projekt bol zameraný na vývoj jednoduchej TCP siete pomocou 
socketov a protokolu HTTP. Pre implemetáciu som si zvolil  jazyk C.
</p>

<h2>Prerekvizity</h2>
<p>Program je odporúčané spúšťať na <i>Linuxe Ubuntu 20.04</i>, na 
ktorom bol aj vyvíjaný.</p>
<ol>
    <li>GCC - preklad zdrojového kódu, ak nie je</li>
    <li>Linux terminál - preloženie, spustenie alebo pripojenie 
        sa na server</li>
    <li>Webový prehliadač - umožnuje sa pripojiť aj takto</li>
</ol>

<h2>Spustenie a používanie</h2>
<p>Priložený Makefile daný zdrojový kód preloží v príkazovom riadku
príkazom:<br><br>
<b>make</b><br><br>
v danom adresári. Následne treba server spustiť príkazom:<br><br>
<b>./hinfosvc port</b><br><br>
kde <i>port</i> je číslo portu na ktorom bude server bežať.
Teraz keď je server spustený a klient sa môže naň pripojiť
pomocou webového prehliadača:<br><br>
<b>http://loacalhost:port</b><br><br>
alebo z príkazového riadka:<br><br>
<b>curl http://loacalhost:port</b><br>
<b>wget http://loacalhost:port</b><br><br>
</p>
<p>Server má ďalej 3 ďalšie funkcie. Ak spustíme server rovnakou
adresou a pridáme <i>/cpu-name</i> server vypíše informácie o CPU,
ak ho spustíme s <i>hostname</i> server vypíše doménové meno a
ak ho spustíme s <i>/load</i> server vypočíťa a vypíše aktuálnu
záťaž procesoru.</p>

<h3>Ostatné</h3>
<p>Makefile okrem prekladania obsahuje funkcie na zmazanie
zbytočných súborov po ukončení práce so serverom príkazom <i>make
clean</i> v terminále a zipovanie zdrojových súborov pomocou
<i>make zip</i>.</p>