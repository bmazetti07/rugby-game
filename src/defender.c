// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "dimension.h"
#include "field.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter
#define TURNO_SPY 5

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(position_t defender_position, Spy attacker_spy) {
  static int turno = 0;
  static position_t pos_atual, pos_anterior;
  static position_t attacker_position;
  direction_t resultado = (direction_t) DIR_STAY;
  
  pos_atual = defender_position;

  if (turno == 0) {
    srand(time(0));
    pos_anterior = defender_position;
    pos_atual.j += -1;
    resultado = (direction_t) DIR_LEFT;
    attacker_position.i = attacker_position.j = 0;
  }

  else {

    if (turno == TURNO_SPY) {
      attacker_position = get_spy_position(attacker_spy);
    }
    //printf("valor da variavel estática: %d\n", turno);

    while ((pos_anterior.i == pos_atual.i) && (pos_anterior.j == pos_atual.j)) {
      if (defender_position.i == 1) {
        pos_atual.i += 1;
        resultado = (direction_t) DIR_DOWN;
      }
      else if (defender_position.i == 8) {
        pos_atual.i += -1;
        resultado = (direction_t) DIR_UP; 
      }

      else {
        int x = random() % 100;

        if (x < 40) {
          pos_atual.i += -1;
          resultado = (direction_t) DIR_UP;
        }
        else if (x < 80) {
          pos_atual.i += 1;
          resultado = (direction_t) DIR_DOWN;
        }

        else {
          resultado = (direction_t) DIR_STAY;
          break;
        }
      }

      if ((turno == TURNO_SPY) &&
        (abs((int) (pos_atual.i - attacker_position.i)) + abs((int) (pos_atual.j - attacker_position.j)) >
        abs((int) (pos_anterior.i - attacker_position.i)) + abs((int) (pos_anterior.j - attacker_position.j)))) {
            pos_atual = pos_anterior;
      }
    }
  }

  pos_anterior = pos_atual;
  turno ++;
  return resultado;
}

/*----------------------------------------------------------------------------*/