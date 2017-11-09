/**
 * Specialization for a conversion to a Difference Bounds representation.
 * @file converterToDifferenceBounds.tpp
 * @author Justin Winkens
 *
 * @since	2017-11-08
 * @version	2017-11-08
 */

#include "Converter.h"
#include "../../util/templateDirections.h"

//conversion from DifferenceBounds to DifferenceBounds (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const DifferenceBounds& source, const CONV_MODE mode){
    return source;
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Box& source, const CONV_MODE mode){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const ConstraintSet& source, const CONV_MODE mode){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Ellipsoid& source, const CONV_MODE mode){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const HPolytope& source, const CONV_MODE mode){

    size_t numclocks = source.dimension();
    // check wether the entire polytope is positive, because we expect clocks
    hypro::matrix_t<Number> mat = hypro::matrix_t<Number>::Identity(numclocks,numclocks);
    mat = mat*-1.0;
    hypro::vector_t<Number> vec = hypro::vector_t<Number>::Zero(numclocks);
    if(source.satisfiesHalfspaces(mat,vec).first != hypro::CONTAINMENT::FULL){
        std::cout << "HPolytope \n " << source << " is not entirely positie. Calculations may be imprecise.";
    }
    //std::cout<< "Hpolytope has " << numclocks << " clocks.\n";
    // 1. introduce a zero clock (numclocks+1)
    numclocks++;
    hypro::matrix_t<typename Converter<Number>::DifferenceBounds::DBMEntry> dbm = hypro::matrix_t<typename Converter<Number>::DifferenceBounds::DBMEntry>(numclocks, numclocks);

    //  for each pair of variables i,j
    for(int i = 0; i < numclocks; i++) {
        for(int j=0; j < numclocks; j++) {
            //      if i!=j (do not consider diagonal entries)
            if(i!=j) {
                vector_t<Number> direction = vector_t<Number>::Zero(numclocks-1);
                //          if (i=0) (query direction vector (0,...,0,-1,0,...,0) -1 at jth position)
                if(i == 0){
                    direction(j-1)=-1.0;
                }
                //          elif (j=0) (query direction vector (0,...,0,+1,0,...,0) +1 at ith position)
                else if(j==0){
                    direction(i-1)=1.0;
                }
                //          else (query direction vector (0,0,...,0,+1,0,..,0,-1,0,...0) +1 at ith position, -1 at jth position)
                else {
                    direction(i-1)=1.0;
                    direction(j-1)=-1.0;
                }
                EvaluationResult<Number> res = source.evaluate(direction);
                if(res.errorCode == hypro::SOLUTION::INFTY){
                    dbm(i, j) = typename Converter<Number>::DifferenceBounds::DBMEntry(0.0, DifferenceBounds::BOUND_TYPE::INFTY);
                }
                else {
                    //std::cout << "Query direction vector " << direction << " yields result: " << res.supportValue << "\n";
                    dbm(i, j) = typename Converter<Number>::DifferenceBounds::DBMEntry(res.supportValue, DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
                }
            }
            else{
                dbm(i,j)=typename Converter<Number>::DifferenceBounds::DBMEntry(0.0, DifferenceBounds::BOUND_TYPE::SMALLER_EQ);
            }
        }
    }
    DifferenceBounds result = DifferenceBounds();
    result.setDBM(dbm);
    //std::cout << "Resulting DBM: \n" << result << "\n";
    return result;
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const VPolytope& source, const CONV_MODE mode){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const SupportFunction& _source, const std::vector<vector_t<Number>>& additionalDirections, const CONV_MODE, std::size_t numberOfDirections){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(_source);
    return toDifferenceBounds(tmp);
}

template<typename Number>
typename Converter<Number>::DifferenceBounds Converter<Number>::toDifferenceBounds(const Zonotope& source, const CONV_MODE mode){
    // TODO make better, this is just the cheap solution
    HPolytope tmp = toHPolytope(source);
    return toDifferenceBounds(tmp);
}
