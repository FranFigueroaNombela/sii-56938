// Raqueta.cpp: implementation of the Raqueta class.
//
//////////////////////////////////////////////////////////////////////

#include "Raqueta.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Raqueta::Raqueta()
{
  velocidad.x=0;
  velocidad.y=0;
}

Raqueta::~Raqueta()
{

}

void Raqueta::Mueve(float t)
{
  x1 += velocidad.x * t;
  y1 += velocidad.y * t;
  
  x2 += velocidad.x * t;
  y2 += velocidad.y * t;
}
