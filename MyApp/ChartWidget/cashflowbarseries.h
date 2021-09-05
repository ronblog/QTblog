#ifndef CASHFLOWBARSERIES_H
#define CASHFLOWBARSERIES_H

#include <QStackedBarSeries>
QT_CHARTS_USE_NAMESPACE

class CashFlowBarSeries : public QStackedBarSeries
{
public:
	CashFlowBarSeries(CashFlowBarSeries* linked,QObject *parent= nullptr);

	CashFlowBarSeries* linkedSeries;
};

#endif // CASHFLOWBARSERIES_H
