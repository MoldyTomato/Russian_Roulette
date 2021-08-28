#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino LEONARDO/Micro:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(128,64, &Wire, OLED_RESET);//Everything in this sketch is for 128x64 pixel displays
//functions for the encoder
#include "f_rotaryencoder.h"
//class for pushbuttons
#include "PushButton.h"
PushButton EncoderButton(10);
PushButton AddChamberButton(13);
PushButton InsertBulletButton(9);
PushButton SpinButton(8);
PushButton TriggerButton(7);
//class for trigger/gate inputs
#include "JackInput.h"
JackInput StepInput(A0);
JackInput TriggerInput(A3);
JackInput SpinInput(A4);
JackInput InsertInput(A5);
JackInput AddInput(6);
//outputs
#define OUT_MISS A1
#define OUT_HIT A2
//text for different variants
#include "v_variantdescriptions.h"
//function for displaying modulename
#include "f_modulename.h"

//some variables
int NUMOFCHAMBERS = 6; //amount of chamber whith which the module starts, range is [2,12]
int CHAMBERS[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //initial chamber fills, 1=full, 0=empty
int currentRotationAngle = 0; //just to track the current rotation
int currentChamber = 0; //chamber to start with
int MODE = 1; //Mode to start with, 1 means we are in the normal playmode, 0 means we are in the menu mode
int GAME_VARIANT = 0; //1 is the normal vanilla russian roulette
int game_variant_current = 0; //to track the shown gamevariant

/* Draws some circles in the middle of the screen to imitate a spinning motion */
void spinImage() {
  clearCenterArea();
  for (int i = 31; i > 0;) {
    display.drawCircle(64, 32, i, SSD1306_WHITE);
    i -= random(3, 8);
  }
}
/* draws the whole revolvercylinder into buffer */
//>parts could be precalculated if space is needed
void drawCylinderIntoBuffer() {
  clearCenterArea();
  int degree = (360 / NUMOFCHAMBERS) * currentChamber * (-1);
  int radius_centercircle = 0; //the inner connecting circle
  int radius_outerchambers = 0; //the outerchambers
  int radius_centerdistance = 0; //distance of the chambers to center
  int radius_chamber = 0; //inner chamber radius
  switch (NUMOFCHAMBERS) {
    case 2: radius_centercircle = 10; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 8; break;
    case 3: radius_centercircle = 13; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 8; break;
    case 4: radius_centercircle = 19; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 8; break;
    case 5: radius_centercircle = 22; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 8; break;
    case 6: radius_centercircle = 26; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 8; break;
    case 7: radius_centercircle = 26; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 7; break;
    case 8: radius_centercircle = 28; radius_outerchambers = 12; radius_centerdistance = 19; radius_chamber = 7; break;
    case 9: radius_centercircle = 28; radius_outerchambers = 11; radius_centerdistance = 19; radius_chamber = 6; break;
    case 10: radius_centercircle = 28; radius_outerchambers = 10; radius_centerdistance = 20; radius_chamber = 5; break;
    case 11: radius_centercircle = 29; radius_outerchambers = 10; radius_centerdistance = 21; radius_chamber = 5; break;
    case 12: radius_centercircle = 30; radius_outerchambers = 10; radius_centerdistance = 21; radius_chamber = 5; break;
  }
  //draw inner connecting circle
  display.drawCircle(64, 32, radius_centercircle, SSD1306_WHITE);
  //draw the outerchambers
  for (int i = 0; i < NUMOFCHAMBERS; i++) {
    int angle = 360 / NUMOFCHAMBERS * i + 90 + degree;
    display.drawCircle(64 + sin(angle * PI / 180)*radius_centerdistance, 32 + cos(angle * PI / 180)*radius_centerdistance, radius_outerchambers, SSD1306_WHITE);
    display.fillCircle(64 + sin(angle * PI / 180)*radius_centerdistance, 32 + cos(angle * PI / 180)*radius_centerdistance, radius_outerchambers - 1, SSD1306_BLACK);
  }
  //clear the inside of inner connecting circle
  display.fillCircle(64, 32, radius_centercircle - 1, SSD1306_BLACK);

  //draw the chambers
  for (int i = 0; i < NUMOFCHAMBERS; i++) {
    int angle = 360 / NUMOFCHAMBERS * i + 90 + degree;
    display.drawCircle(64 + sin(angle * PI / 180)*radius_centerdistance, 32 + cos(angle * PI / 180)*radius_centerdistance, radius_chamber, SSD1306_WHITE);
    //draw '?' in each of the chambers
    if(GAME_VARIANT==8){
      display.setCursor((64 + sin(angle * PI / 180)*radius_centerdistance)-2,(32 + cos(angle * PI / 180)*radius_centerdistance)-3);
      display.write("?");
    }
    //if chamber is full, fill it
    if (CHAMBERS[i] == 1 && GAME_VARIANT!=8) {
      display.fillCircle(64 + sin(angle * PI / 180)*radius_centerdistance, 32 + cos(angle * PI / 180)*radius_centerdistance, radius_chamber, SSD1306_WHITE);
    }
  }
  //draw centercross
  display.drawLine(58, 32, 70, 32, SSD1306_WHITE);
  display.drawLine(64, 26, 64, 38, SSD1306_WHITE);
}
/*clear the center area, where the cylinder of the revolver is displayed*/
void clearCenterArea() {
  display.fillCircle(64, 32, 33, SSD1306_BLACK);
}
/* fills the triangle, which indicates the current chamber used to indicate the presence of a trigger */
void fillTriggerTriangle() {
  display.fillTriangle(98, 32, 108, 42, 108, 22, SSD1306_WHITE);
}
/* draws the triangle which indicates the current chamber */
void drawTriggerTriangle() {
  display.fillTriangle(98, 32, 108, 42, 108, 22, SSD1306_BLACK);
  display.drawTriangle(98, 32, 108, 42, 108, 22, SSD1306_WHITE);
}
/* draws the Icon which indicates a empty chamber is triggered (bottom right) */
void drawMissIcon() {
  //draw the >
  display.drawLine(108, 64, 127, 54, SSD1306_WHITE);
  display.drawLine(110, 64, 127, 55, SSD1306_WHITE);
  display.drawLine(127, 54, 108, 44, SSD1306_WHITE);
  display.drawLine(127, 55, 108, 45, SSD1306_WHITE);
  //draw the end of the arrow
  display.fillTriangle(108, 44, 118, 44, 113, 54, SSD1306_WHITE);
}
/* clears the area where the miss icon is drawn */
void clearMissIcon() {
  display.fillRect(108, 44, 20, 20, SSD1306_BLACK);
}
/* draws the icon which indicates a full chamber is triggered looks like hitmarker (top right) */
void drawHitIcon() {
  //draw a X
  display.drawLine(108, 0, 128, 20, SSD1306_WHITE);
  display.drawLine(109, 0, 128, 19, SSD1306_WHITE);
  display.drawLine(108, 1, 126, 19, SSD1306_WHITE);
  display.drawLine(108, 19, 127, 0, SSD1306_WHITE);
  display.drawLine(108, 18, 126, 0, SSD1306_WHITE);
  display.drawLine(109, 19, 127, 1, SSD1306_WHITE);
  //erase the center of the X
  display.fillCircle(118, 10, 5, SSD1306_BLACK);
}
/* clears the area where the hit icon is drawn (top right) */
void clearHitIcon() {
  display.fillRect(108, 0, 20, 20, SSD1306_BLACK);
}
/* draws a spinning arrow during the spinning action (bottom left) */
void drawSpinIcon() {
  display.fillRect(0, 43, 21, 21, SSD1306_BLACK);
  display.drawCircle(10, 54, 5, SSD1306_WHITE);
  display.drawCircle(10, 54, 6, SSD1306_WHITE);
  display.fillTriangle(6, 49, 12, 49, 12, 53, SSD1306_WHITE);
}
/* clears the area where the spinning icon is drawn (bottom left) */
void clearSpinIcon() {
  display.fillRect(0, 43, 21, 21, SSD1306_BLACK);
}
/* displays a '?' right of the triggertriangle, used during the spinning action */
void updateChamberIndex_Unknown() {
  display.fillRect(109, 23, 20, 20, SSD1306_BLACK);
  //display.setTextSize(1);
  //display.setTextColor(SSD1306_WHITE);
  display.setCursor(112, 29);
  display.print("?");
}
/* displays the number of the chamber, right of the triggertriangle */
void updateChamberIndex() {
  display.fillRect(109, 23, 20, 20, SSD1306_BLACK);
  //display.setTextSize(1);
  //display.setTextColor(SSD1306_WHITE);
  display.setCursor(112, 29);
  display.print((currentChamber + 1)); //chambers are 0-based
}
/* displays the current game variant */
void updateGameVariantNumber() {
  display.fillRect(0, 23, 20, 20, SSD1306_BLACK);
  //display.setTextSize(1);
  //display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 29);
  display.print("#"); display.print(GAME_VARIANT);
}
/* draws a arrow to indicate a rotationstep (top left) */
void drawStepIcon() {
  display.drawLine(0, 9, 10, 9, SSD1306_WHITE);
  display.drawLine(0, 10, 10, 10, SSD1306_WHITE);
  display.drawLine(10, 10, 10, 15, SSD1306_WHITE);
  display.drawLine(9, 10, 9, 15, SSD1306_WHITE);
  display.fillTriangle(9, 15, 7, 12, 12, 12, SSD1306_WHITE);
}
/* clears the area where the step icon is drawn (top left) */
void clearStepIcon() {
  display.fillRect(0, 0, 20, 20, SSD1306_BLACK);
}
/*returns the amount of bullets in the cylinder*/
int countRemainingBullets() {
  int bullets = 0;
  for (int i = 0; i < NUMOFCHAMBERS; i++) {
    bullets += CHAMBERS[i];
  }
  return bullets;
}



/* shows the camevariants flavourtexts, and back screens */
void showGameVariants() {
  //maybe we can put these also into the gamevariants.h file
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  game_variant_current = (game_variant_current < -1) ? -1 : game_variant_current;
  display.print("ROULETTE #"); display.println(game_variant_current);

  if (game_variant_current < 0 || game_variant_current > 8) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(25, 20);
    display.println("Back");
  } else {
    display.println(desc_variants[game_variant_current]);
  }
}

