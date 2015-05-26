/**
 * Test for the wrapper of the PPL Polytope.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-04-02
 * @version     2014-04-08
 */

#include "gtest/gtest.h"
#include "../defines.h"

#include "../../lib/representations/Polytope/Polytope.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class PolytopeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
		
        // p1
        typename Point<Number>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, Number(4)) );
        coordinates1.insert( std::make_pair(y, Number(4)) );
        p1 = Point<Number>({4,4});

        // p2
        typename Point<Number>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, Number(5)) );
        coordinates2.insert( std::make_pair(y, Number(7)) );
        p2 = Point<Number>({5,7});

        // p3
        typename Point<Number>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, Number(7)) );
        coordinates3.insert( std::make_pair(y, Number(7)) );
        p3 = Point<Number>({7,7});
        
        // p4
        typename Point<Number>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, Number(8)) );
        coordinates4.insert( std::make_pair(y, Number(4)) );
        p4 = Point<Number>({8,4});
        
        // p5
        typename Point<Number>::coordinateMap coordinates5;
        coordinates5.insert( std::make_pair(x, Number(3)) );
        coordinates5.insert( std::make_pair(y, Number(3)) );
        p5 = Point<Number>({3,3});
        
        // p6
        typename Point<Number>::coordinateMap coordinates6;
        coordinates6.insert( std::make_pair(x, Number(4)) );
        coordinates6.insert( std::make_pair(y, Number(5)) );
        p6 = Point<Number>({4,5});
        
        // p7
        typename Point<Number>::coordinateMap coordinates7;
        coordinates7.insert( std::make_pair(x, Number(5)) );
        coordinates7.insert( std::make_pair(y, Number(3)) );
        p7 = Point<Number>({5,3});
    }

    virtual void TearDown()
    {
        hypro::VariablePool::getInstance().clear();
    }
	
    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    carl::Variable x;
    carl::Variable y;
	
    Point<Number> p1;
    Point<Number> p2;
    Point<Number> p3;
    Point<Number> p4;
    Point<Number> p5;
    Point<Number> p6;
    Point<Number> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TYPED_TEST(PolytopeTest, Constructor)
{
    hypro::Polytope<TypeParam> p0;
    
    std::vector<Point<TypeParam>> ps;
    ps.push_back(this->p1);
    ps.push_back(this->p2);
    ps.push_back(this->p3);
    ps.push_back(this->p4);
    Polytope<TypeParam> p1 = Polytope<TypeParam>(ps);
//    std::cout << "P1" << std::endl;
//    p1.print();
    EXPECT_EQ(p1.dimension(), unsigned(2));
    EXPECT_FALSE(p1.rawPolyhedron().is_empty());
    Polytope<TypeParam> p3 = Polytope<TypeParam>(ps);
    
    Polytope<TypeParam> p2 = Polytope<TypeParam>(2);
    EXPECT_EQ(p2.dimension(), unsigned(2));
    
    Eigen::Matrix<TypeParam, Eigen::Dynamic, Eigen::Dynamic> A = Eigen::Matrix<TypeParam, Eigen::Dynamic, Eigen::Dynamic>(2,2);
    A(0,0) = 1;
    A(0,1) = 2;
    A(1,0) = 1;
    A(1,1) = 3;
    
    Eigen::Matrix<TypeParam, Eigen::Dynamic, 1> b = Eigen::Matrix<TypeParam, Eigen::Dynamic, 1>(2,1);
    b(0,0) = 4;
    b(1,0) = 5;
    
//    hypro::VariablePool::getInstance().print();
    
    Polytope<TypeParam> p4 = Polytope<TypeParam>(A,b);
    
//    p4.print();
    
    EXPECT_EQ(p4.dimension(), unsigned(2));
    
    SUCCEED();
}

