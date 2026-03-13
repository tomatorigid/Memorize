#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QWheelEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 用于捕获 Ctrl + 滚轮事件
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void toggleAlwaysOnTop(bool checked);
    void autoSaveToFile();

private:
    QCheckBox *topCheckBox;
    QTextEdit *editor;
    QTimer *saveTimer;
    QString savePath;

    void loadFile();
};

#endif // MAINWINDOW_H
