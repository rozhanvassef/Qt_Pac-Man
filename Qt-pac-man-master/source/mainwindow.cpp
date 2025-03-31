#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int last_game_stat, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), menu(new Ui::MainWindow) {
    \
    menu->setupUi(this);
    setWindowTitle(tr("pac-man"));

    QPushButton *welcome = new QPushButton("Welcome to pac-man", this);
    welcome->setStyleSheet("QPushButton {background-color : black; font-family: Fixedsys; color: blue; font-size: 37px;}");
    welcome->setGeometry(QRect(QPoint(140, 50), QSize(400, 50)));

    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/game_objects/sounds/Beginning.mp3"));
    music->setVolume(100);
    music->play();


    if (last_game_stat == 2) {
        QPushButton *lose_button = new QPushButton("You Lost!", this);
        lose_button->setStyleSheet("QPushButton {background-color : black ;font-family: Fixedsys; color: red ;font-size: 90px;}");
        lose_button->setGeometry(QRect(QPoint(100, 150), QSize(500, 100)));
    }
    if (last_game_stat == 1) {
        QPushButton *win_button = new QPushButton("You Won!", this);
        win_button->setStyleSheet("QPushButton {background-color : black ;font-family: Fixedsys; color: green ;font-size: 90px;}");
        win_button->setGeometry(QRect(QPoint(120, 150), QSize(450, 100)));
    }

    play_game_clicked = 0;

    QPushButton *play_game = new QPushButton("Play", this);
    play_game->setStyleSheet("QPushButton {background-color : yellow ;font-family: Fixedsys; color: black ;font-size: 25px;}");
    play_game->setGeometry(QRect(QPoint(240, 320), QSize(200, 50)));

    QPushButton *exit = new QPushButton("Exit", this);
    exit->setStyleSheet("QPushButton {background-color : yellow ;font-family: Fixedsys; color: black ;font-size: 25px;}");
    exit->setGeometry(QRect(QPoint(240, 380), QSize(200, 50)));

    connect(play_game, &QPushButton::clicked, this, [&]() {
        play_game_clicked = 1;

        ui->setupUi(this);
        setWindowTitle(tr("pac-man"));

        ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
        ui->graphicsView->setBackgroundBrush(Qt::black);
        ui->graphicsView->setFocusPolicy(Qt::NoFocus);

        int map_height = 20, map_width = 29;
        int x = 50, y = 50;
        int w = (map_width * GameObject::Width);
        int h = (map_height * GameObject::Width);
        ui->graphicsView->setGeometry(x, y, w, h);
        game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt");
        ui->graphicsView->setScene(game);
        initLabels();
        game->start();
    });

    connect(exit, &QPushButton::clicked, this, [&]() {
        exit->clearFocus();
    });
}

void MainWindow::initLabels() {
    score_title = new QLabel(this);
    score_title->setText("score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys; color: white; font-size: 20px;}");
    score_title->setGeometry(50, 12, 60, 26);
    score_title->show();

    score = new QLabel(this);
    score->setIndent(-80);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 20px;}");
    score->setGeometry(120, 12, 180, 26);
    score->show();

    score_timer = new QTimer(this);
    score_timer->start(25);
    connect(score_timer, SIGNAL(timeout()), this , SLOT(update_score()));
}

void MainWindow::update_score() {
    score->setText(QString::number(game->get_score()));
    if (game->stat == Game::Win) {
        score_timer->stop();
    }
    if (game->stat == Game::Lose) {
        score_timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_A:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_S:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_D:
        game->pacman_next_direction(GameObject::Right);
        break;
    }
}


MainWindow::~MainWindow() {
    delete ui;
}
