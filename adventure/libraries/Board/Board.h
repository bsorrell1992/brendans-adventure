/*
    class Board : public Printable {
    private:
    Board *top, *right, *down, *left;

    public:
    Entity* board[ARRAY_LENGTH][ARRAY_LENGTH];

    Board(Entity* board[ARRAY_LENGTH][ARRAY_LENGTH], Board* top, Board* right, Board* down, Board* left) {
        memcpy(this->board, board, sizeof(Entity*) * ARRAY_LENGTH * ARRAY_LENGTH);
        this->top = top;
        this->right = right;
        this->down = down;
        this->left = left;
    }

    Board(Entity* board[ARRAY_LENGTH][ARRAY_LENGTH]) : Board(board, nullptr, nullptr, nullptr, nullptr) {}

    ~Board() {
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j)
            if (board[i][j] != nullptr) delete board[i][j];
        }
    }

    Board* getTop() { return top; }
    Board* getRight() { return right; }
    Board* getDown() { return down; }
    Board* getLeft() { return left; }
    void setTop(Board* top) { this->top = top; }
    void setRight(Board* right) { this->right = right; }
    void setDown(Board* down) { this->down = down; }
    void setLeft(Board* left) { this->left = left; }

    void getPatternFromBoard(byte pattern[ARRAY_LENGTH][ARRAY_LENGTH]) {
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
            if (board[i][j] == nullptr) pattern[i][j] = 0;
            else pattern[i][j] = 1;
        }
        }
    }

    size_t printTo(Print& p) const {
        size_t r = 0;
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
            if (board[j][i] != nullptr) {
            r += p.print(board[j][i]->getType());
            r += p.print(" ");
            } else {
            r += p.print("null ");
            }
        }
        r += p.print("\n");
        }
    }
    };
*/