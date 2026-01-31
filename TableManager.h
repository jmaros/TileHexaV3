#pragma once
#include <string>
#include <iostream>

class TableManager {
public:
    void TransformShape(char hitKey);
    void TransformShape(const std::string& keycode);
};
