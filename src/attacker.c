// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter
#define TURNO_SPY 5

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(position_t attacker_position, Spy defender_spy) {
  static int turno = 0;
  static position_t pos_atual, pos_anterior;
  static position_t defender_position;
  direction_t resultado = (direction_t) DIR_STAY;
  
  pos_atual = attacker_position;

  if (turno == 0) {
    srand(time(0));
    pos_anterior = attacker_position;
    defender_position.i = defender_position.j = 0;
  }

  if (turno == TURNO_SPY) {
    defender_position = get_spy_position(defender_spy);
  }

  while ((pos_anterior.i == pos_atual.i) && (pos_anterior.j == pos_atual.j)) {
    int x = rand() % 100;


    if (x < 25) {
      pos_atual.j += 1;
      resultado = (direction_t) DIR_RIGHT;
    }
    else if (x < 50) {
      pos_atual.i += -1;
      pos_atual.j += 1;
      resultado = (direction_t) DIR_UP_RIGHT;
    }
    else if (x < 75) {
      pos_atual.i += 1;
      pos_atual.j += 1;
      resultado = (direction_t) DIR_DOWN_RIGHT;
    }
    else if (x < 80) {
      pos_atual.i += -1;
      resultado = (direction_t) DIR_UP;
    }
    else if (x < 85) {
      pos_atual.i += 1;
      resultado = (direction_t) DIR_DOWN;
    }
    else if (x < 90) {
      pos_atual.i += -1;
      pos_atual.j += -1;
      resultado = (direction_t) DIR_UP_LEFT;
    }
    else if (x < 95) {
      pos_atual.i += 1;
      pos_atual.j += -1;
      resultado = (direction_t) DIR_DOWN_LEFT;
    }
    else if (x < 99) {
      pos_atual.j += -1;
      resultado = (direction_t) DIR_LEFT;
    }
    else {
      resultado = (direction_t) DIR_STAY;
      break;
    }

    if ((turno == TURNO_SPY) &&
      (abs((int) (pos_atual.i - defender_position.i)) + abs((int) (pos_atual.j - defender_position.j)) <
      abs((int) (pos_anterior.i - defender_position.i)) + abs((int) (pos_anterior.j - defender_position.j)))) {
          pos_atual = pos_anterior;
    }
  }
  pos_anterior = pos_atual;
  turno ++;
  return resultado;
}

/*----------------------------------------------------------------------------*/