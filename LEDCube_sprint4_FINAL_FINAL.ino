int n, m, i, k, p, q, s; //verboden variabelen voor animaties
int a, b, c, d, e, f, r;
int count = 12;
int patroon2D[4][16];

//dit zijn de rijen en kolommen zoals de shift registers aan de ledcube zijn aangesloten
int k1[4] = {3, 2, 1, 0};         //     K1  K2  K3  K4
int k2[4] = {7, 6, 5, 4};         // R1| 3   7   11  15
int k3[4] = {11, 10, 9, 8};       // R2| 2   6   10  14
int k4[4] = {12, 13, 14, 15};     // R3| 1   5   9   13
int r1[4] = {15, 11, 7, 3};       // R4| 0   4   8   12
int r2[4] = {2, 6, 10, 14};       //
int r3[4] = {1, 5, 9, 13};        //    /__/  /__/ <-Shift Registers
int r4[4] = {0, 4, 8, 12};
int ring[12] = {0, 4, 8, 12, 13, 14, 15, 11, 7, 3, 2, 1}; //alle array plekken van de buitenste ring
int binnenRing[4] = {6, 10, 5, 9}; //alle array plekken van de binnenste ring
int hoek[4] = {0, 12, 3, 15}; //alle array plekken van de 4 hoeken

//dit zijn de dimensies van de array
#define D1 4
#define D2 16

//Dit zijn alle pinnen die een naam hebben gekregen
#define DATA_INPUT 3
#define SHIFT_CLK 6
#define STORAGE_CLK 5
#define OE 4
#define MOSFET1 15 //A1
#define MOSFET2 16 //A2
#define MOSFET3 17 //A3
#define MOSFET4 18 //A4

//~~Hieronder staat alles basiscode om de shift registers goed aan te sturen~~//

void shiftRegister(int *rij) {  //deze functie bestuurd beide shiftregisters
  for (n = 0; n < 16; n++) { //for loop die 16 waardes een voor een naar binnen stuurt
    digitalWrite(DATA_INPUT, rij[n]); //stuurt een 1 of 0 naar binnen
    digitalWrite(SHIFT_CLK, HIGH); //flank van de clock zet de waarde van de array in de shift register
    digitalWrite(SHIFT_CLK, LOW);
  }
  digitalWrite(STORAGE_CLK, HIGH); //flank van de clock zet de byte in de storage
  digitalWrite(STORAGE_CLK, LOW);
}

void knipperLeds(int state) { //aan deze functie geef je de laag mee die je aan wil hebben. Deze functie laat de leds met een frequentie van ~120Hz knipperen
  digitalWrite(state, HIGH); //output ENABLED
  delay(2);
  digitalWrite(state, LOW); //output DISABLED
}

int * convertArray(int rij[][D2], int laag) { //op de 1e plek word de 2D array meegegeven en op de 2e plek de laag die omgezet moet worden.
  static int patroon[16];                     //deze functie zet een 2D array om in een normale array en returned hem
  for (s = 0; s < D2; s++) {
    patroon[s] = rij[laag][s];
  }
  return patroon;
}

void stuurLedsAan(int *arrayCube, int lengte, bool type) { //Op de 1e plek geef je de array mee, op de 2e plek hoelang de huidige status moet blijven en op de 3e plek of het een 1D of 2D array is.
  for (k = 0; k < lengte; k++) {
    shiftRegister(arrayCube); //op de 1e plek word de array meegegeven, op de 2e plek welke laag en op de 3e plek of de array 1D of 2D is
    knipperLeds(MOSFET1);
    shiftRegister(arrayCube);
    knipperLeds(MOSFET2);
    shiftRegister(arrayCube);
    knipperLeds(MOSFET3);
    shiftRegister(arrayCube);
    knipperLeds(MOSFET4);
  }
}

void stuurLedsAan2(int rij[][D2], int lengte) { //deze functie word aangeroepen indien een 2D array word gebruikt
  for (k = 0; k < lengte; k++) {
    shiftRegister(convertArray(rij, 0)); //de return waarde van convertArray(), wat een 1D array is, word meegegeven aan shiftRegister()
    knipperLeds(MOSFET1);
    shiftRegister(convertArray(rij, 1));
    knipperLeds(MOSFET2);
    shiftRegister(convertArray(rij, 2));
    knipperLeds(MOSFET3);
    shiftRegister(convertArray(rij, 3));
    knipperLeds(MOSFET4);
  }
}

void clearPatroon() { //deze functie zet alle plekken van het 2D patroon op 0;
  for (q = 0; q < 4; q++) {
    for (s = 0; s < 16; s++) {
      patroon2D[q][s] = 0;
    }
  }
}

//~~hieronder staat alle code voor de patronen die naar de shiftregisters gestuurd moeten worden~~//

void helpSequentie1(int *patroon, int *rij, int *rij2, int lengte) { //op de 1e plek komt de array te staan, op de 2e plek de kolom/rij die uit moet, op de 3e plek de kolom/rij die aan moet, op de 4e plek de lengte
  for (b = 0; b < 3; b++) {
    patroon[rij[b]] = 0;
    patroon[rij2[b + 1]] = 1;
    stuurLedsAan(patroon, lengte, 0);
  }
}

