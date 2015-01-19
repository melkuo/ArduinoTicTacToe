// Tic Tac Toe
// Melody Kuo, Madeleine Ewins, Juliet Liu
// Due Thursday July 25, 2013
#include <LiquidCrystal.h>
#include <Arduino.h> 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean first = true;
boolean time_limit_reached = false;
int player = 1; //1="x", 2="o"
int p1=0, p2=0, p3=0, p4=0, p5=0, p6=0, p7=0, p8=0, p9=0;  //0=off, 1=x, 2=o
int cursor_position = 0; // the position on board that user selected
int x = 0; // variable to store voltage value when a key is pressed
float time_limit = 10;
float start_time = 0;
float end_time = 0;
float duration = 0; // end_time - start_time

void setup()
{
  first = true;
  lcd.begin(16,2);
  Serial.begin(9600);
}

// ~*~*~*~*~* MAIN PROGRAM *~*~*~*~*~
void loop()
{
  // Print board with instructions if first time, else print board with x/o's
  if (first == true) {
    // Print instructions
    Serial.println("Let's play Tic Tac Toe in 54 Seconds or Less!");
    Serial.println("Use the up and down buttons to choose the position.");
    Serial.println("Press select to make your move.");
    Serial.println("But, be aware, if you take longer than 6 seconds to make your move, you lose your turn!");
    Serial.println(" ");
    
    // Print to LCD
    lcd.setCursor(2,0);
    lcd.print("Tic     Toe");
    lcd.setCursor(6,1);
    lcd.print("Tac"); 
    
    // Print board with numbers representing positions
    Serial.println("1|2|3");
    Serial.println("- - -");
    Serial.println("4|5|6");
    Serial.println("- - -");
    Serial.println("7|8|9");
    Serial.println(" ");
    
    // Display title message for 3 seconds
    delay(3000);
    lcd.clear();
    
    // Countdown before game starts
    for (int i = 3; i>0; i--) {
      lcd.setCursor(3,0);
      lcd.print("Starting in");
      lcd.setCursor(8,1);
      lcd.print(i);
      delay(1000);
    }
    
    // Clear the screen
    lcd.clear();
    
    // Print empty board to lcd
    Serial.println("Let's play!");
    print_board_lcd();
    print_board();
    
    first = false;
  } else if (first == false){  
    print_board();
    print_board_lcd();
  }
  
  // Reset time limit reached
  time_limit_reached = false;
      
  // If the player takes too long to choose, it becomes the other player's turn
  while (time_limit_reached == false) {
    start_time = millis(); // Start counting when it's the player's turn  
    cursor_position = select();
    delay(100);
    lcd.setCursor(4,1);  // Clear second row so "Space taken" goes away
    lcd.print("            ");
    end_time = millis(); // Stop counting when the player has selected
    
    duration = (end_time-start_time)/1000.0;
    if(duration > time_limit){
      // If no one has played yet, display an empty board
      if (p1==0 && p2==0 && p3==0 && p4==0 && p5==0 && p6==0 && p7==0 && p8==0 && p9==0){
        print_board();
      }  
      
      Serial.print("You took ");
      Serial.print(duration);
      Serial.println(" seconds. Too long. Pass the controller over.");
      
      // Display message on LCD
      for (int i = 0; i < 3; i++){
        lcd.setCursor(4,1);
        lcd.print("Pass Arduino");
        delay(500);
        lcd.setCursor(4,1);
        lcd.print("            ");
        delay(500);
      } 
      change_player();
    } else {
      time_limit_reached = true;
    }
  }
  
  // Set the variable to "player" if selected by select()
  switch (cursor_position) {
      case 1:
        p1 = check_space(p1);
        break;
      case 2:
        p2 = check_space(p2);
        break;
      case 3:
        p3 = check_space(p3);
        break;
      case 4:
        p4 = check_space(p4);
        break;
      case 5:
        p5 = check_space(p5);
        break;
      case 6:
        p6 = check_space(p6);
        break;
      case 7:
        p7 = check_space(p7);
        break;
      case 8:
        p8 = check_space(p8);
        break;
      case 9:
        p9 = check_space(p9);
        break;
      default:
        break;  
    }
    
  // Check if someone won
  if ((p1==1&&p2==1&&p3==1) || (p4==1&&p5==1&&p6==1) || (p7==1&&p8==1&&p9==1) || (p1==1&&p4==1&&p7==1) || (p2==1&&p5==1&&p8==1) || (p3==1&&p6==1&&p9==1) || (p1==1&&p5==1&&p9==1) || (p3==1&&p5==1&&p7==1)){
    print_board();
    print_board_lcd();
    lcd.setCursor(4,1);
    lcd.print("X has won!  ");
    Serial.println("X has won!");
    Serial.println(" ");
    Serial.println(" ");
    delay(5000);
    reset();
  } else if ((p1==2&&p2==2&&p3==2) || (p4==2&&p5==2&&p6==2) || (p7==2&&p8==2&&p9==2) || (p1==2&&p4==2&&p7==2) || (p2==2&&p5==2&&p8==2) || (p3==2&&p6==2&&p9==2) || (p1==2&&p5==2&&p9==2) || (p3==2&&p5==2&&p7==2)){
    print_board();
    print_board_lcd();
    lcd.setCursor(4,1);
    lcd.print("O has won!  ");
    Serial.println("O has won!");
    Serial.println(" ");
    Serial.println(" ");
    delay(5000);
    reset(); 
  }
  
  // Check if it is a tie when the board has been filled
  if (p1!=0 && p2!=0 && p3!=0 && p4!=0 && p5!=0 && p6!=0 && p7!=0 && p8!=0 && p9!=0) {
    print_board();
    print_board_lcd();
    lcd.setCursor(5,0);
    lcd.print("It's a tie! ");
    Serial.println("It's a tie!");
    Serial.println(" ");
    Serial.println(" ");
    delay(5000);
    reset();
  }
  
  // Change players
  change_player();
}



