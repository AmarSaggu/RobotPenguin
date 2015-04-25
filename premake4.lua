solution "RobotPengin"
	configurations {"Debug"}

	project "RobotPengin"
		kind "ConsoleApp"
		language "C++"
		files {"**.hpp", "**.cpp"}

		configuration "Debug"
		
			defines {"DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
			buildoptions {"-std=c++11"}
			links {"SDL2"}
