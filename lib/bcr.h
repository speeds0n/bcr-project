#ifndef BCR_H
#define BCR_H

class AnimationManage{

	private:
		int m_frameRate;
		int m_numberOfBar;
		std::string m_fileName;
		std::string m_title;
		std::string m_subtitle;
		std::string m_source;

	public:
		//Constructor
		AnimationManage(int frameRate=24, int numberOfBar=5);
		
		void setAnimationManage(int frameRate, int numberOfBar);
		void setFrameRate(int frameRate);
		void setNumberOfBar(int numberOfBar);
		void setFileName(std::string fileName);
		void setTitle(std::string title);
		void setSubtitle(std::string subtitle);
		void setSource(std::string source);

		int getFrameRate(){ return m_frameRate; }
		int getNumberOfBar(){ return m_numberOfBar; }
		std::string getFileName(){ return m_fileName; }
		std::string getTitle(){ return m_title; }
		std::string getSubtitle(){ return m_subtitle; }
		std::string getSource(){ return m_source; }

		//Nessa função eu preciso abrir o arquivo apartir da linha de commando, tratando os erros
		//erros: arquivo nao encontrado, parametros invalidos
		void initialize(int argc, char *argv[]);

		void process(void);
};

class BarChart{

	private:
		int m_count;
		int m_value;
		std::string m_name;
		std::string category;
};

#endif
