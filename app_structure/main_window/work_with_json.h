#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../../my_tools/json/include/nlohmann/json.hpp"
using json = nlohmann::json;
class ComputerDatabase {
 public:
  ComputerDatabase(const std::string& filename) : filename(filename) {
    loadFromFile();
  }


  std::string printModelByIndex(int index) {
    if (data.is_array() && index >= 0 && index < data.size()) {
      return data[index]["model"];
    } else {
      std::cerr << "Ошибка: недопустимый индекс или файл не содержит массив JSON" << std::endl;
    }
  }

  std::string printInventoryByIndex(int index) {
    if (data.is_array() && index >= 0 && index < data.size()) {
      return data[index]["inventory number"];
    } else {
      std::cerr << "Ошибка: недопустимый индекс или файл не содержит массив JSON" << std::endl;
    }
  }

  int getComputerCount() {
    if (data.is_array()) {
      return data.size();
    } else {
      return 0;
    }
  }

  json getComputerInfo(const std::string& inventoryNumber) {
    if (data.is_array()) {
      for (const auto& item : data) {
        if (item["inventory number"] == inventoryNumber) {
          return item;
        }
      }
    }
    return json();
  }

  std::string getComputerModel(const std::string& inventoryNumber) {
    if (data.is_array()) {
      for (const auto& item : data) {
        if (item["inventory number"] == inventoryNumber) {
          return item["model"];
        }
      }
    }
    return " ";
  }

  std::string getComputerPhoto(const std::string& inventoryNumber) {
    if (data.is_array()) {
      for (const auto& item : data) {
        if (item["inventory number"] == inventoryNumber) {
          return item["photo"];
        }
      }
    }
    return " ";
  }

  std::string getComputerInfoByInven(const std::string& inventoryNumber) {
    if (data.is_array()) {
      for (const auto& computer : data) {
        if (computer["inventory number"] == inventoryNumber) {
          std::string info = "";
          info += "Inventory number: " + computer["inventory number"].get<std::string>() + "\n";
          info += "Type of computer: " + computer["type of computer"].get<std::string>() + "\n";
          info += "Fabricator: " + computer["fabricator"].get<std::string>() + "\n";
          std::string model = computer["model"].get<std::string>();
          model.erase(std::remove(model.begin(), model.end(), '!'), model.end());
          info += "Model: " + model + "\n";
          info += "MAC address: " + computer["mac address"].get<std::string>() + "\n";
          info += "Operating system: " + computer["operating system"].get<std::string>() + "\n";
          info += "Date commissioning: " + computer["dates"]["commissioning"].get<std::string>() + "\n";
          info += "Date decommissioning: " + computer["dates"]["decommissioning"].get<std::string>() + "\n";
          return info;
        }
      }
    }
    return " ";
  }

  bool updateComputerInfo(const std::string& inventoryNumber, const json& updatedInfo) {
    if (data.is_array()) {
      for (size_t i = 0; i < data.size(); ++i) {
        if (data[i]["inventory number"] == inventoryNumber) {
          data[i] = updatedInfo;
          saveToFile();
          return true;
        }
      }
    }
    return false;
  }

 private:
  std::string filename;
  json data;

  void loadFromFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
      file >> data;
    } else {
      std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    }
  }

  void saveToFile() {
    std::ofstream file(filename);
    if (file.is_open()) {
      file << data.dump(4);
    } else {
      std::cerr << "Ошибка записи в файл: " << filename << std::endl;
    }
  }
};