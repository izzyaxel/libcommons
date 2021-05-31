#pragma once

#include "general.hh"

template<typename T> struct circle;

template<typename T> struct linesegment2D
{
	inline constexpr linesegment2D() = default;
	
	inline constexpr linesegment2D(vec2<T> const &p1, vec2<T> const &p2) : point1(p1), point2(p2) {}
	
	/// Reconstruct this line segment
	inline void construct(vec2<T> const &p1, vec2<T> const &p2)
	{
		this->point1 = p1;
		this->point2 = p2;
	}
	
	[[nodiscard]] inline vec2<T> getNormal()
	{
		vec2<T> vec = this->point1 - this->point2;
		vec.normalize();
		return {-vec.y(), vec.x()};
	}
	
	/*/// Find the point of intersection between this line and another
	[[nodiscard]] inline bool isIntersecting(linesegment2D<T> const &other, vec2<T> &out)
	{
		T x1 = this->point1.x(), x2 = this->point2.x(), x3 = other.point1.x(), x4 = other.point2.x();
		T y1 = this->point1.y(), y2 = this->point2.y(), y3 = other.point1.y(), y4 = other.point2.y();
		T pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
		T det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if(det == 0) return false;
		T x = (pre * (x3 - x4) - (x1 - x2) * post) / det;
		T y = (pre * (y3 - y4) - (y1 - y2) * post) / det;
		if(x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4)) return false;
		if(y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4)) return false;
		out = {x, y};
		return true;
	}*/
	
	[[nodiscard]] inline bool isIntersecting(linesegment2D<T> const &other, vec2<T> &out)
	{
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = this->point2.x() - this->point1.x();
		s1_y = this->point2.y() - this->point1.y();
		s2_x = other.point2.x() - other.point1.x();
		s2_y = other.point2.y() - other.point1.y();
		
		float s, t;
		s = (-s1_y * (this->point1.x() - other.point1.x()) + s1_x * (this->point1.y() - other.point1.y())) / (-s2_x * s1_y + s1_x * s2_y);
		t = ( s2_x * (this->point1.y() - other.point1.y()) - s2_y * (this->point1.x() - other.point1.x())) / (-s2_x * s1_y + s1_x * s2_y);
		
		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
			out.x() = this->point1.x() + (t * s1_x);
			out.y() = this->point1.y() + (t * s1_y);
			return true;
		}
		return false;
	}
	
	vec2<T> point1, point2;
};

