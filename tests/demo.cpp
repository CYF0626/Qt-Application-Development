// Continuous, transparent QtTest demonstration of the real calculator widget.
// Run from the repository root: calculator_demo <output folder> [--quick]
#include <QtTest>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../mainwindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    const QString out = argc > 1 ? QString::fromLocal8Bit(argv[1]) : ".";
    const bool quick = app.arguments().contains("--quick");
    QDir().mkpath(out);
    QWidget stage; stage.setWindowTitle("Lab1 Calculator Test Demo");
    stage.setStyleSheet("QWidget {font-family:'Microsoft YaHei';} QLabel {color:#182235;}");
    auto *layout = new QVBoxLayout(&stage);
    auto *title = new QLabel(QString::fromUtf8("实验一 带键盘事件的计算器 · 连续测试"));
    title->setStyleSheet("font-size:23px;font-weight:600;padding:8px;"); layout->addWidget(title);
    auto *subtitle = new QLabel(QString::fromUtf8("陈奕锋  |  Qt 6.9.2  |  QtTest 自动化鼠标与键盘事件  |  真实程序运行"));
    layout->addWidget(subtitle);
    auto *row = new QHBoxLayout; layout->addLayout(row);
    auto *calculator = new MainWindow; calculator->setFixedSize(440,620); row->addWidget(calculator);
    auto *side = new QVBoxLayout; row->addLayout(side);
    auto *scene = new QLabel; scene->setWordWrap(true); scene->setMinimumHeight(110);
    scene->setStyleSheet("font-size:21px;padding:14px;background:#e7f0fa;border-radius:10px;"); side->addWidget(scene);
    auto *logs = new QPlainTextEdit; logs->setReadOnly(true);
    logs->setStyleSheet("font-size:17px;background:#fff;border:1px solid #dae2ec;padding:10px;"); side->addWidget(logs);
    stage.resize(1080,760); stage.show();
    if (!QTest::qWaitForWindowExposed(&stage)) return 2;
    QFile results(out + "/demo-results.txt"); results.open(QIODevice::WriteOnly | QIODevice::Text);
    int failures = 0;
    auto wait = [&](int ms){QTest::qWait(quick ? 80 : ms);};
    auto screenshot = [&](const QString &name){ stage.grab().save(out + "/" + name + ".png"); };
    auto section = [&](const QString &text){scene->setText(text); wait(3000);};
    auto click = [&](const QString &name){auto *b=calculator->findChild<QPushButton *>("button"+name); QTest::mouseClick(b,Qt::LeftButton);wait(700);};
    auto keys = [&](const QString &text){QTest::keyClicks(calculator,text,Qt::NoModifier,quick?0:350);};
    auto key = [&](Qt::Key k){QTest::keyClick(calculator,k);wait(700);};
    auto check = [&](const QString &label,const QString &expected){
        const QString actual=calculator->findChild<QLineEdit *>("displayEdit")->text();
        const bool ok=actual==expected; if(!ok) ++failures;
        const QString line=QString(ok?"PASS  ":"FAIL  ")+label+" | expected="+expected+" actual="+actual;
        logs->appendPlainText(line);results.write((line+"\n").toUtf8());wait(2200);
    };
    section(QString::fromUtf8("01 / 鼠标小数运算\n12.5 + 3.25 = 15.75"));
    screenshot("01-interface");
    for(const auto &n:QStringList{"1","2","Decimal","5","Add","3","Decimal","2","5","Equals"})click(n);
    check("Mouse decimal", "15.75"); screenshot("02-mouse-decimal"); wait(4000);
    section(QString::fromUtf8("02 / 键盘计算\n7 * 8 = 56")); key(Qt::Key_Escape); keys("7*8");key(Qt::Key_Return);check("Keyboard", "56");screenshot("03-keyboard");wait(4000);
    section(QString::fromUtf8("03 / 退格和清除\n123 → 退格 → 12 → Esc → 0"));
    key(Qt::Key_Escape);keys("123");key(Qt::Key_Backspace);check("Backspace", "12");screenshot("04-backspace");key(Qt::Key_Escape);check("Clear", "0");wait(4000);
    section(QString::fromUtf8("04 / 除零和恢复\n8 / 0 → Error\nC 后重新计算 6 / 2 = 3"));
    keys("8/0=");check("Zero division", "Error");screenshot("05-zero-division");wait(4000);
    click("Clear");keys("6/2=");check("Recover", "3");wait(4000);
    section(QString::fromUtf8("05 / 连续运算与结果继续使用\n2 + 3 × 4 = 20\n再 + 5 = 25"));
    key(Qt::Key_Escape);keys("2+3*4=");check("Immediate chain", "20");keys("+5=");check("Continue result", "25");screenshot("06-chain");wait(4000);
    section(QString::fromUtf8("06 / 异常输入和混合输入\n1.2.3 → 1.23\n鼠标 +、键盘 2 = → 3.23"));
    key(Qt::Key_Escape);keys("1.2.3");check("Duplicate decimal", "1.23");screenshot("07-duplicate-decimal");click("Add");keys("2=");check("Mixed input", "3.23");wait(4000);
    section(QString::fromUtf8("07 / 运算符替换和结果编辑\n2 + * 3 = 6\n12 + 3 = 15，退格后输入2 → 12"));
    key(Qt::Key_Escape);keys("2+*3=");check("Operator replacement", "6");key(Qt::Key_Escape);keys("12+3=");key(Qt::Key_Backspace);keys("2");check("Edit completed result", "12");wait(4000);
    section(QString::fromUtf8("08 / 展示真实 Git 提交历史\n功能实现、测试、问题修复与界面完善"));
    QProcess git;git.start("git",{"log","--oneline","--decorate","-10"});git.waitForFinished(5000);
    logs->appendPlainText("\nGIT COMMIT HISTORY\n"+QString::fromUtf8(git.readAllStandardOutput()));
    screenshot("08-git-history");wait(16000);
    section(QString::fromUtf8("测试结束\n以上记录来自实际运行结果"));
    screenshot("09-test-summary");wait(5000);
    results.close(); return failures ? 1 : 0;
}
