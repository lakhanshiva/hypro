/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.tpp
 * @author Simon Froitzheim
 *
 * @since      2015-11-23
 * @version    2015-12-16
 */

#include "SupportFunction.h"

namespace hypro{

//CONSTRUCTORS


    //-------PRIVATE---------
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::shared_ptr<SupportFunctionContent<Number>> _source) : content(_source){
        //handled by initializer list
    }

    //-------PUBLIC---------
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT() : content(std::shared_ptr<SupportFunctionContent<Number>>()){
        //handled by initializer list
    }

    //copy constructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT( const SupportFunctionT<Number,Converter> &_orig ) : content(_orig.content){
        //handled by initializer list
    }

    //move constructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT( SupportFunctionT<Number,Converter>&& other) : SupportFunctionT<Number,Converter>(){
        swap(*this, other);
    }


    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(SF_TYPE _type, Number _radius ) : content(hypro::SupportFunctionContent<Number>::create(_type, _radius)){
        //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::vector<Point<Number>>& _vertices)
        : content(hypro::SupportFunctionContent<Number>::create(SF_TYPE::POLY, _vertices)) {
        //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const matrix_t<Number>& _directions, const vector_t<Number>& _distances) : content(hypro::SupportFunctionContent<Number>::create(SF_TYPE::POLY, _directions, _distances)){
         //handled by initializer list
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::SupportFunctionT(const std::vector<Halfspace<Number>>& _planes) : content(hypro::SupportFunctionContent<Number>::create(SF_TYPE::POLY, _planes)){
         //handled by initializer list
    }

    //destructor
    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>::~SupportFunctionT() {
    }

// OPERATOR OVERLOADING

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>& SupportFunctionT<Number,Converter>::operator=(SupportFunctionT<Number,Converter> _orig) {
        //std::cout << "SupportFunction Copy\n";
        if (this != &_orig){
            swap(*this, _orig);
        }
        return *this;
    }


// FUNCTIONS

    template<typename Number, typename Converter>
    EvaluationResult<Number> SupportFunctionT<Number,Converter>::evaluate( const vector_t<Number> &_direction ) const {
        EvaluationResult<Number> tmp = content->evaluate(_direction);
        //std::cout << __func__ << "(" << _direction << ") :" << tmp.supportValue << std::endl;
        return tmp;
    }

    template<typename Number, typename Converter>
    std::vector<EvaluationResult<Number>> SupportFunctionT<Number,Converter>::multiEvaluate( const matrix_t<Number> &_directions ) const {
        //std::cout << __func__ << " " << convert<Number,double>(_directions) << std::endl;
        std::vector<EvaluationResult<Number>> res = content->multiEvaluate(_directions);
        assert(res.size() == std::size_t(_directions.rows()));
        return res;
    }

    template<typename Number, typename Converter>
    std::size_t SupportFunctionT<Number,Converter>::dimension() const {
        return content->dimension();
    }

    template<typename Number, typename Converter>
    SF_TYPE SupportFunctionT<Number,Converter>::type() const {
        return content->type();
    }

    template<typename Number, typename Converter>
    sumContent<Number> *SupportFunctionT<Number,Converter>::summands() const {
       return content->summands();
    }

    template<typename Number, typename Converter>
    trafoContent<Number> *SupportFunctionT<Number,Converter>::linearTrafoParameters() const {
        return content->linearTrafoParameters();
    }

    template<typename Number, typename Converter>
    scaleContent<Number> *SupportFunctionT<Number,Converter>::scaleParameters() const {
        return content->scaleParameters();
    }

    template<typename Number, typename Converter>
    unionContent<Number> *SupportFunctionT<Number,Converter>::unionParameters() const {
        return content->unionParameters();
    }

    template<typename Number, typename Converter>
    intersectionContent<Number> *SupportFunctionT<Number,Converter>::intersectionParameters() const {
        return content->intersectionParameters();
    }

    template<typename Number, typename Converter>
    PolytopeSupportFunction<Number> *SupportFunctionT<Number,Converter>::polytope() const {
        return content->polytope();
    }

    template<typename Number, typename Converter>
    BallSupportFunction<Number> *SupportFunctionT<Number,Converter>::ball() const {
        return content->ball();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::removeRedundancy() {

    }

    template<typename Number, typename Converter>
    std::vector<Point<Number>> SupportFunctionT<Number,Converter>::vertices() const {
        auto tmp = Converter::toHPolytope(*this);
        return tmp.vertices();
    }

    template<typename Number, typename Converter>
    Number SupportFunctionT<Number,Converter>::supremum() const {
        auto tmp = Converter::toHPolytope(*this);
        return tmp.supremum(); // TODO: Temporary!
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::linearTransformation(const matrix_t<Number> &_A, const vector_t<Number> &_b ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->linearTransformation(_A, _b));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>  SupportFunctionT<Number,Converter>::minkowskiSum( SupportFunctionT<Number,Converter> &_rhs ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->minkowskiSum(_rhs.content));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::intersect(SupportFunctionT<Number,Converter> &_rhs) const {
        //std::cout << __func__ << std::endl;
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->intersect(_rhs.content));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const{
        //std::cout << __func__ << std::endl;
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->intersect(SupportFunctionT<Number,Converter>(_mat,_vec).content));
        return res;
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const Point<Number> &_point ) const {
        return content->contains(_point);
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const vector_t<Number> &_point ) const {
        return content->contains(_point);
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::contains( const SupportFunctionT<Number, Converter>& rhs, unsigned directions ) const {
    	std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(this->dimension(), directions);
    	for(const auto& direction : templateDirections) {
    		if(this->evaluate(direction).supportValue < rhs.evaluate(direction).supportValue)
    			return false;
    	}
    	return true;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter>  SupportFunctionT<Number,Converter>::unite( SupportFunctionT<Number,Converter> &_rhs ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->unite(_rhs.content));
        return res;
    }

    template<typename Number, typename Converter>
    SupportFunctionT<Number,Converter> SupportFunctionT<Number,Converter>::scale( const Number &_factor ) const {
        SupportFunctionT<Number,Converter> res = SupportFunctionT<Number,Converter>(content->scale( _factor));
        return res;
    }

    //template<typename Number, typename Converter>
    //std::pair<bool, SupportFunctionT<Number,Converter>> SupportFunctionT<Number,Converter>::satisfiesHalfspace( const vector_t<Number>& normal, const Number& offset) const {
    //    if(content->evaluate(normal) <= offset)
    //        return true;
//
//    //    return ( -(content->evaluate(-normal)) <= offset);
    //}

    template<typename Number, typename Converter>
    std::pair<bool, SupportFunctionT<Number,Converter>> SupportFunctionT<Number,Converter>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
        //std::cout << __func__ << ": " << _mat << std::endl << " <= " << _vec <<  std::endl;
        assert(_mat.rows() == _vec.rows());
        bool empty = false;
        std::vector<unsigned> limitingPlanes;
        for(unsigned rowI = 0; rowI < _mat.rows(); ++rowI) {
        	EvaluationResult<Number> inDirEval = content->evaluate(_mat.row(rowI));
        	if(inDirEval.errorCode == SOLUTION::INFEAS){
        		empty = true;
        		break;
        	} else if(inDirEval.supportValue > _vec(rowI)){
        		// the actual object will be limited by the new plane
        		limitingPlanes.push_back(rowI);
        	}
            //std::cout << "evaluate(" << convert<Number,double>(-(_mat.row(rowI))) << ") <=  " << -(_vec(rowI)) << ": " << content->evaluate(-(_mat.row(rowI))).supportValue << " <= " << -(_vec(rowI)) << std::endl;
            if(content->evaluate(-(_mat.row(rowI))).supportValue <= -(_vec(rowI))){
                //std::cout << "EMPTY" << std::endl;
                empty = true;
                break;
            }
        }
        if(!empty){
        	if(limitingPlanes.size() < unsigned(_mat.rows())){
        		if(limitingPlanes.size() == 0 ){
        			return std::make_pair(!empty, *this);
        		}
        		// if the result is not empty, only add planes, which affect the object
	        	matrix_t<Number> planes = matrix_t<Number>(limitingPlanes.size(), _mat.cols());
	        	vector_t<Number> distances = vector_t<Number>(limitingPlanes.size());
	        	for(unsigned i = 0; i < limitingPlanes.size(); ++i){
	        		planes.row(i) = _mat.row(limitingPlanes.back());
	        		distances(i) = _vec(limitingPlanes.back());
	        		limitingPlanes.pop_back();
	        	}
	        	return std::make_pair(!empty, this->intersectHalfspaces(planes,distances));
        	} else {
        		assert(limitingPlanes.size() == unsigned(_mat.rows()));
        		return std::make_pair(!empty, this->intersectHalfspaces(_mat,_vec));
        	}

        }
        return std::make_pair(!empty, this->intersectHalfspaces(_mat,_vec));
    }

    template<typename Number, typename Converter>
    bool SupportFunctionT<Number,Converter>::empty() const {
        return content->empty();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::print() const {
        return content->print();
    }

    template<typename Number, typename Converter>
    void SupportFunctionT<Number,Converter>::swap(SupportFunctionT<Number,Converter>& first, SupportFunctionT<Number,Converter>& second){
         first.content.swap(second.content);
     }



} //namespace
