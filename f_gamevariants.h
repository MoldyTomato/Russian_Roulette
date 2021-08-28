/*VARIANT 0: MANUAL*/
/////////////////////
//trigger is pressed
void Trigger_s_0() {
  fillTriggerTriangle();
  //if bullet present: Hit->High else Miss: High
  if (CHAMBERS[currentChamber] == 1) {
    drawHitIcon();
    digitalWrite(OUT_HIT, HIGH);
  } else {
    drawMissIcon();
    digitalWrite(OUT_MISS, HIGH);
  }
}
//trigger released
void Trigger_e_0() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  CHAMBERS[currentChamber] = 0;
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}
//spin pressed
void Spin_s_0() {
  drawSpinIcon();
  spinImage();
  updateChamberIndex_Unknown();
  currentChamber = random(0, NUMOFCHAMBERS); //upperbound is exclusive
}
//spin released
void Spin_e_0() {
  clearSpinIcon();
  updateChamberIndex();
  drawCylinderIntoBuffer();
}
//insert, no press/release logic
void Insert_0() {
  CHAMBERS[currentChamber] = !CHAMBERS[currentChamber];//invert content of current chamber
  drawCylinderIntoBuffer();
}
//step pressed
void Step_s_0() {
  drawStepIcon();
  currentChamber = (currentChamber + 1) % NUMOFCHAMBERS;
  updateChamberIndex();
  drawCylinderIntoBuffer();
}
//step released
void Step_e_0() {
  clearStepIcon();
}
//AddChamber, no press/release logic
void Add_0() {
  NUMOFCHAMBERS = (NUMOFCHAMBERS == 12) ? 2 : NUMOFCHAMBERS + 1;
  currentChamber = (currentChamber > NUMOFCHAMBERS) ? 0 : currentChamber;
  updateChamberIndex();
  drawCylinderIntoBuffer();
}

//////////////////////
/*VARIANT 1: VANILLA*/
//////////////////////
//Trigger released differs
void Trigger_e_1() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  //last bullet is in this chamber
  if(countRemainingBullets()==1 && CHAMBERS[currentChamber]==1){
    //no removal and spin
    currentChamber = random(0,NUMOFCHAMBERS);
    spinImage();
    updateChamberIndex_Unknown();
    display.display();
  }
  else{
    CHAMBERS[currentChamber] = 0;
    currentChamber = (currentChamber+1+NUMOFCHAMBERS)%NUMOFCHAMBERS;
  }
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

/////////////////////////////////
/*VARIANT 2: VANILLA NO REMOVAL*/
/////////////////////////////////
//Trigger released differs
void Trigger_e_2() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  currentChamber = (currentChamber+1+NUMOFCHAMBERS)%NUMOFCHAMBERS;
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

//////////////////////////////
/* VARIANT 3: VANILLA RESPIN*/
//////////////////////////////
//Trigger released differs
void Trigger_e_3() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  //last bullet is in this chamber
  if (countRemainingBullets() != 1) {
    CHAMBERS[currentChamber] = 0;
  }
  //no removal and spin
  currentChamber = random(0, NUMOFCHAMBERS);
  spinImage();
  updateChamberIndex_Unknown();
  display.display();
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

////////////////////////////////////////
/*VARIANT 4: VANILLA RESPIN NO REMOVAL*/
////////////////////////////////////////
//Trigger released differs
void Trigger_e_4() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  //no removal and spin
  currentChamber = random(0, NUMOFCHAMBERS);
  spinImage();
  updateChamberIndex_Unknown();
  display.display();
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

/////////////////////
/*VARIANT 5: INVERT*/
/////////////////////
//Trigger released differs
void Trigger_e_5() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  CHAMBERS[currentChamber] = !CHAMBERS[currentChamber];
  currentChamber = (currentChamber+1+NUMOFCHAMBERS)%NUMOFCHAMBERS;
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

////////////////////////////
/*VARIANT 6: INVERT RESPIN*/
////////////////////////////
//Trigger released differs
void Trigger_e_6() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  CHAMBERS[currentChamber] = !CHAMBERS[currentChamber];
  currentChamber = random(0,NUMOFCHAMBERS);
  updateChamberIndex_Unknown();
  spinImage();
  display.display();
  updateChamberIndex();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
}

/////////////////////
/*VARIANT 7: RANDOM*/
/////////////////////
//Trigger released differs
void Trigger_e_7() {
  int m_num = random(0,7);
  switch(m_num){
    case 0:Trigger_e_0();break;
    case 1:Trigger_e_1();break;
    case 2:Trigger_e_2();break;
    case 3:Trigger_e_3();break;
    case 4:Trigger_e_4();break;
    case 5:Trigger_e_5();break;
    case 6:Trigger_e_6();break;
  }
}

////////////////////////////
/*VARIANT 8: OUTPUT GALORE*/
////////////////////////////
//Trigger pressed differs
void Trigger_s_8() {
  fillTriggerTriangle();
  //if bullet present: Hit->High else Miss: High
  drawHitIcon();
  digitalWrite(OUT_HIT, HIGH);
  drawMissIcon();
  digitalWrite(OUT_MISS, HIGH);
  updateChamberIndex_Unknown();
}
//Trigger released differs
void Trigger_e_8() {
  //remove bullet and set outs to low
  digitalWrite(OUT_MISS, LOW);
  clearMissIcon();
  digitalWrite(OUT_HIT, LOW);
  clearHitIcon();
  drawCylinderIntoBuffer();
  drawTriggerTriangle();
  updateChamberIndex_Unknown();
}
