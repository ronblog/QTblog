#include "cashflowbarseries.h"

CashFlowBarSeries::CashFlowBarSeries(CashFlowBarSeries* linked, QObject *parent)
	:QStackedBarSeries(parent)
{
	linkedSeries = linked;
}
