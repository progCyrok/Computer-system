#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "iostream"
#include <unistd.h>
#include <fstream>
#include <string>
#include "work_with_json.h"
#include "../other_func/creating_computer.h"

std::string current_button_index = "0";
ComputerDatabase DB("/Users/rinatkamalov/CLionProjects/computers/app_structure/data_base.json");
int list = 1;

void modification_photo(sf::Sprite &computer_photo) {
  float center = 732.5f;
  float photo_size_x = computer_photo.getGlobalBounds().getSize().x;
  float photo_size_y = computer_photo.getGlobalBounds().getSize().y;
  float index = 1.f;
  while (photo_size_x * index > 265 || photo_size_y * index > 200) {
    index -= 0.05f;
  }
  computer_photo.setScale(index, index);
  float position_photo_x = center - photo_size_x * index / 2;
  computer_photo.setPosition(position_photo_x, 500.f);
}

void description_computer (sf::RenderWindow & window, std::string &inventory) {
  sf::RectangleShape menu;
  menu.setSize(sf::Vector2f(465.f, 550.f));
  menu.setFillColor(sf::Color::White);
  menu.setPosition(500.f, 150.f);
  menu.setOutlineThickness(2);
  menu.setOutlineColor(sf::Color::Black);
  sf::Text text_model;
  sf::Font font_text;
  if (!font_text.loadFromFile("../my_tools/fonts/ArialRegular.ttf")) {
    std::cerr << "Не удалось загрузить шрифт!" << std::endl;
  }
  text_model.setFont(font_text);
  text_model.setFillColor(sf::Color::Black);
  text_model.setPosition(550.f, 170.f);
  text_model.setCharacterSize(35);
  std::string model = DB.getComputerModel(inventory);
  size_t pos = model.find("!");
  if (pos != std::string::npos) {
    model.erase(pos);
  }
  text_model.setString(model);
  window.draw(menu);
  window.draw(text_model);
  sf::Text description;
  description.setFont(font_text);
  description.setFillColor(sf::Color::Black);
  description.setPosition(520.f, 230.f);
  description.setCharacterSize(26);
  description.setString(DB.getComputerInfoByInven(inventory));
  window.draw(menu);
  window.draw(text_model);
  window.draw(description);
  if (DB.getComputerPhoto(inventory) != " ") {
    sf::Texture texture;
    std::string photo_path = "../my_tools/images/photos_computers/" + DB.getComputerPhoto(inventory);
    if (!texture.loadFromFile(photo_path)) {
      // Обработка ошибки, если изображение не удалось загрузить
      std::cerr << "Ошибка загрузки изображения!" << std::endl;
    }
    sf::Sprite computer_photo(texture);
    modification_photo(computer_photo);
    sf::RectangleShape frame(sf::Vector2f(computer_photo.getGlobalBounds().width + 10, computer_photo.getGlobalBounds().height + 10));
    frame.setFillColor(sf::Color(0, 191, 255));
    frame.setPosition(computer_photo.getPosition().x - 5, computer_photo.getPosition().y - 5);
    window.draw(frame);
    window.draw(computer_photo);
  }
}


