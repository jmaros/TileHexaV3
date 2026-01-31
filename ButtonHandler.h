#pragma once
#include "TableManager.h"
#include <string>

class ButtonHandler {
public:
    TableManager* tableManager;
    ButtonHandler(TableManager* manager);
    void ExecuteTableManager(char hitKey);
    void ExecuteTableManager(const std::string& keycode);
    void Update();
};
