solution "RobotPenguin"
	configurations {"Debug"}

	project "RobotPenguin"
		kind "ConsoleApp"
		language "C++"
		files {"**.hpp", "**.cpp"}

		configuration "Debug"
		
			defines {"DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
			buildoptions {"-std=c++11 -O2"}
			links {"SDL2"}