class Computers_button {
 public:
  Computers_button(const sf::Vector2f& position, const sf::Vector2f& size,
         const sf::Color& normalColor, const sf::Color& pressedColor,  sf::RenderWindow& window, std::string &inven)
      : m_position(position), m_size(size),
        m_normalColor(normalColor), m_pressedColor(pressedColor),
        window_(window), inventory_(inven)
  {
    m_shape.setSize(m_size);
    m_shape.setFillColor(m_normalColor);
    m_originalPosition = m_position;
    m_shape.setOutlineThickness(2);
    m_shape.setOutlineColor(sf::Color::Black);
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
  void draw(sf::RenderWindow& window) {
    window.draw(m_shape);
  }

  void switch_color() {
    if (current_button_index == inventory_ && get_current_add_index() != "-1") {
      m_shape.setFillColor(m_normalColor);
    } else {
      m_shape.setFillColor(m_pressedColor);
    }
  }

  void update(const sf::Vector2f& mousePosition) {
    if (isPressed(mousePosition) > 0) {
      m_shape.setFillColor(m_normalColor);
      description_computer(window_, inventory_);
      if (current_button_index != inventory_) {
        current_button_index = "0";
      }
      update_current_add_button(current_button_index);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (current_button_index != DB.getComputerModel(inventory_)) {
          current_button_index = inventory_;
        }
        update_current_add_button(current_button_index);
        float scaleFactor = 1.2f;
        m_shape.setSize(m_size * scaleFactor);
        m_shape.setPosition(m_originalPosition - (m_size * (scaleFactor - 1.f) / 2.f));
        m_shape.setFillColor(m_normalColor);
      }
    } else {
      m_shape.setSize(m_size);
      m_shape.setPosition(m_originalPosition);
      switch_color();
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
  sf::Font font;
  sf::Text text;
  std::string inventory_;
};



class Switch_button {
 public:
  Switch_button(const sf::Vector2f& position, const sf::Vector2f& size,
                const sf::Color& normalColor, const sf::Color& pressedColor,  sf::RenderWindow& window, int number)
      : m_position(position), m_size(size),
        m_normalColor(normalColor), m_pressedColor(pressedColor),
        window_(window), number_list_(number)
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
  void draw() {
    window_.draw(m_shape);
  }

  void switch_color() {
    if (list == number_list_) {
      m_shape.setFillColor(m_normalColor);
    } else {
        m_shape.setFillColor(m_pressedColor);
    }
  }


  void update(const sf::Vector2f& mousePosition) {
    if (isPressed(mousePosition) > 0) {
      m_shape.setFillColor(m_normalColor);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float scaleFactor = 1.2f;
        m_shape.setSize(m_size * scaleFactor);
        m_shape.setPosition(m_originalPosition - (m_size * (scaleFactor - 1.f) / 2.f));
        m_shape.setFillColor(m_normalColor);
        list = number_list_;
      }
    } else {
      m_shape.setSize(m_size);
      m_shape.setPosition(m_originalPosition);
      switch_color();
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
  sf::Font font;
  sf::Text text;
  int number_list_;
  std::vector<Computers_button> computer_buttons_;
  std::vector<sf::Text> computer_texts_;
  std::vector<Switch_button> switch_buttons_;
  std::vector<sf::Text> switch_texts_;
};






void update_current(sf::RenderWindow &window, Button_Add &add_but,
                    sf::Vector2f &mousePosition, std::vector<TextInput_Add_Computer> &add_comp_inputs,
                    sf::Event &event) {
  if (current_button_index > "0") {
    description_computer(window, current_button_index);
  }
  if (get_current_add_index() == "-1") {
    add_description_computer(window, add_but, mousePosition, add_comp_inputs, event);
  }
}
void menu_computers (sf::RenderWindow &window) {
  sf::RectangleShape menu;
  menu.setSize(sf::Vector2f(400.f, 600.f));
  menu.setFillColor(sf::Color(190, 240, 255));
  menu.setPosition(35.f, 125.f);
  menu.setOutlineThickness(2);
  menu.setOutlineColor(sf::Color::Black);
  window.draw(menu);
}
void default_menu_buttons(ComputerDatabase &db, sf::Font &font_text,
                          std::vector<Computers_button> &computer_buttons, std::vector<sf::Text> &computer_texts,
                          sf::RenderWindow& window, std::vector<Switch_button> &switch_buttons,
                          std::vector<sf::Text> &switch_texts) {
  int start_x = 60.f;
  int start_y = 150.f;
  int buttonWidth = 350;
  int buttonHeight = 30;
  int buttonSpacing = 20;
  int count_computers = db.getComputerCount();
  for (int i = 0 ; i < count_computers; ++i) {
    int kef = i;
    if (i >= 10) {
      kef %= 10;
    }
    std::string model = db.printModelByIndex(i);
    size_t pos = model.find("!");
    if (pos != std::string::npos) {
      model.erase(pos);
    }
    std::string inven = db.printInventoryByIndex(i);
    sf::Vector2f buttonPosition(start_x, start_y + kef * (buttonHeight + buttonSpacing));
    sf::Vector2f buttonSize(buttonWidth, buttonHeight);
    computer_buttons.push_back(Computers_button(buttonPosition,
                                                buttonSize,
                                                sf::Color(0, 255, 255),
                                                sf::Color(0, 191, 255),
                                                window,
                                                inven));
    sf::Text text_button;
    text_button.setFont(font_text);
    text_button.setFillColor(sf::Color::Black);
    text_button.setPosition(buttonPosition.x + 15, buttonPosition.y - 3);
    text_button.setCharacterSize(28);
    text_button.setString(model);
    computer_texts.push_back(text_button);
  }
  int sw_start_x = 60.f;
  int sw_start_y = 670.f;
  int sw_button_size = 30;
  int sw_buttonSpacing = 20;
  int maybe_lists = count_computers / 10 + 2;
  int this_num = 0;
  for (int i = list ; i < maybe_lists; ++i) {
    sf::Vector2f sw_buttonPosition(sw_start_x + this_num * (sw_button_size + sw_buttonSpacing), sw_start_y);
    this_num += 1;
    sf::Vector2f sw_buttonSize(sw_button_size, sw_button_size);
    switch_buttons.push_back(Switch_button(sw_buttonPosition,
                                                sw_buttonSize,
                                                sf::Color(0, 255, 255),
                                                sf::Color(0, 191, 255),
                                                window,
                                                i));
    sf::Text text_button;
    text_button.setFont(font_text);
    text_button.setFillColor(sf::Color::Black);
    text_button.setPosition(sw_buttonPosition.x + 8, sw_buttonPosition.y - 1);
    text_button.setCharacterSize(24);
    text_button.setString(std::to_string(i));
    switch_texts.push_back(text_button);
  }
}

void adding_computers(sf::Font &font_text, Add_button_main &add_but,
                      sf::Vector2f &mousePosition, sf::RenderWindow &window) {
  sf::Text text_button;
  text_button.setFont(font_text);
  text_button.setFillColor(sf::Color::Black);
  text_button.setPosition(558.f, 34.f);
  text_button.setCharacterSize(24);
  text_button.setString("Add Computer");
  add_but.update(mousePosition);
  add_but.draw(window);
  window.draw(text_button);
}



void default_drawwing_buttons(std::vector<Computers_button> &computer_buttons, std::vector<sf::Text> &computer_texts,
                              sf::Vector2f &mousePosition,
                              sf::RenderWindow &window, std::vector<Switch_button> &switch_buttons,
                              std::vector<sf::Text> &switch_texts) {
  int index_start = list * 10 - 10;
  int index_finish = list * 10;
  if (index_finish > computer_buttons.size()) {
    index_finish = computer_buttons.size();
  }
  for (int i = index_start; i < index_finish; ++i) {
    computer_buttons[i].update(mousePosition);
    computer_buttons[i].draw(window);
    window.draw(computer_texts[i]);
  }
  for (int i = 0; i < switch_buttons.size(); ++i) {
    switch_buttons[i].update(mousePosition);
    switch_buttons[i].draw();
    window.draw(switch_texts[i]);
  }
}

std::string get_curent_button() {
  return current_button_index;
}