void sequentie1(int lengte, int rotatie) { //deze sequentie laat een muur rond de kubus gaan
  int patroon[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (r = 0; r < rotatie; r++) { //hoevaak dit patroon uitgevoerd moet worden
    if (r == 0) {
      for (a = 0; a < 4; a++) { //als dit de 1e loop is word 1 zijde aan gezet
        patroon[k1[a]] = 1;
      }
      stuurLedsAan(patroon, 5, 0);
    }
    helpSequentie1(patroon, k1, r4, lengte);
    helpSequentie1(patroon, r4, k4, lengte);
    helpSequentie1(patroon, k4, r1, lengte);
    helpSequentie1(patroon, r1, k1, lengte);
  }
}

void helpSequentie2en3(int *patroon, int *rij, int *rij2, int lengte) { //op de 1e plek stuur je de array mee, op de 2e plek de kolom/rij die uit moet, op de 3e plek de kolom/rij die aan moet, op de 4e plek de lengte
  for (a = 0; a < 4; a++) {
    patroon[rij[a]] = 0;
    patroon[rij2[a]] = 1;
  }
  stuurLedsAan(patroon, lengte, 0);
}

void sequentie2(int lengte, int rotatie) { //deze sequentie laat een muur van voor naar achteren door de kubus heen gaan
  int patroon[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (r = 0; r < rotatie; r++) {
    helpSequentie2en3(patroon, k1, k2, lengte);
    helpSequentie2en3(patroon, k2, k3, lengte);
    helpSequentie2en3(patroon, k3, k4, lengte);
    helpSequentie2en3(patroon, k4, k3, lengte);
    helpSequentie2en3(patroon, k3, k2, lengte);
    helpSequentie2en3(patroon, k2, k1, lengte);
  }
}

void sequentie3(int lengte, int rotatie) { //deze sequentie laat een muur van links naar rechts door de kubus heen gaan
  int patroon[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (r = 0; r < rotatie; r++) {
    if (r == 0) {
      helpSequentie2en3(patroon, r4, r1, lengte);
    }
    helpSequentie2en3(patroon, r1, r2, lengte);
    helpSequentie2en3(patroon, r2, r3, lengte);
    helpSequentie2en3(patroon, r3, r4, lengte);
    helpSequentie2en3(patroon, r4, r3, lengte);
    helpSequentie2en3(patroon, r3, r2, lengte);
    helpSequentie2en3(patroon, r2, r1, lengte);
  }
}

void helpSequentie4(int rij[D1][D2], int hoog, int laag, int lengte) { //op de 1e plek word de 2D array meegegeven, op de 2e plek welke laag hoog moet, op de 3e plek welke laag, laag moet, op de 4e plek de lengte
  for (a = 0; a < 16; a++) {
    rij[laag][a] = 0;
    rij[hoog][a] = 1;
  }
  stuurLedsAan2(rij, lengte);
}

void sequentie4(int lengte, int rotatie) { //deze sequentie laat een laag omlaag en omhoog zakken
  clearPatroon();
  for (r = 0; r < rotatie; r++) {
    if (r == 0) {
      helpSequentie4(patroon2D, 0, 1, lengte);
    }
    helpSequentie4(patroon2D, 1, 0, lengte);
    helpSequentie4(patroon2D, 2, 1, lengte);
    helpSequentie4(patroon2D, 3, 2, lengte);
    helpSequentie4(patroon2D, 2, 3, lengte);
    helpSequentie4(patroon2D, 1, 2, lengte);
    helpSequentie4(patroon2D, 0, 1, lengte);
  }
}

void sequentie5(int lengte, int rotatie) { //dit is de regen animatie
  clearPatroon();
  for (r = 0; r < rotatie; r++) {
    for (c = 0; c < 4; c++) {
      for (b = 0; b < 16; b++) {
        patroon2D[3][b] = patroon2D[2][b];
        patroon2D[2][b] = patroon2D[1][b];
        patroon2D[1][b] = patroon2D[0][b];
        if (r != rotatie - 1) {
          patroon2D[0][b] = random(0, 2); //de bovenste laag word random met een 0 of een 1 gevuld
        }
        else {
          patroon2D[0][b] = 0;
        }
      }
      stuurLedsAan2(patroon2D, lengte);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(DATA_INPUT, OUTPUT); //serial data input
  pinMode(SHIFT_CLK, OUTPUT); //shift register clock
  pinMode(STORAGE_CLK, OUTPUT); //storage register clock
  pinMode(OE, OUTPUT); //output enable (LOW ACTIVE)
  pinMode(MOSFET1, OUTPUT); //MOSFET laag 1
  pinMode(MOSFET2, OUTPUT); //MOSFET laag 2
  pinMode(MOSFET3, OUTPUT); //MOSFET laag 3
  pinMode(MOSFET4, OUTPUT); //MOSFET laag 4
}

void loop() {
  // put your main code here, to run repeatedly:
  randomSeed(analogRead(A5)); //zorgt ervoor dat de random() functie random is

  //op de 1e plek voer je de tijd in dat een waarde in de shift register moet staan (8ms * getal dat je invoert). de 2e plek geeft aan hoeveel loops hij moet maken
  sequentie1(15, 2);
  sequentie2(20, 2);
  sequentie3(20, 2);
  sequentie4(20, 2);
  sequentie7(500, 20);
  sequentie5(20, 6);
  sequentie6(9, 1 );


}
