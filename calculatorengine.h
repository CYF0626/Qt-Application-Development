#pragma once
#include <QString>

class CalculatorEngine {
public:
    void input(const QString &token);
    QString display() const { return current; }
    QString expression() const { return history; }
private:
    QString current = "0", history, pending;
    double accumulator = 0;
    bool waiting = false, finished = false, error = false;
    bool evaluate();
};
