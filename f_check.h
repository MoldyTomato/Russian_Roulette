#include "f_gamevariants.h"
typedef void (*functions)(void);
functions Trigger_e[]={
  Trigger_e_0,
  Trigger_e_1,
  Trigger_e_2,
  Trigger_e_3,
  Trigger_e_4,
  Trigger_e_5,
  Trigger_e_6,
  Trigger_e_7,
  Trigger_e_8,
};
//checks the different conditions and calls the correct functions of the variants; variant 8 is a bit messy because it has special draw calls
void check() {
  bool update_Display=0; //to track if we need to update the display, to reduce draw calls
  
  //Spin
  int b_Spin = SpinButton.ButtonStateChange();
  int j_Spin = SpinInput.state();
  //check if jack or button is high
  if (b_Spin == 1 || j_Spin == 1) { //button pressed or jack went high
    Spin_s_0();
    update_Display=1;
  }  
  //if button is released and jack is low or vice versa  or both are released at the same time, clear the icon
  else if ((b_Spin == -1 && j_Spin == -2) || (j_Spin == -1 && b_Spin == -2) || (j_Spin == -1 && b_Spin == -1)) {
    Spin_e_0();
    if(GAME_VARIANT==8)
      updateChamberIndex_Unknown();
    update_Display=1;
  }
  
  //Step
  int j_Step = StepInput.state();
  if (j_Step == 1) { //pressed
    Step_s_0();
    update_Display=1;
  }
  else if (j_Step == -1) { //released
    Step_e_0();
    if(GAME_VARIANT==8)
      updateChamberIndex_Unknown();
    update_Display=1;
  }
  //TRIGGER
  int b_Trigger = TriggerButton.ButtonStateChange();
  int j_Trigger = TriggerInput.state();
  if (b_Trigger == 1 || j_Trigger == 1) { //pressed
    if(GAME_VARIANT==8)
      Trigger_s_8();
    else
      Trigger_s_0();
    update_Display=1;
  }
  else if ((b_Trigger == -1 && j_Trigger == -2) || (j_Trigger == -1 && b_Trigger == -2) || (j_Trigger == -1 && b_Trigger == -1)) { //released
    Trigger_e[GAME_VARIANT]();
    update_Display=1;
  }
  
  //Insert
  int b_Insert = InsertBulletButton.ButtonStateChange();
  int j_Insert = InsertInput.state();
  if (b_Insert == 1 || j_Insert == 1) {//pressed
    if(GAME_VARIANT!=8){
      Insert_0();
      update_Display=1;
    }
  }
  
  //AddChamber
  int b_AddChamber = AddChamberButton.ButtonStateChange();
  int j_AddChamber = AddInput.state();
  if (b_AddChamber == 1 || j_AddChamber == 1) {//pressed
    Add_0();
    if(GAME_VARIANT==8)
      updateChamberIndex_Unknown();
    update_Display=1;
  }
  if(update_Display==1){
    display.display();
  }
}
