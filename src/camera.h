#ifndef _CAMERA_
#define _CAMERA_

#include "myvector.h"

class camera
{
public:
	myvector eyepoint;
	myvector lookpoint; //�̶�
	
	
	myvector vector_to; //�ӵ�ָ�����λ�õ�����
	
	double length; //���λ�þ���Ŀ���ľ��볤��
	
	double baseLength; //һ���������ƶ����ƶ�����  ����
	
	myvector vector_lr; //��ת��1  �̶�
	myvector vector_ud;// ��ת��2  
	
	double baseAngle;//һ����ת�ĽǶ����� ����
	
	myvector vectorUp;//��������ϵ�����
	
	camera();
	
	~camera();
	
	void calVectorTo();
	void calLength();
	void calVectorUp();
	void calVector_UD();
	void calEyePoint();
	
	void see();
	
	void rotate_LR(int lr);
	void rotate_UD(int ud);
	void move(int cf);
	
	void matrixMult(double matrix[16],myvector& vector_now);
};
#endif

