#include "mainwindow.h"
#include <QApplication>
#include <QTime>

void delay() {
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int last_game_stat = -1;
    while (true) {
        MainWindow w(last_game_stat);
        w.show();
        while (w.play_game_clicked == 0 || (w.game->stat != Game::Lose && w.game->stat != Game::Win))
            delay();
        last_game_stat = w.game->stat;
    }
    return a.exec();
}
