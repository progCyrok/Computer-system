#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "iostream"
#include <unistd.h>
#include <fstream>
#include <string>
#include "../main_window/work_with_json.h"
#include "../main_window/main_objects.h"

bool pressed_add_button = false;
std::string current_item = "0";
class Add_button_main {
 public:
  Add_button_main(const sf::Vector2f& position, const sf::Vector2f& size,
             const sf::Color& normalColor, const sf::Color& pressedColor,  sf::RenderWindow& window)
      : m_position(position), m_size(size),
        m_normalColor(normalColor), m_pressedColor(pressedColor),
        window_(window)
  {
    m_shape.setSize(m_size);
    m_shape.setFillColor(m_normalColor);
    m_originalPosition = m_position;
    m_shape.setOutlineThickness(2);
    m_shape.setOutlineColor(sf::Color::Black);
  }
  int isPressed(const sf::Vector2f& mousePosition) const {
    if(mousePosition.x >= m_originalPosition.x &&
        mousePosition.x <= m_originalPosition.x + m_size.x &&
        mousePosition.y >= m_originalPosition.y &&
        mousePosition.y <= m_originalPosition.y + m_size.y) {
      return 1;
    }
    return 0;
  }
  void draw(sf::RenderWindow& window) {
    window.draw(m_shape);
  }


  void update(const sf::Vector2f& mousePosition) {
    if (isPressed(mousePosition) > 0) {
      m_shape.setFillColor(m_normalColor);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float scaleFactor = 1.2f;
        m_shape.setSize(m_size * scaleFactor);
        m_shape.setPosition(m_originalPosition - (m_size * (scaleFactor - 1.f) / 2.f));
        m_shape.setFillColor(m_normalColor);
        pressed_add_button = true;

      }
    } else {
      m_shape.setSize(m_size);
      m_shape.setPosition(m_originalPosition);
      m_shape.setFillColor(m_pressedColor);
    }
  }

 private:
  sf::RenderWindow& window_;
  sf::RectangleShape m_shape;
  sf::Vector2f m_position;
  sf::Vector2f m_originalPosition;
  sf::Vector2f m_size;
  sf::Color m_normalColor;
  sf::Color m_pressedColor;
  sf::Text text;
};


