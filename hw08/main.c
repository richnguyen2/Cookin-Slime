#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/floors.h"
#include "images/player.h"
#include "images/playerR.h"
#include "images/playerL.h"
#include "images/playerB.h"
#include "images/buns.h"
#include "images/cheese.h"
#include "images/buncheese.h"
#include "images/steak.h"
#include "images/choppedPatty.h"
#include "images/onPan.h"
#include "images/cookingPatty.h"
#include "images/pattyFinished.h"
#include "images/cookedPatty.h"
#include "images/pattyBurnt.h"
#include "images/burntPatty.h"
#include "images/cheeseburger.h"
#include "images/hamburger.h"
#include "images/zero.h"
#include "images/one.h"
#include "images/two.h"
#include "images/three.h"
#include "images/four.h"
#include "images/five.h"
#include "images/six.h"
#include "images/seven.h"
#include "images/eight.h"
#include "images/nine.h"
#include "images/titleScreen.h"
#include "images/rent.h"
#include "images/broke.h"
#include "images/goal.h"
#include "images/loser.h"
#include "images/winner.h"
#include "images/highScoreScreen.h"
#include "images/tutorial.h"
#include "images/slimey.h"

enum gba_state {
  START,
  STORY,
  PLAY,
  WIN,
  LOSE,
  HIGHSCORE,
};


void initializePlayer(struct player *pP) {
  vBlankCounter = 0;
  pP->row = 70;
  pP->col = 110;
  pP->width = 20;
  pP->height = 20;
  pP->facing = FACEDOWN;
  pP->holding = 0; 
  pP->storyTime = 0;
}
void initializeNPC(struct npc *slimeP) {
  slimeP->row = 152;
  slimeP->col = 0;
  slimeP->width = 12;
  slimeP->height = 8;
  slimeP->facing = FACERIGHT;
}

void initializeIngredientStations(struct bunStation *bunSP, struct cheeseStation *cheeseSP, struct meatStation *meatSP) {
  bunSP->rowStart = 45;
  bunSP->rowEnd = 80;
  bunSP->col = 25;
  cheeseSP->rowStart = 70;
  cheeseSP->rowEnd = 105;
  cheeseSP->col = 25;
  meatSP->rowStart = 95;
  meatSP->rowEnd = 130;
  meatSP->col = 25;
}
void initializeIngredients(struct bunIngre *bunP, struct cheeseIngre *cheP, struct meatIngre *meatP, struct choppedPattyIngre *choppedP, struct cookedPattyIngre *cookedP, struct burntPattyIngre *burntP) {
  bunP->row = 0;
  bunP->col = 0;
  bunP->width = BUNS_WIDTH;
  bunP->height = BUNS_HEIGHT;

  cheP->row = 0;
  cheP->col = 0;
  cheP->width = CHEESE_WIDTH;
  cheP->height = CHEESE_HEIGHT;

  meatP->row = 0;
  meatP->col = 0;
  meatP->width = STEAK_WIDTH;
  meatP->height = STEAK_HEIGHT;

  choppedP->row = 0;
  choppedP->col = 0;
  choppedP->width = CHOPPEDPATTY_WIDTH;
  choppedP->height = CHOPPEDPATTY_HEIGHT;

  cookedP->row = 0;
  cookedP->col = 0;
  cookedP->width = COOKEDPATTY_WIDTH;
  cookedP->height = COOKEDPATTY_HEIGHT;
    
  burntP->row = 0;
  burntP->col = 0;
  burntP->width = BURNTPATTY_WIDTH;
  burntP->height = BURNTPATTY_HEIGHT;

}

void initializeCuttingStation(struct cuttingStation *cuttingSP) {
  cuttingSP->row = 50;
  cuttingSP->colStart = 45;
  cuttingSP->colEnd = 80;
  cuttingSP->hasMeat = 0;
  cuttingSP->meatCut = 0;
  cuttingSP->cutTimer = 0;
  cuttingSP->passes = 0;
}

void initializeCookingStation(struct cookingStation *cS1, struct cookingStation *cS2) {
  cS1->colStart = 145;
  cS1->colEnd = 180;
  cS1->row = 50;
  cS1->hasMeat = 0;
  cS1->meatCooked = 0;
  cS1->timer = 0;
  cS1->passes = 0;
  cS1->isCooking = 0;
  cS1->isBurning = 0;
  cS1->meatBurned = 0;
  cS1->burnCounter = 0;
  cS1->finishCooking = 0;

  cS2->colStart = 170;
  cS2->colEnd = 205;
  cS2->row = 50;
  cS2->hasMeat = 0;
  cS2->meatCooked = 0;
  cS2->timer = 0;
  cS2->passes = 0;
  cS2->isCooking = 0;
  cS2->isBurning = 0;
  cS2->meatBurned = 0;
  cS2->burnCounter = 0;
  cS2->finishCooking = 0;
}

void initializeBurgerStation(struct burgerStation *burgerSP1, struct burgerStation *burgerSP2, struct burgerStation *burgerSP3) {
  burgerSP1->row = 50;
  burgerSP1->colStart = 70;
  burgerSP1->colEnd = 105;
  (*burgerSP1).bur.isChe = 0;
  (*burgerSP1).bur.isPat = 0;
  (*burgerSP1).bur.isBun = 0;
  (*burgerSP1).bur.isUnCooked = 0;
  (*burgerSP1).bur.isChopped = 0;
  (*burgerSP1).bur.isBurnt = 0;

  burgerSP2->row = 50;
  burgerSP2->colStart = 95;
  burgerSP2->colEnd = 130;
  (*burgerSP2).bur.isChe = 0;
  (*burgerSP2).bur.isPat = 0;
  (*burgerSP2).bur.isBun = 0;
  (*burgerSP2).bur.isUnCooked = 0;
  (*burgerSP2).bur.isChopped = 0;
  (*burgerSP2).bur.isBurnt = 0;

  burgerSP3->row = 50;
  burgerSP3->colStart = 120;
  burgerSP3->colEnd = 155;
  (*burgerSP3).bur.isChe = 0;
  (*burgerSP3).bur.isPat = 0;
  (*burgerSP3).bur.isBun = 0;
  (*burgerSP3).bur.isUnCooked = 0;
  (*burgerSP3).bur.isChopped = 0;
  (*burgerSP3).bur.isBurnt = 0;

}

void initializeBurgers(struct cheeseburgerDish *cheeseburP, struct hamburgerDish *hamburP, struct cheesebunDish *cheesebunP) {
  cheeseburP->row = 0;
  cheeseburP->col = 0;
  cheeseburP->width = CHEESEBURGER_WIDTH;
  cheeseburP->height = CHEESEBURGER_HEIGHT;

  hamburP->row = 0;
  hamburP->col = 0;
  hamburP->width = HAMBURGER_WIDTH;
  hamburP->height = HAMBURGER_HEIGHT;

  cheesebunP->row = 0;
  cheesebunP->col = 0;
  cheesebunP->width = BUNCHEESE_WIDTH;
  cheesebunP->height = BUNCHEESE_HEIGHT;
}
void initializeGameTime(struct gameTime *gTP) {
  gTP->row = 8;
  gTP->col = 160;
  gTP->time = GAMETIME;
}
void initializeTrash(struct trashCan *trashP) {
  trashP->row = 50;
  trashP->colStart = 20;
  trashP->colEnd = 55;

}
void initializeFinishZone(struct finishZone *finishP) {
  finishP->rowStart = 60;
  finishP->rowEnd = 110;
  finishP->col = 214;

}
void initializeOrders(struct orders *ords1P) {//, struct orders *ords2P, struct orders *ords3P, struct orders *ords4P, struct orders *ords5P) {
  ords1P->row = 5;
  ords1P->col = 5;
  ords1P->orderTime = 0;
  ords1P->isPlaced = 0;
  ords1P->random = 0;
  ords1P->isChe = 0;
  ords1P->isPat = 0;
  ords1P->isBun = 0;
  ords1P->first = 0;
  ords1P->length = 5;
  ords1P->orderFailed = 0;
  ords1P->passed = 0;
  ords1P->counter = 0;
}
void initializeCash(struct cashMoney *cashP) {
  cashP->amount = 0;
  cashP->row = 8;
  cashP->col = 200;
}

