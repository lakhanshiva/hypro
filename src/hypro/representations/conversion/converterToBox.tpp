/**
 * Specialization for a converter to a box.
 * @file converterToBox.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-12
 * @version	2016-03-17
 */

#include "Converter.h"
#ifndef INCL_FROM_CONVERTERHEADER
	static_assert(false, "This file may only be included indirectly by Converter.h");
#endif

//TODO alternative approach for H -> Box (testing which is faster)

// conversion from box to box (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Box& _source, const CONV_MODE  ) {
	return _source;
}

template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox(const ConstraintSet& source, const CONV_MODE) {
	return BoxT<Number,Converter,BoxLinearOptimizationOn>(source.matrix(), source.vector());
}

template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Ellipsoid& _source, const CONV_MODE  ) {
	vector_t<Number> l(_source.dimension());
	vector_t<Number> evaluation;
	l.setZero();
	std::vector<carl::Interval<Number>> intervals(_source.dimension());
	for ( std::size_t i = 0; i < _source.dimension(); i++) {
	    l(i) = 1;
	    evaluation = _source.evaluate(l);
	    intervals.at(i).setLower(evaluation(i));
	    intervals.at(i).setUpper(-evaluation(i));
	    l(i) = 0;
	}
	return BoxT<Number,Converter,BoxLinearOptimizationOn>(intervals);
}

// conversion from support function to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const SupportFunction& _source, const CONV_MODE  ) {
	std::size_t dim = _source.dimension();                                                                     //gets dimension from the source object

	matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
	for ( std::size_t i = 0; i < dim; ++i ) {                                                                  //for every dimension
		directions( 2 * i, i ) = -1;
		directions( 2 * i + 1, i ) = 1;                                                                 //write fixed entries (because of box) into the normal matrix (2 each column)
	}

	std::vector<EvaluationResult<Number>> distances = _source.multiEvaluate( directions );                                       //evaluate the source support function into these 2*dim directions (to get the interval end points)

	std::vector<carl::Interval<Number>> intervals;
	for ( std::size_t i = 0; i < dim; ++i ) {                                                                  //for every dimension
        carl::BoundType lowerBound = carl::BoundType::WEAK;
        carl::BoundType upperBound = carl::BoundType::WEAK;
        //if no bound is found in that direction (infinity) set interval end point to infinity
        if(distances[2*i].errorCode == SOLUTION::INFTY)
            lowerBound = carl::BoundType::INFTY;
        //if no bound is found in that direction (infinity) set interval end point to infinity
        if(distances[2*i+1].errorCode == SOLUTION::INFTY)
            upperBound = carl::BoundType::INFTY;
		intervals.push_back( carl::Interval<Number>( -distances[2*i].supportValue, lowerBound, distances[2*i+1].supportValue, upperBound ) );   //create one interval with the corresponding left and right end points (inverted lower interval end points)
	}

    // if (mode == EXACT){                                                                                      //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _target.vertices();                                         //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                           //for every new vertex (from the box)
    //         foundEqual = _source.contains(newVertex);                                                        //checks if source-object contains the new vertex
    //         if (foundEqual == false){                                                                        //if source object doesn't contain any of the new vertices, the target object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

	return BoxT<Number,Converter,BoxLinearOptimizationOn>( intervals );
}

//conversion from V-Polytope to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const VPolytope& _source, const CONV_MODE  ) {
	typename VPolytopeT<Number,Converter>::pointVector vertices = _source.vertices();               //gets vertices as a vector from the source object
	if(!vertices.empty()){
		vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
		vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

		for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
			for ( unsigned d = 0; d < _source.dimension(); ++d ) {                                  //for every dimension
				minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
				maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
				assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
			}
		}

		std::vector<carl::Interval<Number>> intervals;
		for ( unsigned i = 0; i < _source.dimension(); ++i ) {                                          //for every dimension
			intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
		}

	    // if(mode == EXACT){                                                                               //checks if conversion was exact
	    //     bool foundEqual;
	    //     std::vector<Point<Number>> newVertices = _target.vertices();                                 //computes vertices from the just newly created box
	    //     for (const auto& newVertex : newVertices){                                                   //for every new vertex (from the box)
	    //         foundEqual = _source.hasVertex(newVertex);                                               //checks if source-object contains the new vertex
	    //         if (foundEqual == false){                                                                //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
	    //             return false;
	    //         }
	    //     }
	    // }

		return BoxT<Number,Converter,BoxLinearOptimizationOn>( intervals );                                          //creates a box with the computed intervals
	}
	return BoxT<Number,Converter,BoxLinearOptimizationOn>();
}

