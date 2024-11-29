
//TFT display libraries
#include <SPI.h>
#include <TFT.h>

//lcd display libraries
//#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//tft display pins
const int tft_cs = 10;
const int tft_rst = 8;
const int tft_a0 = 9;

//lcd display pins
const int lcd_sda = A4;
const int lcd_svl = A5;

//joystic pins
const int VRx = A0;
const int VRy = A1;
const int sw = 7;

//ir pins
const int ir_out = 6;

//other pins
const int reset_arduino = 5;


//joystick values
int joy_xVal;
int joy_yVal;
int joy_button;

//other variables
int gameover = 0;

//sanke game variables
int snakeX[100] = {30};  // Snake body X coordinates
int snakeY[100] = {30};  // Snake body Y coordinates
int snakeLength = 3;     // Length of the snake
int direction = 3;       // 0=up, 1=down, 2=left, 3=right
int foodX, foodY;        // Food position
const int gridSize = 5;

//tictactoe variables
int current_player = 1;
int board[3][3]; // 0 = empty, 1 = X, 2 = O
int cursorX = 0, cursorY = 0;

//Creating instances of displays
//LiquidCrystal_I2C lcd(0x27,16,2);
TFT TFTscreen = TFT(tft_cs, tft_a0, tft_rst);

void welcome_screen() {
/*  lcd.setCursor(1,0);
  lcd.print("Insert Coin");
  lcd.setCursor(1,1);
  lcd.print("To Play");*/
  TFTscreen.background(0,0,0);
  TFTscreen.stroke(255,255,255);
  TFTscreen.text("WELCOME", 20, 55);
  int counter = milis();
  while(milis-counter<=1000){
    int ir_state = digitalRead(ir_out);
    delay(200);
    if (ir_state == LOW){
      GameSelect();
    } 
  }
  TFTscreen.background(0,0,0);
  TFTscreen.stroke(0,255,255);
  TFTscreen.text("INSERT COIN", 15, 55);
  int counter = milis();
  while(milis-counter<=1000){
    int ir_state = digitalRead(ir_out);
    delay(200);
    if (ir_state == LOW){
      GameSelect();
    } 
  }
}


//function to select game
void GameSelect() {
  int current_game = 1;
  TFTscreen.background(51,51,51);
  TFTscreen.stroke(0,255,255);
  TFTscreen.text("SELECT GAME", 15, 5);
  TFTscreen.stroke(255,255,255);
  TFTscreen.noFill();
  TFTscreen.rect(0,0,160,128);
  TFTscreen.fill(255,0,255);
  TFTscreen.rect(5,30,150,25);
  TFTscreen.fill(255,255,0);
  TFTscreen.rect(5,65,150,25);
  TFTscreen.fill(255,255,0);
  TFTscreen.rect(5,100,150,25);
  TFTscreen.stroke(255,255,255);
  TFTscreen.text("TIC TAC TOE", 10, 35);
  TFTscreen.stroke(0,255,255);
  TFTscreen.text("SNAKE", 10, 70);
  TFTscreen.stroke(0,255,255);
  TFTscreen.text("PONG", 10, 105);
  while(true){
    joy_yVal = analogRead(VRy);


    if ((current_game == 1 && joy_yVal > 550) || (current_game == 3 && joy_yVal < 450)){
      TFTscreen.background(51,51,51);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("SELECT GAME", 15, 5);
      TFTscreen.stroke(255,255,255);
      TFTscreen.noFill();
      TFTscreen.rect(0,0,160,128);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,30,150,25);
      TFTscreen.fill(255,0,255);
      TFTscreen.rect(5,65,150,25);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,100,150,25);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("TIC TAC TOE", 10, 35);
      TFTscreen.stroke(255,255,255);
      TFTscreen.text("SNAKE", 10, 70);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("PONG", 10, 105);

      current_game =2;
    }
    else if ((current_game == 2 && joy_yVal > 550) || (current_game == 1 && joy_yVal < 450)){
      TFTscreen.background(51,51,51);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("SELECT GAME", 15, 5);
      TFTscreen.stroke(255,255,255);
      TFTscreen.noFill();
      TFTscreen.rect(0,0,160,128);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,30,150,25);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,65,150,25);
      TFTscreen.fill(255,0,255);
      TFTscreen.rect(5,100,150,25);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("TIC TAC TOE", 10, 35);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("SNAKE", 10, 70);
      TFTscreen.stroke(255,255,255);
      TFTscreen.text("PONG", 10, 105);

      current_game = 3;
    }
    else if ((current_game == 3 && joy_yVal > 550) || (current_game == 2 && joy_yVal < 450)){
      TFTscreen.background(51,51,51);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("SELECT GAME", 15, 5);
      TFTscreen.stroke(255,255,255);
      TFTscreen.noFill();
      TFTscreen.rect(0,0,160,128);
      TFTscreen.fill(255,0,255);
      TFTscreen.rect(5,30,150,25);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,65,150,25);
      TFTscreen.fill(255,255,0);
      TFTscreen.rect(5,100,150,25);
      TFTscreen.stroke(255,255,255);
      TFTscreen.text("TIC TAC TOE", 10, 35);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("SNAKE", 10, 70);
      TFTscreen.stroke(0,255,255);
      TFTscreen.text("PONG", 10, 105);

      current_game = 1;
    }

    joy_button = digitalRead(sw);
    if (joy_button == LOW && current_game == 1){
      tictactoe();
    }
    else if (joy_button == LOW && current_game == 2){
      snake();
    }
    else if (joy_button == LOW && current_game == 3){
      pong();
    }

    delay(100);
  }
}

