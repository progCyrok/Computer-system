#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "iostream"
#include <unistd.h>
#include <fstream>
#include <string>
#include "../../my_tools/json/include/nlohmann/json.hpp"
#include "../main_window/work_with_json.h"
#include <cstdlib>


using json = nlohmann::json;
bool press_save = false;
class Create_Button_Enter {
 public:
  Create_Button_Enter(const sf::Vector2f& position, const sf::Vector2f& size,
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
    if (!font.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/fonts/AristaPro-Regular.ttf")) {
      std::cerr << "Error loading font" << std::endl;
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 24, position.y + 1);
    text.setCharacterSize(28);
    text.setString("ADD");
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
    if (type == "Inventory Number") {
      inputText_inventory = textInput;
    }
    if (type == "Type of Computer") {
      inputText_type = textInput;
    }
    if (type == "Fabricator") {
      inputText_fabricator = textInput;
    }
    if (type == "Model") {
      inputText_model = textInput;
    }
    if (type == "Mac Address") {
      inputText_mac = textInput;
    }
    if (type == "Operating system") {
      inputText_os = textInput;
    }
    if (type == "Commissioning") {
      inputText_comiss = textInput;
    }
    if (type == "Decommissioning") {
      inputText_decomiss = textInput;
    }
    if (type == "Name Photo") {
      inputText_photo = textInput;
    }
  }

  bool get_logon() {
    return logon;
  }
  int get_proveril() {
    return proveril;
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
          ComputerDatabase db("/Users/rinatkamalov/CLionProjects/computers/app_structure/data_base.json");
          db.record_computer(inputText_inventory, inputText_type,
                             inputText_fabricator,
                             inputText_model, inputText_mac,
                             inputText_os, inputText_comiss,
                             inputText_decomiss, inputText_photo);
          press_save = true;
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
  std::string inputText_inventory;
  std::string inputText_type;
  std::string inputText_fabricator;
  std::string inputText_model;
  std::string inputText_mac;
  std::string inputText_os;
  std::string inputText_comiss;
  std::string inputText_decomiss;
  std::string inputText_photo;
};



class Create_TextInput {
 public:
  Create_TextInput(float x, float y, std::string name) {
    if (!font.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/fonts/AristaPro-Regular.ttf")) {
      std::cerr << "Error loading font" << std::endl;
    }

    inputBox.setSize(sf::Vector2f(500, 30));
    inputBox.setPosition(x, y);
    inputBox.setFillColor(sf::Color(0, 205, 255));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 1);
    slovo = name;
    if (name == "Inventory Number") {
      ComputerDatabase db("/Users/rinatkamalov/CLionProjects/computers/app_structure/data_base.json");
      inputText = std::to_string(db.getComputerCount() + 1);
      text.setString("Inventory Number: " + inputText);
      if_inven = true;
    }
    else {
      text.setString(slovo);
    }
    text.setCharacterSize(24);
  }

  std::string getInputText() const {
    return inputText;
  }

  void handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left && inputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isSelected = true;
        if (inputText == slovo) {
          inputText = "";
          text.setString(inputText);
        }
        if (slovo == "Inventory Number") {
          ComputerDatabase db("/Users/rinatkamalov/CLionProjects/computers/app_structure/data_base.json");
          inputText = std::to_string(db.getComputerCount() + 1);
          text.setString("Inventory Number: " + inputText);
        }
      } else {
        isSelected = false;
      }
    }

    if (isSelected) {
      inputBox.setFillColor(sf::Color(0, 255, 255));
        if (event.type == sf::Event::TextEntered && if_inven == false) {
          if (event.text.unicode < 128) {
            if (event.text.unicode == '\b' && inputText.size() > 0) {
              inputText.erase(inputText.size() - 1);
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
              inputText += static_cast<char>(event.text.unicode);
            }
          }
          text.setString(inputText);
        }
      } else {
        inputBox.setFillColor(sf::Color(0, 205, 255));
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
  bool if_inven = false;
};

class Add_photo_computer_button {
 public:
  Add_photo_computer_button(float x, float y) {
    if (!font.loadFromFile("/Users/rinatkamalov/CLionProjects/computers/my_tools/fonts/AristaPro-Regular.ttf")) {
      std::cerr << "Error loading font" << std::endl;
    }

    inputBox.setSize(sf::Vector2f(215, 30));
    inputBox.setPosition(x, y);
    inputBox.setFillColor(sf::Color(0, 205, 255));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 6, y + 1);
    text.setString("Watch photo computer");
    text.setCharacterSize(20);
  }


  void handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left && inputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        isSelected = true;
        std::cout << "Photo" << std::endl;
        system("open /Users/rinatkamalov/CLionProjects/computers/my_tools/images/photos_computers");
      } else {
        isSelected = false;
      }
    }

    if (isSelected) {
      inputBox.setFillColor(sf::Color(0, 255, 255));
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
    } else {
      inputBox.setFillColor(sf::Color(0, 205, 255));
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
};
