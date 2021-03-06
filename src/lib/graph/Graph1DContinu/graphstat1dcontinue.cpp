#include "graphstat1dcontinue.h"
#include "ui_graphstat1dcontinue.h"
#include <QtGui/QPainter>

GraphStat1DContinue::GraphStat1DContinue(const Stat1DStudy& E1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphStat1DContinue)
{
    ui->setupUi(this);
this->p = dynamic_cast<DataSourceSerieContinue*>((E1.getSample())->getDataSource());
L = new HeplList<Data1D>(p->getItemOccurrenceList());
std::cout << "dans le graphique" << std::endl;
L->display();
char	Buff[10];
sprintf(Buff,"%6.1f",E1.getMean());
ui->lineMoyenne->setText(Buff);
sprintf(Buff,"%6.1f",E1.getStandardDeviation());
ui->lineEcartType->setText(Buff);
sprintf(Buff,"%6d",E1.getSample()->getDataSource()->getTotalHeadcount());   
sprintf(Buff,"%6.1f",E1.getMedian());   
ui->lineMediane->setText(Buff);
float	M[5];
int i = 0;
memcpy(M,E1.getMode(),40);

char BMode[20];
BMode[0] = '\0';

while (M[i])
{ 
sprintf(Buff,"%6.1f  ",M[i]);std::cout << "----" << Buff << std::endl;
strcat(BMode,Buff);
i++;
}

ui->lineMode->setText(BMode);
}

GraphStat1DContinue::~GraphStat1DContinue()
{
    delete ui;
}

void GraphStat1DContinue::paintEvent()
{
	int 	Taille = L->getNumberItems();
	float	Intervalle = p->getInterval();

	float Debut = p->getStart();
	unsigned int	EffMin = ((Data1D&)L->getElement(0)).getHeadcount(), EffMax = ((Data1D&)L->getElement(0)).getHeadcount();
	int	i = 1,NbIntervalle = 1;
	while (i<= Taille - 1)
		{ if (((Data1D&)L->getElement(i)).getHeadcount() < EffMin ) EffMin = ((Data1D&)L->getElement(i)).getHeadcount();
		  if (((Data1D&)L->getElement(i)).getHeadcount() > EffMax ) EffMax = ((Data1D&)L->getElement(i)).getHeadcount();
		  if (((Data1D&)L->getElement(i)).getValue() >= Debut + (NbIntervalle+1) * Intervalle) 
		     { NbIntervalle++;
		       continue;
		     }
		  NbIntervalle++;
		  i++;
		}

   QPainter painter(this);
// Tracer la mediane
    painter.setPen(Qt::red);
    painter.drawLine(35,350 , 480, 350 );

// Tracer des axes
 	painter.setPen(Qt::black);
 	painter.drawLine(35,18 , 35, 190 );
	painter.drawLine(35,190 , 480, 190 );
	painter.drawLine(35,258 , 35, 440 );
	painter.drawLine(35,440 , 480, 440 );
	painter.drawLine(32, 20, 38, 20);
   painter.drawLine(32,260 , 38, 260 );
// Tracer l'histogramme
i = 0;
int j = 0;
    while (j<NbIntervalle)
    { 
    if (((Data1D&)L->getElement(i)).getValue() > Debut + (j+1) * Intervalle) {j++;continue;}
    painter.drawLine(50 + j * 400 / NbIntervalle ,190 - ((Data1D&)L->getElement(i)).getHeadcount() * 170 / EffMax, 50 + j * 400 / NbIntervalle, 193); 
    painter.drawLine(50 + j * 400 / NbIntervalle ,190 - ((Data1D&)L->getElement(i)).getHeadcount() * 170 / EffMax, 50 + (j + 1) * 400 / NbIntervalle, 190 - ((Data1D&)L->getElement(i)).getHeadcount() * 170/ EffMax); 
    
    j++;
    if (((Data1D&)L->getElement(i)).getValue() > Debut + (j+1) * Intervalle) {j++;continue;}
    painter.drawLine(50 + j * 400 / NbIntervalle, 190 - ((Data1D&)L->getElement(i)).getHeadcount() * 170/ EffMax, 50 + j * 400 / NbIntervalle, 193); 
    i++;
    }
    
// Tracer l'histogramme cumule 
	 Debut = p->getStart();
	 int EffTotal = p->getTotalHeadcount();
	 int 	D1 = 0,D2 = ((Data1D&)L->getElement(0)).getHeadcount();
i=1; j = 1;
    while (j<NbIntervalle)
    {
    
    painter.drawLine(50 + j * 400 / NbIntervalle ,440 -D2*170/	EffTotal,50 + j * 400 / NbIntervalle ,443); 
    painter.drawLine(50 + 400 * (j-1) / NbIntervalle,440 -D1*170/EffTotal ,50 + 400 * j/NbIntervalle,440 -D2*170/EffTotal );
    D1 = D2;
    
    
    if (((Data1D&)L->getElement(i)).getValue() < Debut + (j+1) * Intervalle) {
        D2 += ((Data1D&)L->getElement(i)).getHeadcount();
        i++;j++;continue;}
        j++;
    }
     painter.drawLine(50 + 400 * (j-1) / NbIntervalle,440 -D1*170/EffTotal ,50 + 400 * j/NbIntervalle,440 -D2*170/EffTotal );
    painter.drawLine(50 + j * 400 / NbIntervalle ,440 -D2*170/	EffTotal,50 + j * 400 / NbIntervalle ,443); 

// Ecriture des valeurs 
	
	Debut = p->getStart();
	char	Buff[10];
	i = 0;
	while (i <= NbIntervalle + 1)
	{	sprintf(Buff,"%6.1f",Debut); 
		painter.drawText(30 + i * 400 / NbIntervalle ,220,Buff);
		painter.drawText(30 + i * 400 / NbIntervalle,470,Buff);
		Debut += Intervalle;
		i++;
	}

	sprintf(Buff,"%3d",EffMax);
	painter.drawText(5 ,20,Buff); 
	sprintf(Buff,"%3d",EffTotal);	
	painter.drawText(5 ,258,Buff); 

}