TYPED_TEST(PolytopeTest, Access)
{
    std::vector<Point<TypeParam>> ps1;
    ps1.push_back(this->p1);
    ps1.push_back(this->p2);
    ps1.push_back(this->p3);
    ps1.push_back(this->p4);
    hypro::Polytope<TypeParam> p1 = Polytope<TypeParam>(ps1);
    EXPECT_EQ(p1.dimension(), unsigned(2));
    
    std::vector<Point<TypeParam>> ps2;
    typename Point<TypeParam>::coordinateMap coordinates;
    coordinates.insert( std::make_pair(this->x, TypeParam(7)) );
    coordinates.insert( std::make_pair(this->y, TypeParam(8)) );
    Point<TypeParam> p5 = Point<TypeParam>(coordinates);
    coordinates.clear();
    coordinates.insert( std::make_pair(this->x, TypeParam(1)) );
    coordinates.insert( std::make_pair(this->y, TypeParam(2)) );
    Point<TypeParam> p6 = Point<TypeParam>(coordinates);
    coordinates.clear();
    coordinates.insert( std::make_pair(this->x, TypeParam(4)) );
    coordinates.insert( std::make_pair(this->y, TypeParam(3)) );
    Point<TypeParam> p7 = Point<TypeParam>(coordinates);
    ps2.push_back(p5);
    ps2.push_back(p6);
    ps2.push_back(p7);
    
//    std::cout << "---" << std::endl;
//    hypro::VariablePool::getInstance().print();
    
    Polytope<TypeParam> p2 = Polytope<TypeParam>(ps2);
    
//    std::cout << "---" << std::endl;
//    hypro::VariablePool::getInstance().print();

    EXPECT_EQ(p2.dimension(), unsigned(2));
    
    std::vector<Point<TypeParam>> points = p2.points();
}

TYPED_TEST(PolytopeTest, PointToGenerator)
{
    Generator gs = polytope::pointToGenerator(this->p1);
//    std::cout << "Generator: ";
//    gs.print();
//    std::cout << std::endl;
    gs = polytope::pointToGenerator(this->p2);
//    std::cout << "Generator: ";
//    gs.print();
//    std::cout << std::endl;
    gs = polytope::pointToGenerator(this->p3);
//    std::cout << "Generator: ";
//    gs.print();
//    std::cout << std::endl;
    gs = polytope::pointToGenerator(this->p4);
//    std::cout << "Generator: ";
//    gs.print();
//    std::cout << std::endl;
    
    SUCCEED();
}

TYPED_TEST(PolytopeTest, Intersection)
{
    std::vector<Point<TypeParam>> ps1;
    ps1.push_back(this->p1);
    ps1.push_back(this->p2);
    ps1.push_back(this->p3);
    ps1.push_back(this->p4);
    hypro::Polytope<TypeParam> pt1;
//    pt1.print();
    pt1 = Polytope<TypeParam>(ps1);
//    pt1.print();
    EXPECT_FALSE(pt1.rawPolyhedron().is_universe());
    EXPECT_TRUE(pt1.rawPolyhedron().is_topologically_closed());
    
    std::vector<Point<TypeParam>> ps2;
    ps2.push_back(this->p5);
    ps2.push_back(this->p6);
    ps2.push_back(this->p7);
    hypro::Polytope<TypeParam> pt2 = Polytope<TypeParam>(ps2);
//    pt2.print();
    
    hypro::Polytope<TypeParam> res;
    res = pt1.intersect(pt2);
//    res.print();
    res = res.hull();
//    res.print();
}

TYPED_TEST(PolytopeTest, Union)
{
    std::vector<Point<TypeParam>> ps1;
    ps1.push_back(this->p1);
    ps1.push_back(this->p2);
    ps1.push_back(this->p3);
    ps1.push_back(this->p4);
    hypro::Polytope<TypeParam> pt1;
    pt1 = Polytope<TypeParam>(ps1);
    EXPECT_FALSE(pt1.rawPolyhedron().is_universe());
    EXPECT_TRUE(pt1.rawPolyhedron().is_topologically_closed());
    
    std::vector<Point<TypeParam>> ps2;
    ps2.push_back(this->p5);
    ps2.push_back(this->p6);
    ps2.push_back(this->p7);
    hypro::Polytope<TypeParam> pt2 = Polytope<TypeParam>(ps2);
    
    hypro::Polytope<TypeParam> res;
    res = pt1.unite(pt2);
    res = res.hull();
}

