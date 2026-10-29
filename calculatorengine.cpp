#include "calculatorengine.h"
#include <cmath>
void CalculatorEngine::input(const QString &token) {
    if (token == "C") { *this = CalculatorEngine(); return; }
    // Error is a separate state: a new number or clear starts a clean calculation.
    if (error) {
        if (token == "." || token == "Backspace" || (token.size() == 1 && token[0].isDigit()))
            *this = CalculatorEngine();
        else return;
    }
    if (token == "Backspace") {
        if (waiting && !finished) return;
        if (current.contains('e')) return;
        if (finished) { finished = false; waiting = false; history.clear(); }
        current.chop(1);
        if (current.isEmpty() || current == "-") current = "0";
        return;
    }
    if (token == "." || (token.size() == 1 && token[0].isDigit())) {
        if (waiting) { current = "0"; waiting = false; }
        if (finished) { history.clear(); finished = false; }
        if (token == "." && current.contains('.')) return;
        if (current.size() >= 16) return;
        if (current == "0" && token != ".") current.clear();
        current += token;
        return;
    }
    if (token == "=" || token == "+" || token == "-" || token == "*" || token == "/") {
        const QString calculation = QString::number(accumulator, 'g', 15) + " " + pending + " " + current + " =";
        const bool calculated = !pending.isEmpty() && !waiting;
        if (calculated && !evaluate()) return;
        accumulator = current.toDouble();
        pending = token == "=" ? QString() : token;
        history = token == "=" && calculated ? calculation : current + " " + token;
        waiting = true;
        finished = token == "=";
    }
}
bool CalculatorEngine::evaluate() {
    const double rhs = current.toDouble();
    if (pending == "/" && rhs == 0) {
        history = QString::number(accumulator, 'g', 15) + " / " + current + " =";
        current = "Error"; error = true; pending.clear(); waiting = true; return false;
    }
    if (pending == "+") accumulator += rhs;
    else if (pending == "-") accumulator -= rhs;
    else if (pending == "*") accumulator *= rhs;
    else if (pending == "/") accumulator /= rhs;
    if (!std::isfinite(accumulator)) {
        current = "Error"; history = "Result out of range"; error = true;
        pending.clear(); waiting = true; return false;
    }
    current = QString::number(accumulator, 'g', 15);
    return true;
}
