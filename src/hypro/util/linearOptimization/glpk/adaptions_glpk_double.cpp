#include "adaptions_glpk.h"

namespace hypro {

	template<>
	EvaluationResult<double> glpkOptimizeLinear(glp_prob* glpkProblem, const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>&, bool useExact) {

		//std::cout << __func__ << " in direction " << _direction.transpose() << std::endl;
		//std::cout << __func__ << " constraints: " << std::endl << constraints << std::endl << "Glpk Problem: " << std::endl;
		//printProblem(glpkProblem);


		// setup glpk
		for ( int i = 0; i < constraints.cols(); i++ ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, carl::toDouble( _direction( i ) ) );
		}

		// scale problem to improve its stability
		glp_scale_prob( glpkProblem, GLP_SF_AUTO );

		/* solve problem */
		if(useExact){
			glp_simplex( glpkProblem, NULL );
			glp_exact( glpkProblem, NULL );
		} else {
			glp_simplex( glpkProblem, NULL );
		}

		switch ( glp_get_status( glpkProblem ) ) {
			case GLP_OPT:
			case GLP_FEAS: {
				vector_t<double> glpkModel(constraints.cols());
				for(int i=1; i <= constraints.cols(); ++i) {
					glpkModel(i-1) = glp_get_col_prim( glpkProblem, i);
				}

				return EvaluationResult<double>(glp_get_obj_val(glpkProblem), glpkModel, SOLUTION::FEAS);
				break;
			}
			case GLP_UNBND: {
				vector_t<double> glpkModel(constraints.cols());
				for(int i=1; i <= constraints.cols(); ++i) {
					glpkModel(i-1) = glp_get_col_prim( glpkProblem, i);
				}
				return EvaluationResult<double>(1, glpkModel, SOLUTION::INFTY);
				break;
			}
			default:
				return EvaluationResult<double>(0, vector_t<double>::Zero(1), SOLUTION::INFEAS);
		}
	}

	template<>
	bool glpkCheckPoint(glp_prob* glpkProblem, const matrix_t<double>& constraints, const vector_t<double>& , const Point<double>& point) {
		// set point
		assert(constraints.cols() == point.rawCoordinates().rows());
		for ( int i = 0; i < constraints.cols(); ++i ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FX, point.rawCoordinates()(i), 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, 1.0 ); // not needed?
		}
		glp_simplex( glpkProblem, NULL);
		return (glp_get_status( glpkProblem ) != GLP_NOFEAS);
	}

	template<>
	std::vector<std::size_t> glpkRedundantConstraints(glp_prob* glpkProblem, matrix_t<double> constraints, vector_t<double> constants) {
		std::vector<std::size_t> res;

		// TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
		for ( int i = 0; i < constraints.cols(); ++i ) {
			glp_set_col_bnds( glpkProblem, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( glpkProblem, i + 1, 1.0 ); // not needed?
		}

		// first call to check satisfiability
		glp_simplex( glpkProblem, NULL);

		switch (glp_get_status( glpkProblem )) {
			case GLP_INFEAS:
			case GLP_NOFEAS: {
				return res;
			}
		}

		for(int constraintIndex = int(constraints.rows()-1); constraintIndex >= 0; --constraintIndex) {
			// evaluate in current constraint direction
			EvaluationResult<double> actualRes = glpkOptimizeLinear(glpkProblem, vector_t<double>(constraints.row(constraintIndex)), constraints, constants, false);
			//std::cout << "Actual res support Value: " << actualRes.supportValue << std::endl;
			// Necessary to cope with glpk inexactness.
			if(actualRes.supportValue > constants(constraintIndex)) {
				actualRes.supportValue = constants(constraintIndex);
			}

			// remove constraint by removing the boundaries
			glp_set_row_bnds(glpkProblem, constraintIndex+1, GLP_FR, 0.0, 0.0);
			EvaluationResult<double> updatedRes = glpkOptimizeLinear(glpkProblem, vector_t<double>(constraints.row(constraintIndex)), constraints, constants, false);
			//std::cout << "Updated res support Value: " << updatedRes.supportValue << std::endl;

			if(updatedRes.supportValue == actualRes.supportValue && updatedRes.errorCode == actualRes.errorCode) {
				res.push_back(constraintIndex);
			} else {
				glp_set_row_bnds(glpkProblem, constraintIndex+1, GLP_UP,  0.0, constants(constraintIndex) );
			}
		}

		// restore original problem
		for(const auto item : res ) {
			glp_set_row_bnds(glpkProblem, int(item)+1, GLP_UP,  0.0, constants(item));
		}

		return res;
	}

} // namespace hypro
