/*************************************************************************************
 *  Copyright (C) 2007 by Aleix Pol <aleixpol@gmail.com>                             *
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

#ifndef FUNCTIONIMPL_H
#define FUNCTIONIMPL_H

#include "expression.h"
#include "function.h"
#include "analitza.h"

class FunctionImpl
{
	public:
		enum ImplType { XType, YType, PolarType };
		explicit FunctionImpl(const Expression& e);
		FunctionImpl(const FunctionImpl& fi);
		virtual ~FunctionImpl();
		QStringList bvarList() { return func.bvarList(); }
		bool isCorrect() const { return func.isCorrect(); }
		QString toString() const { return func.expression().toString(); }
		
		virtual Axe axeType() const { return Cartesian; }
		virtual QPair<QPointF, QString> calc(const QPointF& dp)=0;
		virtual void updatePoints(const QRect& viewport, unsigned int resolution)=0;
		virtual QLineF derivative(const QPointF& p) const=0;
		virtual ImplType type() const=0;
		virtual FunctionImpl* copy()=0;
		
		QPointF *points;
		Analitza func;
		Expression *m_deriv;
		QRect m_last_viewport;
		
		unsigned int m_last_resolution;
		unsigned int m_last_max_res;
};

struct FunctionX : public FunctionImpl
{
	explicit FunctionX(const Expression &e) : FunctionImpl(e) {}
	FunctionX(const FunctionX &fx) : FunctionImpl(fx) {}
	
	void updatePoints(const QRect& viewport, unsigned int resolution);
	QPair<QPointF, QString> calc(const QPointF& dp);
	QLineF derivative(const QPointF& p) const;
	ImplType type() const { return XType; }
	virtual FunctionImpl* copy() { return new FunctionX(*this); }
};

struct FunctionY : public FunctionImpl
{
	explicit FunctionY(const Expression &e) : FunctionImpl(e) {}
	FunctionY(const FunctionY &fy) : FunctionImpl(fy) {}
	
	void updatePoints(const QRect& viewport, unsigned int resolution);
	QPair<QPointF, QString> calc(const QPointF& dp);
	QLineF derivative(const QPointF& p) const;
	ImplType type() const { return YType; }
	virtual FunctionImpl* copy() { return new FunctionY(*this); ; }
};

struct FunctionPolar : public FunctionImpl
{
	FunctionPolar(const Expression &e) : FunctionImpl(e) {}
	FunctionPolar(const FunctionPolar &fp) : FunctionImpl(fp) {}
	
	void updatePoints(const QRect& viewport, unsigned int resolution);
	QPair<QPointF, QString> calc(const QPointF& dp);
	Axe axeType() const { return Polar; }
	QLineF derivative(const QPointF& p) const;
	ImplType type() const { return PolarType; }
	virtual FunctionImpl* copy() { return new FunctionPolar(*this); }
	
	inline QPointF fromPolar(double r, double th) { return QPointF(r*cos(th), r*sin(th)); }
};

#endif