TYPED_TEST(PolytopeTest, LinearTransformation)
{
    Point<TypeParam> pt1;
    Point<TypeParam> pt2;
    Point<TypeParam> pt3;
    Point<TypeParam> pt4;
    
    typename Point<TypeParam>::coordinateMap c1;
    c1.insert( std::make_pair(this->x, TypeParam(0)) );
    c1.insert( std::make_pair(this->y, TypeParam(0)) );
    pt1 = Point<TypeParam>(c1);
    typename Point<TypeParam>::coordinateMap c2;
    c2.insert( std::make_pair(this->x, TypeParam(0)) );
    c2.insert( std::make_pair(this->y, TypeParam(4)) );
    pt2 = Point<TypeParam>(c2);
    typename Point<TypeParam>::coordinateMap c3;
    c3.insert( std::make_pair(this->x, TypeParam(4)) );
    c3.insert( std::make_pair(this->y, TypeParam(4)) );
    pt3 = Point<TypeParam>(c3);
    typename Point<TypeParam>::coordinateMap c4;
    c4.insert( std::make_pair(this->x, TypeParam(4)) );
    c4.insert( std::make_pair(this->y, TypeParam(0)) );
    pt4 = Point<TypeParam>(c4);
    
    std::vector<Point<TypeParam>> ps1;
    ps1.push_back(pt1);
    ps1.push_back(pt2);
    ps1.push_back(pt3);
    ps1.push_back(pt4);
    hypro::Polytope<TypeParam> poly1;
    poly1 = Polytope<TypeParam>(ps1);
    EXPECT_FALSE(poly1.rawPolyhedron().is_universe());
    EXPECT_TRUE(poly1.rawPolyhedron().is_topologically_closed());
    
    matrix_t<TypeParam> A = matrix_t<TypeParam>(2,2);
    //vector b = vector(2,1);
    
    A(0,0) = TypeParam(0);
    A(1,0) = TypeParam(1);
    A(0,1) = TypeParam(-1);
    A(1,1) = TypeParam(0);
    //b(0,0) = TypeParam(0);
    //b(1,0) = TypeParam(0);
    
    hypro::Polytope<TypeParam> result;
    result = poly1.linearTransformation(A);
//    result.print();
}

TYPED_TEST(PolytopeTest, MinkowskiSum)
{
    std::vector<Point<TypeParam>> ps1;
    ps1.push_back(this->p1);
    ps1.push_back(this->p2);
    ps1.push_back(this->p3);
    ps1.push_back(this->p4);
    hypro::Polytope<TypeParam> ptpe1 = Polytope<TypeParam>(ps1);
    
    std::vector<Point<TypeParam>> ps2;
    ps2.push_back(this->p5);
    ps2.push_back(this->p6);
    ps2.push_back(this->p7);
    hypro::Polytope<TypeParam> ptpe2 = Polytope<TypeParam>(ps2);
    
    hypro::Polytope<TypeParam> result;
    result = ptpe1.minkowskiSum(ptpe2);
    
//    result.print();
    
    typename Point<TypeParam>::coordinateMap c1;
    c1.insert( std::make_pair(this->x, TypeParam(9)) );
    c1.insert( std::make_pair(this->y, TypeParam(12)) );
    this->p1 = Point<TypeParam>(c1);
    
    typename Point<TypeParam>::coordinateMap c2;
    c2.insert( std::make_pair(this->x, TypeParam(11)) );
    c2.insert( std::make_pair(this->y, TypeParam(12)) );
    this->p2 = Point<TypeParam>(c2);
    
    typename Point<TypeParam>::coordinateMap c3;
    c3.insert( std::make_pair(this->x, TypeParam(8)) );
    c3.insert( std::make_pair(this->y, TypeParam(10)) );
    this->p3 = Point<TypeParam>(c3);
    
    typename Point<TypeParam>::coordinateMap c4;
    c4.insert( std::make_pair(this->x, TypeParam(12)) );
    c4.insert( std::make_pair(this->y, TypeParam(10)) );
    this->p4 = Point<TypeParam>(c4);
    
    typename Point<TypeParam>::coordinateMap c5;
    c5.insert( std::make_pair(this->x, TypeParam(7)) );
    c5.insert( std::make_pair(this->y, TypeParam(7)) );
    this->p5 = Point<TypeParam>(c5);
    
    typename Point<TypeParam>::coordinateMap c6;
    c6.insert( std::make_pair(this->x, TypeParam(13)) );
    c6.insert( std::make_pair(this->y, TypeParam(7)) );
    this->p6 = Point<TypeParam>(c6);
    
    typename Point<TypeParam>::coordinateMap c7;
    c7.insert( std::make_pair(this->x, TypeParam(13)) );
    c7.insert( std::make_pair(this->y, TypeParam(8)) );
    this->p7 = Point<TypeParam>(c7);
    
    EXPECT_TRUE(result.contains(this->p1));
    EXPECT_TRUE(result.contains(this->p2));
    EXPECT_TRUE(result.contains(this->p3));
    EXPECT_TRUE(result.contains(this->p4));
    EXPECT_TRUE(result.contains(this->p5));
    EXPECT_TRUE(result.contains(this->p6));
    
    EXPECT_FALSE(result.contains(this->p7));
    //EXPECT_FALSE(result.contains(p8));
}

