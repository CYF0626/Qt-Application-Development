#include <QtTest>
#include "../calculatorengine.h"

class EngineTests : public QObject {
    Q_OBJECT
private slots:
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
