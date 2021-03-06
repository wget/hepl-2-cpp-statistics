#ifndef GRAPHSTAT1DCONTINUE_H
#define GRAPHSTAT1DCONTINUE_H
#include "../../../Stat1DStudy.hpp"
#include <QMainWindow>

namespace Ui {
class GraphStat1DContinue;
}

class GraphStat1DContinue : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphStat1DContinue(const Stat1DStudy&, QWidget *parent = 0);
    ~GraphStat1DContinue();
    //void paintEvent();
    void paintEvent();

private:
    Ui::GraphStat1DContinue *ui;
    HeplList<Data1D>* L ;
    DataSourceSerieContinue* p;
};

#endif // GRAPHSTAT1DCONTINUE_H
