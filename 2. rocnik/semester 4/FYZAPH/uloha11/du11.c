#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#define NGul 4
#define NDim 2

//const int NGul = 5;  // Takto to nejde, lebo pouzivame staticku alokaciu
//const int NDim = 2;  // a globalne deklarovane a alokovane polia.
// Elegantnou alternativou by bola dynamicka alokacia.


//-----------------------------------------------------------------------------------------
// rand() je funkcia zo stdlib. Vracia celociselne hodnoty z mnoziny {0, 1, ..., RAND_MAX}.
// NAHODNE bude realne z intervalu <-1, 1>.
// Existuju aj kvalitnejsie generatory nahodnych cisiel.
// Tento funguje slabo a mame problem pre NGul > 5 najst pre ne umiestnenia.
//-----------------------------------------------------------------------------------------
#define NAHODNE  (-1.0 + 2*(double)rand()/RAND_MAX)

double Lstol[1+NDim];
double posunDalej, ZorUhY;  // pre kozmicky biliard
double sur[1+NGul][1+NDim];
double vel[1+NGul][1+NDim];

//const double polomer = 0.03075; // naozajstny polomer kazdej z gul
//const double extrad = 0.032;    // Pomocna hodnota (extended radius) o kusok vacsia nez polomer,
// aby sme pomocou nej zabezpecili dostatocne odstupy na zaciatku.

const double polomer = 0.10;  // Pripadne skusme vacsie plomery gul nez sa naozaj pouzivaju,
const double extrad = 0.11;   // lebo to moze pomoct pri odladovani programu.

// Prilis kratsi casovy krok ako 25 ms asi nie, lebo nebude stihat hardver.
// Ale zasa pri 25 to seka ...
const int icaskrok = 15;  // v milisekundach
const double dt = 0.015;  // aj toto je v ms
double Lvacsie;  // pomocna dlzkova skala pre grafiku


void chyba(const int ig, const int ic, const double vel, const double CasZrMozno)
{
    fprintf(stderr, " dalsia_zrazka()/chyba():\n");
    fprintf(stderr, " Zaporny cas do dalsej zrazky so stenou pre ig = %d ic = %d  VelNow = %1.16le :\n", ig, ic, vel);
    fprintf(stderr, " CasZrMozno = %1.16le . Koncim.\n", CasZrMozno);
    exit(3);
}


//==========================================================================================
// Funkcia  dalsia_zrazka()  vypocita a vrati cas najskorsej zrazky od momentalneho okamihu.
// Okrem toho vypocita a do premennych  OdrGula, OdrCart  zapise informaciu,
// ktora gula narazila a ktorej kartezianskej suradnice sa to tyka.
// PosNow  =  Positions Now   (t. j. polohy stredov gul v momentalnom okamihu)
// VelNow  =  Velicities Now  (t. j. rychlosti gul  momentalnom okamihu)
//==========================================================================================

