Norbert Matuška
WinoVote

-   application of three design patterns (except Singleton) (3/3) [ yes ]
- v celom projekte udržujem MVC pattern
- implementovaný observer na sledovanie aktuálne prihláseného usera (triedy UserSession a UserSessionNotifier)
- Singleton (Database, UserSession)
- Facade pattern - VotingController zjednodušuje interakciu medzi VotingSystem a UI v DashboardView
- Dependency Injection - Tým, že konštruktor vo VotingController dostáva dashboardview, mohlo by to byť považované za dependency injection
- Strategy pattern? - IFrame špecifikuje metódy ale nediktuje ich implementáciu.


Polymorfizmus a dedenie obsahujú triedy User a PremiumUser, Agregácia je napríklad v triede LoginView/DashboardView

-   handling exceptional states using own exceptions [ yes ]
-   graphical user interface separated from logic [ yes ]
-   explicit use of multithreading [ no ]
-   use of generics in own classes [ yes ]
-   explicit use of RTTI [ yes ]
-   nested classes and interfaces [ no ]
-   lambda expressions or method references [ yes ]
-   default method implementation in interfaces [ yes ]
-   aspect-oriented programming (AspectJ) [ no ]
-   serialization [ no ]

Projekt bol implementovaný v intellij ale exportol som to do eclipse takže by to malo byť spustitelné aj tam.
LoginView je akoby main takže spúšťať cez to.

Zoznam najhlavnejších commitov:

1. "added basic login window" 39fcb9bf6d7ef9bc490ca36c0fc4762aa14c3387
	Tu som začal robiť na projekte, pridal som v prvom rade login okno, kde sa dalo písať meno a heslo

2. "basic register and login logic" 6b30eea42dc7a97b3c9b2c2a61d1eb6f198e1065
	Následne som pridal aj funkcionalitu overenia prihlásenia, zapisovanie zaregistrovaných použivateľov do CSV a otvorenie 	DashoardView

3. "added various logic for voting system" f9a03894c033a843abae991f0d56495218c0b15c
	Toto bol asi celý deň roboty, kde som pridal niekoľko modelov, utilitiek, nový controller a prerobil veci v oboch views a taktiež 	som aj začal skúšať spojazdniť Observer

4. "added functioning observer" d4bb32f3539898f5a62f2427a06b09b8317eb40d
	podarilo sa mi spojazdniť observer

5. "fixed wine names not being displayed correctly" 386834192d413057714d2c91c8c8c734a70a8ade
	Mal som problém so zobrazovaním vín v DashboardView kedy sa mi zobrazovalo len nejaké ID inštancie objektu a nie názov vína a tu 	sa mi to podarilo opraviť

6. "added logout, cleaned up some things" bdd59feda2212f9d46876a0a69114db4e593314f
	Pridal som logout button a opravil som niekoľko tried.

7. "added custom exception handling + tweaked some things" a6153e367f16f5e8d0eb01a04dba6a7319793110
	samo o sebe hovorí

8. "added javadoc, design patterns.txt" b6782ebc24a59144759fbef3da8c9a1c9561886a
	pridal som komentáre do javadocu a zapracoval som na viacerých design patterns

9. "added PremiumUser functionality" 0379a525eafd3cb5dc0e551cf2ef40ea4526184a
	Zapracoval som na PremiumUser classe, pridal vlastné methody, polymorfizmus, dedenie a funkcionality, ktoré boli opísané v zámere 	ale neboli doteraz zapracované