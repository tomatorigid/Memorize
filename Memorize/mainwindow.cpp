#include "MainWindow.h"
#include <QApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    topCheckBox = new QCheckBox("始终置顶", this);
    editor = new QTextEdit(this);

    layout->addWidget(topCheckBox);
    layout->addWidget(editor);
    setCentralWidget(centralWidget);

    savePath = qApp->applicationDirPath() + "/note.txt";
    loadFile();

    connect(topCheckBox, &QCheckBox::toggled, this, &MainWindow::toggleAlwaysOnTop);

    saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &MainWindow::autoSaveToFile);
    saveTimer->start(1000);

    editor->installEventFilter(this);

    setWindowTitle("Memorize 自动保存编辑器");
    resize(400, 500);
}

MainWindow::~MainWindow()
{
    autoSaveToFile();
}

void MainWindow::toggleAlwaysOnTop(bool checked)
{
    Qt::WindowFlags flags = this->windowFlags();
    if (checked) {
        flags |= Qt::WindowStaysOnTopHint;
    } else {
        flags &= ~Qt::WindowStaysOnTopHint;
    }

    this->setWindowFlags(flags);
    this->show();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == editor && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        if (wheelEvent->modifiers() & Qt::ControlModifier) {
            if (wheelEvent->angleDelta().y() > 0)
                editor->zoomIn(1);
            else
                editor->zoomOut(1);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::autoSaveToFile()
{
    QFile file(savePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(editor->toPlainText().toUtf8());
        file.close();
    }
}


void MainWindow::loadFile()
{
    QFile file(savePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        editor->setPlainText(QString::fromUtf8(file.readAll()));
        file.close();
    }
}
