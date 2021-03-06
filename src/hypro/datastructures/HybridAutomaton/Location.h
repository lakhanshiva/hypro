/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Condition.h"
//#include "LocationManager.h"
//#include "lib/utils/types.h"
//#include <hypro/types.h>
#include "../../types.h"
#include <iostream>
#include <string>

namespace hypro
{
template<typename Number>
class Transition;

template<typename Number>
class LocationManager;

/**
 * @brief      Class for location.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Location
{
    friend LocationManager<Number>;

protected:
    using transitionSet = std::set<Transition<Number>*>;

    /**
     * @brief      Constructor
     * @details    Note that locations should only be constructed from the LocationManager.
     * @param[in]  id    The identifier given by the LocationManager.
     */
    Location(unsigned id);
    ///@{
    /**
     * @param[in]  id    The identifier given by the LocationManager.
     * @param[loc] The original location which is copied.
     */
    Location(unsigned id, const Location& loc);
    Location(unsigned id, const matrix_t<Number>& mat);
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);
    ///@}

private:
    mutable std::vector<matrix_t<Number>> mFlows;
    Box<Number> mExternalInput = Box<Number>::Empty();
    bool mHasExternalInput = false;
    transitionSet mTransitions;
    Condition<Number> mInvariant;
    std::string mName;
    unsigned mId;
    mutable std::size_t mHash = 0;

public:
    Location();
    Location(const Location& loc);
    Location(const matrix_t<Number>& mat);
    Location(const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);
    ~Location(){}

    std::size_t getNumberFlow() const { return mFlows.size(); }
    matrix_t<Number> getFlow(std::size_t I = 0) const { return mFlows.at(I); }
    matrix_t<Number>& rGetFlow(std::size_t I = 0) { return mFlows[I]; }
    const std::vector<matrix_t<Number>>& getFlows() const { return mFlows; }
    const Condition<Number>& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const Box<Number>& getExternalInput() const { return mExternalInput; }
    bool hasExternalInput() const { return mHasExternalInput; }
    [[deprecated("use hash() instead")]]
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }

    void setName(const std::string& name) { mName = name; mHash = 0; }
    void setFlow(const matrix_t<Number>& mat, std::size_t I = 0);
    void setInvariant(const Condition<Number>& inv) { mInvariant = inv; mHash = 0; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; mHash = 0; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); mHash = 0; }
    void updateTransition(Transition<Number>* original, Transition<Number>* newT);
    void setExtInput(const Box<Number>& b);

    std::size_t hash() const;

    /**
     * @brief      Determines if this composed of rhs and some potential rest.
     * @details    Checks whether this location can be the result of a parallel composition where rhs is involved as a composite.
     *
     * @param[in]  rhs       The right hand side
     * @param[in]  rhsVars   The right hand side variables
     * @param[in]  thisVars  The variables of this location
     *
     * @return     True if composed of, False otherwise.
     */
    bool isComposedOf(const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars) const;

    std::string getDotRepresentation(const std::vector<std::string>& vars) const;

    /*
    * decomposes flow and invariant of this location.
    */
    void decompose(std::vector<std::vector<size_t>> decomposition);

    inline bool operator<(const Location<Number>& rhs) const {
        if(this->hash() != rhs.hash()){
            return this->hash() < rhs.hash();
        } else {
            //Case where we have to compare members, as same hashes do not necessarily mean equality between the locations.
            //As order does not mean anything here semantically, we are free to choose anything that gives us an ordering between locations.
            //Here, we choose the lexicographical order between the names.
            return mName < rhs.getName();
        }
    }

    inline bool operator==(const Location<Number>& rhs) const { return (this->hash() == rhs.hash()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (this->hash() != rhs.hash()); }

    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l) {

    #ifdef HYPRO_LOGGING
	    ostr << "location " << l.getName() << " ptr "<< &l  << " (id: " << l.hash() << ")"<< std::endl << "\t Flow: " << std::endl;
	    for(size_t i = 0; i < l.getNumberFlow();i++){
	    	ostr << i << ": " << l.getFlow(i) << std::endl;
	    }
		ostr << "\t Inv: " << std::endl << l.getInvariant();
	    //ostr << l.getInvariant().getDiscreteCondition() << std::endl;
      	ostr << "ExternalInput:\n" << l.getExternalInput() << std::endl;
	    ostr << "Transitions: " << std::endl;
	    for (auto transitionPtr : l.getTransitions()) {
	        ostr << *transitionPtr << std::endl;
	    }
        ostr << "and transitions.size() is: " << l.getTransitions().size() << std::endl;
	    ostr << std::endl << ")";
	#endif
	    return ostr;
    }
};

template<typename Number>
struct locPtrComp {
    bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const { return (*lhs < *rhs); }
    bool operator()(const std::unique_ptr<Location<Number>>& lhs, const std::unique_ptr<Location<Number>>& rhs) const { return (*lhs < *rhs); }
};

template<typename Number>
std::unique_ptr<Location<Number>> parallelCompose(const std::unique_ptr<Location<Number>>& lhs
                                , const std::unique_ptr<Location<Number>>& rhs
                                , const std::vector<std::string>& lhsVar
                                , const std::vector<std::string>& rhsVar
                                , const std::vector<std::string>& haVar);


}  // namespace hypro

namespace std {

    template<typename Number>
    struct hash<hypro::Location<Number>> {
        std::size_t operator()(const hypro::Location<Number>& loc) const
        {
            //Flows
            std::size_t seed = 0;
            for(auto& flow : loc.getFlows()){
                carl::hash_add(seed, std::hash<hypro::matrix_t<Number>>()(flow));
            }

            //Name
            carl::hash_add(seed, std::hash<std::string>()(loc.getName()));

            ////Transitions
            //std::size_t transitionHash = 0;
            //for(auto& t : mTransitions){
            //  seed += std::hash<Transition<Number>*>()(t);
            //}
            ////Extinput
            //if(mHasExternalInput){
            //  seed += std::hash<Box<Number>>()(mExternalInput);
            //}

            ////Imvariant
            carl::hash_add(seed, loc.getInvariant().hash());

            return seed;
        }
    };

}  // namespace std

#include "Location.tpp"
