
void updateDisplay()
{
  display.sendSmooth (message, messageOffset);

  // next time show one pixel onwards
  if (messageOffset++ >= (int) (strlen (message) * 8))
    messageOffset = - chips * 8;
}

void displayLoop() {
  if (millis () - lastMoved >= MOVE_INTERVAL)
  {
    updateDisplay ();
    lastMoved = millis ();
  }
}

