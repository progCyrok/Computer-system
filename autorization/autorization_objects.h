#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "iostream"
#include <unistd.h>
#include <fstream>
#include <string>




class Button_Enter {
 public:
  Button_Enter(const sf::Vector2f& position, const sf::Vector2f& size,
         const sf::Color& normalColor, const sf::Color& pressedColor)
      : m_position(position), m_size(size),
        m_normalColor(normalColor), m_pressedColor(pressedColor)
  {
    m_shape.setSize(m_size);
    m_shape.setFillColor(m_normalColor);
    m_shape.setPosition(m_position);
    m_originalPosition = m_position;
    m_shape.setOutlineThickness(3);
    m_shape.setOutlineColor(sf::Color::Black);
    if (!font.loadFromFile("../my_tools/fonts/AristaPro-Regular.ttf")) {
      std::cerr << "Error loading font" << std::endl;
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 15, position.y + 1);
    text.setCharacterSize(28);
    text.setString("Enter");
  }

  int isPressed(const sf::Vector2f& mousePosition) const {
    if(mousePosition.x >= m_position.x &&
        mousePosition.x <= m_position.x + m_size.x &&
        mousePosition.y >= m_position.y &&
        mousePosition.y <= m_position.y + m_size.y) {
      return 1;
    }
    return 0;
  }

  int proverka(const std::string & login_password) {
    std::ifstream inputFile("/Users/rinatkamalov/CLionProjects/computers/autorization/bd.txt");

    if (!inputFile.is_open()) {
      std::cerr << "Не удалось открыть файл!" << std::endl;
      return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
      if(login_password == line) {
        inputFile.close();
        return 1;
      }
    }

    inputFile.close();
    return -1;
  }

  void draw(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(text);
  }

  void setInputText(const std::string& textInput, const std::string &type) {
    if (type == "Login") {
      inputText_login = textInput;
    }
    if (type == "Password") {
      inputText_password = textInput;
    }
  }

  bool get_logon() {
    return logon;
  }
  int get_proveril() {
    return proveril;
  }

  std::string get_login_password() {
    std::string log_pas = inputText_login + " " + inputText_password;
    return log_pas;
  }


  void update(const sf::Vector2f& mousePosition) {
    if (isPressed(mousePosition) > 0) {
      if (isPressed(mousePosition) == 1) {
        m_shape.setFillColor(m_normalColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          float scaleFactor = 1.2f;
          m_shape.setSize(m_size * scaleFactor);

          m_shape.setPosition(m_originalPosition - (m_size * (scaleFactor - 1.f) / 2.f));
          m_shape.setFillColor(m_normalColor);
          std::string prov = inputText_login + " " + inputText_password;
          if (proverka(prov) == 1) {
            proveril = 1;
            logon = true;
          }
          else if (proverka(prov) == -1) {
            proveril = - 1;
            logon = false;
          }
        }
      }
    } else {
      m_shape.setSize(m_size);
      m_shape.setPosition(m_originalPosition);
      m_shape.setFillColor(m_pressedColor);
    }
  }

  int proveril = 0;
  bool logon = false;
 private:
  sf::RectangleShape m_shape;
  sf::Vector2f m_position;
  sf::Vector2f m_originalPosition;
  sf::Vector2f m_size;
  sf::Color m_normalColor;
  sf::Color m_pressedColor;
  sf::Font font;
  sf::Text text;
  std::string inputText_login;
  std::string inputText_password;
};


class TextInput {
 public:
  TextInput(float x, float y, std::string name) {
    if (!font.loadFromFile("../my_tools/fonts/AristaPro-Regular.ttf")) {
      std::cerr << "Error loading font" << std::endl;
    }

    inputBox.setSize(sf::Vector2f(300, 30));
    inputBox.setPosition(x, y);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 1);
    slovo = name;
    text.setString(slovo);
    text.setCharacterSize(20);
  }

  std::string getInputText() const {
    return inputText;
  }


  void pressed_enter(const sf::Event& event, Button_Enter &button_ent) {
    if(isSelected) {
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (button_ent.proverka(button_ent.get_login_password()) == 1) {
          button_ent.proveril = 1;
          button_ent.logon = true;
        }
        else if (button_ent.proverka(button_ent.get_login_password()) == -1) {
          button_ent.proveril = - 1;
          button_ent.logon = false;
        }
      }
    }
  }

  void handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left && inputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isSelected = true;
        if (inputText == slovo) {
          inputText = "";
          text.setString(inputText);
        }
      } else {
        isSelected = false;
      }
    }

    if (isSelected) {
      inputBox.setFillColor(sf::Color(128, 128, 128));
      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
          if (event.text.unicode == '\b' && inputText.size() > 0) {
            inputText.erase(inputText.size() - 1);
          } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            inputText += static_cast<char>(event.text.unicode);
          }
        }
        text.setString(inputText);
      }
    } else{
      inputBox.setFillColor(sf::Color::White);
      if (inputText.empty()) {
        text.setString(slovo);
      }
    }
  }

  void draw(sf::RenderWindow& window) {
    window.draw(inputBox);
    window.draw(text);
  }

 private:
  sf::RectangleShape inputBox;
  sf::Font font;
  sf::Text text;
  std::string inputText;
  bool isSelected = false;
  std::string slovo;
};