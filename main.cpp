#include <iostream>
#include <fstream>
#include <string>

#include "lib/bcr.h"

int main(int argc, char *argv[]){

	AnimationManage animation;
	std::ifstream file(argv[1]);
	std::string st;

	animation.initialize(argc, argv);

	if(file.is_open()){
		
		while(!file.eof()){
			file >> st;
			std::cout << st << std::endl;
		}
	}

// First Scope
//	Arquitetura gameloop
//	Gerenciador jogo
//
//	inicializarJogo(parametros);
//
//	while(verdade){
//		processar();
//		atualizar();
//		imprime();
//	}

	return 0;
}