double dalsia_zrazka(const double PosNow[1+NGul][1+NDim], const double VelNow[1+NGul][1+NDim],
                     int *OdrGula, int *OdrCart, int *igzr, int *jgzr)
{
    const double NepatrneKladneCislo = 1.0e20*DBL_MIN;
    double CasMin = DBL_MAX;
    //===========================================================
    // Vyhladaj najblizsiu zrazku so stenou, ktora mozno nastane.
    //===========================================================
    *OdrGula = 0;
    *OdrCart = -1;
    for (int ig = 1; ig <= NGul; ig++) for (int ic = 1; ic <= NDim; ic++) {
        double CasZrMozno;
        if      (VelNow[ig][ic] < 0.0) {
            //------------------------------------
            // vypocet pre pohyb dolava alebo dole
            //------------------------------------
            CasZrMozno = ( PosNow[ig][ic] - (-0.5*Lstol[ic]+polomer) ) / (-VelNow[ig][ic]);
            //------------------------------------------------------------------------------------------------
            // osetrenie numericky tazkych pripadov:
            // Velmi zaporne casove intervaly su zasadnou chybou.
            // Nepatrne zaporne CasZrMozno moze niekedy vzniknut z numerickych dovodov, nie ako zasadna chyba.
            // Preklop znamienko pre pripad nepatrnej zapornej hodnoty, inak program zhavaruje.
            //------------------------------------------------------------------------------------------------
            if      (CasZrMozno < -NepatrneKladneCislo) chyba(ig, ic, VelNow[ig][ic], CasZrMozno);
            else if (CasZrMozno < 0.0)                  CasZrMozno *= -1.0;
            //----------------------------------------------------------------------
            // Ak vypocitany casovy interval je kratsi nez zatial najkratsi najdeny,
            // zapamataj si ho, a aj prislusne ig, ic.
            //----------------------------------------------------------------------
            if (CasZrMozno < CasMin) {
                CasMin = CasZrMozno;
                *OdrGula = ig;
                *OdrCart = ic;
            }
        }
        else if (VelNow[ig][ic] >  0.0) {
            //-------------------------------------
            // vypocet pre pohyb doprava alebo hore
            //-------------------------------------
            CasZrMozno = ( PosNow[ig][ic] + (-0.5*Lstol[ic]+polomer) ) / -(VelNow[ig][ic]);
            
            if      (CasZrMozno < -NepatrneKladneCislo) chyba(ig, ic, VelNow[ig][ic], CasZrMozno);
            else if (CasZrMozno < 0.0)                  CasZrMozno *= -1.0;
            
            if (CasZrMozno < CasMin) {
                CasMin = CasZrMozno;
                *OdrGula = ig;
                *OdrCart = ic;
            }
        }
    }
    //====================================================================================
    // Analyzuj moznost vzajomnej zrazky gul.
    // Symbol  bij  je zovseobecnenenie oznacenia  b12  z teorie.
    // rijsq = |rj - ri|^2  je stvorec (square) vzdialenosti stredov gul  ig, jg.
    // Je to zovseobecnenie r12^2 z teorie.
    // vijsq = |vj - vi|^2
    // Hodnoty bij, rijsq, vijsq  sa pocitaju ako skalarne suciny.
    // Mohli by sme teda na ich vypocty pouzit funkciu  skalsuc()  z biliard.c,
    // ale museli by sme alokovat polia pre sucinitele.
    // Povedzme ze sa nam to neoplati alebo nechce, tak sa tu zaobideme aj bez  skalsuc().
    //====================================================================================
    *igzr = 0;
    *jgzr = 0;
    for (int ig = 2; ig <= NGul; ig++) for (int jg = 1; jg < ig; jg++) {
        // Testuj ci sa gule  ig, jg  s momentalnymi smermi a rychlostami vobec zrazia.
        double bij = 0.0;
        for (int ic = 1; ic <= NDim; ic++) bij += (PosNow[jg][ic]-PosNow[ig][ic])*(VelNow[jg][ic]-VelNow[ig][ic]);
        double rijsq = 0.0;
        for (int ic = 1; ic <= NDim; ic++) rijsq += ((PosNow[jg][ic] - PosNow[ig][ic]) * (PosNow[jg][ic] - PosNow[ig][ic]));
        double vijsq = 0.0;
        for (int ic = 1; ic <= NDim; ic++) vijsq += ((VelNow[jg][ic] - VelNow[ig][ic]) * (VelNow[jg][ic] - VelNow[ig][ic]));
        if (bij < 0.0  &&  bij*bij - vijsq*(rijsq-4*polomer*polomer) > 0.0) {
            // Zrazia sa, pocitaj za aku dobu.
            double tij = (-bij - sqrt(pow(bij, 2) - (vijsq*(rijsq - (4 * pow(polomer, 2)))))) / vijsq;
            if (tij >= 0.0 && tij < CasMin) {
                CasMin = tij;
                *igzr = ig;
                *jgzr = jg;
                *OdrCart = 0;  // To znamena, ze ide o zrazku typu gula-gula.
            }
        }
    }
    return CasMin;
}


double skalsuc(const double vec1[1+NDim], const double vec2[1+NDim])
{
    double suma = 0.0;
    for (int cart = 1; cart <= NDim; cart++) suma += vec1[cart]*vec2[cart];
    return suma;
}

