#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>

class TimerBtn : public QPushButton
{
public:
    TimerBtn(QWidget *parent = nullptr);
    ~ TimerBtn();

    // 重写mouseReleaseEvent(从父类里找到有这个函数)
    virtual void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QTimer  *_timer;
    int _counter;
};

#endif // TIMERBTN_H
