#include "mainwindow.h"
#include "ui_calculator.h"
#include <QKeyEvent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::Calculator) {
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("实验一 · 带键盘事件的计算器"));
    // Both input methods dispatch to exactly the same state machine.
    for (auto *button : findChildren<QPushButton *>()) {
        connect(button, &QPushButton::clicked, this, [this, button] {
            handleInput(button->property("inputToken").toString());
        });
    }
    installEventFilter(this);
    for (auto *child : findChildren<QWidget *>()) child->installEventFilter(this);
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::handleInput(const QString &token) {
    engine.input(token);
    ui->displayEdit->setText(engine.display());
    ui->expressionLabel->setText(engine.expression());
    ui->hintLabel->setText(engine.display() == "Error"
        ? QString::fromUtf8("无法计算：除数为零或结果超出范围。输入数字或按 C 重新开始。")
        : QString::fromUtf8("支持鼠标和键盘混合输入 · Esc 清除 · Backspace 退格"));
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *key = static_cast<QKeyEvent *>(event);
        QString token;
        if (key->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier))
            return QWidget::eventFilter(watched, event);
        if (key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter) token = "=";
        else if (key->key() == Qt::Key_Backspace) token = "Backspace";
        else if (key->key() == Qt::Key_Escape || key->key() == Qt::Key_Delete || key->key() == Qt::Key_C) token = "C";
        else if (QString("0123456789.+-*/=").contains(key->text()) && key->text().size() == 1)
            token = key->text();
        if (!token.isEmpty()) { handleInput(token); return true; }
    }
    return QWidget::eventFilter(watched, event);
}
