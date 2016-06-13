#pragma once

#include "c_defs.h"

class CShape {

	public:
	std::vector<Vertex3> GetPoints( ) {
		return _points;
	}

	void AddPoint( Vertex3 vertex ) {
		_points.push_back( vertex );
	}

	protected:
	std::vector<Vertex3> _points;

};

class CShapeRect : public CShape {

	public:
	CShapeRect( t_real x0, t_real y0, t_real x1, t_real y1 ) {

		Vertex3 p0, p1, p2, p3;

		p0.location = { x0, y0, 0.0 };
		p1.location = { x1, y0, 0.0 };
		p2.location = { x1, y1, 0.0 };
		p3.location = { x0, y1, 0.0 };

		p0.normal = { 0.0, 0.0, 1.0 };
		p1.normal = { 0.0, 0.0, 1.0 };
		p2.normal = { 0.0, 0.0, 1.0 };
		p3.normal = { 0.0, 0.0, 1.0 };

		p0.uv = { 0.0, 0.0 };
		p1.uv = { 1.0, 0.0 };
		p2.uv = { 1.0, 1.0 };
		p3.uv = { 0.0, 1.0 };

		p0.color = { 1.0, 1.0, 1.0, 1.0 };
		p1.color = { 1.0, 1.0, 1.0, 1.0 };
		p2.color = { 1.0, 1.0, 1.0, 1.0 };
		p3.color = { 1.0, 1.0, 1.0, 1.0 };

		_points.push_back( p0 );
		_points.push_back( p1 );
		_points.push_back( p2 );
		_points.push_back( p3 );

	}

};