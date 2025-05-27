#include <Constants.h>
#include <Timer.h>

static Board* currentBoard = nullptr;
static Board* spawnBoard = nullptr;
static Player* player = nullptr;

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);

    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  // Initialize serial communication
  Serial.begin(115200);
  Serial.setTimeout(100);

  // Initialize current board
  player = new Player();
  currentBoard = getDebugBoard();
  spawnBoard = currentBoard;
}

Board* getDebugBoard() {
  // Add potion room with health potion
  // Two-wide corridors have patrolmen wandering back and forth
  // Three-wide corridors have patrolmen and a sentry, occur on sides of board with U-shaped bend on other side connecting stacked two-wide corridors
  // Four-wide corridors are empty
  Entity* board[ARRAY_LENGTH][ARRAY_LENGTH];
  // Initialize nullptrs
  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    for (int j = 0; j < ARRAY_LENGTH; ++j) board[i][j] = nullptr;
  }

  // Initialize walls
  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    board[i][0] = &wall;
    board[i][ARRAY_LENGTH - 1] = &wall;
  }

  for (int i = 1; i < ARRAY_LENGTH - 1; ++i) {
    board[0][i] = &wall;
    board[ARRAY_LENGTH - 1][i] = &wall;
  }

  board[SPAWN_X][SPAWN_Y] = player;
  board[0][3] = nullptr;
  board[0][4] = nullptr;
  board[0][5] = nullptr;
  board[3][1] = &door;
  board[4][1] = &door;
  board[5][1] = &door;
  board[6][1] = &door;
  static Key k = Key();
  static Sword s = Sword();
  static Pickaxe p = Pickaxe();
  static SpeedBoots sb = SpeedBoots();
  static Armor a = Armor();
  static HealthPotion hp = HealthPotion();
  static Treasure t = Treasure();
  board[3][5] = &s;
  board[4][6] = &p;
  board[5][5] = &sb;
  board[6][6] = &a;
  board[1][1] = &k;
  board[1][6] = &t;
  
  static Board debugBoard = Board(board);

  // Initialize left board
  Entity* leftBoard[ARRAY_LENGTH][ARRAY_LENGTH];

  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    for (int j = 0; j < ARRAY_LENGTH; ++j) leftBoard[i][j] = nullptr;
  }
  
  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    leftBoard[i][0] = &wall;
    leftBoard[i][ARRAY_LENGTH - 1] = &wall;
  }

  for (int i = 1; i < ARRAY_LENGTH - 1; ++i) {
    leftBoard[0][i] = &wall;
    leftBoard[ARRAY_LENGTH - 1][i] = &wall;
  }

  leftBoard[ARRAY_LENGTH - 1][3] = nullptr;
  leftBoard[ARRAY_LENGTH - 1][4] = nullptr;
  leftBoard[ARRAY_LENGTH - 1][5] = nullptr;
  leftBoard[ARRAY_LENGTH - 2][2] = &wall;
  leftBoard[ARRAY_LENGTH - 2][6] = &wall;
  static Guard g = Guard(false, true, 1);
  leftBoard[ARRAY_LENGTH - 2][3] = &g;
  static Board leftDebugBoard = Board(leftBoard);

  Entity* corridor[ARRAY_LENGTH][ARRAY_LENGTH];
  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    for (int j = 0; j < ARRAY_LENGTH; ++j) corridor[i][j] = nullptr;
  }
  for (int i = 0; i < ARRAY_LENGTH; ++i) {
    for (int j = 0; j < ARRAY_LENGTH; ++j) if (j < 3 || j > 5) corridor[i][j] = &wall;
  }
  static Patrol p1 = Patrol(true, false, 1);
  corridor[1][5] = &p1;
  static Patrol p2 = Patrol(true, false, -1);
  corridor[ARRAY_LENGTH - 2][3] = &p2;
  static Board corridorBoard = Board(corridor, nullptr, &debugBoard, nullptr, &leftDebugBoard);
  leftDebugBoard.setRight(&corridorBoard);
  debugBoard.setLeft(&corridorBoard);

  return &debugBoard;
}

void loop() {
  static bool playing = true;
  if (playing) {
    if (player->isAlive()) {      
      player->move(currentBoard);

      // Move enemies
      for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
          Entity* e = currentBoard->board[i][j];
          if (e != nullptr) {
            String eType = e->getType();
            if (eType == "guard") {
              Guard* g = currentBoard->board[i][j];
              if (g->timeToMove()) g->move(i, j);
            } else if (eType == "patrol") {
              Patrol* p = currentBoard->board[i][j];
              if (p->timeToMove()) p->move(i, j);
            } else if (eType == "sentry") {
              // attack at intervals
            } else if (eType == "boss") {
              Boss* b = currentBoard->board[i][j];
              if (b->timeToMove()) b->move(i, j);
            }
          }

          if (!player->isAlive()) {
            currentBoard->board[player->getX()][player->getY()] = nullptr;
            Serial.println("You died! Would you like to continue playing?");
            return;
          }
        }
      }
    } else if (Serial.available()) {
      String input = Serial.readString();
      input.trim();
      if (input == "yes") {
        player->revive();
        player->setX(SPAWN_X);
        player->setY(SPAWN_Y);
        currentBoard = spawnBoard;
        spawnBoard->board[SPAWN_X][SPAWN_Y] = player;
      } else if (input == "no") playing = false;
    }

    // Display board
    static byte pattern[ARRAY_LENGTH][ARRAY_LENGTH];
    currentBoard->getPatternFromBoard(pattern);
    //Serial.println(*currentBoard);
    display(pattern);
  }
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
void display(byte pattern[ARRAY_LENGTH][ARRAY_LENGTH]) {
  for (byte anode = 0; anode < 8; ++anode) {
    for (byte cathode = 0; cathode < 8; ++cathode) {
      if (pattern[cathode][anode]) digitalWrite(CATHODE_PINS[cathode], LOW);
      else digitalWrite(CATHODE_PINS[cathode], HIGH);
    }
    digitalWrite(ANODE_PINS[anode], LOW);
    delayMicroseconds(PAUSE_DURATION);
    digitalWrite(ANODE_PINS[anode], HIGH);
  }
}