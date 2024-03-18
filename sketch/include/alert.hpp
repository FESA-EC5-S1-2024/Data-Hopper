#pragma once

typedef unsigned char small;

struct Alert {
  small temperature;
  small humidity;
  small luminosity;
};

struct Medias {
  float temperatura;
  float umidade;
  float luminosidade;
};

void warning(short type); 

extern Medias medias;
