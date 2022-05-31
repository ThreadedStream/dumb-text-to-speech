#include <string>
#include <vector>
#include <fstream>

#include "speaker.h"

Speaker::Speaker()
{
	if (FAILED(::CoInitialize(NULL)))
		throw std::exception("Speaker::Speaker(): unable to CoInitialize");
}

Speaker::~Speaker()
{
	::CoUninitialize();
	if (pVoice) {
		pVoice->Release();
	}
	pVoice = nullptr;
	return;
}

MaleSpeaker::MaleSpeaker(): Speaker::Speaker()
{
	auto hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL,
		IID_ISpVoice, (void**)&pVoice);
	if (!SUCCEEDED(hr)) {
		std::cerr << "MaleSpeaker::MaleSpeaker(): Unable to CoCreateInstance\n";
		return;
	}
	// Pick a male gender
	SpFindBestToken(SPCAT_VOICES, L"gender = male", L" ", &voiceGender);
	hr = pVoice->SetVoice(voiceGender);
	if (!SUCCEEDED(hr)) {
		std::cerr << "MaleSpeaker::MaleSpeaker(): Unable to pVoice->SetVoice\n";
		return;
	}
}

MaleSpeaker::~MaleSpeaker() 
{
}


void MaleSpeaker::speak(const std::string &text) 
{
	auto rawText = new wchar_t[text.length()];
	mbstowcs(rawText, text.c_str(), text.length());
	LPWSTR ptr = rawText;
	const auto hr = pVoice->Speak(rawText, SPF_IS_XML, NULL);
	if (!SUCCEEDED(hr)) {
		std::cerr << "MaleSpeaker::speak(): Unable to pVoice->Speak\n";
	}
	delete[] rawText;
	return;
}

void MaleSpeaker::speakFromFile(const std::string& path) 
{
	std::ifstream stream(path, std::ios::in);
	if (!stream) {
		std::cerr << "MaleSpeaker::speakFromFile(): Unable to open a file stream\n";
		return;
	}
	// determine the size of a file
	stream.seekg(std::ios::beg,std::ios::end);
	size_t size = stream.tellg();
	std::vector<char> buffer;
	buffer.resize(size);
	stream.seekg(std::ios::beg);
	stream.read(buffer.data(), size);
	speak(std::string(buffer.data()));
	stream.close();
	return;
}

FemaleSpeaker::FemaleSpeaker() : Speaker::Speaker()
{
	auto hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL,
		IID_ISpVoice, (void**)&pVoice);
	if (!SUCCEEDED(hr)) {
		std::cerr << "FemaleSpeaker::FemaleSpeaker(): Unable to CoCreateInstance\n";
		return;
	}
	// Pick a male gender
	SpFindBestToken(SPCAT_VOICES, L"gender = female", L" ", &voiceGender);
	hr = pVoice->SetVoice(voiceGender);
	if (!SUCCEEDED(hr)) {
		std::cerr << "FemaleSpeaker::FemaleSpeaker(): Unable to pVoice->SetVoice\n";
		return;
	}
}

FemaleSpeaker::~FemaleSpeaker()
{
}


void FemaleSpeaker::speak(const std::string &text)
{
	auto rawText = new wchar_t[text.length()];
	mbstowcs(rawText, text.c_str(), text.length());
	LPWSTR ptr = rawText;
	const auto hr = pVoice->Speak(rawText, SPF_IS_XML, NULL);
	if (!SUCCEEDED(hr)) {
		std::cerr << "FemaleSpeaker::speak(): Unable to pVoice->Speak\n";
	}
	delete[] rawText;
	return;
}

void FemaleSpeaker::speakFromFile(const std::string& path)
{
	std::ifstream stream(path, std::ios::in);
	if (!stream) {
		std::cerr << "FemaleSpeaker::speakFromFile(): Unable to open a file stream\n";
		return;
	}
	// determine the size of a file
	stream.seekg(std::ios::beg, std::ios::end);
	size_t size = stream.tellg();
	std::vector<char> buffer;
	buffer.resize(size);
	stream.seekg(std::ios::beg);
	stream.read(buffer.data(), size);
	speak(std::string(buffer.data()));
	stream.close();
	return;
}


