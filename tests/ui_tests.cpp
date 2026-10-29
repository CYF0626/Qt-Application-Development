#include <QtTest>
#include <QLineEdit>
#include <QPushButton>
#include "../mainwindow.h"
class UiTests : public QObject {
    Q_OBJECT
private slots:
    void readableBackground() {
        QWidget host; host.setStyleSheet("background:#202020;");
        MainWindow w(&host); host.resize(460,640); host.show();
        QVERIFY(QTest::qWaitForWindowExposed(&host));
        QCOMPARE(host.grab().toImage().pixelColor(2,2), QColor("#f1f5fa"));
    }
    void mixedInput() {
        MainWindow w; w.show(); QVERIFY(QTest::qWaitForWindowExposed(&w));
        QTest::mouseClick(w.findChild<QPushButton *>("button1"), Qt::LeftButton);
        QTest::keyClicks(&w, "2.5+");
        QTest::mouseClick(w.findChild<QPushButton *>("button3"), Qt::LeftButton);
        QTest::keyClicks(&w, ".25=");
        QCOMPARE(w.findChild<QLineEdit *>("displayEdit")->text(), QString("15.75"));
    }
    void focusedButtonKeyboard() {
        MainWindow w; w.show(); QVERIFY(QTest::qWaitForWindowExposed(&w));
        auto *button = w.findChild<QPushButton *>("button7"); button->setFocus();
        QTest::keyClicks(button, "8/0"); QTest::keyClick(button, Qt::Key_Return);
        QCOMPARE(w.findChild<QLineEdit *>("displayEdit")->text(), QString("Error"));
        QTest::keyClick(button, Qt::Key_Escape);
        QTest::keyClicks(button, "123"); QTest::keyClick(button, Qt::Key_Backspace);
        QCOMPARE(w.findChild<QLineEdit *>("displayEdit")->text(), QString("12"));
    }
};
QTEST_MAIN(UiTests)
#include "ui_tests.moc"
