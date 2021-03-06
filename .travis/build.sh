#!/usr/bin/env bash

mkdir -p build || return 1
pushd build

function keep_waiting() {
  while true; do
    echo -e "."
    sleep 60
  done
}

if [[ ${TASK} == "sonarcloud" ]]; then
	cmake ../ -DHYPRO_COVERAGE=ON -DCMAKE_CXX_COMPILER=$COMPILER || return 1
	WRAPPER="build-wrapper-linux-x86-64 --out-dir ../bw-out"
	$WRAPPER make hypro -j4 || return 1
	#make coverage-collect
	#echo "This folder:"
	#ls -la
	#echo "Parent folder:"
	#ls ../

	cd ../ && sonar-scanner -X -Dproject.settings=.travis/sonar-project.properties && cd build/

else
	git clone https://github.com/smtrat/carl.git
	pushd carl
		mkdir build
		pushd build && cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_BUILD_TYPE=Release ..
			keep_waiting &
			make resources || return 1
			kill $!
			make lib_carl VERBOSE=1 || return 1
		popd
	popd
	cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
	make resources -j2 || return 1
	echo /home/travis/build/hypro/hypro/build/resources/antlr_build/src/antlr4cpp-stamp/antlr4cpp-build-out.log
	echo /home/travis/build/hypro/hypro/build/resources/antlr_build/src/antlr4cpp-stamp/antlr4cpp-build-err.log
	keep_waiting &
	make -j2 VERBOSE=1 || return 1
	kill $!
	make test

fi

popd


