# Russian_Roulette (Eurorack Trigger/Gate-Module Arduino Micro) 

![finished_module](https://github.com/MoldyTomato/Russian_Roulette/blob/main/module_finished.jpg)

## Description

This module tries to emulate a game known as \"Russian
Roulette\" in which players take alternating turns shooting
themselves in the head or at least attempting to do so.

## Simple Manual

### Inputs/Buttons:

Behaviour may change depending on selected variant!  
**Step:** advances the cylinder clockwise by one chamber.  
As long as voltage is present on the input a symbol is shown on the top left corner of the screen.  
**Trigger:** \"pulls the trigger of the revolver.\"  
As long as voltage is present on the input or the button is pressed, the triangle indicating the current chamber (right of the cylinder) is filled. Depending on the current chamber, voltage will be present on the outputs.  
If the chamber is full the **HIT** output will be high (indicator top right) - if it is empty **MISS** will be high (indicator bottom right).  
**Spin:** spins the cylinder to a random position.  
As long as voltage is present on the input or the button is pressed a symbol is shown on the bottom left corner of the screen.  
**Insert:** will fill the current chamber if it is empty or empty it if it is full.  
**Add:** will add a chamber to the cylinder - the maximum is twelve chambers, the minimum
is two (cycling in ascending order).

### Outputs:

**HIT** outputs ~5V if trigger is pulled on a full chamber.  
**MISS** outputs ~5V if trigger is pulled on an empty chamber.

### Encoder:

**Left/Right:** either rotates the cylinder or cycles through the variants.  
**Button:** switches between the normal mode and the variant selection. Press the encoder to select a variant.

### Variants:

**Variant \#0: Manual**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS), removes the bullet if present  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#1: Vanilla**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS), removes the bullet if present and advances the cylinder by one chamber, if the last bullet is fired, the cylinder will be spun with one full chamber.  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#2: Vanilla No Removal**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS) and advances the cylinder by one chamber  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#3: Vanilla Respin**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS), removes the bullet if present and spins the cylinder, if the last bullet is fired, the cylinder will be spun with one full
chamber.  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#4: Vanilla Respin No Removal**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS) and spins the cylinder  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#5: Invert**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS), inverts the current chamber and advances the cylinder by one chamber  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#6: Invert Respin**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS), inverts the current chamber and spins the cylinder  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#7: Random**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger (full->HIT/empty->MISS) and randomizes between variants \#0 to \#6  
Spin: spins the cylinder  
Insert: inserts/removes bullet  
Add: adds a chamber  

**Variant \#8: Output Galore**  
Step: advances cylinder by one chamber  
Trigger: pulls the trigger and outputs on both **HIT** ***and*** **MISS**  
Spin: spins the cylinder  
Insert: not available  
Add: adds a chamber  

### Some notes:

The module is designed to work with inputs 0-5V (Trigger/Gate-signals), which will trigger on ~3V, and outputs ~5V on high.  
- Gates on **Trigger** will output gates on **HIT/MISS**
- Variant \#8 is basically a Trigger/Gate-Mult
- Variant \#2 and \#5 will result in repeating patterns
- Respin variants randomize but tend to keep some rhythm.

## Materials used

- 6hp Eurorack blankpanel
- Arduino Micro 5V
- 0.96\"-OLED 128x64
- Pushbuttons 4x
- Schottkydiodes BAT42 10x
- Diodes 1N4148 2x
- Capacitors 100nF 5x
- Rotaryencoder with pushbutton
- Regulator L7805CV
- Resistors 1k 5x 100k 5x
- 3.5mm sockets 7x

## Schematic

![schematic](https://github.com/MoldyTomato/Russian_Roulette/blob/main/schematic.png)

## Faceplate

![faceplate](https://github.com/MoldyTomato/Russian_Roulette/blob/main/faceplate.jpg)
![faceplate_dimensions](https://github.com/MoldyTomato/Russian_Roulette/blob/main/faceplate_markings.jpg)

## Disclaimer

This module is more a proof of concept than anything else. It can break if pushed and could potentially cause damage and harm. Use at your own risk!
Regarding the code: Readability, speed and size could be improved. But: finish fast :) may revisit this later 

## Changelog

22/9/21 Release for public
25/9/21 Added Faceplate images
