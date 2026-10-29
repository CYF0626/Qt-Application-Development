#include "calculatorengine.h"
void CalculatorEngine::input(const QString &token) {
    if (token == "C") { *this = CalculatorEngine(); return; }
    if (token == "Backspace") {
        current.chop(1);
        if (current.isEmpty()) current = "0";
        return;
    }
    if (token == "." || (token.size() == 1 && token[0].isDigit())) {
        if (token == "." && current.contains('.')) return;
        if (current == "0" && token != ".") current.clear();
        current += token;
    }
}
bool CalculatorEngine::evaluate() { return false; }
