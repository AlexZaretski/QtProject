#include <time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include "widget.h"
#include "ui_widget.h"

//фигуры
int item1[4][4]=
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
};
int item2[4][4]=
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
};
int item3[4][4]=
    {
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
};
int item4[4][4]=
    {
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
};
//左S
int item5[4][4]=
    {
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
};
int item6[4][4]=
    {
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,1},
        {0,0,0,0}
};
int item7[4][4]=
    {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
};

//Копия квадратного узора
inline void block_cpy(int dblock[4][4],int sblock[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dblock[i][j]=sblock[i][j];
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Настройка размера макета окна
    resize(AREA_COL*BLOCK_SIZE+MARGIN*4+4*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE+MARGIN*2);
    //Инициализация игры
    InitGame();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //Граница поля
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE);
    //
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(next_block[i][j]==1)
                painter.drawRect(MARGIN*3+AREA_COL*BLOCK_SIZE+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    //Ничья
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(QRect(MARGIN*3+AREA_COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4),Qt::AlignCenter,"score: "+QString::number(score));


    //падающий квадрат и устойчивый, цвет зависит от setPen
    for(int i=0;i<AREA_ROW;i++)
        for(int j=0;j<AREA_COL;j++)
        {
            //Активные квадраты
            if(game_area[i][j]==1)
            {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            //Статические квадраты
            else if(game_area[i][j]==2)
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
}

void Widget::timerEvent(QTimerEvent *event)
{
    //ПАДЕНИЕ
    if(event->timerId()==game_timer)
        BlockMove(DOWN);
    //Обновление экрана
    if(event->timerId()==paint_timer)
        update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        BlockMove(UP);
        break;
    case Qt::Key_Down:
        BlockMove(DOWN);
        break;
    case Qt::Key_Left:
        BlockMove(LEFT);
        break;
    case Qt::Key_Right:
        BlockMove(RIGHT);
        break;
    case Qt::Key_Space:
        BlockMove(SPACE);
        break;
    default:
        break;
    }
}

void Widget::CreateBlock(int block[4][4],int block_id)
{
    switch (block_id)
    {
    case 0:
        block_cpy(block,item1);
        break;
    case 1:
        block_cpy(block,item2);
        break;
    case 2:
        block_cpy(block,item3);
        break;
    case 3:
        block_cpy(block,item4);
        break;
    case 4:
        block_cpy(block,item5);
        break;
    case 5:
        block_cpy(block,item6);
        break;
    case 6:
        block_cpy(block,item7);
        break;
    default:
        break;
    }
}

void Widget::GetBorder(int block[4][4],Border &border)
{
    //Вычисление границ игрового поля
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(block[i][j]==1)
            {
                border.dbound=i;
                break; //пока в последней строке не 1
            }
    for(int i=3;i>=0;i--)
        for(int j=0;j<4;j++)
            if(block[i][j]==1)
            {
                border.ubound=i;
                break;
            }
    for(int j=0;j<4;j++)
        for(int i=0;i<4;i++)
            if(block[i][j]==1)
            {
                border.rbound=j;
                break;
            }
    for(int j=3;j>=0;j--)
        for(int i=0;i<4;i++)
            if(block[i][j]==1)
            {
                border.lbound=j;
                break;
            }
    //    qDebug()<<cur_border.ubound<<cur_border.dbound<<cur_border.lbound<<cur_border.rbound;
}

void Widget::setSpeed(int speed) {
    speed_ms = speed;
}

void Widget::InitGame()
{
    for(int i=0;i<AREA_ROW;i++)
        for(int j=0;j<AREA_COL;j++)
            game_area[i][j]=0;

    refresh_ms=30;

    srand(time(0));

    //начало
    score=0;

    //функция начала игры
    StartGame();
}

void Widget::ResetBlock()
{
    //Генерация фигуры
    block_cpy(cur_block,next_block);
    GetBorder(cur_block,cur_border);

    //Генерация след фигуры
    int block_id=rand()%7;
    CreateBlock(next_block,block_id);

    //начальные координаты фигуры(привязан верхний левый угол)
    block_point start_point;
    start_point.pos_x=AREA_COL/2-2;
    start_point.pos_y=0;
    block_pos=start_point;
}

void Widget::StartGame()
{
    game_timer=startTimer(speed_ms); //Игровой таймер
    paint_timer=startTimer(refresh_ms); //Интерфейс, чтобы обновить таймер
    //начальный след квадрат
    int block_id=rand()%7;
    CreateBlock(next_block,block_id);
    ResetBlock(); //генерация блока
}

void Widget::GameOver()
{
    //конец игры
    killTimer(game_timer);
    killTimer(paint_timer);
    QMessageBox::information(this,"failed","game over");

}

void Widget::BlockRotate(int block[4][4])
{
    int temp_block[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp_block[3-j][i]=block[i][j];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            block[i][j]=temp_block[i][j];
}

void Widget::ConvertStable(int x,int y)
{
    for(int i=cur_border.ubound;i<=cur_border.dbound;i++)
        for(int j=cur_border.lbound;j<=cur_border.rbound;j++)
            if(cur_block[i][j]==1)
                game_area[y+i][x+j]=2;
}

bool Widget::IsCollide(int x,int y,Direction dir)
{
    //Используется скопированное временное поле, чтобы принять решение
    int temp_block[4][4];
    block_cpy(temp_block,cur_block);
    Border temp_border;
    GetBorder(temp_block,temp_border);
    switch(dir)
    {
    case UP:
        BlockRotate(temp_block);
        GetBorder(temp_block,temp_border); //Пересчитайте границу после поворота
        break;
    case DOWN:
        y+=1;
        break;
    case LEFT:
        x-=1;
        break;
    case RIGHT:
        x+=1;
        break;
    default:
        break;
    }
    for(int i=temp_border.ubound;i<=temp_border.dbound;i++)
        for(int j=temp_border.lbound;j<=temp_border.rbound;j++)
            if((game_area[y+i][x+j]==2&&temp_block[i][j]==1)||x+temp_border.lbound<0||x+temp_border.rbound>AREA_COL-1)
                return true;
    return false;
}

void Widget::BlockMove(Direction dir)
{
    switch (dir) {
    case UP:
        if(IsCollide(block_pos.pos_x,block_pos.pos_y,UP))
            break;
        //Поворот на 90 градусов против часовой стрелки
        BlockRotate(cur_block);
        //Чтобы предотвратить ошибки после поворота, i и j сбрасывают значения квадратов с 0 на 4
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
        GetBorder(cur_block,cur_border);
        break;
    case DOWN:
        //Квадрат больше не будет двигаться, когда достигнет границы
        if(block_pos.pos_y+cur_border.dbound==AREA_ROW-1)
        {
            ConvertStable(block_pos.pos_x,block_pos.pos_y);
            ResetBlock();
            break;
        }
        //Обнаружение столкновений, вычисляйте только верхнюю и нижнюю левую и правую границы
        if(IsCollide(block_pos.pos_x,block_pos.pos_y,DOWN))
        {
            //Только если в конце концов он не упадет, то превратится в устойчивый квадрат.
            ConvertStable(block_pos.pos_x,block_pos.pos_y);
            ResetBlock();
            break;
        }
        //Восстановление сцены на блоке, чтобы удалить остатки блока во время перемещения
        for(int j=cur_border.lbound;j<=cur_border.rbound;j++)
            game_area[block_pos.pos_y][block_pos.pos_x+j]=0;
        //Если столкновения не будет, то упадет одна сетка
        block_pos.pos_y+=1;
        //Квадрат опускается на одну сетку и копируется в сцену.
        for(int i=0;i<4;i++) //Должно быть от 0 до 4 вместо граничного индекса, принимая во внимание пересчет границы после поворота
            for(int j=cur_border.lbound;j<=cur_border.rbound;j++)
                if(block_pos.pos_y+i<=AREA_ROW-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2) //массив сцен не пересекает границу и не стирает устойчивые квадраты
                    game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
        break;
    case LEFT:
        //Двигаясь к левой границе, больше не сталкивайтесь с левой
        if(block_pos.pos_x+cur_border.lbound==0||IsCollide(block_pos.pos_x,block_pos.pos_y,LEFT))
            break;
        //Восстановление сцены с правой стороны квадрата, чтобы убрать остатки квадрата во время движения
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++)
            game_area[block_pos.pos_y+i][block_pos.pos_x+3]=0;
        block_pos.pos_x-=1;
        //Переместил квадратную сетку на одну клетку влево и скопировал ее в сцену
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++)
            for(int j=0;j<4;j++)
                if(block_pos.pos_x+j>=0&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2) //массив сцен не пересекает линию
                    game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
        break;
    case RIGHT:
        if(block_pos.pos_x+cur_border.rbound==AREA_COL-1||IsCollide(block_pos.pos_x,block_pos.pos_y,RIGHT))
            break;
        //Восстановление сцены с левой стороны квадрата, чтобы убрать остатки квадрата во время движения
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++)
            game_area[block_pos.pos_y+i][block_pos.pos_x]=0;
        block_pos.pos_x+=1;
        //Переместите квадратную сетку вправо и скопируйте ее в сцену
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++)
            for(int j=0;j<4;j++)
                if(block_pos.pos_x+j<=AREA_COL-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2) //массив сцен не пересекает линию
                    game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
        break;
    case SPACE: //в конце концов
        //Перемещайтесь вниз по сетке за сеткой, пока не сможете двигаться дальше
        while(block_pos.pos_y+cur_border.dbound<AREA_ROW-1&&!IsCollide(block_pos.pos_x,block_pos.pos_y,DOWN))
        {
            //Восстановление сцены на блоке, чтобы удалить остатки блока во время перемещения
            for(int j=cur_border.lbound;j<=cur_border.rbound;j++)
                game_area[block_pos.pos_y][block_pos.pos_x+j]=0;
            //Если столкновения не будет, то упадет одна сетка
            block_pos.pos_y+=1;
            //Квадрат опускается на одну сетку и копируется в сцену, обрати внимание на левую и правую границы.
            for(int i=0;i<4;i++) //Должно быть от 0 до 4
                for(int j=cur_border.lbound;j<=cur_border.rbound;j++)
                    if(block_pos.pos_y+i<=AREA_ROW-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2) //массив сцен не пересекает границу и не стирает устойчивые квадраты
                        game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
        }
        ConvertStable(block_pos.pos_x,block_pos.pos_y);
        ResetBlock();
        break;
    default:
        break;
    }
    // удаление строк, и строки, расположенные над всей сценой, по очереди будут перемещены вниз
    int i=AREA_ROW-1;
    int line_count=0; //Записыввается количество строк
    while(i>=1)
    {
        bool is_line_full=true;
        for(int j=0;j<AREA_COL;j++)
            if(game_area[i][j]==0)
            {
                is_line_full=false;
                i--;
                break;
            }
        if(is_line_full)
        {
            for(int k=i;k>=1;k--)
                for(int j=0;j<AREA_COL;j++)
                    game_area[k][j]=game_area[k-1][j];
            line_count++;//Увеличение количество удаляемых строк с каждым разом
        }
    }
    score+=line_count*10; //вести счет
    //Определение, окончена ли игра
    for(int j=0;j<AREA_COL;j++)
        if(game_area[0][j]==2) //Вверху также есть устойчивые квадраты
            GameOver();
}
