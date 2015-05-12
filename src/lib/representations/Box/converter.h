/**
 * Specialization for a converter to a box.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-05-12
 * @version	2015-05-12
 */

#pragma once

#include "Box.h"
#include "../SupportFunction/SupportFunction.h"

namespace hypro {

	template<typename Number>
	class Converter <hypro::Box<Number>, hypro::SupportFunction<Number> > {
		private:
			VariablePool& mPool;

		public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		hypro::Box<Number> convert(const hypro::SupportFunction<Number>& _source) const {
			unsigned dim = _source.dimension();
			std::cout << "Dimension: " << dim << std::endl;
			
			matrix_t<Number> directions = matrix_t<Number>::Zero(2*dim,dim);
			for(unsigned i=0; i<dim; ++i) {
				directions(2*i, i) = -1;
				directions(2*i+1, i) = 1;
			}

			std::cout << directions << std::endl;

			vector_t<Number> distances = _source.multiEvaluate(directions);

			typename Box<Number>::intervalMap intervals;
			for(unsigned i=0; i<dim; ++i) {
				intervals.insert(std::make_pair(mPool.carlVarByIndex(i), carl::Interval<Number>(distances(2*i), distances(2*i+1))));
			}

			return Box<Number>(intervals);
		}

	private:
	};

} //namespace