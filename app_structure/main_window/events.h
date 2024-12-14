#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../autorization/authorization.h"
bool flag_on_off = true;
void main_events(sf::RenderWindow &window, sf::Event &event) {
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      flag_on_off = false;
      window.close();
      std::cout << "FINISH" << std::endl;
    }
  }
}