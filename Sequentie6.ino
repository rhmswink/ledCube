
void sequentie6(int lengte, int rotatie) { //dit is de extra animatie die allemaal super coole shit doet
  clearPatroon();
  for (r = 0; r < rotatie; r++) {
    for (a = 0; a < 12; a++) {
      patroon2D[0][ring[a]] = 1;
      stuurLedsAan2(patroon2D, lengte);
    }
    for (c = 0; c < 3; c++) {
      for (b = 0; b < 12; b++) {
        patroon2D[c][ring[b]] = 0;
        patroon2D[c + 1][ring[b]] = 1;
        stuurLedsAan2(patroon2D, lengte);
      }
    }
    for (d = 3; d > 0; d--) {
      for (e = 0; e < 12; e++) {
        patroon2D[d][ring[e]] = 0;
        patroon2D[d - 1][ring[e]] = 1;
      }
      for (f = 0; f < 4; f++) {
        patroon2D[d][binnenRing[f]] = 1;
        if (d == 1) {
          patroon2D[0][binnenRing[f]] = 1;
        }
      }
      stuurLedsAan2(patroon2D, lengte * 2);
    }
    for (a = 12; a >= 0; a--) {
      patroon2D[0][ring[a]] = 0;
      stuurLedsAan2(patroon2D, lengte);
    }
    for (b = 0; b < 4; b++) {
      for (c = 0; c < 4; c++) {
        patroon2D[b][binnenRing[c]] = 1;
      }
    }
    stuurLedsAan2(patroon2D, 30);
    for (a = 0; a < 4; a++) {
      for (b = 0; b < 4; b++) {
        patroon2D[a][binnenRing[b]] = 0;
        patroon2D[a][hoek[b]] = 1;
      }
    }
    stuurLedsAan2(patroon2D, 50);
    for (a = 0; a < 12; a++) {
      if (a == 2 || a == 5 || a == 9) {
        count++;
      }
      for (b = 1; b < 3; b++) {
        patroon2D[b][ring[0]] = 0;
        patroon2D[b][ring[11 - a]] = 1;
        patroon2D[b][ring[count - a]] = 0;
      }
      patroon2D[3][ring[0]] = 1;
      stuurLedsAan2(patroon2D, lengte);
    }
    for (c = 3; c >= 0; c--) {
      patroon2D[1][ring[c]] = 0;
      patroon2D[2][ring[c]] = 0;
      stuurLedsAan2(patroon2D, lengte);
    }
    count = 12;
    for (a = 0; a < 12; a++) {
      patroon2D[0][ring[a]] = 1;
      patroon2D[3][ring[a]] = 1;
      stuurLedsAan2(patroon2D, lengte);
    }
    stuurLedsAan2(patroon2D, 25);
    clearPatroon();
    for (a = 0; a < 12; a++) {
      patroon2D[1][ring[a]] = 1;
      patroon2D[2][ring[a]] = 1;
    }
    stuurLedsAan2(patroon2D, 50);
    for (a = 12; a > 0; a--) {
      patroon2D[1][ring[a]] = 0;
      patroon2D[2][ring[a]] = 0;
      patroon2D[2][ring[0]] = 1;
      stuurLedsAan2(patroon2D, lengte);
    }
    stuurLedsAan2(patroon2D, 30);
    for (a = 3; a >= 0; a--) {
      patroon2D[0][k1[a]] = 1;
      patroon2D[a][0] = 0;
      patroon2D[0][0] = 1;
      stuurLedsAan2(patroon2D, lengte * 2);
    }
    for (b = 1; b < 4; b++) {
      for (c = 0; c < 4; c++) {
        patroon2D[b][k1[c]] = 1;
      }
      stuurLedsAan2(patroon2D, lengte * 2);
    }
  }
}
