#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <unistd.h>
#include "create_objects.h"
#include "../other_func/creating_computer.h"


int create_computer_monitor() {
  if (pressed_add_button == true) {
    int width = 600, height = 700;
    sf::RenderWindow window(sf::VideoMode(width, height), "Create_New_Element");
    // Загружаем изображение для курсора
    sf::Image cursorImage;
    if (!cursorImage.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/images/mini_cursor.png")) {
      std::cerr << "Ошибка загрузки изображения курсора!" << std::endl;
      return 1;
    }

    sf::Text text_log;
    sf::Font font_text;
    if (!font_text.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/fonts/ArialRegular.ttf")) {
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
    if (!floorTexture.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/images/black_blue.jpg")) {
      std::cerr << "Фото не поддерживается";
    }
    sf::Sprite floorSprite(floorTexture);
    sf::Event event;

    Create_Button_Enter button(sf::Vector2f(250.f, 550.f), sf::Vector2f(100.f, 40.f),
                        sf::Color(30, 144, 255), sf::Color(sf::Color::Blue));

    Create_TextInput inputField1(50, 150, "Inventory Number");
    Create_TextInput inputField2(50, 200, "Type of Computer");
    Create_TextInput inputField3(50, 250, "Fabricator");
    Create_TextInput inputField4(50, 300, "Model");
    Create_TextInput inputField5(50, 350, "Mac Address");
    Create_TextInput inputField6(50, 400, "Operating system");
    Create_TextInput inputField7(50, 450, "Commissioning");
    Create_TextInput inputField8(50, 500, "Decommissioning");

    while (window.isOpen()) {
      while (window.pollEvent(event)) {
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        if (event.type == sf::Event::Closed) {
          window.close();
          pressed_add_button = false;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
          window.close();
          pressed_add_button = false;
        }

        button.update(mousePosition);
        window.draw(floorSprite);
        button.draw(window);

        inputField1.handleEvent(event);
        inputField2.handleEvent(event);
        inputField3.handleEvent(event);
        inputField4.handleEvent(event);
        inputField5.handleEvent(event);
        inputField6.handleEvent(event);
        inputField7.handleEvent(event);
        inputField8.handleEvent(event);

        button.setInputText(inputField1.getInputText(), "Inventory Number");
        button.setInputText(inputField2.getInputText(), "Type of Computer");
        button.setInputText(inputField3.getInputText(), "Fabricator");
        button.setInputText(inputField4.getInputText(), "Model");
        button.setInputText(inputField5.getInputText(), "Mac Address");
        button.setInputText(inputField6.getInputText(), "Operating system");
        button.setInputText(inputField7.getInputText(), "Commissioning");
        button.setInputText(inputField8.getInputText(), "Decommissioning");

        inputField1.draw(window);
        inputField2.draw(window);
        inputField3.draw(window);
        inputField4.draw(window);
        inputField5.draw(window);
        inputField6.draw(window);
        inputField7.draw(window);
        inputField8.draw(window);

//        inputField1.pressed_enter(event, button);
//        inputField2.pressed_enter(event, button);
//        inputField3.pressed_enter(event, button);
//        inputField4.pressed_enter(event, button);
//        inputField5.pressed_enter(event, button);
//        inputField6.pressed_enter(event, button);
//        inputField7.pressed_enter(event, button);
//        inputField8.pressed_enter(event, button);
        if (save == true) {
          window.close();
        }
        window.draw(text_log);
        window.display();
      }
    }
    return 0;
  }
}