//conversion from H-Polytope to box (OVER or ALTERNATIVE)
//ALTERNATIVE evaluates instead of converting to V-Polytope (may be faster with only 2d directions for complex objects)
//ALTERNATIVE is nearly always faster with same precision => use it
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const HPolytope& _source, const CONV_MODE mode ) {
        BoxT<Number,Converter,BoxLinearOptimizationOn> result;
        if (mode == OVER){
                std::vector<Point<Number>> vertices = _source.vertices();                                  //gets vertices as a vector from the source object (is actually a conversion from H-Polytope to V-Polytope)
                if(!vertices.empty()){
                	vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
	                vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

	                for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
	                        for ( unsigned d = 0; d < _source.dimension(); ++d ) {                                  //for every dimension
	                                minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
	                                maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
	                                assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
	                        }
	                }

	                std::vector<carl::Interval<Number>> intervals;
	                for ( std::size_t i = 0; i < _source.dimension(); ++i ) {                                          //for every dimension
	                        intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
	                }

	                result = BoxT<Number,Converter,BoxLinearOptimizationOn>(intervals); //creates a box with the computed intervals
                }
         }

        if (mode == ALTERNATIVE){
            std::size_t dim = _source.dimension();                                                                              //gets dimension from the source object

            matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                                            //initialize normal matrix as zero matrix with 2*dim rows and dim columns
            for ( std::size_t i = 0; i < dim; ++i ) {                                                                           //for every dimension
                     directions( 2 * i, i ) = -1;
                     directions( 2 * i + 1, i ) = 1;                                                                          //write fixed entries (because of box) into the normal matrix (2 each column)
            }
            //evaluate the source support function into these 2*dim directions (to get the interval end points)
            std::vector<EvaluationResult<Number>> distances = std::vector<EvaluationResult<Number>>(2*dim);
            for (std::size_t i=0; i < dim; ++i){
                distances[2*i] = _source.evaluate(directions.row(2*i));
                distances[2*i+1] = _source.evaluate(directions.row(2*i+1));
            }

		    std::vector<carl::Interval<Number>> intervals;
		    for ( std::size_t i = 0; i < dim; ++i ) {                                                                                      //for every dimension
               carl::BoundType lowerBound = carl::BoundType::WEAK;
               carl::BoundType upperBound = carl::BoundType::WEAK;
               //if no bound is found in that direction (infinity) set interval end point to infinity
               if(distances[2*i].errorCode == SOLUTION::INFTY){
                  lowerBound = carl::BoundType::INFTY;
               }
               //if no bound is found in that direction (infinity) set interval end point to infinity
               if(distances[2*i+1].errorCode == SOLUTION::INFTY){
                  upperBound = carl::BoundType::INFTY;
               }
		       intervals.push_back( carl::Interval<Number>( -distances[2*i].supportValue, lowerBound, distances[2*i+1].supportValue, upperBound ) );   //create one interval with the corresponding left and right end points (inverted lower interval end points)
		    }
            result = BoxT<Number,Converter,BoxLinearOptimizationOn>(intervals);
        }
    // if(mode == EXACT){                                                                              //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _result.vertices();                                //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
    //         foundEqual = _source.contains(newVertex);                                               //checks if source-object contains the new vertex
    //         if (foundEqual == false){                                                               //if no equal vertex was found, the result object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

    return result;
}

#ifdef HYPRO_USE_PPL
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Polytope& _source, const CONV_MODE  ) {
	BoxT<Number,Converter,BoxLinearOptimizationOn> tmp(_source.vertices());
	return BoxT<Number,Converter,BoxLinearOptimizationOn>( _source.vertices() );
}
#endif

