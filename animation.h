#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

/*
  Gibt den �bergebenen Text von Links nach Rechts auf dem Bildschirm aus.
  Die Buchstaben erscheinen einzeln, zeitversetzt.
  Parameter
    - velocity - Geschwindigkeit in Buchstaben pro Sekunde,
                 bestimmt die Verz�gerungszeit zwischen den einzelnen Buchstaben

*/
void animi_out(char const *text, float velocity);

#endif // ANIMATION_H_INCLUDED
