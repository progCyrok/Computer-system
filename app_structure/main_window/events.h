#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../autorization/authorization.h"

void main_events(sf::RenderWindow &window, sf::Event &event) {
  float scrollOffset = 0; // Смещение прокрутки
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
      std::cout << "FINISH" << std::endl;
    }
  }
}