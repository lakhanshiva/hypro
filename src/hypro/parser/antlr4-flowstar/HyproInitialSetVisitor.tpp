#include "HyproInitialSetVisitor.h"

namespace hypro {

	//Constructor & Destructor
	template<typename Number>
	HyproInitialSetVisitor<Number>::HyproInitialSetVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet) :
		vars(varVec),
		locSet(lSet)
	{ }

	template<typename Number>
	HyproInitialSetVisitor<Number>::~HyproInitialSetVisitor() { }

	//Inherited
	template<typename Number>
	antlrcpp::Any HyproInitialSetVisitor<Number>::visitInit(HybridAutomatonParser::InitContext *ctx){

		typename HybridAutomaton<Number, State_t<Number,Number>>::locationStateMap initialState;

		//For all initialstates - there must be at least one according to grammar
		for(auto initStateCtx : ctx->initstate()){

			//0.Syntax Check - all given variable names really a location name?
			//If it is, save the location pointers for the localStateMap
			bool found = false;
			Location<Number>* initialLoc = NULL;
			for(const auto& loc : locSet){
				if(initStateCtx->VARIABLE()->getText() == loc->getName()){
					found = true;
					initialLoc = loc;
				}
			}
			if(!found){
				std::cerr << "ERROR: Given location name " << initStateCtx->VARIABLE()->getText() << " in init does not exist." << std::endl;
				exit(0);
			}

			//1.Get ConstraintSet, build State and add to localStateMap
			ConstraintSet<Number> conSet = visit(initStateCtx);
			State_t<Number, Number> state;
			assert(initialLoc != NULL);
			state.setLocation(initialLoc);
			state.setSet(conSet,0);
			assert(state.getNumberSets() == 1);
			state.setTimestamp(carl::Interval<Number>(0));
			initialState.emplace(std::make_pair(initialLoc, state));
		}

		return initialState;
	}

	template<typename Number>
  	antlrcpp::Any HyproInitialSetVisitor<Number>::visitInitstate(HybridAutomatonParser::InitstateContext *ctx){

  		//0.Check if there is a constraint for every stated variable
  		//We get the the assigned text via the start and stop indices given by ctx.
  		//In the text we count the occurrences of every variable name and check if every variable occurs
  		//at least one time.
  		std::vector<unsigned> varCount;
  		for(unsigned i=0; i < vars.size(); i++){
  			varCount.push_back(0);
  		}
  		std::size_t startIndex = ctx->start->getStartIndex();
  		std::size_t endIndex = ctx->stop->getStopIndex();
  		misc::Interval inter(startIndex, endIndex);
  		CharStream* input = ctx->start->getInputStream();
  		std::string text = input->getText(inter);
  		for(std::size_t i=0; i < vars.size(); i++){
  			//std::string currText = text;
  			std::size_t pos = text.find(vars[i] + " ");		//What is with x1, x10 and only x10=...?
  			if(pos != std::string::npos){
  				varCount[i]++;
  				//currText = currText.erase(pos, vars[i].size());
  			}
  		}
  		for(unsigned i=0; i < varCount.size(); i++){
  			if(varCount[i] == 0){
  				std::cerr << "ERROR: For variable " << vars[i] << " no initial constraint has been set." << std::endl;
  				exit(0);
  			}
  		}

  		//1.Call HyproFormulaVisitor and get pair of matrix and vector
		HyproFormulaVisitor<Number> visitor(vars);
		std::pair<matrix_t<Number>,vector_t<Number>> result = visitor.visit(ctx->constrset());

		//2.Build ConstraintSet and return it
		return ConstraintSet<Number>(result.first, result.second);
  	}
}
