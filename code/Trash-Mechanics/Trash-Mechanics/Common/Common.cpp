#include "Common.h"

Vec originPoint(0, 0);
Segment emptySegment(originPoint, originPoint);

Vec::Vec()
{
	m_X = m_Y = 0;
}

Vec::Vec(const double &x, const double &y)
{
	m_X = x;
	m_Y = y;
}

Vec Vec::operator +(const Vec &x) const
{
	Vec t(this->m_X + x.m_X, this->m_Y + x.m_Y);
	return t;
}

Vec Vec::operator -(const Vec &x) const
{
	Vec t(this->m_X - x.m_X, this->m_Y - x.m_Y);
	return t;
}

Vec Vec::operator *(const double &x) const
{
	Vec t(x * this->getX(), x * this->getY());
	return t;	
}

Vec Vec::operator/(const double & x) const
{
	Vec t(this->getX() / x, this->getY() / x);
	return t;
}

double Vec::operator %(const Vec & x) const
{
	return (this->getX() * x.getY() - x.getX() * this->getY());
}

double Vec::operator ^(const Vec & x) const
{
	return (this->getX() * x.getX() + this->getY() * x.getY());
}


Vec& Vec::operator +=(const Vec & x)
{
	this->m_X += x.m_X;
	this->m_Y += x.m_Y;
	return (*this);
}

Vec& Vec::operator -=(const Vec & x)
{
	this->m_X -= x.m_X;
	this->m_Y -= x.m_Y;
	return (*this);
}

Vec & Vec::operator *=(const double & x)
{
	(*this) = (*this) * x;
	return (*this);
}

Vec & Vec::operator/=(const double & x)
{
	(*this) = (*this) / x;
	return (*this);
}

Vec& Vec::operator =(const Vec &x)
{
	if (this == &x)
		return (*this);
	this->m_X = x.m_X;
	this->m_Y = x.m_Y;
	return (*this);
}

bool Vec::setX(const double &x)
{
	this->m_X = x;
	return true;
}

bool Vec::setY(const double &y)
{
	this->m_Y = y;
	return true;
}

double Vec::getX() const
{
	return this->m_X;
}

double Vec::getY() const
{
	return this->m_Y;
}

double Vec::getAngle() const
{
	return (std::atan2(m_X, m_Y));
}

double Vec::getMagnitude() const
{
	return (sqrt(m_X * m_X + m_Y * m_Y));
}

void Vec::show() const
{
	std::cout << "X " << m_X << " Y " << m_Y << std::endl;
}

void Vec::rotate(const Vec & center, const double &angle)
{
	Vec diff = (*this) - center;
	double r = diff.getMagnitude(), tAngle = diff.getAngle() + angle;
	this->setXY(center.getX() + r * cos(tAngle), center.getY() + r * sin(tAngle));
}

void Vec::rotate(const double & angle)
{
	this->Vec::rotate(originPoint, angle);
}

Vec::~Vec()
{
	return;
}

bool Vec::setXY(const double &x, const double &y)
{
	this->m_X = x;
	this->m_Y = y;
	return true;
}





bool Poly::setPoly(const Vec &center, const std::vector<Vec> &P)
{
	m_CenterPoint = center;
	m_Point = P;
	m_PointNum = P.size();
	return false;
}
/*
bool Poly::isIntersected(const Segment &s) const
{
	for (std::vector<Vec>::const_iterator i = m_Point.begin(); i != m_Point.end(); i++)
	{
		if (VecToSegmentDist(*i, s) < NearDist)
		{
			return true;
		}	
	}
	return false;
}*/

bool Poly::inPoly_Vec(const Vec &v) const
{
	if (this->m_PointNum == 1)
		return false;
	inPoint = false;
	inEdge = false;
	double angleSum = 0.0;
	for (std::vector<Vec>::const_iterator i = m_Point.begin(); i != m_Point.end(); i++)
	{
		Vec v1(*i), v2;
		if (i == m_Point.end() - 1) v2 = *(m_Point.begin());
		else v2 = *(i + 1);
		angleSum += VecAngle(v, v1, v2);
		if (inPoint || inEdge) return true;
		//std::cout << VecAngle(v, v1, v2) << ' ' << angleSum << std::endl;
	}
	if (fabs(angleSum - 2 * pi) < eps) 
		return true;
	return false;
}

bool Poly::inPoly_PolyVec(const Poly &pol) const
{
	for (std::vector<Vec>::const_iterator i = pol.getPoint().begin(); i != pol.getPoint().end(); i++)
	{
		if (this->inPoly_Vec(*i))
			return true;
	}
	return false;
}

