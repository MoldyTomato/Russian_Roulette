/* Displays the module name, by flashing the single letters and filling the whole screen with the appropraite voltage */
void displayModuleName() {
  char MODULE_NAME[] = "RUSSIAN ROULETTE";
  display.clearDisplay(); //clear display
  display.setTextSize(8); // Draw 8X-scale text
  display.setTextColor(SSD1306_WHITE); //set color to white
  //cycle trough the modulename and display the letters
  for (int i = 0; i < 15; i++) {
    char x = MODULE_NAME[i];
    display.setCursor(45, 5);
    display.println(x);
    display.display();
    delay(15);
    display.clearDisplay();
    display.display();
    delay(15);
  }
  //fill the whole screen with the acceptable input voltage for this module
  //the curcuit surrounding the arduino should protect it from overvoltage, but there is no sense in feeding it more than 0 to 5V for triggers or gates
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 15);
  display.print("0-5V");
  display.display();
  delay(250);
  display.clearDisplay();
  display.display();
}
