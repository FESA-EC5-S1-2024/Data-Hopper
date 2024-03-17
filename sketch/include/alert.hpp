#pragma once

typedef unsigned char small;

struct Alert {
  small temperature;
  small humidity;
  small luminosity;
};

void warning(short type); 
