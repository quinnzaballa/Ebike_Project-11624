  // Infos
  // Controls
  // Electronics
  // Settings
  // Credits

void updatemenu() {
  // Add if, if the user is not on the sub, then continue main menu selecting
  if (inSmenu == false) {
  // Update menu for MMenu
  if (Cursor == 0) infos();
  if (Cursor == 1) Controls();
  if (Cursor == 2) Electronics();
  if (Cursor == 3) Settings();
  if (Cursor == 4) Credits();
  } else {
   updateSmenu();
  }
}