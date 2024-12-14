#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <unistd.h>
#include "autorization_objects.h"

bool autor = false;
int autorization_monitor(){
  int width = 600, height = 400;
  sf::RenderWindow window(sf::VideoMode(width, height), "Autorization");
  // Загружаем изображение для курсора
  sf::Image cursorImage;
  if (!cursorImage.loadFromFile("../my_tools/images/mini_cursor.png")) {
    std::cerr << "Ошибка загрузки изображения курсора!" << std::endl;
    return 1;
  }


  sf::Text text_log;
  sf::Font font_text;
  if (!font_text.loadFromFile("../my_tools/fonts/AristaPro-Regular.ttf")) {
    std::cerr << "Не удалось загрузить шрифт!" << std::endl;
    return -1;
  }


  text_log.setFont(font_text);
  text_log.setString("Please log in to the system");
  text_log.setCharacterSize(30);
  text_log.setFillColor(sf::Color::Blue);
  text_log.setPosition(120, 50);

  sf::Text text_incorrect;
  text_incorrect.setFont(font_text);
  text_incorrect.setString("Enter the correct data");
  text_incorrect.setCharacterSize(20);
  text_incorrect.setFillColor(sf::Color::Red);
  text_incorrect.setPosition(195, 100);

  sf::Cursor custom_cursor;
  custom_cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(8, 8));
  window.setMouseCursor(custom_cursor);
  sf::Font font;
  sf::Texture floorTexture;
  if (!floorTexture.loadFromFile("../my_tools/images/test_blue_white.jpg")) {
    std::cerr << "Фото не поддерживается";
  }
  sf::Sprite floorSprite(floorTexture);
  sf::Event event;

  Button_Enter button(sf::Vector2f(250.f, 250.f), sf::Vector2f(100.f, 40.f),
                sf::Color(30, 144, 255), sf::Color(sf::Color::Blue));

  TextInput inputField1(150, 150, "Login");
  TextInput inputField2(150, 200, "Password");


  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
        usleep(1000000);
        autor = true;
      }

      button.update(mousePosition);
      window.draw(floorSprite);
      button.draw(window);
      inputField1.handleEvent(event);
      inputField2.handleEvent(event);


      button.setInputText(inputField1.getInputText(), "Login");
      button.setInputText(inputField2.getInputText(), "Password");

      inputField1.draw(window);
      inputField2.draw(window);

      inputField1.pressed_enter(event, button);
      inputField2.pressed_enter(event, button);
      if (button.get_logon()) {
        autor = true;
        window.close();
      }
      if (button.get_proveril() == -1) {
        window.draw(text_incorrect);

      }
      window.draw(text_log);
      window.display();
    }
  }
  return 0;
}

