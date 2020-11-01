/*!
 *
 * \file main.cpp
 * \author Edson Cassiano
 * \date November, 1st
 */

#include <iostream>
#include <fstream>
#include <string>

#include "lib/bcr.h"

int main(int argc, char *argv[]){

	AnimationManage animation;

	animation.initialize(argc, argv);

	while(not animation.exit()){

		animation.process();
		animation.update();
		animation.render();
	}

	return 0;
}
