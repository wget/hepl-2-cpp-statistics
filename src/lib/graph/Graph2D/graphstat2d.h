#ifndef GRAPHSTAT2D_H
#define GRAPHSTAT2D_H

#include <QMainWindow>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include "../../../Stat2DStudy.hpp"
#include "../../../DataSourceSerie2D.hpp"

namespace Ui {
class GraphStat2D;
}

class GraphStat2D : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphStat2D(const Stat2DStudy*,QWidget *parent = 0);
    ~GraphStat2D();
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_ButtonTracer_clicked();
    void on_ButtonSelectionner_clicked();
    void on_ButtonAnnuler_clicked();

private:
    Ui::GraphStat2D 		*ui;
    QPoint      			PointDepart,
    		      			PointArrivee;
    bool        			Pt,
                			TracerLigne;
    float       			MinX,MinY,
                			MaxX,MaxY;
                
    HeplList<Data2D>* 	L ;
    HeplList<Data2D>*	LUndo ;
    DataSourceSerie2D* 	p;
    Stat2DStudy*			EtudeLocal;

};

#endif // GRAPHSTAT2D_H
