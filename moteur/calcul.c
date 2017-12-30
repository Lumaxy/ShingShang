#include "../structure.h"

int distance(Coordinate position, Coordinate target){
  //Pour eviter la racine carre, je renvoie le res au carre.
  return ((position.x - target.x)*(position.x - target.x) + (position.y - target.y)*(position.y - target.y));
}

float abso(float x){
  if(x < 0){
    x *= -1;
  }
  return x;
}
