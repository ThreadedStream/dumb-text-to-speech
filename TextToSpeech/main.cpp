#include <iostream>
#include <sstream>
#include <string.h>

#include "speaker.h"

int main()
{
	// helper lambdas 
	const auto speakFromFileOptCallback = [](Speaker* speaker) -> void {
		std::string path;
		std::cout << "Ok, type in a file path, please\n";
		std::ws(std::cin);
		std::getline(std::cin, path);
		speaker->speakFromFile(path);
	};

	const auto speakFromTextOptCallback = [](Speaker* speaker) -> void {
		std::string text;
		std::cout << "Ok, type in a text, please\n";
		std::ws(std::cin);
		std::getline(std::cin, text);
		speaker->speak(text);
	};

	int choice = 0;
	std::cout << "Welcome to a very primitive text-to-speech program that I've composed in just about an hour\n";
	std::cout << "Choose a voice gender, please. 1 for male, and 2 for a female\n";
	std::cin >> choice;
	Speaker *speaker;
	switch (choice) {
	default:
		std::cerr << "Unknown voice gender type. Please try again\n";
		return 0;
	case 1:
		speaker = new MaleSpeaker();
		break;
	case 2:
		speaker = new FemaleSpeaker();
		break;
	}
	std::cout << "Ok, read from file? (1) or just type in a text? (2)\n";
	std::cin >> choice;
	switch (choice) {
		default:
			std::cerr << "Unknown voice gender type. Please try again\n";
			delete speaker;
			return 0;
		case 1:
			speakFromFileOptCallback(speaker);
			break;
		case 2:
			speakFromTextOptCallback(speaker);
			break;
	}

	delete speaker;
	return 0;
}