/// 2-dimensional axis aligned bounding box
template<typename T> struct aabb2D
{
	inline constexpr aabb2D() = default;
	
	inline constexpr aabb2D(T minX, T maxX, T minY, T maxY)
	{
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
		this->centerX = (maxX - minX) / (T)2.0;
		this->centerY = (maxY - minY) / (T)2.0;
	}
	
	inline constexpr aabb2D(T minX, T maxX, T minY, T maxY, T centerX, T centerY)
	{
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
		this->centerX = centerX;
		this->centerY = centerY;
	}
	
	inline constexpr aabb2D(vec2<T> center, vec2<T> dimensions)
	{
		this->centerX = center.x();
		this->centerY = center.y();
		T halfX = dimensions.x() / (T)2, halfY = dimensions.y() / (T)2;
		this->minX = this->centerX - halfX;
		this->maxX = this->centerX + halfX;
		this->minY = this->centerY - halfY;
		this->maxY = this->centerY + halfY;
	}
	
	/// Reconstruct this AABB
	inline void construct(T minX, T maxX, T minY, T maxY)
	{
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
		this->centerX = (maxX - minX) / (T)2.0;
		this->centerY = (maxY - minY) / (T)2.0;
	}
	
	inline void offset(T xOffset, T yOffset)
	{
		this->minX += xOffset;
		this->maxX += xOffset;
		this->minY += yOffset;
		this->maxY += yOffset;
		this->centerX = (maxX - minX) / (T)2.0;
		this->centerY = (maxY - minY) / (T)2.0;
	}
	
	/// Check if this AABB contains a given point
	[[nodiscard]] inline bool containsPoint(T x, T y)
	{
		return x > this->minX && x < this->maxX && y > this->minY && y < this->maxY;
	}
	
	/// AABB-line segment collision
	[[nodiscard]] inline bool isIntersecting(linesegment2D<T> const &other, T &closestHit)
	{
		T hWidth = (this->maxX - this->minX) / (T)2, hHeight = (this->maxY - this->minY) / 2;
		linesegment2D<T> top{vec2<T>{this->centerX - hWidth, this->centerY + hHeight}, vec2<T>{this->centerX + hWidth, this->centerY + hHeight}},
		bottom{vec2<T>{this->centerX - hWidth, this->centerY - hHeight}, vec2<T>{this->centerX + hWidth, this->centerY - hHeight}},
		left{vec2<T>{this->centerX - hWidth, this->centerY - hHeight}, vec2<T>{this->centerX - hWidth, this->centerY + hHeight}},
		right{vec2<T>{this->centerX + hWidth, this->centerY - hHeight}, vec2<T>{this->centerX + hWidth, this->centerY + hHeight}};
		vec2<T> topInterPt{}, bottomInterPt{}, leftInterPt{}, rightInterPt{};
		bool topInter = top.isIntersecting(other, topInterPt);
		bool bottomInter = bottom.isIntersecting(other, bottomInterPt);
		bool leftInter = left.isIntersecting(other, leftInterPt);
		bool rightInter = right.isIntersecting(other, rightInterPt);
		float topDist = distance<T>(top.point2, topInterPt);
		float bottomDist = distance<T>(bottom.point2, bottomInterPt);
		float leftDist = distance<T>(left.point2, leftInterPt);
		float rightDist = distance<T>(right.point2, rightInterPt);
		if(topInter || bottomInter || leftInter || rightInter) closestHit = std::min(std::min(topDist, bottomDist), std::min(leftDist, rightDist));
		return topInter || bottomInter || leftInter || rightInter;
	}
	
	/// AABB-aabb collision
	[[nodiscard]] inline bool isIntersecting(aabb2D<T> const &other)
	{
		return (this->minX < other.maxX) != (this->maxX < other.minX) && (this->minY < other.maxY) != (this->maxY < other.minY);
	}
	
	/// AABB-circle collision
	[[nodiscard]] inline bool isIntersecting(circle<T> const &other)
	{
		aabb2D<T> broadOther = aabb2D<T>(other.center.x() - other.radius, other.center.x() + other.radius, other.center.y() - other.radius, other.center.y() + other.radius);
		if(!this->isIntersecting(broadOther)) return false;
		vec2<T> ul = {this->minX, this->maxY};
		vec2<T> ur = {this->maxX, this->maxY};
		vec2<T> ll = {this->minX, this->minY};
		vec2<T> lr = {this->maxX, this->maxY};
		T distUL = std::sqrt((other.center.x() - ul.x()) * (other.center.x() - ul.x()) + (other.center.y() - ul.y()) * (other.center.y() - ul.y()));
		T distUR = std::sqrt((other.center.x() - ur.x()) * (other.center.x() - ur.x()) + (other.center.y() - ur.y()) * (other.center.y() - ur.y()));
		T distLL = std::sqrt((other.center.x() - ll.x()) * (other.center.x() - ll.x()) + (other.center.y() - ll.y()) * (other.center.y() - ll.y()));
		T distLR = std::sqrt((other.center.x() - lr.x()) * (other.center.x() - lr.x()) + (other.center.y() - lr.y()) * (other.center.y() - lr.y()));
		return distUL < other.radius || distUR < other.radius || distLR < other.radius || distLL < other.radius;
	}
	
	/// Predict an intersection with another AABB
	[[nodiscard]] inline bool predictIntersection(T xOffset, T yOffset, aabb2D<T> const &other)
	{
		return (this->minX + xOffset < other.maxX) != (this->maxX + xOffset < other.minX) && (this->minY + yOffset < other.maxY) != (this->maxY + yOffset < other.minY);
	}
	
	T minX, minY, maxX, maxY, centerX, centerY;
};

/// 3-dimensional axis aligned bounding box
template<typename T> struct aabb3D
{
	inline constexpr aabb3D() = default;
	
	inline constexpr aabb3D(T minX, T maxX, T minY, T maxY, T minZ, T maxZ) : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ)
	{}
	
	/// Construct/reconstruct this AABB
	inline void construct(T minX, T maxX, T minY, T maxY, T minZ, T maxZ)
	{
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
		this->minZ = minZ;
		this->maxZ = maxZ;
		this->centerX = (maxX - minX) / (T)2.0;
		this->centerY = (maxY - minY) / (T)2.0;
		this->centerZ = (maxZ - minZ) / (T)2.0;
	}
	
	/// Check if this AABB contains a given point
	[[nodiscard]] inline bool containsPoint(T x, T y, T z)
	{
		return x > this->minX && x < this->maxX && y > this->minY && y < this->maxY && z > this->minZ && z < this->maxZ;
	}
	
	/// Check if this AABB is intersecting with another
	[[nodiscard]] inline bool isIntersecting(aabb3D<T> const &other)
	{
		return (this->minX < other.maxX) != (this->maxX < other.minX) && (this->minY < other.maxY) != (this->maxY < other.minY) && (this->minZ < other.maxZ) != (this->maxZ < other.minZ);
	}
	
	/// Predict an intersection with another AABB
	[[nodiscard]] inline bool predictIntersection(T xOffset, T yOffset, T zOffset, aabb3D<T> const &other)
	{
		return (this->minX + xOffset < other.maxX) != (this->maxX + xOffset < other.minX) && (this->minY + yOffset < other.maxY) != (this->maxY + yOffset < other.minY) && (this->minZ + zOffset < other.maxZ) != (this->maxZ + zOffset < other.minZ);
	}
	
	T minX, minY, minZ, maxX, maxY, maxZ, centerX, centerY, centerZ;
};

