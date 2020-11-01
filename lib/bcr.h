/*!
 *
 * \file bcr.h
 * \author Edson Cassiano
 * \date November, 1st
 */

#ifndef BCR_H
#define BCR_H

#include <vector>

/*!
 * BarChart class that saves one chart date
 *
 */
class BarChart{

	private:
		std::string m_count; /*< Used in Stamp of bar chart */
		std::string m_value; /*< Used to order the bar charts */
		std::string m_name;	/*< Save name of bar */
		std::string m_category; /*< save the category of bar */

	public:

		/*!
		 * Default Constructor
		 */
		BarChart(std::string count="", std::string value="", std::string name="", std::string category="");

		/*!
		 * Function aux used in the Constructor
		 *
		 * This function is used only to access the private members when to start de class, via constructor
		 *
		 * \param count Stamp of bar Chart
		 * \param value Value used to order the bar Chart
		 * \param name Name of Bar
		 * \param category Category of Bar
		 *
		 */
		void setBarChart(std::string count, std::string value, std::string name, std::string category);

		void setCount(std::string count); /*< Change value of stamp */
		void setValue(std::string value); /*< Change value of Bar */
		void setNameBar(std::string name); /*< Change value of name Bar */
		void setCategory(std::string category);/*< Change value of Category */

		std::string getCount(){ return m_count; } /*< get value of title */
		std::string getValue(){ return m_value; } /*< get value of bar */
		std::string getNameBar(){ return m_name; } /*< get value of Name Bar */
		std::string getCategory(){ return m_category; } /*< get value of Category */

	};

/*!
 * AnimationManage is the class with management program
 *
 * All action treated here, process, update, render, sort bar chart
 * also management the flow of screens.
 * Frame Rate is between [1, 24], default value is 24, the user can be adjusted in command line, if user uses a number out of range, the program takes on default value.
 * Number of Bar in Screen, default is 12, between [1, 14] and the user can be adjusted in command line, is user uses a number out of range, the program takes on default value.
 *
 */
class AnimationManage{

	private:
		int m_frameRate;/*< Frame Rate */
		int m_numberOfBar;/*< Number of Bar in Screen */
		int m_numberOfChart;/*< Number of Chart Groups */
		int m_numberOfItems;/*< Number of Items in the Chart Groups */
		int m_currentBarChart;/*< Current Chart count being processed */
		int m_animationStage;/*< Animation Stage controls the screen and the stage of animation */
		std::string m_fileName;/*< File name */
		std::string m_title;/*< Title of Bar Chart */
		std::string m_subtitle;/*< Subtitle of Bar Chart */
		std::string m_source;/*< Information source */
		std::ifstream file;/*< File with dates */
		std::vector<std::string> timeStamp;/*< Vector with the Stamp to be printed */
		std::vector<std::string> categorySubtitle;/*< Vector with the category of subtitle to be printed and select color */
		std::vector<std::vector<BarChart>> bChart;/*< Vector with all dates about Bar Charts */

	public:
		/*!
		 *
		 * Default construct of Class
		 *
		 */
		AnimationManage(int frameRate=24, int numberOfBar=12);

		/*!
		 * Function aux used in the Constructor
		 *
		 * This function is used only to access the private members when to start de class, via constructor
		 *
		 * \param frameRate Frame Rate
		 * \param numberOfBar Number of Bar that will show on the screen
		 *
		 */
		void setAnimationManage(int frameRate, int numberOfBar);
		void setFrameRate(int frameRate); /*< Change Frame Rate */
		void setNumberOfBar(int numberOfBar); /*< Change Number Of Bar that will show on the screen*/
		void setNumberOfChart(int numberOfChart);/*< Change Number of Charts */
		void setNumberOfItems(int numberOfItems); /*< Change number of Items */
		void setCurrentBarChart(int currentBarChart); /*< Change the Current Bar Chart count */
		void setAnimationStage(int animationStage);/*< Change Stage of Animation */
		void setFileName(std::string fileName);/*< Change name of file */
		void setTitle(std::string title);/*< Change title of Bar */
		void setSubtitle(std::string subtitle);/*< Change subtitle of Bar */
		void setSource(std::string source);/*< Change information source */

		int getFrameRate(){ return m_frameRate; } /*< Get frame rate */
		int getNumberOfBar(){ return m_numberOfBar; } /*< Get number of Bar */
		int getNumberOfChart(){ return m_numberOfChart; } /*< Get number of Chart */
		int getNumberOfItems(){ return m_numberOfItems; } /*< Get number of items */
		int getCurrentBarChart(){ return m_currentBarChart; } /*< get the current Bar Chart */
		int getAnimationStage(){ return m_animationStage; } /*< get current stage of animation */
		std::string getFileName(){ return m_fileName; } /*< get file name */
		std::string getTitle(){ return m_title; } /*< get title of Chart */
		std::string getSubtitle(){ return m_subtitle; } /*< get subtitle Chart */
		std::string getSource(){ return m_source; } /*< get information source Chart */

		int addCurrentBarChart(){ return ++m_currentBarChart; } /*< next Bar Chart */

		/*!
		 * Enum controll Animation Stage
		 */
		enum AnimationStage{
			START = 0,			/*< 0 First process Screen */
			WELCOME_MSG,		/*< 1 Show Welcome message */
			PROCESS_INPUT,		/*< 2 Process file input */
			INPUT_READ,			/*< 3 Show the message about process file */
			FILE_INFO,			/*< 4 Show files infos */
			SETUP_INFO,			/*< 5 Show the setup info(frame rate and number of bar) */
			STAY_INPUT,			/*< 6 Stay <enter> to continue */
			RUN,				/*< 7 Read input file and print */
			EXIT				/*< 8 How much the file was read */
		};

		/*!
		 *
		 * Handles the input provided by user and show error message
		 *
		 * \param argc count of command in commad line
		 * \param argv list of command save in the char list
		 *
		 */
		void initialize(int argc, char *argv[]);

		void welcome_msg(void); /*< Show Welcome message */

		void read_file(void); /*< Read file provided by user */

		void sort(std::vector<BarChart> &chart); /*< sort the bar Chart using bubble sort */

		void process(void); /*< process file */

		void update(void); /*< update flow screens */

		void render(void);/*< print the current screen */

		bool exit(); /*< used to exit of program when all bar Chart is read */
};

#endif