/*
TYPED_TEST(PolytopeTest, ConvexHull)
{
    vector_t<double> v01 = vector_t<double>(3);
	v01(0) = 0;
	v01(1) = 0;
	v01(2) = 0;
	this->p1 = Point<double>(v01);

	vector_t<double> v02 = vector_t<double>(3);
	v02(0) = 0;
	v02(1) = 2;
	v02(2) = 0;
	this->p2 = Point<double>(v02);

	vector_t<double> v03 = vector_t<double>(3);
	v03(0) = 2;
	v03(1) = 0;
	v03(2) = 0;
	this->p3 = Point<double>(v03);

	vector_t<double> v04 = vector_t<double>(3);
	v04(0) = 0;
	v04(1) = 0;
	v04(2) = 2;
	this->p4= Point<double>(v04);

	vector_t<double> v05 = vector_t<double>(3);
	v04(0) = 0.5;
	v04(1) = 0.5;
	v04(2) = 0.5;
	this->p5= Point<double>(v05);

	hypro::Polytope<TypeParam> result;
	ptpe1.hull(result)

	EXPECT_TRUE(result.contains(this->p1));
    EXPECT_TRUE(result.contains(this->p2));
    EXPECT_TRUE(result.contains(this->p3));
    EXPECT_TRUE(result.contains(this->p4));
	EXPECT_FALSE(result.contains(this->p5));

	//neighborhood.....
}

TYPED_TEST(PolytopeTest, Membership)
{
    vector_t<double> v01 = vector_t<double>(3);
	v01(0) = 4;
	v01(1) = 4;
	Point<Number> p01 = Point<double>(v01);

	vector_t<double> v02 = vector_t<double>(3);
	v02(0) = 5;
	v02(1) = 6;
	Point<Number> p02 = Point<double>(v02);

	vector_t<double> v03 = vector_t<double>(3);
	v03(0) = 6;
	v03(1) = 4;
	Point<Number> p03 = Point<double>(v03);

	vector_t<double> v04 = vector_t<double>(3);
	v04(0) = 10;
	v04(1) = 0;
	Point<Number> p04= Point<double>(v04);

	std::vector<Point<Number>> v1;
	v1.push_back(p01);
	v1.push_back(p02);
	v1.push_back(p03);

	Polytope<Number> pt2 = Polytope<Number>(v1);

	EXPECT_TRUE(ptpe1.contains(pt2));

	v1.push_back(p04);

	Polytope<Number> pt3 = Polytope<Number>(v1);

	EXPECT_FALSE(ptpe1.contains(pt3));
}
*/
