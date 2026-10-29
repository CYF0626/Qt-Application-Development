#include "calculatorengine.h"
#include <cmath>
void CalculatorEngine::input(const QString &token) {
    if (token == "C") { *this = CalculatorEngine(); return; }
    if (token == "Backspace") {
        current.chop(1);
        if (current.isEmpty()) current = "0";
        return;
    }
    if (token == "." || (token.size() == 1 && token[0].isDigit())) {
        if (waiting) { current = "0"; waiting = false; }
        if (token == "." && current.contains('.')) return;
        if (current == "0" && token != ".") current.clear();
        current += token;
        return;
    }
    if (token == "=" || token == "+" || token == "-" || token == "*" || token == "/") {
        if (!pending.isEmpty() && !waiting) evaluate();
        accumulator = current.toDouble();
        pending = token == "=" ? QString() : token;
        history = current + " " + token;
        waiting = true;
        finished = token == "=";
    }
}
bool CalculatorEngine::evaluate() {
    const double rhs = current.toDouble();
    if (pending == "+") accumulator += rhs;
    else if (pending == "-") accumulator -= rhs;
    else if (pending == "*") accumulator *= rhs;
    else if (pending == "/") accumulator /= rhs;
    current = QString::number(accumulator, 'g', 15);
    return true;
}
