/*!
 *
 * \file bcr.cpp
 * \author Edson Cassiano
 * \date November, 1st
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

#include "../lib/bcr.h"
#include "../lib/text_color.h"

//Construct

//BEGIN class BarChart sets
BarChart::BarChart(std::string count, std::string value, std::string name, std::string category){
	setBarChart(count, value, name, category);
}

void BarChart::setBarChart(std::string count, std::string value, std::string name, std::string category){
	m_count = count;
	m_name = name;
	m_value = value;
	m_category = category;
}

void BarChart::setCount(std::string count){
	m_count = count;
}

void BarChart::setValue(std::string value){
	m_value = value;
}

void BarChart::setNameBar(std::string name){
	m_name = name;
}

void BarChart::setCategory(std::string category){
	m_category = category;
}

//END class BarChart sets
AnimationManage::AnimationManage(int frameRate, int numberOfBar){
	setAnimationManage(frameRate, numberOfBar);
}

void AnimationManage::setAnimationManage(int frameRate, int numberOfBar){
	m_frameRate = frameRate;
	m_numberOfBar = numberOfBar;
	m_currentBarChart = 0;
}

void AnimationManage::setFrameRate(int frameRate){
	m_frameRate = frameRate;
}

void AnimationManage::setNumberOfBar(int numberOfBar){
	m_numberOfBar = numberOfBar;
}

void AnimationManage::setNumberOfChart(int numberOfChart){
	m_numberOfChart = numberOfChart;
}

void AnimationManage::setNumberOfItems(int numberOfItems){
	m_numberOfItems = numberOfItems;
}

void AnimationManage::setCurrentBarChart(int currentBarChart){
	m_currentBarChart = currentBarChart;
}

void AnimationManage::setAnimationStage(int animationStage){
	m_animationStage = animationStage;
}

void AnimationManage::setFileName(std::string fileName){
	m_fileName = fileName;
}

void AnimationManage::setTitle(std::string title){
	m_title = title;
}

void AnimationManage::setSubtitle(std::string subtitle){
	m_subtitle = subtitle;
}

void AnimationManage::setSource(std::string source){
	m_source = source;
}

//end sets

bool AnimationManage::exit(){
	return getAnimationStage() == 8;
}

void AnimationManage::initialize(int argc, char *argv[]){

	std::string firstArgument;
	std::string secondArgument;
//	std::string temp;

	int aux;

	if(argc == 1){// Caso o user nao passe argumentos retornar erro

		std::cout << "Usage: bcr [<options>] <input data_file>" << std::endl;
		std::cout << "	Bar Chart Race options:" << std::endl;
		std::cout << "		-b <num> Max # of bars in a single char." << std::endl;
		std::cout << "			Valid range is[1,14]. Default values is 5." << std::endl;
		std::cout << "		-f <num> Animation speed in fps (frames per second)." << std::endl;
		std::cout << "			Valid range is[1,24]. Default values is 24." << std::endl;

		setAnimationStage(8);

	}else if(argc >= 2){// Se o user digitar o nome do arquivo, verifica se é valido

		setFileName(argv[1]);
		setAnimationStage(0);
	}	
	
	if(argc == 3){//parametros digitados mas invalidos
		
		std::cout << Color::tcolor("Insufficient Parameters", Color::RED, Color::REGULAR) << std::endl;
		setAnimationStage(8);

	}else if(argc == 4){//Caso o user digite apenas um parametro

		firstArgument = argv[2];

		if(firstArgument.compare("-b") == 0){//Check se o user quer mudar a qnt de barras
			//vai até 14

			aux = atoi(argv[3]);

			if(aux >= 1 && aux <= 14){

				setNumberOfBar(aux);

			}else{
				// Quantidade de Barras padrão
			}

		}else if(firstArgument.compare("-s") == 0){//Check se o user quer mudar a quantidade de frames

			aux = atoi(argv[3]);

			if(aux >= 1 && aux <= 24){
				setFrameRate(aux);
			}else{
				// Quantidade de Frames padrão
			}

		}else{//Se o user Digitar algum comando invalido

			std::cout << Color::tcolor("Invalid Command", Color::RED, Color::REGULAR) << std::endl;
			setAnimationStage(8);
		}
	}else if(argc == 5){//Segundo parametro invalido

		std::cout << Color::tcolor("Invalid Second Parameter", Color::RED, Color::REGULAR) << std::endl;
		setAnimationStage(8);

	}else if(argc == 6){//tamanho esperado

		firstArgument = argv[2];
		secondArgument = argv[4];
		//Check se Ambos argumentos sao validos
		if(firstArgument.compare("-b") == 0 || firstArgument.compare("-s") == 0){

			if(secondArgument.compare(firstArgument) != 0){//Check se os args sao diferentes

				if(secondArgument.compare("-b") == 0){

					aux = atoi(argv[3]);

					if(aux >= 1 && aux <= 24){

						setFrameRate(aux);

					}else{
						// Quantidade de Barras padrão
					}

					aux = atoi(argv[5]);

					if(aux >= 1 && aux <= 14){

						setNumberOfBar(aux);

					}else{
						// Quantidade de Barras padrão
					}

				}else if(secondArgument.compare("-s") == 0){

					aux = atoi(argv[3]);

					if(aux >= 1 && aux <= 14){

						setNumberOfBar(aux);

					}else{
						// Quantidade de Barras padrão
					}

					aux = atoi(argv[5]);

					if(aux >= 1 && aux <= 24){

						setFrameRate(aux);

					}else{
						// Quantidade de Barras padrão
					}

				}else{

					std::cout << Color::tcolor("Invalid Command", Color::RED, Color::REGULAR) << std::endl;
					setAnimationStage(8);

				}
			}else{
					std::cout << Color::tcolor("Same Command", Color::RED, Color::REGULAR) << std::endl;
					setAnimationStage(8);
			}
		}else{//Check se os comandos sao invalidos(cmds inexistentes ou errados)

			std::cout << Color::tcolor("Invalid Command", Color::RED, Color::REGULAR) << std::endl;
			setAnimationStage(8);
		}
	}
}

void AnimationManage::sort(std::vector<BarChart> &chart){

	long long int i{0}, j{0};
	auto aux{bChart[getCurrentBarChart()][0]};

	while(i < (long long) ((bChart[getCurrentBarChart()].size()-1))){
		while(j < (long long) ((bChart[getCurrentBarChart()].size()-1)-i)){
			if(std::stoll(bChart[getCurrentBarChart()][j].getValue()) < std::stoll(bChart[getCurrentBarChart()][j+1].getValue())){
				aux = bChart[getCurrentBarChart()][j];
				bChart[getCurrentBarChart()][j] = bChart[getCurrentBarChart()][j+1];
				bChart[getCurrentBarChart()][j+1] = aux;
			}
			j++;
		}
		j = 0;
		i++;
	}

}

void AnimationManage::welcome_msg(void){
	std::cout << "=================================================" << std::endl;
	std::cout << "  Welcome to the Bar Chart Race, v1.0" << std::endl;
	std::cout << "  Copyright (C) 2020, Edson Cassiano" << std::endl;
	std::cout << "=================================================" << std::endl;

}

void AnimationManage::read_file(void){

	std::string temp;

	file.open(getFileName());
		
		if(file.is_open()){

			getline(file, temp);
			setTitle(temp);

			getline(file, temp);
			setSubtitle(temp);

			getline(file, temp);
			setSource(temp);

			getline(file, temp);
			int i=0,j=0, k=0;
			bool found=false;

			while(getline(file, temp)){

				setNumberOfItems(std::stoi(temp));

				bChart.push_back(std::vector<BarChart>());

				while(i < getNumberOfItems()){

					bChart[j].push_back(BarChart());

					getline(file, temp, ',');
					bChart[j][i].setCount(temp);
					if(timeStamp.size() == 0){
						timeStamp.push_back(temp);
					}
					found = false;
					k = 0;
					while(k < int(timeStamp.size())){
						if(timeStamp[k] == temp){
							found = true;
						}
						k++;
					}
					if(found == false){
						timeStamp.push_back(temp);
					}

					getline(file, temp, ',');
					bChart[j][i].setNameBar(temp);

					getline(file, temp, ',');

					getline(file, temp, ',');
					bChart[j][i].setValue(temp);

					getline(file, temp);
					bChart[j][i].setCategory(temp);

					if(categorySubtitle.size() == 0){
						categorySubtitle.push_back(temp);
					}
					found = false;
					k = 0;
					while(k < int(categorySubtitle.size())){
						if(categorySubtitle[k] == temp){
							found = true;
						}
						k++;
					}
					if(found == false){
						categorySubtitle.push_back(temp);
					}

					i++;
				}

				getline(file, temp);
				i=0;
				j++;
			}

		}else{//O arquivo não foi encontrado, não pode ser aberto
			std::cout << Color::tcolor("Dont Opened!", Color::RED, Color::REGULAR) << std::endl;
			setAnimationStage(8);
		}

		file.close();

}

void AnimationManage::process(void){

	std::string temp;

	if(getAnimationStage() == AnimationStage::START){

	}else if(getAnimationStage() == AnimationStage::WELCOME_MSG){

	}else if(getAnimationStage() == AnimationStage::PROCESS_INPUT){

		read_file();

	}else if(getAnimationStage() == AnimationStage::STAY_INPUT){

		getline(std::cin, temp);

	}else if(getAnimationStage() == AnimationStage::RUN){
		if(getCurrentBarChart() == int(bChart.size()-1)){
			setAnimationStage(8);
		}
		std::chrono::milliseconds dura(1000/getFrameRate());
		std::this_thread::sleep_for(dura);
		addCurrentBarChart();
	}

}

void AnimationManage::update(void){

	if(getAnimationStage() == AnimationStage::START){

		setAnimationStage(1);

	}else if(getAnimationStage() == AnimationStage::WELCOME_MSG){

		setAnimationStage(2);

	}else if(getAnimationStage() == AnimationStage::PROCESS_INPUT){

		setAnimationStage(3);

	}else if(getAnimationStage() == AnimationStage::INPUT_READ){

		setAnimationStage(4);

	}else if(getAnimationStage() == AnimationStage::FILE_INFO){

		setAnimationStage(5);

	}else if(getAnimationStage() == AnimationStage::SETUP_INFO){

		setAnimationStage(6);

	}else if(getAnimationStage() == AnimationStage::STAY_INPUT){

		setAnimationStage(7);
		sort(bChart[getCurrentBarChart()]);

	}else if(getAnimationStage() == AnimationStage::RUN){

		sort(bChart[getCurrentBarChart()]);

	}else if(getAnimationStage() == AnimationStage::EXIT){

		exit();
	}

}

void AnimationManage::render(void){

	const std::string interface_msg[] {
		">>> Processing data, please wait.",
		">>> Input file sucessfuly read.",
		};

	if(getAnimationStage() == AnimationStage::START){

	}else if( getAnimationStage() == AnimationStage::WELCOME_MSG){

		welcome_msg();
		std::cout << std::endl;

	}else if(getAnimationStage() == AnimationStage::PROCESS_INPUT){

		std::cout << Color::tcolor(">>> Preparing to read input file \"", Color::GREEN, Color::REGULAR) << Color::tcolor(getFileName(), Color::GREEN, Color::REGULAR) << Color::tcolor("\"...", Color::GREEN, Color::REGULAR);
		std::cout << std::endl << std::endl;
		std::cout << Color::tcolor(interface_msg[0], Color::GREEN, Color::REGULAR) << std::endl;

	}else if(getAnimationStage() == AnimationStage::INPUT_READ){

		std::cout << Color::tcolor(interface_msg[1], Color::GREEN, Color::REGULAR) << std::endl;

	}else if(getAnimationStage() == AnimationStage::FILE_INFO){

		std::cout << std::endl;
		std::cout << Color::tcolor(">>> We have \"", Color::GREEN, Color::REGULAR) << Color::tcolor(std::to_string(bChart.size()), Color::GREEN, Color::REGULAR) << Color::tcolor("\" bar charts.", Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor(">>> Title: ", Color::GREEN, Color::REGULAR) << Color::tcolor(getTitle(), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor(">>> Value is: ", Color::GREEN, Color::REGULAR) << Color::tcolor(getSubtitle(), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor(">>> Source: ", Color::GREEN, Color::REGULAR) << Color::tcolor(getSource(), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor(">>> # of categories found: ", Color::GREEN, Color::REGULAR) << Color::tcolor(std::to_string(categorySubtitle.size()), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << std::endl;

	}else if(getAnimationStage() == AnimationStage::SETUP_INFO){

		std::cout << Color::tcolor(">>> Animation speed is: ", Color::GREEN, Color::REGULAR) << Color::tcolor(std::to_string(getFrameRate()), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor(">>> Requested # of bars to display: ", Color::GREEN, Color::REGULAR) << Color::tcolor(std::to_string(getNumberOfBar()), Color::GREEN, Color::REGULAR) << std::endl;
		std::cout << Color::tcolor("Press enter to begin the animation.", Color::GREEN, Color::REGULAR);

	}else if(getAnimationStage() == AnimationStage::STAY_INPUT){

	}else if(getAnimationStage() == AnimationStage::RUN){

		long long int aux{0};
		long long int b{0};
		for(int a{0}; a < 50; a++){
			std::cout << std::endl;
		}
		std::cout <<"			" << Color::tcolor(getTitle(), Color::BLUE, Color::REGULAR) << std::endl;
		std::cout << std::endl;
		std::cout << Color::tcolor("					Time Stamp: ", Color::BLUE, Color::REGULAR) << Color::tcolor(timeStamp[getCurrentBarChart()], Color::BLUE, Color::REGULAR) << std::endl;
		std::cout << std::endl;
		while(aux < (long long) (bChart[getCurrentBarChart()].size())){
			if(aux < getNumberOfBar()){
				if(aux == 0){
					for(long long int a{0};a < 55; a++){
						if(categorySubtitle.size() <= 14){//Bloco para mudar a cor do primeiro colocado, O primeiro colocado foi separado pois como seu tamanho é fixo, foi mais facil tratar-lo assim
							if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[0]){
								std::cout << Color::tcolor(u8"\u2588", Color::RED, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[1]){
								std::cout << Color::tcolor(u8"\u2588", Color::GREEN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[2]){
								std::cout << Color::tcolor(u8"\u2588", Color::YELLOW, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[3]){
								std::cout << Color::tcolor(u8"\u2588", Color::BLUE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[4]){
								std::cout << Color::tcolor(u8"\u2588", Color::MAGENTA, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[5]){
								std::cout << Color::tcolor(u8"\u2588", Color::CYAN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[6]){
								std::cout << Color::tcolor(u8"\u2588", Color::WHITE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[7]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_RED, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[8]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_GREEN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[9]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_YELLOW, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[10]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_BLUE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[11]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_MAGENTA, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[12]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_CYAN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[13]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_WHITE, Color::REGULAR);
							}
						}else{//Caso tenham mais categorias do que cores o primeiro colocado será da cor verde
							std::cout << Color::tcolor(u8"\u2588", Color::GREEN, Color::REGULAR) ;
						}
					}
					std::cout << " ";
				}else{// Todos os outras barras tem sua cor alterada aqui, seguindo o mesmo conceito do primeiro colocado, a unica diferença é que seu tamanho é alterado constantimente
					// Para calcular o tamanho das outras barras é usado regra de três, sabendo que o tamanho do primeiro colocado são 55 caracteres
					for(long long int a{0}; a < ((std::stoll(bChart[getCurrentBarChart()][aux].getValue()))*55)/(std::stoll(bChart[getCurrentBarChart()][0].getValue())+1); a++){
						if(categorySubtitle.size() <= 14){
							if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[0]){
								std::cout << Color::tcolor(u8"\u2588", Color::RED, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[1]){
								std::cout << Color::tcolor(u8"\u2588", Color::GREEN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[2]){
								std::cout << Color::tcolor(u8"\u2588", Color::YELLOW, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[3]){
								std::cout << Color::tcolor(u8"\u2588", Color::BLUE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[4]){
								std::cout << Color::tcolor(u8"\u2588", Color::MAGENTA, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[5]){
								std::cout << Color::tcolor(u8"\u2588", Color::CYAN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[6]){
								std::cout << Color::tcolor(u8"\u2588", Color::WHITE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[7]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_RED, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[8]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_GREEN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[9]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_YELLOW, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[10]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_BLUE, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[11]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_MAGENTA, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[12]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_CYAN, Color::REGULAR);
							}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[13]){
								std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_WHITE, Color::REGULAR);
							}
						}else{// Caso a quantidade de categorias seja maior que a quantidade maxima de cores, todas barras seram verdes
							std::cout << Color::tcolor(u8"\u2588", Color::GREEN, Color::REGULAR);
						}
							b = a;
					}
				}
				std::cout << " ";
				if(categorySubtitle.size() <= 14){// Altera a cor do nome da barra que está acompanhado do seu valor
					if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[0]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::RED, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[1]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::GREEN, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[2]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::YELLOW, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[3]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BLUE, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[4]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::MAGENTA, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[5]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::CYAN, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[6]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::WHITE, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[7]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_RED, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[8]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_GREEN, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[9]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_YELLOW, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[10]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_BLUE, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[11]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_MAGENTA, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[12]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_CYAN, Color::REGULAR) << " ";
					}else if(bChart[getCurrentBarChart()][aux].getCategory() == categorySubtitle[13]){
						std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::BRIGHT_WHITE, Color::REGULAR) << " ";
					}
				}else{
					std::cout << Color::tcolor(bChart[getCurrentBarChart()][aux].getNameBar(), Color::GREEN, Color::REGULAR) << " ";
				}
				std::cout << "[" << bChart[getCurrentBarChart()][aux].getValue() << "]";
				std::cout << std::endl;
				std::cout << std::endl;
			}
			aux++;
		}
		// EIXO X - Para o eixo x foi implementado apenas o primeiro, o ultimo e um marcador no meio, seus valores não foram arredondados
		std::cout << "+";
		for(long long int a{0};a < 80; a++){

			if(a == 20+b && 20+b < 55){

				std::cout << "+";

			}if(a == b || a == 55){

				std::cout << "+";
				
			}else{

				std::cout << "-";
			}
		}
		std::cout << ">";
		std::cout << std::endl;
		for(long long int a{0};a < 80; a++){
			if(a == 55){
				std::cout << Color::tcolor(bChart[getCurrentBarChart()][0].getValue(), Color::YELLOW, Color::REGULAR);
			}else if(a == b){
				std::cout << Color::tcolor(bChart[getCurrentBarChart()][11].getValue(), Color::YELLOW, Color::REGULAR);
			}else if(a == 20+b && b+20 < 55){
				std::cout << Color::tcolor(bChart[getCurrentBarChart()][5].getValue(), Color::YELLOW, Color::REGULAR);
			}else{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
		std::cout << Color::tcolor(getSubtitle(), Color::YELLOW, Color::REGULAR) << std::endl;
		std::cout << std::endl;
		std::cout << getSource() << std::endl;
		aux = 0;
		if(int(categorySubtitle.size()) < 15){// Muda a cor da categoria, caso a quantidade de categorias seja menor que a quantidade e cores, é mostrado a cor correspondente e sua categoria
			while(aux < int(categorySubtitle.size())){
				if(aux == 0){
					std::cout << Color::tcolor(u8"\u2588", Color::RED, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::RED, Color::REGULAR) << " ";
				}else if(aux == 1){
					std::cout << Color::tcolor(u8"\u2588", Color::GREEN, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::GREEN, Color::REGULAR) << " ";
				}else if(aux == 2){
					std::cout << Color::tcolor(u8"\u2588", Color::YELLOW, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::YELLOW, Color::REGULAR) << " ";
				}else if(aux == 3){
					std::cout << Color::tcolor(u8"\u2588", Color::BLUE, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BLUE, Color::REGULAR) << " ";
				}else if(aux == 4){
					std::cout << Color::tcolor(u8"\u2588", Color::MAGENTA, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::MAGENTA, Color::REGULAR) << " ";
				}else if(aux == 5){
					std::cout << Color::tcolor(u8"\u2588", Color::CYAN, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::CYAN, Color::REGULAR) << " ";
				}else if(aux == 6){
					std::cout << Color::tcolor(u8"\u2588", Color::WHITE, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::MAGENTA, Color::REGULAR) << " ";
				}else if(aux == 7){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_RED, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_RED, Color::REGULAR) << " ";
				}else if(aux == 8){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_GREEN, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_GREEN, Color::REGULAR) << " ";
				}else if(aux == 9){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_YELLOW, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_YELLOW, Color::REGULAR) << " ";
				}else if(aux == 10){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_BLUE, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_BLUE, Color::REGULAR) << " ";
				}else if(aux == 11){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_MAGENTA, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_MAGENTA, Color::REGULAR) << " ";
				}else if(aux == 12){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_CYAN, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_CYAN, Color::REGULAR) << " ";
				}else if(aux == 13){
					std::cout << Color::tcolor(u8"\u2588", Color::BRIGHT_WHITE, Color::REGULAR);
					std::cout << ":" << Color::tcolor(categorySubtitle[aux], Color::BRIGHT_WHITE, Color::REGULAR) << " ";
				}

				aux++;
			}
		}
		std::cout << std::endl;
	}else if(getAnimationStage() == AnimationStage::EXIT){
		std::string temp;
		std::cout << "Hope you have enjoyed the Chart Race!" << std::endl;
		getline(std::cin, temp);
	}
}
