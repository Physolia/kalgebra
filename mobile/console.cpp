/*************************************************************************************
 *  Copyright (C) 2007 by Aleix Pol <aleixpol@kde.org>                               *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#include "console.h"
#include <QFile>
#include <QHeaderView>

#include <klocale.h>

#include <analitza/variables.h>
#include <analitza/expression.h>

using namespace Analitza;

Console::Console(QWidget *parent) : QListWidget(parent), outs(0), m_mode(Evaluation) {}

Console::~Console() {}

bool Console::addOperation(const QString& op, bool mathml)
{
	QString result;
	a.setExpression(Expression(op, mathml));
	if(a.isCorrect()) {
		if(m_mode==Evaluation) {
			Expression res=a.evaluate();
			result = res.toString();
			a.insertVariable("ans", res);
		} else {
			Expression val=a.calculate();
			result = val.toString();
			a.insertVariable("ans", val);
		}
	}
	
	QListWidgetItem *item = new QListWidgetItem(this);
	QFont f = item->font();
	if(a.isCorrect()) {
		m_script += op; //Script won't have errors
		item->setText(QString("%1 = %2").arg(a.expression().toString()).arg(result));
		item->setToolTip(result);
		if(++outs % 2)
			item->setBackgroundColor(QColor(233,233,222));
		else
			item->setBackgroundColor(QColor(250,250,250));
	} else {
		item->setText(i18n("%1\nError: %2",op,a.errors().join("\n")));
		item->setBackgroundColor(QColor(255,222,222));
		item->setTextAlignment(Qt::AlignRight);
		f.setBold(true);
		item->setFont(f);
	}
	
// 	qApp->processEvents();
// 	this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
	emit changed();
	return a.isCorrect();
}

bool Console::loadScript(const QString& path)
{
	bool correct=false;
	if(!path.isEmpty()) {
		QStringList lines;
		QFile file(path);
		if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream stream(&file);
			QString line;
			correct=true;
			while (!stream.atEnd()) {
				line = stream.readLine(); // line of text excluding '\n'
				line = line.trimmed();
				if(!line.isEmpty())
					correct &= addOperation(line);
			}
			file.close();
		}

	}
	return correct;
}

bool Console::saveScript(const QString & path) const
{
	bool correct=false;
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			correct=false;
		else {
			QTextStream out(&file);
			QStringList::const_iterator it = m_script.begin();
			for(; it!=m_script.end(); ++it)
				out << *it << endl;
			
			correct=true;
		}
		file.close();
	}
	return correct;
}

bool Console::saveLog(const QString& path) const
{
	bool correct=false;
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			correct=false;
		else {
			QTextStream out(&file);
			for(int i=0; i<this->count(); i++)
				out << this->item(i)->text() << endl;
			
			correct=true;
		}
		file.close();
	}
	return correct;
}

#include "console.moc"