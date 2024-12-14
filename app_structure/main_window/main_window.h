#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../../autorization/authorization.h"
#include "events.h"
#include "main_objects.h"
#include "work_with_json.h"
#include "../other_func/creating_computer.h"
#include "../add_new_computer/monitor_create.h"

int main_window() {
  ComputerDatabase db("/Users/rinatkamalov/CLionProjects/computers/app_structure/data_base.json");
  int width = 1000, height = 1000;
  sf::RenderWindow window(sf::VideoMode(width, height), "MyApp");
  sf::Image cursorImage;
  if (!cursorImage.loadFromFile("../my_tools/images/mini_cursor.png")) {
    std::cerr << "Ошибка загрузки изображения курсора!" << std::endl;
    return 1;
  }
  sf::Cursor main_cursor;
  main_cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(8, 8));
  window.setMouseCursor(main_cursor);
  sf::Texture floorTexture;
  if (!floorTexture.loadFromFile("../my_tools/images/backgrounds/img.png")) {
    std::cerr << "Фото не поддерживается";
  }
  sf::Sprite floorSprite(floorTexture);
  sf::Text text_list;
  sf::Font font_text;
  if (!font_text.loadFromFile("../my_tools/fonts/AristaPro-Regular.ttf")) {
    std::cerr << "Не удалось загрузить шрифт!" << std::endl;
    return -1;
  }
  text_list.setFont(font_text);
  text_list.setString("List of computers");
  text_list.setCharacterSize(40);
  text_list.setFillColor(sf::Color(0, 191, 255));
  text_list.setPosition(80, 50);
  std::vector<Computers_button> computer_buttons;
  std::vector<sf::Text> computer_texts;
  std::vector<Switch_button> switch_buttons;
  std::vector<sf::Text> switch_texts;
  default_menu_buttons(db, font_text, computer_buttons, computer_texts, window, switch_buttons, switch_texts);
  Add_button_main main_add(sf::Vector2f(550.f, 35.f), sf::Vector2f(160, 30),
                           sf::Color(26, 251, 254),
                           sf::Color(70, 122, 254),
                           window);
  while (window.isOpen()) {
    sf::Event event;
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    window.draw(floorSprite);
    main_events(window, event);
    menu_computers(window);
    update_current(window, mousePosition, event);
    window.draw(text_list);
    default_drawwing_buttons(computer_buttons, computer_texts, mousePosition, window, switch_buttons, switch_texts);
    adding_computers(font_text, main_add, mousePosition, window);
    window.display();
    if (pressed_add_button == true) {
      window.close();
      list = 1;
    }
  }
  return 0;
}