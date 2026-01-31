#include "ButtonHandler.h"
#include <iostream>

ButtonHandler::ButtonHandler(TableManager* manager) : tableManager(manager) {}

void ButtonHandler::ExecuteTableManager(char hitKey) {
    if (tableManager) {
        tableManager->TransformShape(hitKey);
    }
}

void ButtonHandler::ExecuteTableManager(const std::string& keycode) {
    if (tableManager) {
        tableManager->TransformShape(keycode);
    }
}

void ButtonHandler::Update() {
    std::cout << "Press a key (W, F1, F2, 0-9), or Q to quit: ";
    std::string input;
    std::getline(std::cin, input);
    if (input == "Q" || input == "q") return;
    if (input == "W" || input == "w") {
        std::cout << "W key pressed" << std::endl;
        // Add your logic here
    } else if (input == "F1") {
        std::cout << "F1 key pressed" << std::endl;
        ExecuteTableManager("F1");
    } else if (input == "F2") {
        std::cout << "F2 key pressed" << std::endl;
        ExecuteTableManager("F2");
    } else if (input.length() == 1 && isdigit(input[0])) {
        std::cout << "Key '" << input << "' pressed down!" << std::endl;
        ExecuteTableManager(input[0]);
    } else {
        std::cout << "Unknown key." << std::endl;
    }
}
