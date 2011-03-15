/*************************************************************************************
 *  Copyright (C) 2010 by Aleix Pol <aleixpol@kde.org>                               *
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

#ifndef EXPRESSIONTYPE_H
#define EXPRESSIONTYPE_H

#include "analitzaexport.h"
#include <QString>
#include <QList>
#include <QMap>

namespace Analitza
{

class ANALITZA_EXPORT ExpressionType
{
	public:
		///Just use undefined type when returning from a recursion
		enum Type { Error=0, Value, Vector, List, Lambda, Any, Many, Object, Undefined };
		QString toString() const;
		
		ExpressionType(Type t=Error, int any=-1);
		ExpressionType(Type t, const ExpressionType& contained, int s=0);
		ExpressionType(Type t, const QList<ExpressionType>& alternatives);
		
		/** Constructs a type that identifies a custom Object */
		ExpressionType(const QString& objectName);
		ExpressionType(const ExpressionType& t);
		
		~ExpressionType() {/* delete contained; */}
		
		bool operator==(const ExpressionType& t) const;
		bool operator!=(const ExpressionType& t) const { return !operator==(t); }
		ExpressionType operator=(const ExpressionType& et);
		
		/** Depth search to check if it's defined */
		bool isError() const;
		
		Type type() const { return m_type; }
		ExpressionType contained() const { Q_ASSERT(m_type==Vector || m_type==List); return m_contained.first(); }
		QList<ExpressionType> alternatives() const { Q_ASSERT(m_type==Many); return m_contained; }
		
		/** In case it's a Many type, it adds @p t as an alternative. If @p t is a Many type too, they will be merged */
		void addAlternative(const ExpressionType& t);
		int size() const { return m_size; }
		int anyValue() const { return m_any; }
		
		ExpressionType& addParameter(const ExpressionType& t);
		QList<ExpressionType> parameters() const { Q_ASSERT(m_type==Lambda); return m_contained; }
		ExpressionType returnValue() const;
		
		void addAssumption(const QString& bvar, const ExpressionType& t);
		QMap<QString, ExpressionType> assumptions() const;
		QMap<QString, ExpressionType>& assumptions();
		ExpressionType assumptionFor(const QString& bvar) const { return m_assumptions.value(bvar); }
		void addAssumptions(const QMap< QString, ExpressionType >& a);
		void clearAssumptions();
		
		/** Returns a new type with the stars solved according t @p info */
		ExpressionType starsToType(const QMap<int, ExpressionType>& info) const;
		
		bool isUndefined() const { return m_type==Undefined; }
		bool canReduceTo(const ExpressionType& type) const;
		int increaseStars(int stars, QMap<int, int>* values=0);
		
		ExpressionType& simplifyStars();
		
		/** when it's a many type, reduce to the one(s) that can be reduced to */
		void reduce(const ExpressionType& type);
		
		static ExpressionType minimumType(const ExpressionType& t1, const ExpressionType& t2);
	private:
		static void starsSimplification(ExpressionType& t, QMap<int, int>& reductions, int& next);
		
		Type m_type;
		///In case of list and vector the inside type
		QList<ExpressionType> m_contained;
		QMap<QString, ExpressionType> m_assumptions;
		union { int m_size; int m_any; };
        QString m_objectName;
};

}
#endif // EXPRESSIONTYPE_H
