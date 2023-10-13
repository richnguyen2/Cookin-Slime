#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

#define EMPTY 0
#define HOLDBUN 1
#define HOLDCHE 2
#define HOLDUNCOOKEDMEAT 3
#define HOLDCHOPPEDMEAT 4
#define HOLDCOOKEDMEAT 5
#define HOLDBURNTMEAT 6
#define HOLDCHEESEBURGER 7
#define HOLDHAMBURGER 8
#define HOLDCHEESEBUN 9
#define FACEUP 0
#define FACERIGHT 1
#define FACEDOWN 2
#define FACELEFT 3
#define MEATCHOPTIME 180 
#define MEATCOOKTIME 600
#define MEATBURNTIME 600
#define ORDERTIMELIMIT 1800
#define NEWORDERTIME 300
#define CASHTOWIN 1000
#define GAMETIME 300

// Player

struct player {
    int row;
    int col;
    int width;
    int height;
    int facing;
    int holding;
    int storyTime;
};

// NPC
struct npc {
    int row;
    int col;
    int width;
    int height;
    int facing;
};

// Ingredient Stations

struct bunStation {
    int rowStart;
    int rowEnd;
    int col;
};

struct cheeseStation {
    int rowStart;
    int rowEnd;
    int col;
};

struct meatStation {
    int rowStart;
    int rowEnd;
    int col;    
};
struct bunIngre {
    int row;
    int col;
    int width;
    int height;
};
struct cheeseIngre {
    int row;
    int col;
    int width;
    int height;
};

struct meatIngre {
    int row;
    int col;
    int width;
    int height;
};

struct choppedPattyIngre {
    int row;
    int col;
    int width;
    int height;
};

struct cookedPattyIngre {
    int row;
    int col;
    int width;
    int height;
};

struct burntPattyIngre {
    int row;
    int col;
    int width;
    int height;    
};

struct cheeseburgerDish {
    int row;
    int col;
    int width;
    int height;    
};

struct hamburgerDish {
    int row;
    int col;
    int width;
    int height;    
};

struct cheesebunDish {
    int row;
    int col;
    int width;
    int height;    
};

struct burger {
    int isChe;
    int isPat;
    int isBun;
    int isUnCooked;
    int isChopped;
    int isBurnt;
};

// Cooking Stations

struct burgerStation {
    int row;
    int colStart;
    int colEnd;
    struct burger bur;
};

struct cuttingStation {
    int row;
    int colStart;
    int colEnd;
    int hasMeat;
    int meatCut;
    int cutTimer;
    int passes;
};

struct cookingStation {
    int row;
    int colStart;
    int colEnd;
    int hasMeat;
    int meatCooked;
    int timer;
    int passes;
    int isCooking;
    int isBurning;
    int meatBurned;
    int burnCounter;
    int finishCooking;
};

struct finishZone {
    int rowStart;
    int rowEnd;
    int col;
    int isChe;
    int isPat;
    int isBun;
};

// Orders
struct orders {
    int row;
    int col;
    int orderTime;
    int isPlaced;
    int random;
    int isChe;
    int isPat;
    int isBun;
    int first;
    int length;
    int orderFailed;
    int passed;
    int counter;
};

// Cash
struct cashMoney {
    int row;
    int col;
    int amount;
};

// Game Time
struct gameTime {
    int row;
    int col;
    int time;
    int fastestTime;
};

// TRASH
struct trashCan {
    int row;
    int colStart;
    int colEnd;
};




void redrawPlayer(struct player p);
void redrawHoldingIngredients(struct player p, struct bunIngre bunI, struct cheeseIngre cheeseI, struct meatIngre meatI, struct choppedPattyIngre choppedI, struct cookedPattyIngre cookedI, struct burntPattyIngre burntI, struct cheeseburgerDish cheesebur, struct hamburgerDish hambur, struct cheesebunDish cheesebun);
void drawBuns(struct bunIngre bunI, int row, int col);
void drawCheese(struct cheeseIngre cheeseI, int row, int col);
void drawMeat(struct meatIngre meatI, int row, int col);
void drawChoppedMeat(struct choppedPattyIngre choppedI, int row, int col);
void drawCookedMeat(struct cookedPattyIngre cookedI, int row, int col);
void drawBurntMeat(struct burntPattyIngre burntI, int row, int col);
void drawCheeseBurger(struct cheeseburgerDish cheesebur, int row, int col);
void drawHamBurger(struct hamburgerDish hambur, int row, int col);
void drawCheeseBun(struct cheesebunDish cheesebun, int row, int col);

#endif
