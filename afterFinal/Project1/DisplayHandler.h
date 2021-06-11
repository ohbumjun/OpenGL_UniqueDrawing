#pragma once
#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

class DisplayHandler
	// �ϴ� �� 
	// >  ������ �⺻ setting
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
	// �ϳ��� instance���� ����ϴ� singletonpattern�� �����ϱ� ����
	// �Ʒ��� ���� �����Ѵ� 
	// ���� ����� Screen �̶�� �� �ϳ��� instance ���� ����� ���̴� 
	DisplayHandler();
	DisplayHandler(const DisplayHandler&); // cannot make duplicates
	DisplayHandler& operator =(const DisplayHandler&);
};

#endif