// ~*~*~*~*~*~*~FUNCTIONZ******************~*********~********~********~*******~*******~*********~*******~********~*********~****~*********
// Select number 1 through 9
int select() 
{
  int counter = 1;
  boolean cont = true;
  
  while (cont==true) {
    x = analogRead(0);
    
    if (x < 100){ // Right button
    } else if (x < 200 && counter == 9) { // Up button & counter = 9, counter resets to 1
      counter = 1; 
    } else if (x < 200) { // Up button & counter != 9
      counter = counter + 1; 
    } else if (x < 400 && counter == 1) { //Down button & counter = 1, counter goes to 9
      counter = 9; 
    } else if (x < 400) { // Down button & counter != 1
      counter = counter - 1; 
    } else if (x < 600) { //Left button
    } else if (x < 800) { //Select button
      cont = false;
    }
    
    // LCD COUNTER CODE BELOW
    lcd.setCursor(5, 0);
    lcd.print(counter);
    
    if (player == 1){
      lcd.setCursor(7,0);
      lcd.print("You are X");
    } else if (player == 2){
      lcd.setCursor(7,0);
      lcd.print("You are O");
    }
    
    delay(150);
  }  
  return counter;
}

// Prints board with x's and o's to serial monitor
void print_board() {
  // First row
  print_p(p1);
  Serial.print("|");
  print_p(p2);
  Serial.print("|");
  print_p(p3);
  Serial.println(" ");
  
  Serial.println("- - -");
  
  // Second row
  print_p(p4);
  Serial.print("|");
  print_p(p5);
  Serial.print("|");
  print_p(p6);
  Serial.println(" ");
  
  Serial.println ("- - -");
  
  // Third row
  print_p(p7);
  Serial.print("|");
  print_p(p8);
  Serial.print("|");
  print_p(p9);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
}

// Prints x, o or empty space
void print_p(int p) {
  if(p == 0){
    Serial.print(" ");
  }
  else if(p == 1){
    Serial.print("x");
  }
  else if(p == 2) {
    Serial.print("o");
  }
}

