#include <QtTest>
#include "../calculatorengine.h"

class EngineTests : public QObject {
    Q_OBJECT
private slots:
    void boundaries_data() {
        QTest::addColumn<QStringList>("tokens"); QTest::addColumn<QString>("expected");
        QTest::newRow("zero-division") << QStringList({"8","/","0","="}) << "Error";
        QTest::newRow("edit-result") << QStringList({"1","2","+","3","=","Backspace","2"}) << "12";
        QTest::newRow("error-recovery") << QStringList({"8","/","0","=","2","+","3","="}) << "5";
        QTest::newRow("backspace-after-operator") << QStringList({"1","2","+","Backspace","3","="}) << "15";
        QTest::newRow("new-number-after-result") << QStringList({"2","+","3","=","7"}) << "7";
        QTest::newRow("replace-operator") << QStringList({"2","+","*","3","="}) << "6";
        QTest::newRow("continue-result") << QStringList({"2","+","3","=","*","4","="}) << "20";
        QTest::newRow("missing-operand") << QStringList({"2","+","="}) << "2";
        QTest::newRow("repeated-equals") << QStringList({"2","+","3","=","="}) << "5";
        QTest::newRow("leading-decimal") << QStringList({".","5","+",".","5","="}) << "1";
        QTest::newRow("clear-pending") << QStringList({"8","/","C","2","+","3","="}) << "5";
        QTest::newRow("backspace-all") << QStringList({"1","Backspace","Backspace"}) << "0";
        QTest::newRow("decimal-precision") << QStringList({"0",".","1","+","0",".","2","="}) << "0.3";
    }
    void boundaries() {
        QFETCH(QStringList, tokens); QFETCH(QString, expected);
        CalculatorEngine e; for (const auto &t : tokens) e.input(t);
        QCOMPARE(e.display(), expected);
    }
    void arithmetic_data() {
        QTest::addColumn<QString>("keys"); QTest::addColumn<QString>("expected");
        QTest::newRow("add") << "12.5+3.25=" << "15.75";
        QTest::newRow("subtract") << "2-5=" << "-3";
        QTest::newRow("multiply") << "2.5*4=" << "10";
        QTest::newRow("divide") << "7/2=" << "3.5";
        QTest::newRow("chain") << "2+3*4=" << "20";
    }
    void arithmetic() {
        QFETCH(QString, keys); QFETCH(QString, expected);
        CalculatorEngine e;
        for (const auto &c : keys) e.input(QString(c));
        QCOMPARE(e.display(), expected);
    }
    void repeatedDecimal() {
        CalculatorEngine e;
        for (const auto &c : QString("1.2.3")) e.input(QString(c));
        QCOMPARE(e.display(), QString("1.23"));
    }
    void inputAndEditing() {
        CalculatorEngine e;
        e.input("1"); e.input("2"); e.input("."); e.input("5");
        QCOMPARE(e.display(), QString("12.5"));
        e.input("Backspace"); QCOMPARE(e.display(), QString("12."));
        e.input("C"); QCOMPARE(e.display(), QString("0"));
    }
};
QTEST_APPLESS_MAIN(EngineTests)
#include "engine_tests.moc"