//conversion from zonotope to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Zonotope& _source, const CONV_MODE mode ) {

	if( mode != CONV_MODE::ALTERNATIVE ){

	    typename std::vector<Point<Number>> vertices = _source.vertices();                                   //computes vertices from source object
	    if(vertices.empty()){
	    	return BoxT<Number,Converter,BoxLinearOptimizationOn>();
	    }
		assert( !vertices.empty() );                                                                            //only continue if any actual vertices were received at all
		Point<Number> minima = vertices[0];                                                                  //creates a vector_t with the first vertex of the source object
		Point<Number> maxima = vertices[0];                                                                  //creates another vector_t with the first vertex of the source object

		for ( std::size_t i = 0; i < vertices.size(); ++i ) {                                                   //for each vertex of the source object
			for ( std::size_t d = 0; d < _source.dimension(); ++d ) {                                       //for every dimension
				minima[d] = vertices[i].at( d ) < minima.at( d ) ? vertices[i].at( d ) : minima.at( d );          //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
				maxima[d] = vertices[i].at( d ) > maxima.at( d ) ? vertices[i].at( d ) : maxima.at( d );          //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
				assert( minima.at( d ) <= maxima.at( d ) );                                                   //only continue if the maximum value is not smaller than the minimum value
			}
		}

	    // if(mode == EXACT){                                                                                      //checks if conversion was exact
	    //     bool foundEqual;
	    //     std::vector<Point<Number>> newVertices = _target.vertices();                                        //computes vertices from the just newly created box
	    //     for (const auto& newVertex : newVertices){                                                          //for every new vertex (from the box)
	    //         foundEqual = false;
	    //         for (const auto& oldVertex : vertices){                                                         //checks if source-object contains the new vertex
	    //             if (newVertex == oldVertex){
	    //                 foundEqual = true;
	    //             }
	    //         }
	    //         if (foundEqual == false){                                                                       //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
	    //             return false;
	    //         }
	    //     }
	    // }

		return BoxT<Number,Converter,BoxLinearOptimizationOn>( std::make_pair(minima, maxima) );                                                 //creates a box with the computed intervals

	} else {

		//Alternative: By only adding the coefficients of one dimension together, and this for each dimension, 
		//we can determine every halfspace needed for the box.
		
		//1.For every dimension, add the coefficients of every generator for that dimension together
		matrix_t<Number> generatorMat = _source.generators();
		vector_t<Number> summedCoeffs = vector_t<Number>::Zero(generatorMat.rows());
		unsigned dim = summedCoeffs.rows();
		for(unsigned d = 0; d < dim; d++){
			for(unsigned j = 0; j < generatorMat.cols(); j++){
				Number coeffAbs = generatorMat(d,j) >= 0 ? generatorMat(d,j) : Number(-1)*generatorMat(d,j);
				summedCoeffs(d) = summedCoeffs(d) + coeffAbs;
			}
		}

		//2.Double the summedcoeffs like: before summedCoeffs = (1,2) and center = (-2,1) after summedcoeffs = (-1,3,-1,3)
		summedCoeffs += _source.center();
		vector_t<Number> extendedSummedCoeffs = vector_t<Number>::Zero(2*summedCoeffs.rows());
		for(unsigned i = 0; i < extendedSummedCoeffs.rows(); i++){
			unsigned coeffIndex = i % dim;
			extendedSummedCoeffs(i) = summedCoeffs(coeffIndex);
		}

		//2.Build every halfspace needed for a box
		std::vector<vector_t<Number>> directions = computeTemplate<Number>(dim, 4);
		matrix_t<Number> halfspaceMat = matrix_t<Number>::Zero(directions.size(), dim);
		for(unsigned i = 0; i < directions.size(); i++){
			halfspaceMat.row(i) = directions.at(i);
		}
		Converter<Number>::Box box = Converter<Number>::Box(halfspaceMat, extendedSummedCoeffs);
		return box;
	}
}

