#include "editplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpressionMatch>


class PythonHighter: public QSyntaxHighlighter
{
public:
	// QSyntaxHighlighter interface
	PythonHighter(QTextDocument *parent) : QSyntaxHighlighter( parent)
	{

	}
protected:
	virtual void highlightBlock(const QString &text);
};

void PythonHighter::highlightBlock(const QString &text)
{
	QStringList keywordPatterns;
	keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
					<< "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
					<< "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
					<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
					<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
					<< "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
					<< "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
					<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
					<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
					<< "\\bvoid\\b" << "\\bvolatile\\b" << "\\bstring\\b"
			<< "\\bif\\b" << "\\belse\\b" << "\\band\\b" << "\\bfor\\b"
			<< "\\bwhile\\b" << "\\bnumber\\b" << "\\breturn\\b"
			<< "\\bsqrt\\b" << "\\bcontinue\\b" << "\\bbreak\\b"
			<< "\\bcheck\\b" << "\\bchoice\\b" << "\\bformat\\b"
			<< "\\bgroup\\b" << "\\bvas\\b" << "\\btime\\b"
			<< "\\bdate\\b" << "\\bedit\\b" << "\\bexit\\b";

	QTextCharFormat myClassFormat;
	myClassFormat.setFontWeight(QFont::Bold);
	myClassFormat.setForeground(Qt::darkMagenta);

	foreach (auto rule, keywordPatterns)
	{
		QRegularExpression expression(rule);
		 QRegularExpressionMatchIterator i = expression.globalMatch(text);
		 while (i.hasNext())
		 {
		   QRegularExpressionMatch match = i.next();
		   setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
		 }
	}
}



EditPlugin::EditPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

QString EditPlugin::name() {return "C++Edit";}

void EditPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *EditPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *EditPlugin::createWidget(QWidget* parent)
{
	auto textedit = new QTextEdit(parent);
	textedit->setTabStopDistance(40);


	auto ht = new PythonHighter(textedit->document());
	return textedit;

}

QMenu *EditPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &EditPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
