#include "../src/lib/util/convexHull.h"
#include "../src/lib/config.h"
//#include "../src/lib/datastructures/Point.h"
#include "../src/lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../src/lib/representations/Polytope/Polytope.h"


using namespace hypro;

int main(int argc, char** argv) {

	vector_t<double> v01 = vector_t<double>(3);
	v01(0) = 0;
	v01(1) = 0;
	v01(2) = 0;
/*	v01(3) = 0;
	v01(4) = 0;*/
	Point<double> p01 = Point<double>(v01);

	vector_t<double> v02 = vector_t<double>(3);
	v02(0) = 3;
	v02(1) = 0;
	v02(2) = 0;
/*	v02(3) = 0;
	v02(4) = 0;*/
	Point<double> p02 = Point<double>(v02);

	vector_t<double> v03 = vector_t<double>(3);
	v03(0) = 0;
	v03(1) = 3;
	v03(2) = 0;
/*	v03(3) = 0;
	v03(4) = 0;*/
	Point<double> p03 = Point<double>(v03);

	vector_t<double> v04 = vector_t<double>(3);
	v04(0) = 0;
	v04(1) = 0;
	v04(2) = 3;
/*	v04(3) = 0;
	v04(4) = 0;*/
	Point<double> p04 = Point<double>(v04);

	vector_t<double> v05 = vector_t<double>(3);
	v05(0) = 0; //0
	v05(1) = 3; //0
	v05(2) = 3; //0
/*	v05(3) = 3;
	v05(4) = 0;*/
	Point<double> p05 = Point<double>(v05);

	vector_t<double> v06 = vector_t<double>(3);
	v06(0) = 3; //0
	v06(1) = 0; //0
	v06(2) = 3; //0
/*	v06(3) = 0;
	v06(4) = 3;*/
	Point<double> p06 = Point<double>(v06);

	vector_t<double> v07 = vector_t<double>(3);
	v07(0) = 3;
	v07(1) = 3;
	v07(2) = 0;
/*	v07(3) = 0;
	v07(4) = 0;*/
	Point<double> p07 = Point<double>(v07);

	vector_t<double> v08 = vector_t<double>(3);
	v08(0) = 3; //3
	v08(1) = 3; //0
	v08(2) = 3; //3
/*	v08(3) = 0;
	v08(4) = 0; */
	Point<double> p08 = Point<double>(v08);

/*	vector_t<double> v09 = vector_t<double>(5);
	v09(0) = 3;
	v09(1) = 0;
	v09(2) = 0;
	v09(3) = 3;
	v09(4) = 0;
	Point<double> p09 = Point<double>(v09);

	vector_t<double> v10 = vector_t<double>(5);
	v10(0) = 3;
	v10(1) = 0;
	v10(2) = 0;
	v10(3) = 0;
	v10(4) = 3;
	Point<double> p10 = Point<double>(v10);

	vector_t<double> v11 = vector_t<double>(5);
	v11(0) = 0;
	v11(1) = 3;
	v11(2) = 3;
	v11(3) = 0;
	v11(4) = 0;
	Point<double> p11 = Point<double>(v11);

	vector_t<double> v12 = vector_t<double>(5);
	v12(0) = 0;
	v12(1) = 3;
	v12(2) = 0;
	v12(3) = 3;
	v12(4) = 0;
	Point<double> p12 = Point<double>(v12);

	vector_t<double> v13 = vector_t<double>(5);
	v13(0) = 0;
	v13(1) = 3;
	v13(2) = 0;
	v13(3) = 0;
	v13(4) = 3;
	Point<double> p13 = Point<double>(v13);

	vector_t<double> v14 = vector_t<double>(5);
	v14(0) = 0;
	v14(1) = 0;
	v14(2) = 3;
	v14(3) = 3;
	v14(4) = 0;
	Point<double> p14 = Point<double>(v14);

	vector_t<double> v15 = vector_t<double>(5);
	v15(0) = 0;
	v15(1) = 0;
	v15(2) = 3;
	v15(3) = 0;
	v15(4) = 3;
	Point<double> p15 = Point<double>(v15);

	vector_t<double> v16 = vector_t<double>(5);
	v16(0) = 0;
	v16(1) = 0;
	v16(2) = 0;
	v16(3) = 3;
	v16(4) = 3;
	Point<double> p16 = Point<double>(v16);

	vector_t<double> v17 = vector_t<double>(5);
	v17(0) = 3;
	v17(1) = 3;
	v17(2) = 3;
	v17(3) = 0;
	v17(4) = 0;
	Point<double> p17 = Point<double>(v17);

	vector_t<double> v18 = vector_t<double>(5);
	v18(0) = 3;
	v18(1) = 3;
	v18(2) = 0;
	v18(3) = 3;
	v18(4) = 0;
	Point<double> p18 = Point<double>(v18);

	vector_t<double> v19 = vector_t<double>(5);
	v19(0) = 3;
	v19(1) = 3;
	v19(2) = 0;
	v19(3) = 0;
	v19(4) = 3;
	Point<double> p19 = Point<double>(v19);

	vector_t<double> v20 = vector_t<double>(5);
	v20(0) = 3;
	v20(1) = 0;
	v20(2) = 3;
	v20(3) = 3;
	v20(4) = 0;
	Point<double> p20 = Point<double>(v20);

	vector_t<double> v21 = vector_t<double>(5);
	v21(0) = 3;
	v21(1) = 0;
	v21(2) = 3;
	v21(3) = 0;
	v21(4) = 3;
	Point<double> p21 = Point<double>(v21);
	ardReachabilityTest.cpp.o

	vector_t<double> v22 = vector_t<double>(5);
	v22(0) = 3;
	v22(1) = 0;
	v22(2) = 0;
	v22(3) = 3;
	v22(4) = 3;
	Point<double> p22 = Point<double>(v22);

	vector_t<double> v23 = vector_t<double>(5);
	v23(0) = 0;
	v23(1) = 3;
	v23(2) = 3;
	v23(3) = 3;
	v23(4) = 0;
	Point<double> p23 = Point<double>(v23);

	vector_t<double> v24 = vector_t<double>(5);
	v24(0) = 0;
	v24(1) = 3;
	v24(2) = 3;
	v24(3) = 0;
	v24(4) = 3;
	Point<double> p24 = Point<double>(v24);

	vector_t<double> v25 = vector_t<double>(5);
	v25(0) = 0;
	v25(1) = 3;
	v25(2) = 0;
	v25(3) = 3;
	v25(4) = 3;
	Point<double> p25 = Point<double>(v25);

	vector_t<double> v26 = vector_t<double>(5);
	v26(0) = 0;
	v26(1) = 0;
	v26(2) = 3;
	v26(3) = 3;
	v26(4) = 3;
	Point<double> p26 = Point<double>(v26);

	vector_t<double> v27 = vector_t<double>(5);
	v27(0) = 3;
	v27(1) = 3;
	v27(2) = 3;
	v27(3) = 3;
	v27(4) = 0;
	Point<double> p27 = Point<double>(v27);

	vector_t<double> v28 = vector_t<double>(5);
	v28(0) = 3;
	v28(1) = 3;
	v28(2) = 3;
	v28(3) = 0;
	v28(4) = 3;
	Point<double> p28 = Point<double>(v28);

	vector_t<double> v29 = vector_t<double>(5);
	v29(0) = 3;
	v29(1) = 3;
	v29(2) = 0;
	v29(3) = 3;ardReachabilityTest.cpp.o

	v29(4) = 3;
	Point<double> p29 = Point<double>(v29);

	vector_t<double> v30 = vector_t<double>(5);
	v30(0) = 3;
	v30(1) = 0;
	v30(2) = 3;
	v30(3) = 3;
	v30(4) = 3;
	Point<double> p30 = Point<double>(v30);

	vector_t<double> v31 = vector_t<double>(5);
	v31(0) = 0;
	v31(1) = 3;
	v31(2) = 3;
	v31(3) = 3;
	v31(4) = 3;
	Point<double> p31 = Point<double>(v31);

	vector_t<double> v32 = vector_t<double>(5);
	v32(0) = 3;
	v32(1) = 3;
	v32(2) = 3;
	v32(3) = 3;
	v32(4) = 3;
	Point<double> p32 = Point<double>(v32);*/

	std::vector<Point<double>> points;
	points.push_back(p01);
		points.push_back(p02);
		points.push_back(p03);
		points.push_back(p04);
	//points.push_back(p09);

	std::vector<Point<double>> points2;
	points2.push_back(p05);
	points2.push_back(p06);
	points2.push_back(p07);
	points2.push_back(p08);

/*	points.push_back(p09);
	points.push_back(p10);
	points.push_back(p11);
	points.push_back(p12);
	points.push_back(p13);
	points.push_back(p14);
	points.push_back(p15);
	points.push_back(p16);
	points.push_back(p17);
	points.push_back(p18);
	points.push_back(p19);
	points.push_back(p20);
	points.push_back(p21);
	points.push_back(p22);
	points.push_back(p23);
	points.push_back(p24);
	points.push_back(p25);
	points.push_back(p26);
	points.push_back(p27);
	points.push_back(p28);
	points.push_back(p29);
	points.push_back(p30);
	points.push_back(p31);
	points.push_back(p32); */


//	Polytope<double> polytope = Polytope<double>(points);
//	Polytope<double> polytope2 = Polytope<double>(points2);

	//std::cout<< polytope <<std::endl;
	//std::cout<< polytope2 <<std::endl;

	//std::vector<Halfspace<double>> Halfspaces;
	//std::vector<Facet<double>> facets = convexHull(vpolytope.vertices());
	//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	//for(unsigned i = 0; i<facets.size(); i++) {
	//	Halfspaces.push_back(facets[i].Halfspace());
	//}
	//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	//HPolytope<double> hpolytope = HPolytope<double>(Halfspaces);
	//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;

	//std::cout<<__func__ << " : " <<__LINE__ << " matrix: " << hpolytope.peter() << std::endl;
	//Polytope<double> polytope3 = polytope.unite(polytope2);

	points.push_back(p05);
		points.push_back(p06);
		points.push_back(p07);
		points.push_back(p08);

	//std::cout<< "Polytope 3 is Empty : " << polytope3.isEmpty() <<std::endl;

/*	while(!points.empty()){
		for(unsigned i = 0; i<polytope3.vertices().size(); i++){
			if(points.front() == polytope3.vertices().at(i)) {
				points.erase(points.begin());
				std::cout<< "Found Point at " << i <<std::endl;
			}
		}
	}*/

/*	for(auto& vertex : polytope.vertices()) {
		if(!polytope3.hasVertex(vertex)){
			std::cout<< "has Vertex " << vertex << " is false" <<std::endl;
		}
		if(!polytope3.contains(vertex)){
			std::cout<< "contains " << vertex << " is false" <<std::endl;
		}
	}
	for(auto& vertex : polytope2.vertices()) {
		if(!polytope3.hasVertex(vertex)){
			std::cout<< "has Vertex " << vertex << " is false" <<std::endl;
		}
		if(!polytope3.contains(vertex)){
			std::cout<< "contains " << vertex << " is false" <<std::endl;
		}
	} */

	/*std::vector<Facet<double>*> facets = convexHull(polytope3.vertices());
	std::set<Point<double>> preresult;
	for(unsigned i = 0; i<facets.size(); i++) {
		for(unsigned j = 0; j<facets[i]->vertices().size(); j++) {
			preresult.insert(facets[i]->vertices().at(j));
		}
	}
	std::vector<Point<double>> points5;
	for(auto& point : preresult) {
		points5.push_back(point);
	}
	Polytope<double> result = Polytope<double>(points5);*/


		Polytope<double> polytope3 = Polytope<double>(points);
	//	polytope3 = polytope3.hull();

/*	points.push_back(p01);
		points.push_back(p02);
		points.push_back(p03);
		points.push_back(p04);
		points.push_back(p05);
			points.push_back(p06);
			points.push_back(p07);
			points.push_back(p08);*/
/*	while(!points.empty()){
			for(unsigned i = 0; i<polytope3.vertices().size(); i++){
				if(points.front() == polytope3.vertices().at(i)) {
					points.erase(points.begin());
					std::cout<< "Found Point at " << i <<std::endl;
				}
			}
		}*/


		Point<double> p1 = Point<double>({4,4});

		Point<double> p2 = Point<double>({5,7});

		Point<double> p3 = Point<double>({7,7});

		Point<double> p4 = Point<double>({8,4});

		Point<double> p5 = Point<double>({3,3});

		Point<double> p6 = Point<double>({4,5});

		Point<double> p7 = Point<double>({5,3});

		 std::vector<Point<double>> ps1;
		 ps1.push_back(p1);
		 ps1.push_back(p2);
		 ps1.push_back(p3);
		 ps1.push_back(p4);
		 Polytope<double> pt1;
		 pt1 = Polytope<double>(ps1);
		 //EXPECT_FALSE(pt1.rawPolyhedron().is_universe());
		 //EXPECT_TRUE(pt1.rawPolyhedron().is_topologically_closed());

		 std::vector<Point<double>> ps2;
		 ps2.push_back(p5);
		 ps2.push_back(p6);
		 ps2.push_back(p7);
		 Polytope<double> pt2 = Polytope<double>(ps2);

		 Polytope<double> res;
		 res = pt1.unite(pt2);
		 res = res.hull();

		 //polytope3 = polytope3.hull();

	//std::cout<< polytope3 <<std::endl;
}
