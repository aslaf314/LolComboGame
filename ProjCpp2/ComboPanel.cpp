#include "ComboPanel.h"

std::random_device rd; 
std::mt19937 Combo::rand(rd());
std::uniform_int_distribution<std::mt19937::result_type> Combo::combo_length_dist(3, MAX_COMBO_LENGTH); 
std::uniform_int_distribution<std::mt19937::result_type> Combo::combo_dist(0, 7); 