int main(void) {

  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  drawFullScreenImageDMA(titleScreen);
  // Initalizing //

  // player
  struct player p;
  initializePlayer(&p);

  // npc
  struct npc slime;
  initializeNPC(&slime);
  // ingredient stations

  struct bunStation bunS; 
  struct cheeseStation cheeseS; 
  struct meatStation meatS; 
  initializeIngredientStations(&bunS, &cheeseS, &meatS);
  // ingredients
  struct bunIngre bunI;
  struct cheeseIngre cheeseI;
  struct meatIngre meatI;
  struct choppedPattyIngre choppedI;
  struct cookedPattyIngre cookedI;
  struct burntPattyIngre burntI;
  initializeIngredients(&bunI, &cheeseI, &meatI, &choppedI, &cookedI, &burntI);
  // cutting station
  struct cuttingStation cuttingS;
  initializeCuttingStation(&cuttingS);
  struct cookingStation cookingS1;
  struct cookingStation cookingS2;
  initializeCookingStation(&cookingS1, &cookingS2);
  struct burgerStation burgerS1;
  struct burgerStation burgerS2;
  struct burgerStation burgerS3;
  initializeBurgerStation(&burgerS1, &burgerS2, &burgerS3);
  // burger dishes
  struct cheeseburgerDish cheesebur;
  struct hamburgerDish hambur;
  struct cheesebunDish cheesebun;
  initializeBurgers(&cheesebur, &hambur, &cheesebun);
  // trash
  struct trashCan trash;
  initializeTrash(&trash);
  //finish zone
  struct finishZone finish;
  initializeFinishZone(&finish);
  // orders
  struct orders ords1;
  initializeOrders(&ords1);
  // cash
  struct cashMoney cash;
  initializeCash(&cash);
  // Game Time
  struct gameTime gTime;
  gTime.fastestTime = 0;
  initializeGameTime(&gTime);
  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    // RESETTING THE GAME //
    
    waitForVBlank();

    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      state = START;
      drawFullScreenImageDMA(titleScreen);
      initializePlayer(&p);
      initializeGameTime(&gTime);
      initializeIngredientStations(&bunS, &cheeseS, &meatS);
      initializeIngredients(&bunI, &cheeseI, &meatI, &choppedI, &cookedI, &burntI);
      initializeCuttingStation(&cuttingS);
      initializeCookingStation(&cookingS1, &cookingS2);
      initializeBurgerStation(&burgerS1, &burgerS2, &burgerS3);
      initializeBurgers(&cheesebur, &hambur, &cheesebun);
      initializeTrash(&trash);
      initializeFinishZone(&finish);
      initializeOrders(&ords1);    
      initializeCash(&cash);
      initializeNPC(&slime);  
   }
    switch (state) {
      case START:
      if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
        state = STORY;
        drawFullScreenImageDMA(rent);
      } else if (KEY_JUST_PRESSED(BUTTON_B, currentButtons, previousButtons)) {
        state = HIGHSCORE;
        drawFullScreenImageDMA(highScoreScreen);
        int minP = gTime.fastestTime / 60;
        int secondsTensP = (gTime.fastestTime % 60) / 10;
        int secondsOnesP = ((gTime.fastestTime % 60) % 10);
        drawChar(80, 112 + 5, ':', BLACK);
        if (minP == 0) {
          drawImageDMA(80, 112, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (minP == 1) {
          drawImageDMA(80, 112, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (minP == 2) {
          drawImageDMA(80, 112, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (minP == 3) {
          drawImageDMA(80, 112, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (minP == 4) {
          drawImageDMA(80, 112, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (minP == 5) {
          drawImageDMA(80, 112, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (minP == 6) {
          drawImageDMA(80, 112, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (minP == 7) {
          drawImageDMA(80, 112, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (minP == 8) {
          drawImageDMA(80, 112, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (minP == 9) {
          drawImageDMA(80, 112, NINE_WIDTH, NINE_HEIGHT, nine);
        }

        if (secondsTensP == 0) {
          drawImageDMA(80, 112 + (ZERO_WIDTH * 2) + 2, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (secondsTensP == 1) {
          drawImageDMA(80, 112 + (ONE_WIDTH * 2) + 2, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (secondsTensP == 2) {
          drawImageDMA(80, 112 + (TWO_WIDTH * 2) + 2, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (secondsTensP == 3) {
          drawImageDMA(80, 112 + (THREE_WIDTH * 2) + 2, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (secondsTensP == 4) {
          drawImageDMA(80, 112 + (FOUR_WIDTH * 2) + 2, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (secondsTensP == 5) {
          drawImageDMA(80, 112 + (FIVE_WIDTH * 2) + 2, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (secondsTensP == 6) {
          drawImageDMA(80, 112 + (SIX_WIDTH * 2) + 2, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (secondsTensP == 7) {
          drawImageDMA(80, 112 + (SEVEN_WIDTH * 2) + 2, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (secondsTensP == 8) {
          drawImageDMA(80, 112 + (EIGHT_WIDTH * 2) + 2, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (secondsTensP == 9) {
          drawImageDMA(80, 112 + NINE_WIDTH + 1, NINE_WIDTH, NINE_HEIGHT, nine);
        }

        if (secondsOnesP == 0) {
          drawImageDMA(80, 112 + (ZERO_WIDTH * 3) + 3, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (secondsOnesP == 1) {
          drawImageDMA(80, 112 + (ONE_WIDTH * 3) + 3, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (secondsOnesP == 2) {
          drawImageDMA(80, 112 + (TWO_WIDTH * 3) + 3, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (secondsOnesP == 3) {
          drawImageDMA(80, 112 + (THREE_WIDTH * 3) + 3, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (secondsOnesP == 4) {
          drawImageDMA(80, 112 + (FOUR_WIDTH * 3) + 3, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (secondsOnesP == 5) {
          drawImageDMA(80, 112 + (FIVE_WIDTH * 3) + 3, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (secondsOnesP == 6) {
          drawImageDMA(80, 112 + (SIX_WIDTH * 3) + 3, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (secondsOnesP == 7) {
          drawImageDMA(80, 112 + (SEVEN_WIDTH * 3) + 3, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (secondsOnesP == 8) {
          drawImageDMA(80, 112 + (EIGHT_WIDTH * 3) + 3, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (secondsOnesP == 9) {
          drawImageDMA(80, 112 + (NINE_WIDTH * 3) + 3, NINE_WIDTH, NINE_HEIGHT, nine);
        }
      
      }
        break;
      case HIGHSCORE:

      break;
      case STORY:
      if (p.storyTime == 0) {
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
          drawFullScreenImageDMA(broke);
          p.storyTime = 1;
        }
      } else if (p.storyTime == 1) {
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
            drawFullScreenImageDMA(tutorial);
            p.storyTime = 2;
        }
      } else if (p.storyTime == 2) {
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
            drawFullScreenImageDMA(goal);
            p.storyTime = 3;
        }
      } else if (p.storyTime == 3) {
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
          state = PLAY;
          initializePlayer(&p);
          drawFullScreenImageDMA(floors);
        }
      }
      break;
      case PLAY:
      // UNDRAWING //
      undrawImageDMA(p.row - 6, p.col - 1, p.width + 2, p.height + 7, floors);
      undrawImageDMA(cash.row, cash.col, 24, 20, floors);
      undrawImageDMA(slime.row, slime.col, slime.width, slime.height, floors);
      if (vBlankCounter % 60 == 0) {
        undrawImageDMA(gTime.row, gTime.col - 10, 35, 10, floors);
      }
      
      if(vBlankCounter % 2 == 0) {
        if (slime.facing == FACERIGHT) {
          if (slime.col + slime.width + 1 >= 240) {
            slime.facing = FACELEFT;
          } else {
            slime.col += 1;
          }
        } else if (slime.facing == FACELEFT) {
          if (slime.col - 1 <= 0) {
            slime.facing = FACERIGHT;
          } else {
            slime.col -= 1;
          }
        }

      }

      // Orders //
      // Initializes orders
      struct orders ords[5];
      if (ords1.first == 0) {
        for (int i = 0; i < ords1.length; i++) {
        ords[i].row = ords1.row;
        if (i == 0) {
          ords[i].col = 5;
        } else {
          ords[i].col = ords[i - 1].col + 25;
        }
        ords[i].orderTime = 0;
        ords[i].isPlaced = 0;
        ords[i].random = 0;
        ords[i].isChe = 0;
        ords[i].isPat = 0;
        ords[i].isBun = 0;
        ords[i].length = 5;
        ords[i].passed = 0;
        ords[i].counter = 0;
        }
        ords1.first = 1;
      }

      // Every 5 seconds new order is placed unless max orders
      if (vBlankCounter % NEWORDERTIME == 0) {
        for (int i = 0; i < ords1.length; i++) {
          if (ords[i].isPlaced == 0) {
            ords[i].counter = 0;
            ords[i].passed = 0;
            ords[i].random = randint(0, 7);
            if (ords[i].random == 0 || ords[i].random == 6) {
              ords[i].isBun = 1;
              ords[i].isChe = 1;
              ords[i].isPat = 1;
              drawCheeseBurger(cheesebur, ords[i].row, ords[i].col);
            } else if (ords[i].random == 1 || ords[i].random == 7) {
              ords[i].isBun = 1; 
              ords[i].isPat = 1;
              ords[i].isChe = 0;
              drawHamBurger(hambur, ords[i].row, ords[i].col);
            } else if (ords[i].random == 2) {
              ords[i].isBun = 1;
              ords[i].isChe = 1;
              ords[i].isPat = 0;
              drawCheeseBun(cheesebun, ords[i].row, ords[i].col);
            } else if (ords[i].random == 3) {
              ords[i].isBun = 1;
              ords[i].isPat = 0;
              ords[i].isChe = 0;
              drawBuns(bunI, ords[i].row, ords[i].col);
            } else if (ords[i].random == 4) {
              ords[i].isChe = 1;
              ords[i].isBun = 0;
              ords[i].isPat = 0;
              drawCheese(cheeseI, ords[i].row, ords[i].col);
            } else if(ords[i].random == 5) {
              ords[i].isPat = 1;
              ords[i].isChe = 0;
              ords[i].isBun = 0;
              drawCookedMeat(cookedI, ords[i].row, ords[i].col);
            }
            ords[i].isPlaced = 1;
            ords[i].orderTime = vBlankCounter + ORDERTIMELIMIT;
            i = 6;
          }
        }
      }

      // Order Time Running Out
      ords1.orderFailed = vBlankCounter;
      for (int i = 0; i < ords1.length; i++) {
        if (ords[i].isPlaced == 1) {
          ords[i].counter++;
          if (ords[i].counter % 90 == 0) {
          ords[i].passed++;
            if (ords[i].passed > 15) {
              drawRectDMA(ords[i].row + 10, ords[i].col, ords[i].passed , 3, RED);
            } else if (ords[i].passed > 10) {
              drawRectDMA(ords[i].row + 10, ords[i].col, ords[i].passed , 3, YELLOW);
            } else {
              drawRectDMA(ords[i].row + 10, ords[i].col, ords[i].passed , 3, GREEN);
            }
          }      
        }
        if (ords1.orderFailed == ords[i].orderTime) {
          ords[i].isPlaced = 0;
          undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
          undrawImageDMA(ords[i].row + 10, ords[i].col, ords[i].passed , 3, floors);
        }
      }

      // Maybe make it only 1 ingredient and just change image loaded to remove all of the else if.
      // Player Movement //
      if (KEY_DOWN(BUTTON_UP,currentButtons)) {
        if (p.row - 2 < 50) {
          p.row = 50;
          p.facing = FACEUP;
          if (p.holding == HOLDBUN) {
            bunI.row = p.row;
          } else if (p.holding == HOLDCHE) {
            cheeseI.row = p.row;
          } else if(p.holding == HOLDUNCOOKEDMEAT) {
            meatI.row = p.row;
          } else if(p.holding == HOLDCHOPPEDMEAT) {
            choppedI.row = p.row;
          } else if(p.holding == HOLDCOOKEDMEAT) {
            cookedI.row = p.row;
          } else if(p.holding == HOLDBURNTMEAT) {
            burntI.row = p.row;
          } else if(p.holding == HOLDCHEESEBURGER) {
            cheesebur.row = p.row - 1;
          } else if(p.holding == HOLDHAMBURGER) {
            hambur.row = p.row;
          } else if(p.holding == HOLDCHEESEBUN) {
            cheesebun.row = p.row;
          }
        } else {
          p.row -= 2;
          p.facing = FACEUP;
          if (p.holding == HOLDBUN) {
            bunI.row -= 2;
          } else if (p.holding == HOLDCHE) {
            cheeseI.row -= 2;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.row -= 2;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.row -= 2;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.row -= 2;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.row -= 2;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.row -= 2;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.row -= 2;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.row -= 2;
          }
        }
      }
      if (KEY_DOWN(BUTTON_DOWN,currentButtons)) {
        if (p.row + p.height + 2 > 150) {
          p.row = 150 - p.height;
          p.facing = FACEDOWN;
          if (p.holding == HOLDBUN) {
            bunI.row = 150 - p.height;
          } else if (p.holding == HOLDCHE) {
            cheeseI.row = 150 - p.height;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.row = 150 - p.height;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.row = 150 - p.height;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.row = 150 - p.height;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.row = 150 - p.height;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.row = 150 - p.height - 1;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.row = 150 - p.height;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.row = 150 - p.height;
          }
        } else {
          p.row += 2;
          p.facing = FACEDOWN;
          if (p.holding == HOLDBUN) {
            bunI.row += 2;
          } else if (p.holding == HOLDCHE) {
            cheeseI.row += 2;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.row += 2;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.row += 2;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.row += 2;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.row += 2;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.row += 2;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.row += 2;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.row += 2;
          }
        }
      }
      if (KEY_DOWN(BUTTON_LEFT,currentButtons)) {
        if (p.col - 2 < 25) {
          p.col = 25;
          p.facing = FACELEFT;
          if (p.holding == HOLDBUN) {
            bunI.col = p.col;
          } else if (p.holding == HOLDCHE) {
            cheeseI.col = p.col;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.col = p.col;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.col = p.col;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.col = p.col;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.col = p.col;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.col = p.col;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.col = p.col;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.col = p.col;
          }
        } else {
          p.col -= 2;
          p.facing = FACELEFT;
          if (p.holding == HOLDBUN) {
            bunI.col -= 2;
          } else if (p.holding == HOLDCHE) {
            cheeseI.col -= 2;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.col -= 2;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.col -= 2;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.col -= 2;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.col -= 2;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.col -= 2;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.col -= 2;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.col -= 2;
          }
        }
      }
      if (KEY_DOWN(BUTTON_RIGHT,currentButtons)) {
        if (p.col + 2 + p.width > 214) {
          p.col = 214 - p.width;
          p.facing = FACERIGHT;
          if (p.holding == HOLDBUN) {
            bunI.col = 214 - p.width;
          } else if (p.holding == HOLDCHE) {
            cheeseI.col = 214 - p.width;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.col = 214 - p.width;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.col = 214 - p.width;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.col = 214 - p.width;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.col = 214 - p.width;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.col = 214 - p.width;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.col = 214 - p.width;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.col = 214 - p.width;
          }
        } else {
          p.col += 2;
          p.facing = FACERIGHT;
          if (p.holding == HOLDBUN) {
            bunI.col += 2;
          } else if (p.holding == HOLDCHE) {
            cheeseI.col += 2;
          } else if (p.holding == HOLDUNCOOKEDMEAT) {
            meatI.col += 2;
          } else if (p.holding == HOLDCHOPPEDMEAT) {
            choppedI.col += 2;
          } else if (p.holding == HOLDCOOKEDMEAT) {
            cookedI.col += 2;
          } else if (p.holding == HOLDBURNTMEAT) {
            burntI.col += 2;
          } else if (p.holding == HOLDCHEESEBURGER) {
            cheesebur.col += 2;
          } else if (p.holding == HOLDHAMBURGER) {
            hambur.col += 2;
          } else if (p.holding == HOLDCHEESEBUN) {
            cheesebun.col += 2;
          }
        }
      }

      // Picking Up Ingredients //

      // With Buns
      if ((p.col >= bunS.col && p.col < bunS.col + p.width) && 
      (p.row >= bunS.rowStart && p.row + p.height <= bunS.rowEnd) &&
      p.facing == FACELEFT && p.holding == EMPTY) {
        if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
          p.holding = HOLDBUN;
          bunI.row = p.row;
          bunI.col = p.col;
        }
      }

      // With Cheese
      if ((p.col >= cheeseS.col && p.col < cheeseS.col + p.width) && 
      (p.row >= cheeseS.rowStart && p.row + p.height <= cheeseS.rowEnd) &&
      p.facing == FACELEFT && p.holding == EMPTY) {
        if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
          p.holding = HOLDCHE;
          cheeseI.row = p.row;
          cheeseI.col = p.col;
        }
      }

      // With Uncooked Meat
      if ((p.col >= meatS.col && p.col < meatS.col + p.width) && 
      (p.row >= meatS.rowStart && p.row + p.height <= meatS.rowEnd) &&
      p.facing == FACELEFT && p.holding == EMPTY) {
        if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
          p.holding = HOLDUNCOOKEDMEAT;
          meatI.row = p.row;
          meatI.col = p.col;
        }
      }
      
      //make a placeItem(ingredient *item) remove the need to check each item.
      // Burger Station 1
        if ((p.row >= burgerS1.row && p.row < burgerS1.row + p.height) && 
        (p.col >= burgerS1.colStart && p.col + p.width <= burgerS1.colEnd) && p.facing == FACEUP) {
          if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
            // Placing Ingredients on burger station
            if (p.holding == HOLDUNCOOKEDMEAT && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isUnCooked = 1;
            } else if (p.holding == HOLDCHOPPEDMEAT && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isChopped = 1;
            } else if (p.holding == HOLDBURNTMEAT && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isBurnt = 1;
            } else if (p.holding == HOLDCHEESEBURGER && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isPat = 1;
              burgerS1.bur.isBun = 1;
              burgerS1.bur.isChe = 1;
            } else if (p.holding == HOLDHAMBURGER && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isPat = 1;
              burgerS1.bur.isBun = 1;              
            } else if (p.holding == HOLDCHEESEBUN && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0 && burgerS1.bur.isPat == 0 && burgerS1.bur.isBun == 0 && burgerS1.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isChe = 1;
              burgerS1.bur.isBun = 1;     
            } else if (p.holding == HOLDCOOKEDMEAT && burgerS1.bur.isPat == 0 && (burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0) && (burgerS1.bur.isChe == 0 || (burgerS1.bur.isChe == 1 && burgerS1.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS1.bur.isPat = 1;
            } else if (p.holding == HOLDBUN && burgerS1.bur.isBun == 0 && burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0) {
              p.holding = EMPTY;
              burgerS1.bur.isBun = 1;
            } else if (p.holding == HOLDCHE && burgerS1.bur.isChe == 0 && (burgerS1.bur.isUnCooked == 0 && burgerS1.bur.isChopped == 0
            && burgerS1.bur.isBurnt == 0) && (burgerS1.bur.isPat == 0 || (burgerS1.bur.isPat == 1 && burgerS1.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS1.bur.isChe = 1;
            } else if (p.holding == EMPTY) {
              if (burgerS1.bur.isBun == 1 && burgerS1.bur.isChe == 1 && burgerS1.bur.isPat == 1) {
                burgerS1.bur.isBun = 0;
                burgerS1.bur.isChe = 0;
                burgerS1.bur.isPat = 0;
                p.holding = HOLDCHEESEBURGER;
                cheesebur.row = p.row - 1;
                cheesebur.col = p.col;
              } else if (burgerS1.bur.isBun == 1 && burgerS1.bur.isPat == 1) {
                burgerS1.bur.isBun = 0;
                burgerS1.bur.isPat = 0;
                p.holding = HOLDHAMBURGER;
                hambur.row = p.row;
                hambur.col = p.col;
              } else if (burgerS1.bur.isBun == 1 && burgerS1.bur.isChe == 1) {
                burgerS1.bur.isBun = 0;
                burgerS1.bur.isChe = 0;
                p.holding = HOLDCHEESEBUN;
                cheesebun.row = p.row;
                cheesebun.col = p.col;
              } else if(burgerS1.bur.isBun == 1) {
                burgerS1.bur.isBun = 0;
                p.holding = HOLDBUN;
                bunI.row = p.row;
                bunI.col = p.col;
              } else if(burgerS1.bur.isChe == 1) {
                burgerS1.bur.isChe = 0;
                p.holding = HOLDCHE;
                cheeseI.row = p.row;
                cheeseI.col = p.col;
              } else if (burgerS1.bur.isPat == 1) {
                burgerS1.bur.isPat = 0;
                p.holding = HOLDCOOKEDMEAT;
                cookedI.row = p.row;
                cookedI.col = p.col;
              } else if (burgerS1.bur.isUnCooked == 1) {
                burgerS1.bur.isUnCooked = 0;
                p.holding = HOLDUNCOOKEDMEAT;
                meatI.row = p.row;
                meatI.col = p.col;
              } else if (burgerS1.bur.isChopped == 1) {
                burgerS1.bur.isChopped = 0;
                p.holding = HOLDCHOPPEDMEAT;
                choppedI.row = p.row;
                choppedI.col = p.col;
              } else if (burgerS1.bur.isBurnt == 1) {
                burgerS1.bur.isBurnt = 0;
                p.holding = HOLDBURNTMEAT;
                burntI.row = p.row;
                burntI.col = p.col;
              }
              undrawImageDMA(burgerS1.row - 20, burgerS1.colStart + 7, cheesebur.width + 3, cheesebur.height + 3, floors);
            }
          }
          // Drawing Burgers
          if (burgerS1.bur.isBun == 1 && burgerS1.bur.isChe == 1 && burgerS1.bur.isPat == 1) {
            drawCheeseBurger(cheesebur, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if (burgerS1.bur.isBun == 1 && burgerS1.bur.isPat == 1) {
            drawHamBurger(hambur, burgerS1.row - 20, burgerS1.colStart + 7);
          }else if (burgerS1.bur.isBun == 1 && burgerS1.bur.isChe == 1) {
            drawCheeseBun(cheesebun, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if (burgerS1.bur.isBun == 1) {
            drawBuns(bunI, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if (burgerS1.bur.isChe == 1 ) {
            drawCheese(cheeseI, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if(burgerS1.bur.isPat == 1) {
            drawCookedMeat(cookedI, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if(burgerS1.bur.isUnCooked == 1) {
            drawMeat(meatI, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if(burgerS1.bur.isChopped == 1) {
            drawChoppedMeat(choppedI, burgerS1.row - 20, burgerS1.colStart + 7);
          } else if(burgerS1.bur.isBurnt == 1) {
            drawBurntMeat(burntI, burgerS1.row - 20, burgerS1.colStart + 7);
          }
        }   
        // Burger Station 2
        if ((p.row >= burgerS2.row && p.row < burgerS2.row + p.height) && 
        (p.col >= burgerS2.colStart && p.col + p.width <= burgerS2.colEnd) && p.facing == FACEUP) {
          if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
            // Placing Ingredients on burger station
            if (p.holding == HOLDUNCOOKEDMEAT && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isUnCooked = 1;
            } else if (p.holding == HOLDCHOPPEDMEAT && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isChopped = 1;
            } else if (p.holding == HOLDBURNTMEAT && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isBurnt = 1;
            } else if (p.holding == HOLDCHEESEBURGER && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isPat = 1;
              burgerS2.bur.isBun = 1;
              burgerS2.bur.isChe = 1;
            } else if (p.holding == HOLDHAMBURGER && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isPat = 1;
              burgerS2.bur.isBun = 1;              
            } else if (p.holding == HOLDCHEESEBUN && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0 && burgerS2.bur.isPat == 0 && burgerS2.bur.isBun == 0 && burgerS2.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isChe = 1;
              burgerS2.bur.isBun = 1;     
            }else if (p.holding == HOLDCOOKEDMEAT && burgerS2.bur.isPat == 0 && (burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0) && (burgerS2.bur.isChe == 0 || (burgerS2.bur.isChe == 1 && burgerS2.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS2.bur.isPat = 1;
            } else if (p.holding == HOLDBUN && burgerS2.bur.isBun == 0 && burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0) {
              p.holding = EMPTY;
              burgerS2.bur.isBun = 1;
            } else if (p.holding == HOLDCHE && burgerS2.bur.isChe == 0 && (burgerS2.bur.isUnCooked == 0 && burgerS2.bur.isChopped == 0
            && burgerS2.bur.isBurnt == 0) && (burgerS2.bur.isPat == 0 || (burgerS2.bur.isPat == 1 && burgerS2.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS2.bur.isChe = 1;
            } else if (p.holding == EMPTY) {
              if (burgerS2.bur.isBun == 1 && burgerS2.bur.isChe == 1 && burgerS2.bur.isPat == 1) {
                burgerS2.bur.isBun = 0;
                burgerS2.bur.isChe = 0;
                burgerS2.bur.isPat = 0;
                p.holding = HOLDCHEESEBURGER;
                cheesebur.row = p.row - 1;
                cheesebur.col = p.col;
              } else if (burgerS2.bur.isBun == 1 && burgerS2.bur.isPat == 1) {
                burgerS2.bur.isBun = 0;
                burgerS2.bur.isPat = 0;
                p.holding = HOLDHAMBURGER;
                hambur.row = p.row;
                hambur.col = p.col;
              } else if (burgerS2.bur.isBun == 1 && burgerS2.bur.isChe == 1) {
                burgerS2.bur.isBun = 0;
                burgerS2.bur.isChe = 0;
                p.holding = HOLDCHEESEBUN;
                cheesebun.row = p.row;
                cheesebun.col = p.col;
              } else if(burgerS2.bur.isBun == 1) {
                burgerS2.bur.isBun = 0;
                p.holding = HOLDBUN;
                bunI.row = p.row;
                bunI.col = p.col;
              } else if(burgerS2.bur.isChe == 1) {
                burgerS2.bur.isChe = 0;
                p.holding = HOLDCHE;
                cheeseI.row = p.row;
                cheeseI.col = p.col;
              } else if (burgerS2.bur.isPat == 1) {
                burgerS2.bur.isPat = 0;
                p.holding = HOLDCOOKEDMEAT;
                cookedI.row = p.row;
                cookedI.col = p.col;
              } else if (burgerS2.bur.isUnCooked == 1) {
                burgerS2.bur.isUnCooked = 0;
                p.holding = HOLDUNCOOKEDMEAT;
                meatI.row = p.row;
                meatI.col = p.col;
              } else if (burgerS2.bur.isChopped == 1) {
                burgerS2.bur.isChopped = 0;
                p.holding = HOLDCHOPPEDMEAT;
                choppedI.row = p.row;
                choppedI.col = p.col;
              } else if (burgerS2.bur.isBurnt == 1) {
                burgerS2.bur.isBurnt = 0;
                p.holding = HOLDBURNTMEAT;
                burntI.row = p.row;
                burntI.col = p.col;
              }
              undrawImageDMA(burgerS2.row - 20, burgerS2.colStart + 7, cheesebur.width + 3, cheesebur.height + 3, floors);
            }
          }
          // Drawing Burgers
          if (burgerS2.bur.isBun == 1 && burgerS2.bur.isChe == 1 && burgerS2.bur.isPat == 1) {
            drawCheeseBurger(cheesebur, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if (burgerS2.bur.isBun == 1 && burgerS2.bur.isPat == 1) {
            drawHamBurger(hambur, burgerS2.row - 20, burgerS2.colStart + 7);
          }else if (burgerS2.bur.isBun == 1 && burgerS2.bur.isChe == 1) {
            drawCheeseBun(cheesebun, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if (burgerS2.bur.isBun == 1) {
            drawBuns(bunI, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if (burgerS2.bur.isChe == 1 ) {
            drawCheese(cheeseI, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if(burgerS2.bur.isPat == 1) {
            drawCookedMeat(cookedI, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if(burgerS2.bur.isUnCooked == 1) {
            drawMeat(meatI, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if(burgerS2.bur.isChopped == 1) {
            drawChoppedMeat(choppedI, burgerS2.row - 20, burgerS2.colStart + 7);
          } else if(burgerS2.bur.isBurnt == 1) {
            drawBurntMeat(burntI, burgerS2.row - 20, burgerS2.colStart + 7);
          }
        }   
        // Burger Station 3
        if ((p.row >= burgerS3.row && p.row < burgerS3.row + p.height) && 
        (p.col >= burgerS3.colStart && p.col + p.width <= burgerS3.colEnd) && p.facing == FACEUP) {
          if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) {
            // Placing Ingredients on burger station
            if (p.holding == HOLDUNCOOKEDMEAT && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isUnCooked = 1;
            } else if (p.holding == HOLDCHOPPEDMEAT && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isChopped = 1;
            } else if (p.holding == HOLDBURNTMEAT && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isBurnt = 1;
            } else if (p.holding == HOLDCHEESEBURGER && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isPat = 1;
              burgerS3.bur.isBun = 1;
              burgerS3.bur.isChe = 1;
            } else if (p.holding == HOLDHAMBURGER && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isPat = 1;
              burgerS3.bur.isBun = 1;              
            } else if (p.holding == HOLDCHEESEBUN && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0 && burgerS3.bur.isPat == 0 && burgerS3.bur.isBun == 0 && burgerS3.bur.isChe == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isChe = 1;
              burgerS3.bur.isBun = 1;     
            } else if (p.holding == HOLDCOOKEDMEAT && burgerS3.bur.isPat == 0 && (burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0) && (burgerS3.bur.isChe == 0 || (burgerS3.bur.isChe == 1 && burgerS3.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS3.bur.isPat = 1;
            } else if (p.holding == HOLDBUN && burgerS3.bur.isBun == 0 && burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0) {
              p.holding = EMPTY;
              burgerS3.bur.isBun = 1;
            } else if (p.holding == HOLDCHE && burgerS3.bur.isChe == 0 && (burgerS3.bur.isUnCooked == 0 && burgerS3.bur.isChopped == 0
            && burgerS3.bur.isBurnt == 0) && (burgerS3.bur.isPat == 0 || (burgerS3.bur.isPat == 1 && burgerS3.bur.isBun == 1))) {
              p.holding = EMPTY;
              burgerS3.bur.isChe = 1;
            } else if (p.holding == EMPTY) {
              if (burgerS3.bur.isBun == 1 && burgerS3.bur.isChe == 1 && burgerS3.bur.isPat == 1) {
                burgerS3.bur.isBun = 0;
                burgerS3.bur.isChe = 0;
                burgerS3.bur.isPat = 0;
                p.holding = HOLDCHEESEBURGER;
                cheesebur.row = p.row - 1;
                cheesebur.col = p.col;
              } else if (burgerS3.bur.isBun == 1 && burgerS3.bur.isPat == 1) {
                burgerS3.bur.isBun = 0;
                burgerS3.bur.isPat = 0;
                p.holding = HOLDHAMBURGER;
                hambur.row = p.row;
                hambur.col = p.col;
              } else if (burgerS3.bur.isBun == 1 && burgerS3.bur.isChe == 1) {
                burgerS3.bur.isBun = 0;
                burgerS3.bur.isChe = 0;
                p.holding = HOLDCHEESEBUN;
                cheesebun.row = p.row;
                cheesebun.col = p.col;
              } else if(burgerS3.bur.isBun == 1) {
                burgerS3.bur.isBun = 0;
                p.holding = HOLDBUN;
                bunI.row = p.row;
                bunI.col = p.col;
              } else if(burgerS3.bur.isChe == 1) {
                burgerS3.bur.isChe = 0;
                p.holding = HOLDCHE;
                cheeseI.row = p.row;
                cheeseI.col = p.col;
              } else if (burgerS3.bur.isPat == 1) {
                burgerS3.bur.isPat = 0;
                p.holding = HOLDCOOKEDMEAT;
                cookedI.row = p.row;
                cookedI.col = p.col;
              } else if (burgerS3.bur.isUnCooked == 1) {
                burgerS3.bur.isUnCooked = 0;
                p.holding = HOLDUNCOOKEDMEAT;
                meatI.row = p.row;
                meatI.col = p.col;
              } else if (burgerS3.bur.isChopped == 1) {
                burgerS3.bur.isChopped = 0;
                p.holding = HOLDCHOPPEDMEAT;
                choppedI.row = p.row;
                choppedI.col = p.col;
              } else if (burgerS3.bur.isBurnt == 1) {
                burgerS3.bur.isBurnt = 0;
                p.holding = HOLDBURNTMEAT;
                burntI.row = p.row;
                burntI.col = p.col;
              }
              undrawImageDMA(burgerS3.row - 20, burgerS3.colStart + 7, cheesebur.width + 3, cheesebur.height + 3, floors);
            }
          }
          // Drawing Burgers
          if (burgerS3.bur.isBun == 1 && burgerS3.bur.isChe == 1 && burgerS3.bur.isPat == 1) {
            drawCheeseBurger(cheesebur, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if (burgerS3.bur.isBun == 1 && burgerS3.bur.isPat == 1) {
            drawHamBurger(hambur, burgerS3.row - 20, burgerS3.colStart + 7);
          }else if (burgerS3.bur.isBun == 1 && burgerS3.bur.isChe == 1) {
            drawCheeseBun(cheesebun, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if (burgerS3.bur.isBun == 1) {
            drawBuns(bunI, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if (burgerS3.bur.isChe == 1 ) {
            drawCheese(cheeseI, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if(burgerS3.bur.isPat == 1) {
            drawCookedMeat(cookedI, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if(burgerS3.bur.isUnCooked == 1) {
            drawMeat(meatI, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if(burgerS3.bur.isChopped == 1) {
            drawChoppedMeat(choppedI, burgerS3.row - 20, burgerS3.colStart + 7);
          } else if(burgerS3.bur.isBurnt == 1) {
            drawBurntMeat(burntI, burgerS3.row - 20, burgerS3.colStart + 7);
          }
        }  


      // Cutting Station
      if ((p.row >= cuttingS.row && p.row < cuttingS.row + p.height) && 
      (p.col >= cuttingS.colStart && p.col + p.width <= cuttingS.colEnd) &&
      p.facing == FACEUP) {
        // Placing Raw Meat
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
        && cuttingS.hasMeat == 0 && p.holding == HOLDUNCOOKEDMEAT) { 
          cuttingS.hasMeat = 1;
          p.holding = EMPTY;
          cuttingS.meatCut = 0;
          drawMeat(meatI, cuttingS.row - 19, cuttingS.colStart + 7);
        } else if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
        && cuttingS.hasMeat == 1 && p.holding == EMPTY) { 
          // Picking Up Meat (Uncut)
          if (cuttingS.meatCut == 0) {
            meatI.row = p.row;
            meatI.col = p.col;
            p.holding = HOLDUNCOOKEDMEAT;
          } else if (cuttingS.meatCut == 1) {
          // Picking Up Meat (Cut)
            choppedI.row = p.row;
            choppedI.col = p.col;
            p.holding = HOLDCHOPPEDMEAT;
          }
          cuttingS.hasMeat = 0;
          cuttingS.meatCut = 0;
          undrawImageDMA(cuttingS.row - 19, cuttingS.colStart + 7, CHOPPEDPATTY_WIDTH, CHOPPEDPATTY_HEIGHT, floors);
          undrawImageDMA(cuttingS.row - 10, cuttingS.colStart + 7, 20, 3, floors);
        }
        // Cutting Raw Meat
        if (KEY_JUST_PRESSED(BUTTON_B, currentButtons, previousButtons) 
        && cuttingS.hasMeat == 1 && p.holding == EMPTY) {
          cuttingS.cutTimer = 0;
          undrawImageDMA(cuttingS.row - 10, cuttingS.colStart + 7, 20, 3, floors);
          cuttingS.passes = 0;
        }

        if(KEY_DOWN(BUTTON_B,currentButtons) && cuttingS.hasMeat == 1 && p.holding == EMPTY && cuttingS.meatCut == 0) {
          cuttingS.cutTimer++;
          if (cuttingS.cutTimer % 30 == 0) {
            cuttingS.passes++;
            drawRectDMA(cuttingS.row - 10, cuttingS.colStart + 7, 3 * cuttingS.passes, 3, RED);
          }
          if (cuttingS.cutTimer >= MEATCHOPTIME) {
            drawChoppedMeat(choppedI, cuttingS.row - 19, cuttingS.colStart + 7);
            cuttingS.meatCut = 1;
            cuttingS.passes = 0;
            drawRectDMA(cuttingS.row - 10, cuttingS.colStart + 7, 20, 3, GREEN);
          }
        }
      }

      // Cooking Stations //
      // 1
        if ((p.row >= cookingS1.row && p.row < cookingS1.row + p.height) && 
        (p.col >= cookingS1.colStart && p.col + p.width <= cookingS1.colEnd) &&
        p.facing == FACEUP) {
          // Placing/Picking Up Chopped meat into pan
          if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
          && cookingS1.hasMeat == 0 && p.holding == HOLDCHOPPEDMEAT) { 
            cookingS1.hasMeat = 1;
            p.holding = EMPTY;
            cookingS1.meatCooked = 0;
            drawImageDMA(cookingS1.row - 22, cookingS1.colStart + 9, ONPAN_WIDTH, ONPAN_HEIGHT, onPan);
          } else if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
          && cookingS1.hasMeat == 1 && p.holding == EMPTY && cookingS1.isCooking == 0) { 
            if (cookingS1.meatCooked == 0 && cookingS1.meatBurned == 0) {
              choppedI.row = p.row;
              choppedI.col = p.col;
              p.holding = HOLDCHOPPEDMEAT;
            } else if (cookingS1.meatCooked == 1) { 
              // Meat is cooked
              cookedI.row = p.row;
              cookedI.col = p.col;
              p.holding = HOLDCOOKEDMEAT;
            } else if (cookingS1.meatBurned == 1) {
              // Meat is burned
              burntI.row = p.row;
              burntI.col = p.col;
              p.holding = HOLDBURNTMEAT;
            }
            cookingS1.hasMeat = 0;
            cookingS1.meatCooked = 0;
            cookingS1.isBurning = 0;
            cookingS1.meatBurned = 0;
            cookingS1.burnCounter = 0;
            cookingS1.passes = 0;
            undrawImageDMA(cookingS1.row - 26, cookingS1.colStart + 9, ONPAN_WIDTH, ONPAN_HEIGHT + 5, floors);
            undrawImageDMA(cookingS1.row - 9, cookingS1.colStart + 7, 21, 3, floors);
        } 
        // Cooking Raw Meat
        if (KEY_JUST_PRESSED(BUTTON_B, currentButtons, previousButtons) && cookingS1.hasMeat == 1 
        && cookingS1.meatCooked == 0 && p.holding == EMPTY && cookingS1.isCooking == 0 && cookingS1.meatBurned == 0) {
          cookingS1.isCooking = 1;
          cookingS1.timer = MEATCOOKTIME; // 10 secs
          drawImageDMA(cookingS1.row - 22, cookingS1.colStart + 9, COOKINGPATTY_WIDTH, COOKINGPATTY_HEIGHT, cookingPatty);
        }
      
      }
      
        // Cooking Meat Timer
      if(cookingS1.isCooking == 1) {
        cookingS1.finishCooking++;
        if (cookingS1.finishCooking % 30 == 0) {
          cookingS1.passes++;
          drawRectDMA(cookingS1.row - 9, cookingS1.colStart + 7, cookingS1.passes, 3, RED);
        }
        if (cookingS1.timer <= cookingS1.finishCooking) {
          cookingS1.finishCooking = 0;
          cookingS1.isCooking = 0;
          cookingS1.meatCooked = 1;
          cookingS1.isBurning = 1;
          cookingS1.timer = MEATBURNTIME;
          drawRectDMA(cookingS1.row - 9, cookingS1.colStart + 7, cookingS1.passes, 3, GREEN);
          drawImageDMA(cookingS1.row - 22, cookingS1.colStart + 9, PATTYFINISHED_WIDTH, PATTYFINISHED_HEIGHT, pattyFinished);
          cookingS1.passes = 0;
        }
      } else if (cookingS1.isBurning == 1) {
        cookingS1.burnCounter++;
        if (cookingS1.burnCounter >= 300) {
          cookingS1.passes++;
          if (cookingS1.passes % 60 == 0) {
          drawRectDMA(cookingS1.row - 26, cookingS1.colStart + 15, 3, 7, RED);
          drawRectDMA(cookingS1.row - 18, cookingS1.colStart + 15, 3, 2, RED);
          } else if ((cookingS1.passes + 30) % 60 == 0) {
          undrawImageDMA(cookingS1.row - 26, cookingS1.colStart + 15, 3, 7, floors);
          undrawImageDMA(cookingS1.row - 18, cookingS1.colStart + 15, 3, 2, floors);
          drawImageDMA(cookingS1.row - 22, cookingS1.colStart + 9, PATTYFINISHED_WIDTH, PATTYFINISHED_HEIGHT, pattyFinished);
          }
        }
        if (cookingS1.timer == cookingS1.burnCounter) {
          cookingS1.meatCooked = 0;
          cookingS1.isBurning = 0;
          cookingS1.meatBurned = 1;
          drawRectDMA(cookingS1.row - 9, cookingS1.colStart + 7, 21, 3, RED);
          drawImageDMA(cookingS1.row - 22, cookingS1.colStart + 9, PATTYBURNT_WIDTH, PATTYBURNT_HEIGHT, pattyBurnt);
          drawRectDMA(cookingS1.row - 26, cookingS1.colStart + 15, 3, 7, RED);
          drawRectDMA(cookingS1.row - 18, cookingS1.colStart + 15, 3, 2, RED);
          cookingS1.passes = 0;
          cookingS1.burnCounter = 0;
        }
      }

      // 2
        if ((p.row >= cookingS2.row && p.row < cookingS2.row + p.height) && 
        (p.col >= cookingS2.colStart && p.col + p.width <= cookingS2.colEnd) &&
        p.facing == FACEUP) {
          // Placing/Picking Up Chopped meat into pan
          if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
          && cookingS2.hasMeat == 0 && p.holding == HOLDCHOPPEDMEAT) { 
            cookingS2.hasMeat = 1;
            p.holding = EMPTY;
            cookingS2.meatCooked = 0;
            drawImageDMA(cookingS2.row - 22, cookingS2.colStart + 9, ONPAN_WIDTH, ONPAN_HEIGHT, onPan);
          } else if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) 
          && cookingS2.hasMeat == 1 && p.holding == EMPTY && cookingS2.isCooking == 0) { 
            if (cookingS2.meatCooked == 0 && cookingS2.meatBurned == 0 && cookingS1.meatBurned == 0) {
              choppedI.row = p.row;
              choppedI.col = p.col;
              p.holding = HOLDCHOPPEDMEAT;
            } else if (cookingS2.meatCooked == 1) { 
              // Meat is cooked
              cookedI.row = p.row;
              cookedI.col = p.col;
              p.holding = HOLDCOOKEDMEAT;
            } else if (cookingS2.meatBurned == 1) {
              // Meat is burned
              burntI.row = p.row;
              burntI.col = p.col;
              p.holding = HOLDBURNTMEAT;
            }
            cookingS2.hasMeat = 0;
            cookingS2.meatCooked = 0;
            cookingS2.isBurning = 0;
            cookingS2.meatBurned = 0;
            cookingS2.burnCounter = 0;
            cookingS2.passes = 0;
            undrawImageDMA(cookingS2.row - 26, cookingS2.colStart + 9, ONPAN_WIDTH, ONPAN_HEIGHT + 5, floors);
            undrawImageDMA(cookingS2.row - 9, cookingS2.colStart + 7, 21, 3, floors);
        } 
        // Cooking Raw Meat
        if (KEY_JUST_PRESSED(BUTTON_B, currentButtons, previousButtons) && cookingS2.hasMeat == 1 
        && cookingS2.meatCooked == 0 && p.holding == EMPTY && cookingS2.isCooking == 0) {
          cookingS2.isCooking = 1;
          cookingS2.timer = MEATCOOKTIME; // 10 secs
          drawImageDMA(cookingS2.row - 22, cookingS2.colStart + 9, COOKINGPATTY_WIDTH, COOKINGPATTY_HEIGHT, cookingPatty);
        }
      
      }
      
        // Cooking Meat Timer
      if(cookingS2.isCooking == 1) {
        cookingS2.finishCooking++;
        if (cookingS2.finishCooking % 30 == 0) {
          cookingS2.passes++;
          drawRectDMA(cookingS2.row - 9, cookingS2.colStart + 7, cookingS2.passes, 3, RED);
        }
        if (cookingS2.timer <= cookingS2.finishCooking) {
          cookingS2.finishCooking = 0;
          cookingS2.isCooking = 0;
          cookingS2.meatCooked = 1;
          cookingS2.isBurning = 1;
          cookingS2.timer = MEATBURNTIME;
          drawRectDMA(cookingS2.row - 9, cookingS2.colStart + 7, cookingS2.passes, 3, GREEN);
          drawImageDMA(cookingS2.row - 22, cookingS2.colStart + 9, PATTYFINISHED_WIDTH, PATTYFINISHED_HEIGHT, pattyFinished);
          cookingS2.passes = 0;
        }
      } else if (cookingS2.isBurning == 1) {
        cookingS2.burnCounter++;
        if (cookingS2.burnCounter >= 300) {
          cookingS2.passes++;
          if (cookingS2.passes % 60 == 0) {
          drawRectDMA(cookingS2.row - 26, cookingS2.colStart + 15, 3, 7, RED);
          drawRectDMA(cookingS2.row - 18, cookingS2.colStart + 15, 3, 2, RED);
          } else if ((cookingS2.passes + 30) % 60 == 0) {
          undrawImageDMA(cookingS2.row - 26, cookingS2.colStart + 15, 3, 7, floors);
          undrawImageDMA(cookingS2.row - 18, cookingS2.colStart + 15, 3, 2, floors);
          drawImageDMA(cookingS2.row - 22, cookingS2.colStart + 9, PATTYFINISHED_WIDTH, PATTYFINISHED_HEIGHT, pattyFinished);
          }
        }
        if (cookingS2.timer == cookingS2.burnCounter) {
          cookingS2.meatCooked = 0;
          cookingS2.isBurning = 0;
          cookingS2.meatBurned = 1;
          drawRectDMA(cookingS2.row - 9, cookingS2.colStart + 7, 21, 3, RED);
          drawImageDMA(cookingS2.row - 22, cookingS2.colStart + 9, PATTYBURNT_WIDTH, PATTYBURNT_HEIGHT, pattyBurnt);
          drawRectDMA(cookingS2.row - 26, cookingS2.colStart + 15, 3, 7, RED);
          drawRectDMA(cookingS2.row - 18, cookingS2.colStart + 15, 3, 2, RED);
          cookingS2.passes = 0;
          cookingS2.burnCounter = 0;
        }
      }
        
      // Orders == Finish Zone
      if ((p.col <= finish.col && p.col >= finish.col - p.width - 2) && 
        (p.row >= finish.rowStart && p.row + p.height <= finish.rowEnd) &&
        p.facing == FACERIGHT) {
          if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
            for (int i = 0; i < ords1.length && p.holding != EMPTY; i++) {
              if (ords[i].isPlaced == 1) {
                if (ords[i].isBun == 1 && ords[i].isPat == 1 && ords[i].isChe == 1 
                && p.holding == HOLDCHEESEBURGER) {
                  cash.amount += 100;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                } else if (ords[i].isBun == 1 && ords[i].isPat == 1 && ords[i].isChe == 0 
                && p.holding == HOLDHAMBURGER) {
                  cash.amount += 80;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                } else if (ords[i].isBun == 1 && ords[i].isPat == 0 && ords[i].isChe == 1 
                && p.holding == HOLDCHEESEBUN) {
                  cash.amount += 40;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                } else if (ords[i].isBun == 1 && ords[i].isPat == 0 && ords[i].isChe == 0
                && p.holding == HOLDBUN) {
                  cash.amount += 30;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                } else if (ords[i].isBun == 0 && ords[i].isPat == 1 && ords[i].isChe == 0
                && p.holding == HOLDCOOKEDMEAT) {
                  cash.amount += 50;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                } else if (ords[i].isBun == 0 && ords[i].isPat == 0 && ords[i].isChe == 1
                && p.holding == HOLDCHE) {
                  cash.amount += 30;
                  ords[i].isPlaced = 0;
                  p.holding = EMPTY;
                  undrawImageDMA(ords[i].row + 10, ords[i].col, 20, 3, floors);
                  undrawImageDMA(ords[i].row, ords[i].col, CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, floors);
                }
              }
            }
          }
        }
      // Trash Can
      if ((p.row >= trash.row && p.row < trash.row + p.height) && 
      (p.col >= trash.colStart && p.col + p.width <= trash.colEnd) &&
      p.facing == FACEUP && p.holding != EMPTY) {
        if (KEY_JUST_PRESSED(BUTTON_A,currentButtons, previousButtons)) { 
          p.holding = EMPTY;
        }
      }

      // Drawing Cash //

      drawChar(cash.row, cash.col, '$', BLACK);
      int thouplace = cash.amount / 1000;
      int hundplace = (cash.amount % 1000) / 100;
      int tenplace = ((cash.amount % 1000) % 100) / 10;
      if (thouplace == 0) {
        drawImageDMA(cash.row, cash.col + ZERO_WIDTH + 1, ZERO_WIDTH, ZERO_HEIGHT, zero);
      } else if (thouplace == 1) {
        drawImageDMA(cash.row, cash.col + ONE_WIDTH + 1, ONE_WIDTH, ONE_HEIGHT, one);
      } else if (thouplace == 2) {
        drawImageDMA(cash.row, cash.col + TWO_WIDTH + 1, TWO_WIDTH, TWO_HEIGHT, two);
      } else if (thouplace == 3) {
        drawImageDMA(cash.row, cash.col + THREE_WIDTH + 1, THREE_WIDTH, THREE_HEIGHT, three);
      } else if (thouplace == 4) {
        drawImageDMA(cash.row, cash.col + FOUR_WIDTH + 1, FOUR_WIDTH, FOUR_HEIGHT, four);
      } else if (thouplace == 5) {
        drawImageDMA(cash.row, cash.col + FIVE_WIDTH + 1, FIVE_WIDTH, FIVE_HEIGHT, five);
      } else if (thouplace == 6) {
        drawImageDMA(cash.row, cash.col + SIX_WIDTH + 1, SIX_WIDTH, SIX_HEIGHT, six);
      } else if (thouplace == 7) {
        drawImageDMA(cash.row, cash.col + SEVEN_WIDTH + 1, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
      } else if (thouplace == 8) {
        drawImageDMA(cash.row, cash.col + EIGHT_WIDTH + 1, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
      } else if (thouplace == 9) {
        drawImageDMA(cash.row, cash.col + NINE_WIDTH + 1, NINE_WIDTH, NINE_HEIGHT, nine);
      }

      if (hundplace == 0) {
        drawImageDMA(cash.row, cash.col + (ZERO_WIDTH * 2) + 2, ZERO_WIDTH, ZERO_HEIGHT, zero);
      } else if (hundplace == 1) {
        drawImageDMA(cash.row, cash.col + (ONE_WIDTH * 2) + 2, ONE_WIDTH, ONE_HEIGHT, one);
      } else if (hundplace == 2) {
        drawImageDMA(cash.row, cash.col + (TWO_WIDTH * 2) + 2, TWO_WIDTH, TWO_HEIGHT, two);
      } else if (hundplace == 3) {
        drawImageDMA(cash.row, cash.col + (THREE_WIDTH * 2) + 2, THREE_WIDTH, THREE_HEIGHT, three);
      } else if (hundplace == 4) {
        drawImageDMA(cash.row, cash.col + (FOUR_WIDTH * 2) + 2, FOUR_WIDTH, FOUR_HEIGHT, four);
      } else if (hundplace == 5) {
        drawImageDMA(cash.row, cash.col + (FIVE_WIDTH * 2) + 2, FIVE_WIDTH, FIVE_HEIGHT, five);
      } else if (hundplace == 6) {
        drawImageDMA(cash.row, cash.col + (SIX_WIDTH * 2) + 2, SIX_WIDTH, SIX_HEIGHT, six);
      } else if (hundplace == 7) {
        drawImageDMA(cash.row, cash.col + (SEVEN_WIDTH * 2) + 2, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
      } else if (hundplace == 8) {
        drawImageDMA(cash.row, cash.col + (EIGHT_WIDTH * 2) + 2, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
      } else if (hundplace == 9) {
        drawImageDMA(cash.row, cash.col + (NINE_WIDTH * 2) + 2, NINE_WIDTH, NINE_HEIGHT, nine);
      }

      if (tenplace == 0) {
        drawImageDMA(cash.row, cash.col + (ZERO_WIDTH * 3) + 3, ZERO_WIDTH, ZERO_HEIGHT, zero);
      } else if (tenplace == 1) {
        drawImageDMA(cash.row, cash.col + (ONE_WIDTH * 3) + 3, ONE_WIDTH, ONE_HEIGHT, one);
      } else if (tenplace == 2) {
        drawImageDMA(cash.row, cash.col + (TWO_WIDTH * 3) + 3, TWO_WIDTH, TWO_HEIGHT, two);
      } else if (tenplace == 3) {
        drawImageDMA(cash.row, cash.col + (THREE_WIDTH * 3) + 3, THREE_WIDTH, THREE_HEIGHT, three);
      } else if (tenplace == 4) {
        drawImageDMA(cash.row, cash.col + (FOUR_WIDTH * 3) + 3, FOUR_WIDTH, FOUR_HEIGHT, four);
      } else if (tenplace == 5) {
        drawImageDMA(cash.row, cash.col + (FIVE_WIDTH * 3) + 3, FIVE_WIDTH, FIVE_HEIGHT, five);
      } else if (tenplace == 6) {
        drawImageDMA(cash.row, cash.col + (SIX_WIDTH * 3) + 3, SIX_WIDTH, SIX_HEIGHT, six);
      } else if (tenplace == 7) {
        drawImageDMA(cash.row, cash.col + (SEVEN_WIDTH * 3) + 3, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
      } else if (tenplace == 8) {
        drawImageDMA(cash.row, cash.col + (EIGHT_WIDTH * 3) + 3, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
      } else if (tenplace == 9) {
        drawImageDMA(cash.row, cash.col + (NINE_WIDTH * 3) + 3, NINE_WIDTH, NINE_HEIGHT, nine);
      }
      drawImageDMA(cash.row, cash.col + (ZERO_WIDTH * 4) + 4, ZERO_WIDTH, ZERO_HEIGHT, zero);
      // Drawing Time //
      if (vBlankCounter % 60 == 0) {
        gTime.time -= 1;
        int minP = gTime.time / 60;
        int secondsTensP = (gTime.time % 60) / 10;
        int secondsOnesP = ((gTime.time % 60) % 10);
        drawChar(gTime.row, gTime.col + 5, ':', BLACK);
        if (minP == 0) {
          drawImageDMA(gTime.row, gTime.col, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (minP == 1) {
          drawImageDMA(gTime.row, gTime.col, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (minP == 2) {
          drawImageDMA(gTime.row, gTime.col, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (minP == 3) {
          drawImageDMA(gTime.row, gTime.col, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (minP == 4) {
          drawImageDMA(gTime.row, gTime.col, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (minP == 5) {
          drawImageDMA(gTime.row, gTime.col, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (minP == 6) {
          drawImageDMA(gTime.row, gTime.col, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (minP == 7) {
          drawImageDMA(gTime.row, gTime.col, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (minP == 8) {
          drawImageDMA(gTime.row, gTime.col, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (minP == 9) {
          drawImageDMA(gTime.row, gTime.col, NINE_WIDTH, NINE_HEIGHT, nine);
        }

        if (secondsTensP == 0) {
          drawImageDMA(gTime.row, gTime.col + (ZERO_WIDTH * 2) + 2, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (secondsTensP == 1) {
          drawImageDMA(gTime.row, gTime.col + (ONE_WIDTH * 2) + 2, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (secondsTensP == 2) {
          drawImageDMA(gTime.row, gTime.col + (TWO_WIDTH * 2) + 2, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (secondsTensP == 3) {
          drawImageDMA(gTime.row, gTime.col + (THREE_WIDTH * 2) + 2, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (secondsTensP == 4) {
          drawImageDMA(gTime.row, gTime.col + (FOUR_WIDTH * 2) + 2, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (secondsTensP == 5) {
          drawImageDMA(gTime.row, gTime.col + (FIVE_WIDTH * 2) + 2, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (secondsTensP == 6) {
          drawImageDMA(gTime.row, gTime.col + (SIX_WIDTH * 2) + 2, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (secondsTensP == 7) {
          drawImageDMA(gTime.row, gTime.col + (SEVEN_WIDTH * 2) + 2, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (secondsTensP == 8) {
          drawImageDMA(gTime.row, gTime.col + (EIGHT_WIDTH * 2) + 2, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (secondsTensP == 9) {
          drawImageDMA(gTime.row, gTime.col + NINE_WIDTH + 1, NINE_WIDTH, NINE_HEIGHT, nine);
        }

        if (secondsOnesP == 0) {
          drawImageDMA(gTime.row, gTime.col + (ZERO_WIDTH * 3) + 3, ZERO_WIDTH, ZERO_HEIGHT, zero);
        } else if (secondsOnesP == 1) {
          drawImageDMA(gTime.row, gTime.col + (ONE_WIDTH * 3) + 3, ONE_WIDTH, ONE_HEIGHT, one);
        } else if (secondsOnesP == 2) {
          drawImageDMA(gTime.row, gTime.col + (TWO_WIDTH * 3) + 3, TWO_WIDTH, TWO_HEIGHT, two);
        } else if (secondsOnesP == 3) {
          drawImageDMA(gTime.row, gTime.col + (THREE_WIDTH * 3) + 3, THREE_WIDTH, THREE_HEIGHT, three);
        } else if (secondsOnesP == 4) {
          drawImageDMA(gTime.row, gTime.col + (FOUR_WIDTH * 3) + 3, FOUR_WIDTH, FOUR_HEIGHT, four);
        } else if (secondsOnesP == 5) {
          drawImageDMA(gTime.row, gTime.col + (FIVE_WIDTH * 3) + 3, FIVE_WIDTH, FIVE_HEIGHT, five);
        } else if (secondsOnesP == 6) {
          drawImageDMA(gTime.row, gTime.col + (SIX_WIDTH * 3) + 3, SIX_WIDTH, SIX_HEIGHT, six);
        } else if (secondsOnesP == 7) {
          drawImageDMA(gTime.row, gTime.col + (SEVEN_WIDTH * 3) + 3, SEVEN_WIDTH, SEVEN_HEIGHT, seven);
        } else if (secondsOnesP == 8) {
          drawImageDMA(gTime.row, gTime.col + (EIGHT_WIDTH * 3) + 3, EIGHT_WIDTH, EIGHT_HEIGHT, eight);
        } else if (secondsOnesP == 9) {
          drawImageDMA(gTime.row, gTime.col + (NINE_WIDTH * 3) + 3, NINE_WIDTH, NINE_HEIGHT, nine);
        }
      }

      // DRAWING Player //
      drawImageDMA(slime.row, slime.col, slime.width, slime.height, slimey);
      redrawPlayer(p);
      redrawHoldingIngredients(p, bunI, cheeseI, meatI, choppedI, cookedI, burntI, cheesebur, hambur, cheesebun);
      if (cash.amount >= CASHTOWIN) {
        state = WIN;
        if (gTime.time > gTime.fastestTime) {
          gTime.fastestTime =gTime.time;
        }
        drawFullScreenImageDMA(winner);
        
      }
      if (gTime.time == 0) {
          state = LOSE;
          drawFullScreenImageDMA(loser);
        }
        break;
      case WIN:

        // state = ?
        break;
      case LOSE:

        // state = ?
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  return 0;
}

void redrawHoldingIngredients(struct player p, struct bunIngre bunI, struct cheeseIngre cheeseI, struct meatIngre meatI, 
struct choppedPattyIngre choppedI, struct cookedPattyIngre cookedI, struct burntPattyIngre burntI, struct cheeseburgerDish cheesebur,
struct hamburgerDish hambur, struct cheesebunDish cheesebun) {
  if (p.holding == HOLDBUN) {
    drawBuns(bunI, bunI.row, bunI.col);
  } else if(p.holding == HOLDCHE) {
    drawCheese(cheeseI, cheeseI.row, cheeseI.col);
  } else if(p.holding == HOLDUNCOOKEDMEAT) {
    drawMeat(meatI, meatI.row, meatI.col);
  } else if(p.holding == HOLDCHOPPEDMEAT) {
    drawChoppedMeat(choppedI, choppedI.row, choppedI.col);
  } else if(p.holding == HOLDCOOKEDMEAT) {
    drawCookedMeat(cookedI, cookedI.row, cookedI.col);
  } else if(p.holding == HOLDBURNTMEAT) {
    drawBurntMeat(burntI, burntI.row, burntI.col);
  } else if(p.holding == HOLDCHEESEBURGER) {
    drawCheeseBurger(cheesebur, cheesebur.row, cheesebur.col);
  } else if(p.holding == HOLDHAMBURGER) {
    drawHamBurger(hambur, hambur.row, hambur.col);
  } else if(p.holding == HOLDCHEESEBUN) {
    drawCheeseBun(cheesebun, cheesebun.row, cheesebun.col);
  }
}

void redrawPlayer(struct player p) {
  if (p.facing == FACEUP) {
      drawImageDMA(p.row, p.col, PLAYER_WIDTH, PLAYER_HEIGHT, playerB);
      undrawImageDMA(p.row, p.col, p.width, 3, floors);
      undrawImageDMA(p.row, p.col, 1, 11, floors);
      undrawImageDMA(p.row, p.col + 1, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 2, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 3, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 4, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 14, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 16, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 17, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 18, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 19, 1, 11, floors);
      undrawImageDMA(p.row + 19, p.col, 1, 2, floors);
      undrawImageDMA(p.row + 20, p.col + 1, 1, 1, floors);
      undrawImageDMA(p.row + 19, p.col + 19, 1, 2, floors);
      undrawImageDMA(p.row + 20, p.col + 18, 1, 1, floors);
  } else if (p.facing == FACERIGHT) {
      drawImageDMA(p.row, p.col, PLAYER_WIDTH, PLAYER_HEIGHT, playerR);
      undrawImageDMA(p.row, p.col, p.width, 3, floors);
      undrawImageDMA(p.row, p.col, 1, 11, floors);
      undrawImageDMA(p.row, p.col + 1, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 2, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 3, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 4, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 14, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 16, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 17, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 18, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 19, 1, 11, floors);
      undrawImageDMA(p.row + 19, p.col, 1, 1, floors);
      undrawImageDMA(p.row + 18, p.col + 19, 1, 2, floors);
      undrawImageDMA(p.row + 19, p.col + 18, 1, 1, floors);
  } else if (p.facing == FACEDOWN) {
      drawImageDMA(p.row, p.col, PLAYER_WIDTH, PLAYER_HEIGHT, player);
      undrawImageDMA(p.row, p.col, p.width, 3, floors);
      undrawImageDMA(p.row, p.col, 1, 11, floors);
      undrawImageDMA(p.row, p.col + 1, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 2, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 3, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 4, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 14, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 16, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 17, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 18, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 19, 1, 11, floors);
      undrawImageDMA(p.row + 19, p.col, 1, 2, floors);
      undrawImageDMA(p.row + 20, p.col + 1, 1, 1, floors);
      undrawImageDMA(p.row + 19, p.col + 19, 1, 2, floors);
      undrawImageDMA(p.row + 20, p.col + 18, 1, 1, floors);
  } else if (p.facing == FACELEFT) {
      drawImageDMA(p.row, p.col, PLAYER_WIDTH, PLAYER_HEIGHT, playerL);
      undrawImageDMA(p.row, p.col, p.width, 3, floors);
      undrawImageDMA(p.row, p.col, 1, 11, floors);
      undrawImageDMA(p.row, p.col + 1, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 2, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 3, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 4, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 14, 2, 4, floors);
      undrawImageDMA(p.row, p.col + 16, 1, 5, floors);
      undrawImageDMA(p.row, p.col + 17, 1, 7, floors);
      undrawImageDMA(p.row, p.col + 18, 1, 8, floors);
      undrawImageDMA(p.row, p.col + 19, 1, 11, floors);
      undrawImageDMA(p.row + 19, p.col, 2, 1, floors);
      undrawImageDMA(p.row + 18, p.col, 1, 1, floors);
      undrawImageDMA(p.row + 19, p.col + 19, 1, 1, floors);
    }
}

// Drawing ingredients function
void drawBuns(struct bunIngre bunI, int row, int col) {
    drawImageDMA(row, col, bunI.width, bunI.height, buns);
    undrawImageDMA(row, col, 9, 1, floors);
    undrawImageDMA(row + 1, col, 3, 1, floors);
    undrawImageDMA(row + 2, col, 1, 1, floors);
    undrawImageDMA(row + 4, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 4, 1, floors);
    undrawImageDMA(row + 6, col, 3, 1, floors);
    undrawImageDMA(row, col + 13, 7, 1, floors);
    undrawImageDMA(row + 1, col + 15, 5, 1, floors);
    undrawImageDMA(row + 2, col + 19, 1, 1, floors);
    undrawImageDMA(row + 4, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 16, 4, 1, floors);
    undrawImageDMA(row + 6, col + 17, 3, 1, floors);
}

void drawCheese(struct cheeseIngre cheeseI, int row, int col) {
    drawImageDMA(row, col, cheeseI.width, cheeseI.height, cheese);
    undrawImageDMA(row, col, 9, 1, floors);
    undrawImageDMA(row + 1, col, 8, 1, floors);
    undrawImageDMA(row + 2, col, 1, 1, floors);
    undrawImageDMA(row + 2, col + 5, 2, 1, floors);
    undrawImageDMA(row + 4, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 4, 1, floors);
    undrawImageDMA(row + 6, col, 2, 1, floors);
    undrawImageDMA(row, col + 14, 6, 1, floors);
    undrawImageDMA(row + 1, col + 15, 5, 1, floors);
    undrawImageDMA(row + 2, col + 14, 2, 1, floors);
    undrawImageDMA(row + 2, col + 19, 1, 1, floors);
    undrawImageDMA(row + 4, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 16, 4, 1, floors);
    undrawImageDMA(row + 6, col + 18, 2, 1, floors);
}

void drawMeat(struct meatIngre meatI, int row, int col) {
    drawImageDMA(row, col, meatI.width, meatI.height, steak);
    undrawImageDMA(row, col, 6, 1, floors);
    undrawImageDMA(row + 1, col, 5, 1, floors);
    undrawImageDMA(row + 2, col, 1, 1, floors);
    undrawImageDMA(row + 4, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 4, 1, floors);
    undrawImageDMA(row + 6, col, 2, 1, floors);

    undrawImageDMA(row, col + 9, 11, 1, floors);
    undrawImageDMA(row + 1, col + 13, 7, 1, floors);
    undrawImageDMA(row + 2, col + 15, 1, 1, floors);
    undrawImageDMA(row + 2, col + 19, 1, 1, floors);
    undrawImageDMA(row + 4, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 16, 4, 1, floors);
    undrawImageDMA(row + 6, col + 18, 2, 1, floors);
}
void drawChoppedMeat(struct choppedPattyIngre choppedI, int row, int col) {
    drawImageDMA(row, col, choppedI.width, choppedI.height, choppedPatty);
    undrawImageDMA(row, col,11, 1, floors);
    undrawImageDMA(row + 1, col, 7, 1, floors);
    undrawImageDMA(row + 1, col + 9, 1, 1, floors);
    undrawImageDMA(row + 2, col, 4, 1, floors);
    undrawImageDMA(row + 3, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 4, 1, floors);

    undrawImageDMA(row, col + 12, 8, 1, floors);
    undrawImageDMA(row + 1, col + 13, 7, 1, floors);
    undrawImageDMA(row + 2, col + 16, 4, 1, floors);
    undrawImageDMA(row + 3, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col + 16, 4, 1, floors);
    
}
void drawCookedMeat(struct cookedPattyIngre cookedI, int row, int col) {
    drawImageDMA(row, col, cookedI.width, cookedI.height, cookedPatty);
    undrawImageDMA(row, col, 6, 1, floors);
    undrawImageDMA(row + 1, col, 5, 1, floors);
    undrawImageDMA(row + 2, col, 4, 1, floors);
    undrawImageDMA(row + 3, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 4, 1, floors);

    undrawImageDMA(row, col + 14, 6, 1, floors);
    undrawImageDMA(row + 1, col + 15, 5, 1, floors);
    undrawImageDMA(row + 2, col + 16, 4, 1, floors);
    undrawImageDMA(row + 3, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col + 16, 4, 1, floors);
}
void drawBurntMeat(struct burntPattyIngre burntI, int row, int col) {
    drawImageDMA(row, col, burntI.width, burntI.height, burntPatty);
    undrawImageDMA(row, col, 6, 1, floors);
    undrawImageDMA(row + 1, col, 5, 1, floors);
    undrawImageDMA(row + 2, col, 4, 1, floors);
    undrawImageDMA(row + 3, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 4, 1, floors);

    undrawImageDMA(row, col + 14, 6, 1, floors);
    undrawImageDMA(row + 1, col + 15, 5, 1, floors);
    undrawImageDMA(row + 2, col + 16, 4, 1, floors);
    undrawImageDMA(row + 3, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col + 16, 4, 1, floors);
}
void drawCheeseBurger(struct cheeseburgerDish cheesebur, int row, int col) {
    drawImageDMA(row, col, cheesebur.width, cheesebur.height, cheeseburger);
    undrawImageDMA(row, col, 7, 1, floors);
    undrawImageDMA(row + 1, col, 6, 1, floors);
    undrawImageDMA(row + 2, col, 5, 1, floors);
    undrawImageDMA(row + 3, col, 5, 1, floors);
    undrawImageDMA(row + 4, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 1, 1, floors);
    undrawImageDMA(row + 7, col, 4, 1, floors);

    undrawImageDMA(row, col + 13, 7, 1, floors);
    undrawImageDMA(row + 1, col + 14, 6, 1, floors);
    undrawImageDMA(row + 2, col + 15, 5, 1, floors);
    undrawImageDMA(row + 3, col + 15, 5, 1, floors);
    undrawImageDMA(row + 4, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col + 19, 1, 1, floors);
    undrawImageDMA(row + 7, col+ 16, 4, 1, floors);
}

void drawHamBurger(struct hamburgerDish hambur, int row, int col) {
    drawImageDMA(row, col, hambur.width, hambur.height, hamburger);
    undrawImageDMA(row, col, 7, 1, floors);
    undrawImageDMA(row + 1, col, 6, 1, floors);
    undrawImageDMA(row + 2, col, 5, 1, floors);
    undrawImageDMA(row + 3, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 4, 1, floors);

    undrawImageDMA(row, col + 13, 7, 1, floors);
    undrawImageDMA(row + 1, col + 14, 6, 1, floors);
    undrawImageDMA(row + 2, col + 15, 5, 1, floors);
    undrawImageDMA(row + 3, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col+ 16, 4, 1, floors);
}
void drawCheeseBun(struct cheesebunDish cheesebun, int row, int col) {
    drawImageDMA(row, col, cheesebun.width, cheesebun.height, buncheese);
    undrawImageDMA(row, col, 7, 1, floors);
    undrawImageDMA(row + 1, col, 6, 1, floors);
    undrawImageDMA(row + 2, col, 5, 1, floors);
    undrawImageDMA(row + 3, col, 1, 1, floors);
    undrawImageDMA(row + 5, col, 1, 1, floors);
    undrawImageDMA(row + 6, col, 4, 1, floors);

    undrawImageDMA(row, col + 13, 7, 1, floors);
    undrawImageDMA(row + 1, col + 14, 6, 1, floors);
    undrawImageDMA(row + 2, col + 15, 5, 1, floors);
    undrawImageDMA(row + 3, col + 19, 1, 1, floors);
    undrawImageDMA(row + 5, col + 19, 1, 1, floors);
    undrawImageDMA(row + 6, col+ 16, 4, 1, floors);
}