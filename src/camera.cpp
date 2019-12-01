#include "head.h"
#include "camera.h"

using namespace std;
void camera::calVectorTo()
{
	vector_to=eyepoint-lookpoint;
}
void camera::calVectorUp()
{
	vectorUp.x=vector_to.y*vector_ud.z-vector_ud.y*vector_to.z;
	vectorUp.y=vector_to.z*vector_ud.x-vector_to.x*vector_ud.z;
	vectorUp.z=vector_to.x*vector_ud.y-vector_ud.x*vector_to.y;
}
void camera::calLength()
{
	length=sqrt(vector_to.len_sq());
}

void camera::calVector_UD()
{
	calVectorTo();

	vector_ud.x=vectorUp.y*vector_to.z-vector_to.y*vectorUp.z;
	vector_ud.y=vector_to.x*vectorUp.z-vectorUp.x*vector_to.z;
	vector_ud.z=vectorUp.x*vector_to.y-vector_to.x*vectorUp.y;
}

void camera::calEyePoint()
{
	eyepoint=vector_to+lookpoint;
}

camera::camera()
{
	lookpoint=myvector(0,0,0);
	this->length=40;
	eyepoint=myvector(0,-40,0);

	this->baseAngle=5;
	this->baseLength=1;

	vector_lr=myvector(0,0,1);
	vector_ud=myvector(1,0,0);

	calVectorTo();
	calVectorUp();

}

camera::~camera()
{
	;
}

void camera::matrixMult(double matrix[16],myvector& vector_now)
{
	double vec[3];
	int i;
	for(i=0;i<3;i++)
	{
		vec[i]=vector_now.x*matrix[i]+vector_now.y*matrix[i+4]+vector_now.z*matrix[i+8]+matrix[i+12]; //����ԭ��μ�3Dͼ��ѧ ������
	//	printf("%lf %lf %lf %lf test\n",matrix[i],matrix[i+4],matrix[i+8],matrix[i+12]);
	}
	i=3;
	//printf("%lf %lf %lf %lf test\n",matrix[i],matrix[i+4],matrix[i+8],matrix[i+12]);

	vector_now.set(vec[0],vec[1],vec[2]);
	return ;
}

void  camera::see()
{
	glMatrixMode(GL_MODELVIEW);  //model and view �ȿ���ģ�ͱ任(�ƶ�ģ�ͣ�����ģ�ͣ���תģ�͵ȵ�) Ҳ������ͼ�任(�ƶ������) ������������ǿ��Ի���ת����
	glLoadIdentity();
	gluLookAt(eyepoint.x,eyepoint.y,eyepoint.z,lookpoint.x,lookpoint.y,lookpoint.z,vectorUp.x,vectorUp.y,vectorUp.z);
}

void camera::rotate_LR(int lr)
{
	double matrix_now[16];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotated(lr*baseAngle,vector_lr.x,vector_lr.y,vector_lr.z);
	glGetDoublev(GL_MODELVIEW_MATRIX,matrix_now);  //ע�⵱ǰ������һά��������ʱ�ǰ������ȴ洢��
	glPopMatrix();
	matrixMult(matrix_now,vector_to); //������������˷�����
	calEyePoint();
	calVector_UD(); //���¼�����ת��2

	see();
}

void camera::rotate_UD(int ud)
{
	double matrix_now[16]; 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotated(ud*baseAngle,vector_ud.x,vector_ud.y,vector_ud.z);
	glGetDoublev(GL_MODELVIEW_MATRIX,matrix_now);
	glPopMatrix();
	matrixMult(matrix_now,vector_to);
	calEyePoint();
	calVectorUp(); //���¼�����������ϵ����� 

	see();

}

void camera::move(int cf) 
//�Ŵ�ʱ����Ϊ�������ĵ���ӵ��������ƽ�Ʊ任��������Ŵ��ӵ�λ�����ĵ�ʱ�������Լ����Ŵ󣬴˴���Ϊд�������˹۲췶Χ
{
	double matrix_now[16];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(vector_to.x*cf*baseLength/length,vector_to.y*cf*baseLength/length,vector_to.z*cf*baseLength/length);
	glGetDoublev(GL_MODELVIEW_MATRIX,matrix_now);
	glPopMatrix();
	matrixMult(matrix_now,vector_to);
	calEyePoint();
	calVectorTo();
	calLength();
	
	see();
}
