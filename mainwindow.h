#pragma once
#include <QWidget>
#include "calculatorengine.h"
namespace Ui { class Calculator; }
class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    Ui::Calculator *ui;
    CalculatorEngine engine;
    void handleInput(const QString &token);
};