// Print board to lcd display
void print_board_lcd() {  
  // Initialize empty grid
  byte loc1[8] = {B00001, B00001, B00001, B00001, B00001, B11111, B00001, B00001};
  byte loc2[8] = {B00000, B00000, B00000, B00000, B00000, B11111, B00000, B00000};
  byte loc3[8] = {B10000, B10000, B10000, B10000, B10000, B11111, B10000, B10000};
  byte loc4[8] = {B00001, B00001, B00001, B11111, B00001, B00001, B00001, B00001};
  byte loc5[8] = {B00000, B00000, B00000, B11111, B00000, B00000, B00000, B00000};
  byte loc6[8] = {B10000, B10000, B10000, B11111, B10000, B10000, B10000, B10000};
  
  // Initialize x/o on board based on values of p
  if (p1 == 0) {
  } else if (p1 == 1) {
      //byte loc1[8] = {B00001, B10101, B01001, B10101, B00001, B11111, B00001, B00001};
      loc1[1] = B10101;
      loc1[2] = B01001;
      loc1[3] = B10101;
  } else if (p1 == 2) {
      loc1[1] = B11101;
      loc1[2] = B10101;
      loc1[3] = B11101;
  }
  
  if (p2 == 0) {
  } else if (p2 == 1) {
      loc2[1] = B01010;
      loc2[2] = B00100;
      loc2[3] = B01010;
  } else if (p2 == 2) {
      loc2[1] = B01110;
      loc2[2] = B01010;
      loc2[3] = B01110;
  }
  
  if (p3 == 0) {
  } else if (p3 == 1) {
      loc3[1] = B10101;
      loc3[2] = B10010;
      loc3[3] = B10101;
  } else if (p3 == 2) {
      loc3[1] = B10111;
      loc3[2] = B10101;
      loc3[3] = B10111;
  }
  
  if (p4 == 0) {
  } else if (p4 == 1) {
      loc1[7] = B10101;
      loc4[0] = B01001;
      loc4[1] = B10101;
  } else if (p4 == 2) {
      loc1[7] = B11101;
      loc4[0] = B10101;
      loc4[1] = B11101;
  }
  
  if (p5 == 0) {
  } else if (p5 == 1) {
      loc2[7] = B01010;
      loc5[0] = B00100;
      loc5[1] = B01010;
  } else if (p5 == 2) {
      loc2[7] = B01110;
      loc5[0] = B01010;
      loc5[1] = B01110; 
  }  
  
  if (p6 == 0) {
  } else if (p6 == 1) {
      loc3[7] = B10101;
      loc6[0] = B10010;
      loc6[1] = B10101;
  } else if (p6 == 2) {
      loc3[7] = B10111;
      loc6[0] = B10101;
      loc6[1] = B10111;
  }
  
  if (p7 == 0) {
  } else if (p7 == 1) {
      loc4[5] = B10101;
      loc4[6] = B01001;
      loc4[7] = B10101;
  } else if (p7 == 2) {
      loc4[5] = B11101;
      loc4[6] = B10101;
      loc4[7] = B11101;
  }
  
  if (p8 == 0) {
  } else if (p8 == 1) {
      loc5[5] = B01010;
      loc5[6] = B00100;
      loc5[7] = B01010;
  } else if (p8 == 2) {
      loc5[5] = B01110;
      loc5[6] = B01010;
      loc5[7] = B01110;
  }
  
  if (p9 == 0) {
  } else if (p9 == 1) {
      loc6[5] = B10101;
      loc6[6] = B10010;
      loc6[7] = B10101;
  } else if (p9 == 2) {
      loc6[5] = B10111;
      loc6[6] = B10101;
      loc6[7] = B10111;
  }
  
  lcd.createChar(0, loc1);
  lcd.createChar(1, loc2);
  lcd.createChar(2, loc3);
  lcd.createChar(3, loc4);
  lcd.createChar(4, loc5);
  lcd.createChar(5, loc6);
  
  // Print the left column
  //Serial.println(loc1);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));       // loc1
  
  //Serial.println(loc2);
  lcd.setCursor(1, 0);
  lcd.write(byte(1));       // loc2
  
  // Print the middle column
  //Serial.println(loc3);
  lcd.setCursor(2, 0);
  lcd.write(byte(2));       // loc3
  
  //Serial.println(loc4);
  lcd.setCursor(0, 1);
  lcd.write(byte(3));       // loc4
  
  // Print the right column
  //Serial.println(loc5);
  lcd.setCursor(1, 1);
  lcd.write(byte(4));       // loc5 
  
  //Serial.println(loc6); 
  lcd.setCursor(2, 1);
  lcd.write(byte(5));       // loc6
}

// Check if space already taken   
int check_space(int p){
  if (p == 1 || p == 2) {
     Serial.println("Space already taken");
     lcd.setCursor(4,1);
     lcd.print("Space taken");
     change_player();
  } else {
    p = player;
  }
  return p;
}

// Change player
void change_player () {
  if (player == 1){
    player = 2;
  } else if (player == 2){
    player = 1;
  }  
}

// Game over, clear all values off serial monitor and lcd board
void reset () {
  p1=0, p2=0, p3=0, p4=0, p5=0, p6=0, p7=0, p8=0, p9=0;
  first = true;
  player = 2;
  lcd.clear();
}