void aktualizuj(const int iusek)
{
    extern double dalsia_zrazka(const double PosNow[1+NGul][1+NDim], const double VelNow[1+NGul][1+NDim],
                                int *OdrGula, int *OdrCart, int *igzr, int *jgzr);
    
    static int OdrGula, OdrCart, igzr, jgzr, PUsekov;  // Trieda static, aby boli hodnoty zapamatane aj medzi jednotlivymi
    static double dtloc;          // volaniami funkcie aktualizuj. Inak by sme museli tieto parametre deklarovat globalne.
    const double MaleKladneCislo = 100*DBL_EPSILON;
    
    if (iusek == 1) {
        double CasZr = dalsia_zrazka(sur, vel, &OdrGula, &OdrCart, &igzr, &jgzr);
        PUsekov = 1 + (int)(CasZr/dt);
        dtloc = CasZr/PUsekov;  // icaskrok zatial neriesme; vznikne len nebadatelna odchylka
    }
    for (int ig = 1; ig <= NGul; ig++) for (int ic = 1; ic <= NDim; ic++) sur[ig][ic] += vel[ig][ic]*dtloc;
    glutPostRedisplay();
    if (iusek == PUsekov) {
        //-----------------------------------------------------------------------------------------------------
        // Prave sme dosli po okamih nejakej zrazky v sustave.
        // Preto upravime rychlosti gul (alebo gule), ktorych sa to tyka,
        // a zresetujeme pocitanie casovych usekov medzi po sebe nasledujucimi zrazkami.
        // Teda nastavime posledny parameter v glutTimerFunc na 1.
        //-----------------------------------------------------------------------------------------------------
        if (OdrCart > 0) { // zrazka jednej gule so stenou
            vel[OdrGula][OdrCart] *= -1;
            glutTimerFunc(icaskrok, aktualizuj, 1);  // reset hodnoty iusek
        }
        else if (OdrCart == 0) { // zrazka dvoch gul navzajom; ich indexy su igzr, jgzr  (i-ta, j-ta)
            double uij[1+NDim], vij[1+NDim], dvi[1+NDim];
            for (int ic = 1; ic <= NDim; ic++) uij[ic] = sur[jgzr][ic]-sur[igzr][ic];  // Toto je zatial len vektor rij.
            double rijsq = skalsuc(uij, uij);  // Toto je naozaj  rij^2  a ma to byt rovne (2*polomer)^2.
            if (fabs(rijsq-4*polomer*polomer) > MaleKladneCislo) {
                fprintf(stdout, " aktualizuj(): CHYBA: |rijsq-4*polomer*polomer| = %1.14le  je prilis velka odchylka.\n",
                        fabs(rijsq-4*polomer*polomer));
            }
            
            for (int ic = 1; ic <= NDim; ic++) uij[ic] /= (2*polomer);  // Uz je to teraz naozaj jednotkovy vektor.
            for (int ic = 1; ic <= NDim; ic++) vij[ic] = (vel[jgzr][ic] - vel[igzr][ic]); // (rozdiel rychlosti j-tej a i-tej gule, kart. zlozka ic)
            
            for (int ic = 1; ic <= NDim; ic++) dvi[ic] = uij[ic]*skalsuc(uij, vij);  // zmena rychlosti i-tej gule pri zrazke
            for (int ic = 1; ic <= NDim; ic++) vel[igzr][ic] += dvi[ic];
            for (int ic = 1; ic <= NDim; ic++) vel[jgzr][ic] -= dvi[ic];
            glutTimerFunc(icaskrok, aktualizuj, 1);  // reset hodnoty iusek
        }
        else {
            fprintf(stderr, " aktualizuj(): Chyba: Zrazka nebola spravne urcena. Koncim.\n\n");
            exit(9);
        }
    }
    else glutTimerFunc(icaskrok, aktualizuj, iusek+1);
}

