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
#include "main_window.h"
bool flag = true;
int main() {
  autorization_monitor();
  while (flag == true) {
    if (autor == true) {
      main_window();
      if (pressed_add_button == true) {
        autor = false;
        create_computer_monitor();
      }
    }
    if (pressed_add_button == false) {
      autor = true;
    }


    if (flag_on_off == false) {
      flag = false;
    }
  }
  return 0;
}