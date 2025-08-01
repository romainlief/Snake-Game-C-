#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "src/const.hpp"
#include "src/game.hpp"

using namespace std;


int difChoice() {
  int choix;
  int diffi = 1;
  bool choixValide = false;
  while (!choixValide) {
    try {
      cout << "Choisissez la difficulté : " << endl;
      cout << "1. Normal" << endl;
      cout << "2. Multi Fruit" << endl;
      cout << "3. Hard core" << endl;
      cin >> choix;

      if (cin.fail()) {
        throw invalid_argument("Entrée invalide");
      }
      if (choix == 1) {
        diffi = 1;
        choixValide = true;
      } else if (choix == 2) {
        diffi = 2;
        choixValide = true;
      } else if (choix == 3) {
        diffi = 3;
        choixValide = true;
      } else {
        throw invalid_argument("Choix invalide");
      }
    } catch (const invalid_argument &e) {
      cin.clear(); // clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << e.what() << ", veuillez réessayer." << endl;
    }
  }
  return diffi;
}

int main() {
  int diffi = difChoice();
  Game game(diffi);
  game.run();
  return 0;
}