void obsluhaResize(int sirka, int vyska)
{
    glViewport(0, 0, sirka, vyska);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (sirka == 0) sirka++;
    if (vyska == 0) vyska++;
    const double    pomstr = ((double)vyska)/sirka;
    if (NDim <= 2) {
        //const double invpomstr = ((double)sirka)/vyska;
        gluOrtho2D(-0.6*Lvacsie, 0.6*Lvacsie , -0.6*Lvacsie*pomstr, 0.6*Lvacsie*pomstr);
        //---------------------------------------------------------------------------------------
        // pouzit (zakomentovane), ak chceme, aby sa 2D scena vzdy spravne zmestila na obrazovku.
        //---------------------------------------------------------------------------------------
        /*
         const double    pomstr = ((double)vyska)/sirka;
         const double invpomstr = ((double)sirka)/vyska;
         if (sirka >= vyska)
         gluOrtho2D(-0.5*Lvacsie*invpomstr, 0.5*Lvacsie*invpomstr , -0.5*Lvacsie, 0.5*Lvacsie);
         else
         gluOrtho2D(-0.5*Lvacsie, 0.5*Lvacsie , -0.5*Lvacsie*pomstr, 0.5*Lvacsie*pomstr);
         */
    }
    else {
        const double invpomstr = ((double)sirka)/vyska;
        const double dnear = 0.0*Lstol[3];  // Toto su len dost provizorne nastavenia,
        const double dfar  = 1.0*Lstol[3];  // ale funguje to.
        gluPerspective(ZorUhY, invpomstr, dnear, dfar);
    }
}

void kresliObjekty2D()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //================
    // biliardovy stol
    //================
    glLoadIdentity();
    glColor3f(0.0, 1.0, 0.0);  // zelena farba stola
    glScalef(Lstol[1], Lstol[2], 1.0);
    glRectf(-0.5, -0.5, 0.5, 0.5);
    //====================================================
    // gula (zobrazena ako kruh, vlastne ako mnohouholnik)
    //====================================================
    const int PLucov = 36;
    for (int ig = 1; ig <= NGul; ig++) {
        glColor3f(1-(float)(ig-1)/NGul, 0.0, (float)(ig-1)/NGul);  // farba gule
        glLoadIdentity();
        glTranslatef(sur[ig][1], sur[ig][2], 0.0); // Najprv glTranslatef,
        glScalef(polomer, polomer, 1.0); // potom glScalef.
        glBegin(GL_TRIANGLE_FAN);
        //----------------------------------------------------------------
        // Stred kruhu najprv umiestnime do pociatku suradnicovej sustavy.
        // Nasledne kruh posunieme na fyzikalne spravne miesto
        // (to spravi vyssie uvedena funkcia glTranslatef)
        // a natiahneme na pozadovany polomer (pomocou glScalef).
        //----------------------------------------------------------------
        //TU_NAKRESLITE_KRUH O POLOMERE 1 SO STREDOM V POCIATKU
        GLfloat angle;
        for ( angle = 0.0f; angle <= (2.0f * M_PI); angle += 0.01 ) {
            glVertex2f(sin(angle), cos(angle));
        }
        glEnd();
    }
    glutSwapBuffers();
}

