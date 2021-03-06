#ifndef GRAPHSTATIS1DDISCRETE_H
#define GRAPHSTATIS1DDISCRETE_H
#include <QMainWindow>

//#include "Echantillon.h"
#include "../../../Stat1DStudy.hpp"
namespace Ui {
class GraphStat1DDiscrete;
}

class GraphStat1DDiscrete : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphStat1DDiscrete(const Stat1DStudy& , QWidget *parent = 0);
//        explicit GraphStat1DDiscrete( Echantillon&, QWidget *parent = 0);
    ~GraphStat1DDiscrete();
 	void paintEvent(QPaintEvent *event);
private:
    Ui::GraphStat1DDiscrete *ui;
    HeplList<Data1D>* L ;
};

#endif // GRAPHSTATIS1DDISCRETE_H