Vec Poly::getInterPoint(const Poly & pol) const
{
	for (std::vector<Vec>::const_iterator i = pol.getPoint().begin(); i != pol.getPoint().end(); i++)
	{
		if (this->inPoly_Vec(*i))
			return *i;
	}
	return originPoint;
}

Segment Poly::getInterSegment(const Poly & pol) const
{
	if (inPoly_PolyVec(pol) == false)
		return emptySegment;
	double m = INF;
	Segment ms;
	for (std::vector<Vec>::const_iterator i = pol.getPoint().begin(); i != pol.getPoint().end(); i++)
	{
		Vec v1(*i), v2;
		if (i == m_Point.end() - 1) v2 = *(m_Point.begin());
		else v2 = *(i + 1);
		Segment s(v1, v2);
		if (m > VecToSegmentDist(*i, s))
		{
			m = VecToSegmentDist(*i, s);
			ms.set(v1, v2);
		}
	}
	return ms;
}

bool Poly::move(const Vec & v)
{
	for (std::vector<Vec>::iterator i = m_Point.begin(); i != m_Point.end(); i++)
	{
		(*i) += v;
	}
	m_CenterPoint += v;
	return false;
}

bool Poly::rotate(const double & angle, const Vec & center)
{
	for (std::vector<Vec>::iterator i = m_Point.begin(); i != m_Point.end(); i++)
	{
		i->rotate(center, angle);
	}
	return true;
}

bool Poly::rotate(const double & angle)
{
	this->rotate(angle, this->m_CenterPoint);
	return true;
}

double VecToVecDist(const Vec &v1, const Vec &v2)
{
	return ((v1 - v2).getMagnitude());
}

double VecToSegmentDist(const Vec &v, const Segment &s)
{
	Vec v1 = s.getV1();
	Vec v2 = s.getV2();
	double d1 = VecToVecDist(v, v1);
	double d2 = VecToVecDist(v, v2);
	double A = v1.getY() - v2.getY();
	double B = v2.getX() - v1.getX();
	double C = v1.getX() * v2.getY() - v2.getX() * v1.getY();
	double d3 = fabs(A * v.getX() + B * v.getY() + C) / sqrt(A * A + B * B);
	return min(min(d1, d2), d3);
}

double VecAngle(const Vec &v, const Vec &v1, const Vec &v2)
{
	double a = VecToVecDist(v, v1);
	double b = VecToVecDist(v, v2);
	double c = VecToVecDist(v1, v2);
	if (fabs(a) < eps || fabs(b) < eps)
	{
		inPoint = true;
		return 0.0;
	}
	long double x = (a * a + b * b - c * c) / (2 * a * b);
	if (fabs(x - 1) < eps) 
	{
		inEdge = true;
		return 0;
	}
	if (fabs(x + 1) < eps)
	{
		inEdge = true;
		return 0;
	}
	//std::cout << x << std::endl;
	return acos(x);
}

RigidBody::RigidBody(const Poly &InputShape, const double &InputMass, const double &InputInertiaConstant, const Vec &InputVelocity, const double &InputAngularVelocity) {
	m_Shape = InputShape;
	m_Mass = InputMass;
	m_InertiaConstant = InputInertiaConstant;
	m_Velocity = InputVelocity;
	m_AngularVelocity = InputAngularVelocity;
}

void RigidBody::applyForce(const Vec &NewForce) {
	m_Force += NewForce;
}

void RigidBody::removeForce(const Vec &NewForce) {
	m_Force -= NewForce;
}

double RigidBody::m() const{
	return m_Mass;
}

Vec RigidBody::v() const{
	return m_Velocity;
}

double RigidBody::vAbs() const{
	return m_Velocity.getMagnitude();
}

double RigidBody::i() const{
	return m_InertiaConstant;
}
double RigidBody::w() const{
	return m_AngularVelocity;
}

void RigidBody::move(const double &dt) {
	/* dx=v*dt */
	m_Shape.move(m_Velocity*dt);
}

void RigidBody::accelerate(const double &dt) {
	/* F=ma */
	m_Velocity += (m_Force / m_Mass) * dt;
}

void RigidBody::rotate(const double &dt) {
	/* dtheta=omega*dt */
	m_Shape.rotate(m_AngularVelocity*dt);
}

void RigidBody::collide(RigidBody &Tag) {
	/* TBD */
	/*double Ek1 =
		0.5*m()*vAbs()*vAbs() +
		0.5*i()*w()*w() +
		0.5*Tag.m()*Tag.vAbs()*Tag.vAbs() +
		0.5*Tag.i()*Tag.w()*Tag.w();
	double f = 10000;
	double dt = 0.1;
	while (m_Shape.inPoly_PolyVec(Tag.m_Shape)) {

	}*/
}

Poly RigidBody::getShape() const{
	return m_Shape;
}