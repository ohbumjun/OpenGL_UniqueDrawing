#pragma once
#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

class DisplayHandler
	// 하는 일 
	// >  윈도우 기본 setting
	// >  clear buffer
	// >  end the window properly
{
public:
	float r, g, b;
	static DisplayHandler* Instance();
public:
	bool Initialize();
	void Display();

private:
	// 하나의 instance만을 사용하는 singletonpattern을 적용하기 위해
	// 아래와 같이 설정한다 
	// 현재 만드는 Screen 이라는 단 하나의 instance 만을 사용할 것이다 
	DisplayHandler();
	DisplayHandler(const DisplayHandler&); // cannot make duplicates
	DisplayHandler& operator =(const DisplayHandler&);
};

#endif
