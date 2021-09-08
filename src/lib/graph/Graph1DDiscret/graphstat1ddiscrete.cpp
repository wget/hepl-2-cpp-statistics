#include "graphstat1ddiscrete.h"

#include <string.h>

#include <QtGui/QPainter>

#include "../../../Stat1DStudy.hpp"
#include "ui_graphstat1ddiscrete.h"

GraphStat1DDiscrete::GraphStat1DDiscrete(const Stat1DStudy& E1, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::GraphStat1DDiscrete) {
  ui->setupUi(this);
  QPainter painter(this);
  std::cout << std::endl << "dans GraphStat1DDiscrete merce" << std::endl;
  DataSourceSerieDiscrete* p =
      dynamic_cast<DataSourceSerieDiscrete*>((E1.getSample())->getDataSource());
  L = new HeplList<Data1D>(p->getItemOccurrenceList());  //-------------------

  char Buff[10];

  sprintf(Buff, "%6.1f", E1.getMean());
  ui->lineMoyenne->setText(Buff);
  sprintf(Buff, "%6.1f", E1.getStandardDeviation());
  ui->lineEcartType->setText(Buff);
  // sprintf(Buff,"%6.1f",E1.getSample()->getDataSource()->getHeadcountTotal());
  sprintf(Buff, "%6.1f", E1.getMedian());
  ui->lineMediane->setText(Buff);
  float M[5];
  int i = 0;
  memcpy(M, E1.getMode(), 40);

  char BMode[20];
  BMode[0] = '\0';

  while (M[i]) {
    sprintf(Buff, "%6.1f  ", M[i]);
    std::cout << "----" << Buff << std::endl;
    strcat(BMode, Buff);
    i++;
  }

  ui->lineMode->setText(BMode);
}

GraphStat1DDiscrete::~GraphStat1DDiscrete() { delete ui; }

void GraphStat1DDiscrete::paintEvent(QPaintEvent* event)
// void GraphStat1DContinue::paintEvent()
{
  QPainter painter(this);
  // Etendue
  int Taille = L->getNumberItems();
  float Etendue = ((Data1D&)L->getElement(L->getNumberItems() - 1)).getValue() -
                  ((Data1D&)L->getElement(0)).getValue();
  int EffMin = ((Data1D&)L->getElement(0)).getHeadcount(),
      EffMax = ((Data1D&)L->getElement(Taille - 1)).getHeadcount();

  for (int i = 1; i < Taille - 1; i++) {
    if (((Data1D&)L->getElement(i)).getHeadcount() < EffMin)
      EffMin = ((Data1D&)L->getElement(i)).getHeadcount();
    if (((Data1D&)L->getElement(i)).getHeadcount() > EffMax)
      EffMax = ((Data1D&)L->getElement(i)).getHeadcount();
  }

  int EcartY = 170 / EffMax;
  int EcartX = 400 / Etendue;

  // Tracer l'histogramme
  for (int i = 0; i < Taille; i++)
    painter.drawRect(50 + EcartX * (((Data1D&)L->getElement(i)).getValue() -
                                    ((Data1D&)L->getElement(0)).getValue()),
                     190 - ((Data1D&)L->getElement(i)).getHeadcount() * EcartY,
                     5, ((Data1D&)L->getElement(i)).getHeadcount() * EcartY);

  // Tracer l'histogramme cumule
  int Hauteur = 0;
  int EffCumule = 0;
  for (int i = 0; i < Taille; i++)
    EffCumule += ((Data1D&)L->getElement(i)).getHeadcount();

  for (int i = 0; i < Taille; i++) {
    Hauteur += ((Data1D&)L->getElement(i)).getHeadcount();
    painter.drawRect(50 + EcartX * (((Data1D&)L->getElement(i)).getValue() -
                                    ((Data1D&)L->getElement(0)).getValue()),
                     440 - Hauteur * 180 / EffCumule, 5,
                     Hauteur * 180 / EffCumule);
  }

  // Ecriture des valeurs
  char Buff[10];
  for (int i = 0; i < Taille; i++) {
    sprintf(Buff, "%6.1f", ((Data1D&)L->getElement(i)).getValue());
    painter.drawText(30 + EcartX * ((Data1D&)L->getElement(i)).getValue() -
                         ((Data1D&)L->getElement(0)).getValue(),
                     220, Buff);  // --------------
    painter.drawText(30 + EcartX * ((Data1D&)L->getElement(i)).getValue() -
                         ((Data1D&)L->getElement(0)).getValue(),
                     470, Buff);
    //		painter.drawText(30 + EcartX * i,470,Buff);
  }
  // Tracer la mediane
  painter.setPen(Qt::red);
  painter.drawLine(35, 350, 480, 350);
  // Tracer des axes
  painter.setPen(Qt::black);
  painter.drawLine(35, 18, 35, 190);
  painter.drawLine(35, 190, 480, 190);
  painter.drawLine(35, 258, 35, 440);
  painter.drawLine(35, 440, 480, 440);
  painter.drawLine(32, 20, 38, 20);
  painter.drawLine(32, 260, 38, 260);
}
