/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since		2015-01-20
 * @version		2015-01-22
 */

#include "../../lib/representations/SupportFunction/PolytopeSupportfunction.h"
#include "gtest/gtest.h"
#include "../defines.h"


using namespace hypro;
using namespace carl;

template<typename Number>
class PolytopeSupportFunctionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
		constraints = matrix_t<Number>::Zero(3,2);
		constraints(0,0) = Number(2);
		constraints(0,1) = Number(4);
		constraints(1,0) = Number(1);
		constraints(1,1) = Number(-2);
		constraints(2,0) = Number(-4);
		constraints(2,1) = Number(1);
		constants = matrix_t<Number>(3,1);
		constants(0,0) = Number(20);
		constants(1,0) = Number(5);
		constants(2,0) = Number(17);

		ad = new artificialDirections<Number>();
		ad->dir1 = getZeroVector<Number>(constraints.cols());
		ad->dir2 = getZeroVector<Number>(constraints.cols());

		ad->dir1(constraints.cols()-1,0) = 1;
		ad->dir2(constraints.cols()-1,0) = -1;
    }
	
    virtual void TearDown(){
		delete ad;
    }
	
	matrix_t<Number> constraints;
	matrix_t<Number> constants;
	artificialDirections<Number>* ad;
};

TYPED_TEST(PolytopeSupportFunctionTest, constructor) {
	PolytopeSupportFunction<TypeParam> psf1 = PolytopeSupportFunction<TypeParam>(this->constraints, this->constants, operator_e::LEQ, 2, this->ad);
}

TYPED_TEST(PolytopeSupportFunctionTest, access) {

}

TYPED_TEST(PolytopeSupportFunctionTest, linearTransformation) {

}

TYPED_TEST(PolytopeSupportFunctionTest, MinkowskiSum) {

}

TYPED_TEST(PolytopeSupportFunctionTest, contains) {

}