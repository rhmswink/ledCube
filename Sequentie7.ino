int P1 = 0;
int P2 = 0;
int keuze;

int plek0[3] = {1, 5, 4};
int plek1[5] = {0, 4, 5, 6, 2};
int plek2[5] = {1, 5, 6, 7, 3};
int plek3[3] = {2, 6, 7};
int plek4[5] = {0, 1, 5, 9, 8};
int plek5[8] = {0, 1, 2, 6, 10, 9, 8, 4};
int plek6[8] = {5, 1, 2, 3, 7, 11, 10, 9};
int plek7[5] = {3, 2, 6, 10, 11};
int plek8[5] = {4, 5, 9, 13, 12};
int plek9[8] = {8, 4, 5, 6, 10, 14, 13, 12};
int plek10[8] = {9, 5, 6, 7, 11, 15, 14, 13};
int plek11[5] = {7, 6, 10, 14, 15};
int plek12[3] = {8, 9, 13};
int plek13[5] = {12, 8, 9, 10, 14};
int plek14[5] = {13, 9, 10, 11, 15};
int plek15[3] = {11, 10, 14};

int laag1[2] = {0, 2};
int laag2[2] = {1, 3};

void sequentie7(int lengte, int rotatie) { //dit patroon werkt door pure magie
  clearPatroon();
  patroon2D[P2][P1] = 1;
  stuurLedsAan2(patroon2D, lengte);
  for (r = 0; r < rotatie; r++) {
    patroon2D[P2][P1] = 0; //maakt de oude positie laag
    keuze = random(0, 2);  //hier kiest hij of de led omhoog/omlaag (0) moet gaan of links/rechts/schuin (1)
    if (keuze) {
      switch (P1) {
        case 0:
          P1 = plek0[random(0, 3)];
          break;
        case 1:
          P1 = plek1[random(0, 5)];
          break;
        case 2:
          P1 = plek2[random(0, 5)];
          break;
        case 3:
          P1 = plek3[random(0, 3)];
          break;
        case 4:
          P1 = plek4[random(0, 5)];
          break;
        case 5:
          P1 = plek5[random(0, 8)];
          break;
        case 6:
          P1 = plek6[random(0, 8)];
          break;
        case 7:
          P1 = plek7[random(0, 5)];
          break;
        case 8:
          P1 = plek8[random(0, 5)];
          break;
        case 9:
          P1 = plek9[random(0, 8)];
          break;
        case 10:
          P1 = plek10[random(0, 8)];
          break;
        case 11:
          P1 = plek11[random(0, 5)];
          break;
        case 12:
          P1 = plek12[random(0, 3)];
          break;
        case 13:
          P1 = plek13[random(0, 5)];
          break;
        case 14:
          P1 = plek14[random(0, 5)];
          break;
        case 15:
          P1 = plek15[random(0, 3)];
          break;
      }
    }
    else {
      switch (P2) {
        case 0:
          P2 = 1;
          break;
        case 1:
          P2 = laag1[random(0, 2)];
          break;
        case 2:
          P2 = laag2[random(0, 2)];
          break;
        case 3:
          P2 = 2;
          break;
      }
    }
    patroon2D[P2][P1] = 1;  //maakt de nieuwe positie hoog
    stuurLedsAan2(patroon2D, lengte);
  }
}
