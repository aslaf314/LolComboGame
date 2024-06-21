#include "MousePanel.h"


std::random_device dv;
std::mt19937 MousePanel::rand(dv());
std::uniform_int_distribution<std::mt19937::result_type> MousePanel::coordsX(30,170);
std::uniform_int_distribution<std::mt19937::result_type> MousePanel::coordsY(30, 170);