//conversion from difference bounds to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const DifferenceBounds& _source, const CONV_MODE ) {
	if(_source.getDBM().rows() < 1){
		return BoxT<Number,Converter,BoxLinearOptimizationOn>();
	}
 	//first column describes upper bounds, first row describes lower bounds, cast these to point
 	std::vector<Number> upper;
 	// i=1 -- do not consider 0 clock
 	for(int i = 1; i < _source.getDBM().rows(); i++){
 		if(_source.getDBM()(i,0).second == DifferenceBoundsT<Number,Converter,DifferenceBoundsSetting>::BOUND_TYPE::INFTY){
 			// no infinite boxes
 			return BoxT<Number,Converter,BoxLinearOptimizationOn>();
 		}
 		upper.push_back(_source.getDBM()(i,0).first);
 	}

 	std::vector<Number> lower;
 	// i=1 -- do not consider 0 clock
 	for(int i = 1; i < _source.getDBM().cols(); i++){
 		if(_source.getDBM()(0,i).second == DifferenceBoundsT<Number,Converter,DifferenceBoundsSetting>::BOUND_TYPE::INFTY){
 			// no infinite boxes
 			return BoxT<Number,Converter,BoxLinearOptimizationOn>();
 		}
 		// note that the entries are always </<= so a lower bound is given by a negative number
 		// eg. (-3,<=) <=> 0-x <= -3 <=> -x <= -3 <=> x >= 3
 		// eg. (3, <=) <=> 0-x <= 3 <=> -x <= 3 <=> x >= -3
 		Number value = _source.getDBM()(0,i).first;
 		if(value != Number(0)){
 			value = -1.0*value;
 		}
 		lower.push_back(value);
 	}

 	Point<Number> minimum(lower);
 	Point<Number> maximum(upper);
	return BoxT<Number,Converter,BoxLinearOptimizationOn>(std::make_pair(minimum, maximum));
}


//conversion from Polytope to box (different data structure)
//template<typename Number>
//Box Converter<Number>::toBox( const hypro::Polytope<Number>& _source, const CONV_MODE mode ) {
//	std::vector<Point<Number>> points = _source.vertices();                                                                         //gets vertices as a vector from the source object
//	assert( !points.empty() );                                                                                                      //only continue if any actual vertices were received at all
//
//	vector_t<Number> minima = points[0].rawCoordinates();                                                                           //creates a vector_t with the first vertex of the source object
//	vector_t<Number> maxima = points[0].rawCoordinates();                                                                           //creates another vector_t with the first vertex of the source object
//
//	for ( std::size_t i = 0; i < points.size(); ++i ) {                                                                             //for each vertex of the source object
//		for ( std::size_t d = 0; d < _source.dimension(); ++d ) {                                                               //for every dimension
//			minima( d ) = points[i].rawCoordinates()( d ) < minima( d ) ? points[i].rawCoordinates()( d ) : minima( d );    //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
//			maxima( d ) = points[i].rawCoordinates()( d ) > maxima( d ) ? points[i].rawCoordinates()( d ) : maxima( d );    //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
//			assert( minima( d ) <= maxima( d ) );                                                                           //only continue if the maximum value is not smaller than the minimum value
//		}
//	}
//
//	std::vector<carl::Interval<Number>> intervals;
//	for ( std::size_t i = 0; i < _source.dimension(); ++i ) {                                                                       //for every dimension
//		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );                                              //create one interval per dimension with the corresponding minimal and maximal values
//	}
//
//    // if(mode == EXACT){                                                                                                              //checks if conversion was exact
//    //     bool foundEqual;
//    //     std::vector<Point<Number>> newVertices = _target.vertices();                                                                //computes vertices from the just newly created box
//    //     for (const auto& newVertex : newVertices){                                                                                  //for every new vertex (from the box)
//    //         foundEqual = false;
//    //         for (const auto& oldVertex : points){                                                                                   //checks if source-object contains the new vertex
//    //             if (newVertex == oldVertex){
//    //                 foundEqual = true;
//    //             }
//    //         }
//    //         if (foundEqual == false){                                                                                               //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
//    //             return false;
//    //         }
//    //     }
//    // }
//
//	return std::move(BoxT<Number,Converter,BoxLinearOptimizationOn>( intervals ));
//}
