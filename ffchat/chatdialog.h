#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include "statewidget.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

private:
    void ShowSearch(bool bsearch = false);
    // 用作测试
    void addChatUserList();

    void AddLBGroup(StateWidget* lb);
    void ClearLabelState(StateWidget* lb);

    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    QList<StateWidget*> _lb_list;

public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
};

#endif // CHATDIALOG_H
