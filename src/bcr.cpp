#include <iostream>
#include <string>

#include "../lib/bcr.h"

void teste(){ std::cout << "TESTE" << std::endl; }

//Construct
AnimationManage::AnimationManage(int frameRate, int numberOfBar){
	setAnimationManage(frameRate, numberOfBar);
}

//start sets
void AnimationManage::setAnimationManage(int frameRate, int numberOfBar){
	m_frameRate = frameRate;
	m_numberOfBar = numberOfBar;
}

void AnimationManage::setFrame(int frameRate){
	m_frameRate = frameRate;
}

void AnimationManage::setNumberOfBar(int numberOfBar){
	m_numberOfBar = numberOfBar;
}

void AnimationManage::setFileName(std::string fileName){
	m_fileName = fileName;
}
//end sets

void AnimationManage::initialize(int argc, char *argv[]){

	std::string firstArgument;
	std::string secondArgument;

	std::cout << "argc: " << argc << std::endl;

	if(argc == 1){// Caso o user nao passe argumentos retornar erro

		std::cout << "Sem parametros validos" << std::endl;

	}else if(argc == 2){//Caso o user passe apenas o nome do arquivo: carregar valores padroes

		setFileName(argv[1]);
		std::cout << "file: " << getFileName() << std::endl;

	}else if(argc == 3){//parametros digitados mas invalidos
		
		std::cout << "Faltam parametros" << std::endl;

	}
	else if(argc == 4){//Caso o user digite apenas um parametro

		firstArgument = argv[2];

		if(firstArgument.compare("-b") == 0){//Check se o user quer mudar a qnt de barras

			std::cout << "Bars Command Valid" << std::endl;
			//TODO Checkar se argumento 3(argv[3]) é um inteiro

		}else if(firstArgument.compare("-s") == 0){//Check se o user quer mudar a quantidade de frames

			std::cout << "Frames Command Valid" << std::endl;
			//TODO Checkar se argumento 3(argv[3]) é um inteiro

		}else{//Se o user Digitar algum comando invalido

			std::cout << "Invalid Command" << std::endl;
		}
	}else if(argc == 5){//Segundo parametro invalido

		std::cout << "Segundo parametro invalido" << std::endl;

	}else if(argc == 6){//tamanho esperado

		firstArgument = argv[2];
		secondArgument = argv[4];
		//Check se Ambos argumentos sao validos
		if(firstArgument.compare("-b") == 0 || firstArgument.compare("-s") == 0){
			if(secondArgument.compare(firstArgument) != 0){//Check se os args sao diferentes
				if(secondArgument.compare("-b") == 0){
					std::cout << "primeiro arg: -s segundo arg: -b " << std::endl;
				}else if(secondArgument.compare("-s") == 0){
					std::cout << "primeiro arg: -b segundo arg: -s " << std::endl;
				}else{
					std::cout << "Comandos Invalidos" << std::endl;
				}
			}else{
					std::cout << "Mesmo comandos" << std::endl;
			}
		}else{//Check se os comandos sao invalidos(cmds inexistentes ou errados)
			std::cout << "Comandos invalidos" << std::endl;
		}
	}
}