void kresliObjekty3D()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //====================================================
    // gula (zobrazena ako kruh, vlastne ako mnohouholnik)
    // Sem by sa vsak viac hodila naozaj gula, nie kruh.
    //====================================================
    const int PLucov = 36;
    for (int ig = 1; ig <= NGul; ig++) {
        glColor3f(1-(float)(ig-1)/NGul, 0.0, (float)(ig-1)/NGul);  // farba gule
        glLoadIdentity();
        glTranslatef(sur[ig][1], sur[ig][2], sur[ig][3] + posunDalej); // Najprv glTranslatef,
        glScalef(polomer, polomer, 1.0); // potom glScalef.
        glBegin(GL_TRIANGLE_FAN);
        //TU_NAKRESLITE_KRUH O POLOMERE 1 SO STREDOM V POCIATKU
        GLfloat angle;
        for ( angle = 0.0f; angle <= (2.0f * M_PI); angle += 0.01 ) {
            glVertex2f(sin(angle), cos(angle));
        }
        glEnd();
    }
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    if (NDim < 2 || NDim > 3) {   // Dalo by sa dorobit, aby fungovalo aj NDim = 1.
        fprintf(stderr, " CHYBA:  NDim = %d je nespravne alebo nie uplne implementovane.\n\n", NDim);
        exit(1);
    }
    if (extrad <= polomer) {
        fprintf(stderr, " CHYBA:  extrad = %1.10lf  je prilis male. Musi byt aspon %1.10lf. Koncim.\n", extrad, polomer);
        exit(1);
    }
    //====================================================
    // rozmery stola, mozu by aj pre kozmicky biliard v 3D
    //====================================================
    Lstol[1] = 2.84;  // dlzka stola
    Lstol[2] = 1.42;  // sirka stola
    if (NDim == 3) {
        Lstol[3] = 2.00;  // vyska ,stola', pre nas vizualne hlbka
        posunDalej = -1.50;  // Za obrazovkou je z < 0 .
        ZorUhY = 120.0;
    }
    //===============================
    // Zvol zaciatocne suradnice gul.
    //===============================
    {
        const int ig = 1;
        for (int ic = 1; ic <= NDim; ic++) sur[ig][ic] = NAHODNE*(0.5*Lstol[ic]-extrad);
    }
    for (int ig = 2; ig <= NGul; ig++) {
        bool prekryv;
        do {
            //--------------------------------------------------------------------
            // Vygeneruj (mozno len pokusne) suradnice gule s poradovym cislom ig.
            //--------------------------------------------------------------------
            for (int ic = 1; ic <= NDim; ic++) sur[ig][ic] = NAHODNE*(0.5*Lstol[ic]-extrad);
            //----------------------------------------------------
            // Testuj, ci gula ig nie je prilis blizko predoslych.
            //----------------------------------------------------
            prekryv = false;
            for (int jg = 1; jg < ig; jg++) {
                double distsq = 0.0;
                for (int ic = 1; ic <= NDim; ic++) distsq = pow(sur[ig][ic]-sur[jg][ic], 2);
                if (sqrt(distsq) <= 2*extrad) {
                    prekryv = true;
                    //----------------------------------------------------------------------------------------------------
                    // Kedze sme zistili, ze prave umiestnena gula[ig] sa prekryva s niektorou z predoslych (s gulou[jg]),
                    // tak nema zmysel vyhladavat mozne prekryvy s dalsimi.
                    //----------------------------------------------------------------------------------------------------
                    break;
                }
            }
        } while (prekryv);
    }
    //===============================
    // Zvol zaciatocne rychlosti gul.
    //===============================
    //DOPLNTE - napraktickejsie nahodne, aj kladne, aj zaporne, rozumne velke
    for (int i = 0; i < NGul; i++) {
        for (int ic = 1; ic <= NDim; ic++) vel[i][ic] = -(rand() % 3 + 2);
    }
    
    //=======================================================
    // globalne deklarovana pomocna dlzkova skala pre grafiku
    //=======================================================
    Lvacsie = fmax(Lstol[1],Lstol[2]);
    //===========================================
    // Inicializacie pre grafiku a hlavny cyklus.
    //===========================================
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);  // nie je nutne pisat
    glutInitDisplayMode(GLUT_DOUBLE);
    
    glutInitWindowSize(1250, 750);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL: biliard");
    glClearColor(1.0, 1.0, 1.0, 0.3);  // biela farba pozadia
    
    if (NDim <= 2) glutDisplayFunc(kresliObjekty2D);
    else           glutDisplayFunc(kresliObjekty3D);
    glutReshapeFunc(obsluhaResize);
    //---------------------------------------------------------------------
    // Posledny parameter glutTimerFunc() bude oznacovat casovy krok (usek)
    // medzi dvoma po sebe nasledujucimi zrazkami. Zvolme si, nech toto
    // indexovanie casovych usekov zacina od 1. Takze uz tu to treba
    // nastavit na 1. Tato jednotka bude aj siganizovat, ze treba spravit
    // analyzu, kedy v sustave nastane dalsia zrazka.
    //---------------------------------------------------------------------
    glutTimerFunc(icaskrok, aktualizuj, 1);
    
    glutMainLoop();
    
    return 0;
}