void tictactoe() {
  drawboard();
  while(!gameover){
    int joy_xVal = analogRead(VRx);
    int joy_yVal = analogRead(VRy);
  
    if (joy_xVal < 450) {
      cursorX = max(0, cursorX - 1);
      drawboard();
    } else if (joy_xVal > 550) {
      cursorX = min(2, cursorX + 1);
      drawboard();

    }

    if (joy_yVal < 450) {
      cursorY = max(0, cursorY - 1);
      drawboard();
    } else if (joy_yVal > 550) {
      cursorY = min(2, cursorY + 1);
      drawboard();
    }
    TFTscreen.stroke(0,255,255);
    TFTscreen.rect(cursorX * 43 + 17, cursorY * 43 + 1, 40, 40);
    if (digitalRead(sw) == LOW) {
      if (board[cursorX][cursorY] == 0) {
          board[cursorX][cursorY] = current_player;
          current_player = (current_player == 1) ? 2 : 1; // Switch player
        }
        drawboard();
      }
    if (checkWin()) {
      TFTscreen.rect(0, 100, 128, 28);
      String winner = (current_player == 1) ? "O Wins!" : "X Wins!";
      gameover = 1;
    } else if (isFull()) {
      TFTscreen.rect(0, 100, 128, 28);
      gameover = 1;
    }
    delay(100);
  }
  gameoverscreen();
}

void drawboard() {
  TFTscreen.background(255,255,255);
  TFTscreen.noFill();
  TFTscreen.stroke(0,0,0);
  TFTscreen.rect(16, 0, 128, 128); // Draw outer box

  // Draw board lines
  TFTscreen.line(59, 0, 59, 128); // Vertical lines
  TFTscreen.line(101, 0, 101, 128);
  TFTscreen.line(16, 43, 144, 43); // Horizontal lines
  TFTscreen.line(16, 85, 144, 85);
  
  // Draw the X and O marks
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 1) {
        TFTscreen.setTextSize(4);
        TFTscreen.stroke(0,0,255);
        TFTscreen.text("X", (((i*43)+16)+8), (j*43)+8);
        TFTscreen.setTextSize(2);
      } else if (board[i][j] == 2) {
        TFTscreen.setTextSize(4);
        TFTscreen.stroke(255,0,0);
        TFTscreen.text("O", (((i*43)+16)+8), (j*43)+8);
        TFTscreen.setTextSize(2);
      }
    }
  }
}

bool checkWin() {
  for (int i = 0; i < 3; i++) {
    // Check rows and columns
    if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) ||
        (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0)) {
      return true;
    }
  }
  // Check diagonals
  if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) ||
      (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)) {
    return true;
  }
  return false;
}

bool isFull() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

void snake() {
  TFTscreen.background(51,51,51);
  randomSeed(analogRead(0));
  foodX = (random(0, TFTscreen.width() / gridSize) * gridSize);
  foodY = (random(0, TFTscreen.height() / gridSize) * gridSize);
  while(!gameover){
    int joy_xVal = analogRead(VRx);  // Read joystick X value
    int joy_yVal = analogRead(VRy);  // Read joystick Y value

    // Map joystick values to directions
    if (joy_xVal < 450 && direction != 3) {
      direction = 2; // Left
    } else if (joy_xVal > 550 && direction != 2) {
      direction = 3; // Right
    } else if (joy_yVal < 450 && direction != 1) {
      direction = 0; // Up
    } else if (joy_yVal > 550 && direction != 0) {
      direction = 1; // Down
    }
    moveSnake();

    // Check for collisions with food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
      snakeLength++;
      foodX = (random(0, TFTscreen.width() / gridSize) * gridSize);
      foodY = (random(0, TFTscreen.height() / gridSize) * gridSize);
    }

    // Check for collisions with walls or self
    if (checkCollision()) {
      gameover = 1;
    }

    // Draw the game
    drawGame();
    delay(50);
  }
  gameoverscreen();
}

