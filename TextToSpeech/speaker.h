#pragma once
#pragma warning (disable:4996)

#include <iostream>
#include <sapi.h>
#include <atlbase.h>
#include <atlcom.h>
#include <sphelper.h>
extern CComModule _Module;


// interface speaker
class Speaker {
protected:
	ISpVoice *pVoice = nullptr;
	CComPtr<ISpObjectToken> voiceGender;
public:
	Speaker();
	virtual ~Speaker();
	virtual void speak(const std::string &text) = 0;
	virtual void speakFromFile(const std::string& path) = 0;
};

class MaleSpeaker : public Speaker {
public:
	MaleSpeaker();
	~MaleSpeaker();
	virtual void speak(const std::string &text) override;
	virtual void speakFromFile(const std::string &path) override;
};

class FemaleSpeaker : public Speaker {
public:
	FemaleSpeaker();
	~FemaleSpeaker();
	virtual void speak(const std::string &text) override;
	virtual void speakFromFile(const std::string &path) override;
};

