#pragma once

namespace hypro {

	struct SupportFunctionSetting {
		static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
		static constexpr bool USE_LIN_TRANS_REDUCTION = true;
		static constexpr bool REDUCE_TO_BOX = true;
		static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;
		static constexpr bool BOXOPERATOR_VERBOSE = false;
		static constexpr bool CALCEPSILON_VERBOSE = false;
		static constexpr bool CALCVALUES_VERBOSE = false;
		static constexpr bool TEST_ = false;
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
		// static constexpr bool HYPRO_USE_VECTOR_CACHING = false;
	};

	struct NoBoxReduction : SupportFunctionSetting {
		static constexpr bool REDUCE_TO_BOX = false;
	};

	//PolytopeSupportFunctions
	struct PolytopeSupportFunctionSetting : SupportFunctionSetting {
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
	};

}