void moveSnake() {
  // Shift the snake's body positions
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the head in the current direction
  if (direction == 0) snakeY[0] -= gridSize;  // Up
  if (direction == 1) snakeY[0] += gridSize;  // Down
  if (direction == 2) snakeX[0] -= gridSize;  // Left
  if (direction == 3) snakeX[0] += gridSize;  // Right
}

void drawGame() {
  TFTscreen.background(51,51,51); // Clear the screen
  TFTscreen.noFill();
  TFTscreen.stroke(255,255,0);
  TFTscreen.rect(0,0,160,128);
  
  // Draw the snake
  TFTscreen.stroke(0,255,0);
  TFTscreen.fill(0,255,0);
  for (int i = 0; i < snakeLength; i++) {
    TFTscreen.rect(snakeX[i], snakeY[i], gridSize, gridSize);
  }

  // Draw the food
  TFTscreen.stroke(0,0,255);
  TFTscreen.fill(0,0,255);
  TFTscreen.rect(foodX, foodY, gridSize, gridSize);
}

bool checkCollision() {
  // Check if snake hits the walls
  if (snakeX[0] < 0 || snakeX[0] >= TFTscreen.width() || snakeY[0] < 0 || snakeY[0] >= TFTscreen.height()) {
    return true;
  }

  // Check if snake collides with itself
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      return true;
    }
  }

  return false;
}


void pong() {
  int paddle_x=80;
  int paddle_y=115;
  int ball_direction_x = 3;
  int ball_direction_y = 3;
  int ball_x=80;
  int ball_y=64;
  TFTscreen.background(51,51,51);
  TFTscreen.fill(255,255,255);
  TFTscreen.stroke(255,255,255);
  while(!gameover){
    long int t1 = millis();
    joy_xVal = analogRead(VRx);
    TFTscreen.background(51,51,51);
    TFTscreen.rect(paddle_x,paddle_y,20,5);
    TFTscreen.circle(ball_x,ball_y,5);
    if (joy_xVal > 550 && paddle_x < 140){
      paddle_x = paddle_x + 5;
    }
    else if (joy_xVal < 450 && paddle_x > 20){
      paddle_x = paddle_x - 5;
    }

    if (ball_y < 5) {

    ball_direction_y = -ball_direction_y;
    
    }
  

    if (ball_x > (TFTscreen.width() - 5) || ball_x < 5 ) {

      ball_direction_x = -ball_direction_x;

    }

    if ((ball_x >= paddle_x && ball_x <= (paddle_x + 20)) && ((ball_y + 5)  >= paddle_y && (ball_y+5) <= (paddle_y + 5))) {
    
      ball_direction_y = -ball_direction_y;
  
    }

    if (ball_y > (TFTscreen.height() - 5)){
      gameover = 1;
    }

    ball_x += ball_direction_x;

    ball_y += ball_direction_y;
    long int t2 = millis();
    Serial.println(t2-t1);

  }
  gameoverscreen();
}

void gameoverscreen() {
  TFTscreen.background(0,0,0);
  TFTscreen.stroke(0,0,255);
  TFTscreen.text("GAMEOVER",20,55);
  delay(5000);
  reset();
}

//function to reset all things
void reset(){
  digitalWrite(reset_arduino,LOW);
}


void setup() {
  digitalWrite(reset_arduino,HIGH);
  delay(200);

  Serial.begin(9600);

  pinMode(reset_arduino,OUTPUT);
  pinMode(ir_out,INPUT);
  pinMode(VRx,INPUT);
  pinMode(VRy,INPUT);
  pinMode(sw,INPUT_PULLUP);

  //lcd.begin();
  //lcd.backlight();
  TFTscreen.begin();
  TFTscreen.setTextSize(2);
}


void loop() {
  int ir_state = digitalRead(ir_out);
  delay(200);
  if (ir_state == LOW){
    GameSelect();
  } 
  else {
    welcome_screen();
  }
}


/*colour scheme
backgrounds
primary background 0 0 0 black
playarea background 2 51 51 51 dark grey


Neon Pink: Use for enemies or items that stand out or need to feel dynamic 255 0 255
Neon Blue: This could be your player character or key interactive objects 0 255 255
Electric Green: Power-ups, bonus items, or other special interactive elements 0 255 0
Bright Yellow: High-value targets, score counters, or important alerts like Game Over 255 255 0

Text
white and yellow

buttons
Use Neon Blue for buttons that are neutral or non-dangerous (like "Start" or "Select"), and Electric Green for positive actions (like "Play" or "Confirm").
Menu Buttons: Buttons for “Start,” “Options,” etc., should use Neon Blue or Electric Green for a glowing, engaging effect.
Highlighted Buttons: When a button is selected or active, you can highlight it with Neon Pink or Bright Yellow to indicate the user's selection.

border and framing
Border Around Game Area: Consider a thin Neon Blue border around the game field to give the whole screen a glowing look.
Frame for Menus or Scores: Use Neon Pink for extra emphasis on sections that need to stand out like score displays or special notifications.





*/