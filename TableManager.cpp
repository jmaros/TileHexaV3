#include "TableManager.h"

void TableManager::TransformShape(char hitKey) {
    std::cout << "TransformShape called with char: " << hitKey << std::endl;
}

void TableManager::TransformShape(const std::string& keycode) {
    std::cout << "TransformShape called with string: " << keycode << std::endl;
}
