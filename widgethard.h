#ifndef WIDGETHARD_H
#define WIDGETHARD_H

#include <QWidget>

const int BLOCK_SIZE=25; //Длина стороны одного квадратного элемента
const int MARGIN=5; //Граница сцены
const int AREA_ROW=20; //Количество строк сцены
const int AREA_COL=12; //Количество столбцов сцены

//направление
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};

//Определение информации о границах
struct Border
{
    int ubound;
    int dbound;
    int lbound;
    int rbound;
};

//координата
struct block_point
{
    int pos_x;
    int pos_y;
    //    block_point(int x,int y):pos_x(x),pos_y(y){}
};

namespace Ui {
class WidgetHard;
}

class WidgetHard : public QWidget
{
    Q_OBJECT

public:
    void InitGame();
    void StartGame(); //Начало игры
    void GameOver(); //конец

    void ResetBlock(); //Окно сброса настроек
    void BlockMove(Direction dir); //Изменение площади
    void BlockRotate(int block[4][4]); //вращение
    void CreateBlock(int block[4][4],int block_id); //Генерация блоков
    void GetBorder(int block[4][4],Border &border); //Вычисление границы
    void ConvertStable(int x,int y); //Преобразование в стабильный блок
    bool IsCollide(int x,int y,Direction dir); //столкнется ли он

public:
    explicit WidgetHard(QWidget *parent = 0);
    ~WidgetHard();

    virtual void paintEvent(QPaintEvent *event); //Обновление сцены
    virtual void timerEvent(QTimerEvent *event); //Событие по таймеру
    virtual void keyPressEvent(QKeyEvent *event); //Отклик клавиатуры
private:
    Ui::WidgetHard *ui;

private:
    int game_area[AREA_ROW][AREA_COL]; //Область сцены, 1 представляет активный квадрат, 2 представляет стабильный квадрат, а 0 представляет пустой квадрат
    block_point block_pos; //Текущие квадратные координаты
    int cur_block[4][4]; //Текущая квадратная форма
    Border cur_border; //Текущая граница квадрата
    int next_block[4][4]; //Следующая квадратная форма
    bool isStable; //Стабильна ли текущая площадь?
    int score;  //Счет в игре
    int game_timer; //Таймер сброса квадрата
    int paint_timer; //Таймер обновления рендеринга
    int speed_ms; //Уменьшающийся временной интервал
    int refresh_ms; //Интервал обновления

};

#endif // WIDGETHARD_H

