/**
 *
 */

#include <string>
#include "../src/lib/config.h"
#include "../src/lib/datastructures/hybridAutomata/HybridAutomaton.h"
#include "../src/lib/algorithms/reachability/Reach.h"
#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/parser/flowstar/flowstarParser.h"
#include "../src/lib/util/Plotter.h"

int main(int argc, char** argv) {
	typedef cln::cl_RA number;
	typedef hypro::SupportFunction<number> valuation;

    std::string filename = "../examples/input/bouncing_ball.model";

    hypro::parser::flowstarParser<number,valuation> parser;
    hypro::HybridAutomaton<number> ha = parser.parseInput(filename);

    hypro::reachability::Reach<number,valuation> reacher(ha, parser.mSettings);
    std::vector<std::vector<valuation>> flowpipes = reacher.computeForwardReachability();

    hypro::Plotter<number>& plotter = hypro::Plotter<number>::getInstance();
    plotter.setFilename(parser.mSettings.fileName);
    for(const auto& flowpipe : flowpipes){
    	for(const auto& segment : flowpipe)
    		plotter.addObject(segment.vertices());
    }

    plotter.plot2d();
}
