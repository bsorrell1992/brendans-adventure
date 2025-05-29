#include <Arduino.h>

const byte ARRAY_LENGTH = 8;

const byte ANODE_PINS[ARRAY_LENGTH] = { 13, 12, 11, 10, 9, 8, 7, 6 };
const byte CATHODE_PINS[ARRAY_LENGTH] = { A3, A2, A1, A0, 5, 4, 3, 2 };

const byte X_PIN = A5, Y_PIN = A4;

const unsigned int MAX_NUM_BOSSES = 2;
const unsigned int MAX_NUM_DOORS = 4;
const unsigned int MAX_NUM_GUARDS = 4;
const unsigned int MAX_NUM_ITEMS = 2;
const unsigned int MAX_NUM_PATROLS = 4;
const unsigned int MAX_NUM_SENTRIES = 2;
const unsigned int MAX_NUM_WALLS = 36;

const unsigned long PAUSE_DURATION = 250;
const unsigned long PLAYER_DELAY = 300;
const unsigned long GUARD_DELAY = 150;
const unsigned long PATROL_DELAY = 450;
const unsigned long BOSS_DELAY = 350;

const unsigned long ATTACK_DELAY = 1500;
const unsigned long SENTRY_DELAY = 2000;

// Player instantly kills enemies, but enemies do not instantly kill player
const int PLAYER_INITIAL_HEALTH = 20;
const int GUARD_DAMAGE = 4;
const int PATROL_DAMAGE = 2;
const int SENTRY_DAMAGE = 10;
const int BOSS_DAMAGE = 19;

// Point values
const int GUARD_POINTS = 30;
const int PATROL_POINTS = 50;
const int SENTRY_POINTS = 100;
const int BOSS_POINTS = 200;
const int ITEM_POINTS = 10;
const int BREAKABLE_WALL_POINTS = 5;
const int DOOR_POINTS = 25;
const int TREASURE_POINTS = 1000;

// Items
const int HEALTH_POTION_HEALING = 10;
const int SPEED_BOOTS_MULTIPLIER = 2;

const byte SPAWN_X = 3;
const byte SPAWN_Y = 3;