//class Button_Add {
// public:
//  Button_Add(const sf::Vector2f& position, const sf::Vector2f& size,
//               const sf::Color& normalColor, const sf::Color& pressedColor)
//      : m_position(position), m_size(size),
//        m_normalColor(normalColor), m_pressedColor(pressedColor)
//  {
//    m_shape.setSize(m_size);
//    m_shape.setFillColor(m_normalColor);
//    m_shape.setPosition(m_position);
//    m_originalPosition = m_position;
//    m_shape.setOutlineThickness(3);
//    m_shape.setOutlineColor(sf::Color::Black);
//    if (!font.loadFromFile("../my_tools/fonts/ArialRegular.ttf")) {
//      std::cerr << "Error loading font" << std::endl;
//    }
//    text.setFont(font);
//    text.setFillColor(sf::Color::Black);
//    text.setPosition(position.x + 20, position.y + 6);
//    text.setCharacterSize(28);
//    text.setString("ADD");
//  }
//
//  int isPressed(const sf::Vector2f& mousePosition) const {
//    if(mousePosition.x >= m_position.x &&
//        mousePosition.x <= m_position.x + m_size.x &&
//        mousePosition.y >= m_position.y &&
//        mousePosition.y <= m_position.y + m_size.y) {
//      return 1;
//    }
//    return 0;
//  }
//
//  void draw(sf::RenderWindow& window) {
//    window.draw(m_shape);
//    window.draw(text);
//  }
//
//  void setInputText(const std::string& textInput, const std::string &type) {
//    if (type == "Login") {
//      inputText_login = textInput;
//    }
//    if (type == "Password") {
//      inputText_password = textInput;
//    }
//  }
//
//  bool get_logon() {
//    return logon;
//  }
//  int get_proveril() {
//    return proveril;
//  }
//
//  std::string get_login_password() {
//    std::string log_pas = inputText_login + " " + inputText_password;
//    return log_pas;
//  }
//
//
//  void update(const sf::Vector2f& mousePosition) {
//    if (isPressed(mousePosition) > 0) {
//      if (isPressed(mousePosition) == 1) {
//        m_shape.setFillColor(m_normalColor);
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//          float scaleFactor = 1.2f;
//          m_shape.setSize(m_size * scaleFactor);
//
//          m_shape.setPosition(m_originalPosition - (m_size * (scaleFactor - 1.f) / 2.f));
//          m_shape.setFillColor(m_normalColor);
//          std::string prov = inputText_login + " " + inputText_password;
//        }
//      }
//    } else {
//      m_shape.setSize(m_size);
//      m_shape.setPosition(m_originalPosition);
//      m_shape.setFillColor(m_pressedColor);
//    }
//  }
//
//  int proveril = 0;
//  bool logon = false;
// private:
//  sf::RectangleShape m_shape;
//  sf::Vector2f m_position;
//  sf::Vector2f m_originalPosition;
//  sf::Vector2f m_size;
//  sf::Color m_normalColor;
//  sf::Color m_pressedColor;
//  sf::Font font;
//  sf::Text text;
//  std::string inputText_login;
//  std::string inputText_password;
//};
//
//class TextInput_Add_Computer {
// public:
//  TextInput_Add_Computer(sf::Font &font, float x, float y, std::string &name) : slovo(name), font_(font) {
//    if (!font_.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/fonts/ArialRegular.ttf")) {
//      std::cerr << "Не удалось загрузить шрифт!" << std::endl;
//    }
//
//    inputBox.setSize(sf::Vector2f(425, 30));
//    inputBox.setPosition(x, y);
//    inputBox.setFillColor(sf::Color::White);
//    inputBox.setOutlineColor(sf::Color::Black);
//    inputBox.setOutlineThickness(2);
//
//    text.setFont(font);
//    text.setFillColor(sf::Color::Black);
//    text.setPosition(x + 5, y + 1);
//    text.setString(slovo);
//    text.setCharacterSize(20);
//  }
//
//  std::string getInputText() const {
//    return inputText;
//  }
//  std::string get_slovo() const {
//    return slovo;
//  }
//
//
//  void pressed_enter(const sf::Event& event, Button_Enter &button_ent) {
//    if(isSelected) {
//      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
//        if (button_ent.proverka(button_ent.get_login_password()) == 1) {
//          button_ent.proveril = 1;
//          button_ent.logon = true;
//        }
//        else if (button_ent.proverka(button_ent.get_login_password()) == -1) {
//          button_ent.proveril = - 1;
//          button_ent.logon = false;
//        }
//      }
//    }
//  }
//
//  void switch_color() {
//    if (current_item == slovo) {
//      inputBox.setFillColor(sf::Color(128, 128, 128));
//    } else {
//      inputBox.setFillColor(sf::Color::White);
//    }
//  }
//
//  void handleEvent(const sf::Event& event) {
//    if (event.type == sf::Event::MouseButtonPressed) {
//      if (event.mouseButton.button == sf::Mouse::Left && inputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//        current_item = slovo;
//        switch_color();
//        isSelected = true;
//        if (inputText == slovo) {
//          inputText = "";
//          text.setString(inputText);
//        }
//      } else {
//        isSelected = false;
//      }
//    }
//
//    if (isSelected) {
//      inputBox.setFillColor(sf::Color(128, 128, 128));
//      if (event.type == sf::Event::TextEntered) {
//        if (event.text.unicode < 128) {
//          if (event.text.unicode == '\b' && inputText.size() > 0) {
//            inputText.erase(inputText.size() - 1);
//          } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
//            inputText += static_cast<char>(event.text.unicode);
//          }
//        }
//        text.setString(inputText);
//      }
//    } else{
//      inputBox.setFillColor(sf::Color::White);
//      if (inputText.empty()) {
//        text.setString(slovo);
//      }
//    }
//    switch_color();
//  }
//
//  void draw(sf::RenderWindow& window) {
//    window.draw(inputBox);
//    window.draw(text);
//  }
//
// private:
//  sf::RectangleShape inputBox;
//  sf::Font font_;
//  sf::Text text;
//  std::string inputText;
//  bool isSelected = false;
//  std::string slovo;
//};

//std::string get_current_add_index(){
//  return current_add_button_index;
//}
//
//void refactor_current_item() {
//  current_item = "0";
//}


void add_description_computer(sf::RenderWindow &window,
                              sf::Vector2f &mousePosition,
                              sf::Event &event) {
  sf::RectangleShape menu;
  menu.setSize(sf::Vector2f(465.f, 600.f));
  menu.setFillColor(sf::Color(152, 251, 152));
  menu.setPosition(500.f, 125.f);
  menu.setOutlineThickness(2);
  menu.setOutlineColor(sf::Color::Black);


  sf::Text main_text;
  sf::Font font_text;
  if (!font_text.loadFromFile("../my_tools/fonts/ArialRegular.ttf")) {
    std::cerr << "Не удалось загрузить шрифт!" << std::endl;
  }
  main_text.setFont(font_text);
  main_text.setFillColor(sf::Color::Black);
  main_text.setPosition(590.f, 145.f);
  main_text.setCharacterSize(35);
  main_text.setString("Fill in all the fields");

  window.draw(menu);
  window.draw(main_text);
//  add_but.update(mousePosition);
//  add_but.draw(window);

//  int start_x = 520.f;
//  int start_y = 200.f;
//  std::vector<std::string> strings = {"Inventory number", "Type of computer", "Fabricator", "Model",
//                                      "Mac address", "Operating system", "Commissioning",
//                                      "Decommissioning", "Photo"};
//  for (int i = 0 ; i < strings.size(); ++i) {
//    add_comp_inputs.push_back(TextInput_Add_Computer(font_text, start_x, start_y, strings[i]));
//    start_y += 50;
//  }
//  for (int i = 0; i < add_comp_inputs.size(); ++i) {
//    add_comp_inputs[i].handleEvent(event);
//    add_comp_inputs[i].draw(window);
//  }
}