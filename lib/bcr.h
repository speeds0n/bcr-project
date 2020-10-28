#ifndef BCR_H
#define BCR_H

class AnimationManage{

	private:
		int m_frameRate;
		int m_numberOfBar;
		std::string m_fileName;

	public:
		AnimationManage(int frameRate=24, int numberOfBar=5);
		
		void setAnimationManage(int frameRate, int numberOfBar);
		void setFrame(int frameRate);
		void setNumberOfBar(int numberOfBar);
		void setFileName(std::string fileName);

		int getFrame(){ return m_frameRate; }
		int getnumberOfBar(){ return m_numberOfBar; }
		std::string getFileName(){ return m_fileName; }

		//Nessa função eu preciso abrir o arquivo apartir da linha de commando, tratando os erros
		//erros: arquivo nao encontrado, parametros invalidos
		void initialize(int argc, char *argv[]);
};

void teste();

#endif