//include the main check-function, which checks the conditions and calls the according functions of the variants 
#include "f_check.h"

void setup() {
  //Setup Serial
  //Serial.begin(9600);
  //Setup Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  //outputs
  pinMode(OUT_HIT, OUTPUT);
  pinMode(OUT_MISS, OUTPUT);
  //Encoder
  RotaryEncoder_init();
  //seed random
  pinMode(A6, INPUT);
  randomSeed(analogRead(A6)); //unconnected pin!!! 
  //display the module name
  displayModuleName();
  //clear the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  drawCylinderIntoBuffer(); //draw the cylinder with the correct amount of chambers
  drawTriggerTriangle(); //draw the trigger triangle
  updateGameVariantNumber(); //draw game variant number
  updateChamberIndex(); //draw the index of the current chamber
  display.display();
}

//loop function
void loop() {
  //handle the menu mode
  if (MODE == 0) {
    //handle the encoder buttonpress
    if (EncoderButton.ButtonStateChange() == 1) { //encoder pressed
      //assign the new Variant
      if (game_variant_current >= 0 && game_variant_current <= 8) { //only assign valid cases
        GAME_VARIANT = game_variant_current;
      }
      MODE = 1; //change back to playmode
      display.clearDisplay();
      display.setTextSize(1);
      clearCenterArea();
      drawCylinderIntoBuffer();
      drawTriggerTriangle();
      updateGameVariantNumber();
      if(GAME_VARIANT==8){
        updateChamberIndex_Unknown();
      }
      else{
        updateChamberIndex();
      }
      display.display();
      return; //we can return now!
    }
    //handle the Encoderrotation
    int d_Encoder = Encoder_getDirection();
    if (d_Encoder == 1) {
      game_variant_current++;
      showGameVariants();
      display.display();
      return; //return after increas
    } else if (d_Encoder == -1) {
      //clamp the value [-1,8]
      if (game_variant_current > 8)
        game_variant_current = 8;
      else
        game_variant_current = (game_variant_current < -1) ? -1 : game_variant_current - 1;
      showGameVariants();
      display.display();
      return; //return after decrease
    }
    return;
  }
  //playmode
  //handle encoder button
  if (EncoderButton.ButtonStateChange() == 1) { //encoder pressed
    MODE = 0;
    display.clearDisplay();
    game_variant_current = GAME_VARIANT;
    showGameVariants();
    display.display();
    return; //playmode not available, so return
  }
  //handle the Encoderrotation
  int d_Encoder = Encoder_getDirection();
  if (d_Encoder != 0) {
    currentChamber = (currentChamber + NUMOFCHAMBERS + d_Encoder) % NUMOFCHAMBERS;
    //Serial.println(d_Encoder);
    if(GAME_VARIANT==8){
      updateChamberIndex_Unknown();
    }
    else{
      updateChamberIndex();
    }
    drawCylinderIntoBuffer();
    display.display();
  }
  check(); //check() handles the different variants for us
}