/// A mathematical circle
template<typename T> struct circle
{
	inline constexpr circle() = default;
	
	inline constexpr circle(vec2<T> const &center, T radius)
	{
		this->center = center;
		this->radius = radius;
	}
	
	/// Reconstruct this circle
	inline void construct(vec2<T> const &center, T radius)
	{
		this->center = center, this->radius = radius;
	}
	
	/// Circle-circle collision
	[[nodiscard]] inline bool isIntersecting(circle<T> const &other)
	{
		aabb2D<T> broadThis = aabb2D<T>(this->center.x() - this->radius, this->center.x() + this->radius, this->center.y() - this->radius, this->center.y() + this->radius);
		aabb2D<T> broadOther = aabb2D<T>(other.center.x() - other.radius, other.center.x() + other.radius, other.center.y() - other.radius, other.center.y() + other.radius);
		if(!broadThis.isIntersecting(broadOther)) return false;
		T a = (this->center.x() - other.center.x()) * (this->center.x() - other.center.x());
		T b = (this->center.y() - other.center.y()) * (this->center.y() - other.center.y());
		T distance = std::sqrt(a + b);
		return distance < this->radius + other.radius;
	}
	
	/// Circle-line
	[[nodiscard]] inline bool isIntersecting(linesegment2D<T> const &other)
	{
		T dX, dY, dR, D, incidence;
		dX = other.point2.x() - other.point1.x();
		dY = other.point2.y() - other.point1.y();
		dR = std::sqrt((dX * dX) + (dY * dY));
		D = (other.point1.x() * other.point2.y()) - (other.point2.x() * other.point1.y());
		incidence = (this->radius * this->radius) * (dR * dR) - (D * D);
		if(incidence < 0) return false;
		else if(incidence == 0) return false;
		else //TODO finish
		{
			/*outFirst.x() = ((D * dY) + sign<T>(dY) * dX * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
			outFirst.y() = ((-D * dX) + std::abs(dY) * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
			outSecond.x() = ((D * dY) - sign<T>(dY) * dX * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
			outSecond.y() = ((-D * dX) - std::abs(dY) * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);*/
			return true;
		}
	}
	
	/// Circle-aabb collision
	[[nodiscard]] inline bool isIntersecting(aabb2D<T> const &other) //TODO optimization
	{
		//broad phase
		if(this->containsPoint({other.centerX, other.centerY})) return true;
		aabb2D<T> broadThis = aabb2D<T>(this->center.x() - this->radius, this->center.x() + this->radius, this->center.y() - this->radius, this->center.y() + this->radius);
		if(!broadThis.isIntersecting(other)) return false;
		
		vec2<T> ul = {other.minX, other.maxY};
		if(this->containsPoint(ul)) return true;
		vec2<T> ur = {other.maxX, other.maxY};
		if(this->containsPoint(ur)) return true;
		vec2<T> ll = {other.minX, other.minY};
		if(this->containsPoint(ll)) return true;
		vec2<T> lr = {other.maxX, other.maxY};
		if(this->containsPoint(lr)) return true;
		
		linesegment2D<T> top = linesegment2D<T>(ul, ur);
		if(this->isIntersecting(top)) return true;
		linesegment2D<T> bottom = linesegment2D<T>(ll, lr);
		if(this->isIntersecting(bottom)) return true;
		linesegment2D<T> right = linesegment2D<T>(ur, lr);
		if(this->isIntersecting(right)) return true;
		linesegment2D<T> left = linesegment2D<T>(ul, ll);
		return this->isIntersecting(left);
	}
	
	[[nodiscard]] inline bool containsPoint(vec2<T> const &point)
	{
		T distance = std::sqrt(((this->center.x() - point.x()) * (this->center.x() - point.x())) + ((this->center.y() - point.y()) * (this->center.y() - point.y())));
		return distance < this->radius;
	}
	
	vec2<T> center;
	T radius;
};
