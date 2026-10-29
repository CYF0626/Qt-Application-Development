#include <QtTest>
#include "../calculatorengine.h"

class EngineTests : public QObject {
    Q_OBJECT
private slots:
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
