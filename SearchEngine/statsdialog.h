#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = 0);
    ~StatsDialog();
    void setStats(int pages,int words, std::vector< std::pair<std::string,int> >& top50);
private:
    Ui::StatsDialog *ui;
};

#endif // STATSDIALOG_H
