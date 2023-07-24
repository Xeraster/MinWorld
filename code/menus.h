int textSizeSmall;
int textSizeMedium;
int textSizeLarge;

void setupMainMenu();

void drawMainMenu(int mouseX, int mouseY, int lastMouse);

void drawNewgameScreen1(int mouseX, int mouseY, int lastMouse);

void drawNewgameScreen2(int mouseX, int mouseY, int lastMouse);

void drawMenus(int mouseX, int mouseY, int lastMouse);

button mainMenu_newGame;
button mainMenu_loadGame;
button mainMenu_mods;
button mainMenu_settings;
button mainMenu_quitGame;

//use this for both "main menu screen 1" and "main menu screen 2"
button mainScreen1Next;
button mainScreen1Back;

//screen1 elements
sideScroll startingPawns; //damn. "sideScroll". What a stupid name for a class
sideScroll aiIqbar;
sideScroll difficultyBar;

//screen2 elements
textbox planetSeedBox;
button randomizeSeedButton;
int additionalSalt = 0;//for random seed generation. increment every time randomize button gets clicked for even randomer randomness
sideScroll planetSizeSideScroll;

slider planetTempSlider;
slider planetOrbitEccentricity;
slider planetAxialTilt;
slider planetWaterAbundance;
slider planetPopulation;

extern planet newPlanet;

//initialize handles all the one-time setups for the ui elements
void ui_initialize();

//resize handles all the setup for the ui elements taht have to be rerun every time the screen resolution changes
void on_resize();

bool atMainMenu = true;//initially set to true since the game starts on the main menu
bool newGameScreen1 = false;
bool newGameScreen2 = false;

bool normalInGame = false;  //if user is in game or not. If in game, playerInfo starts doing ui stuff for each player
#include "menus.cpp"