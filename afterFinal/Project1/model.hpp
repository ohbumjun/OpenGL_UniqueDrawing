#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//.obj ���� �ؼ��ϱ� (.txt )

//o. ~ : object �� �̸�
//v  ~ : vertex�� x,y,z ��ǥ
//vt ~ : texture vector
//vn ~ : normal vector(���� ����)
//f ~  : �� ��
//	�̾����ִ���/texture/normal vector

using namespace std;

// 2���� ���� ������ class ( ex. x,y )
class CPoint2f {
public:
	vector <float> d{ 0,0 };
};

// 3���� ���� ������ class
class CPoint3f {
public:
	vector <float> d{ 0,0,0 };
};

// ������ 
class CPoint3i {
public:
	vector <int> d{ 0,0,0 };
};

// 3��,Ȥ�� 4���� ���� �ϳ��� ���� ����
class CFace {
	// f ~: �� ��
	//	�̾����ִ��� / texture / normal vector
public:
	vector <CPoint3i> v_pairs;
};

// Obj
class CObj {
public:
	string name;
	vector <CPoint3f> v;
	vector <CPoint2f> vt;
	vector <CPoint3f> vn;
	vector <CFace> f;
};

// Model : �������� obj
class CModel {
public:
	vector <CObj> objs;

	// �ϳ��� str �κ���, �������� delimeter(������)
	// �� ������,
	// ��, ���ڿ� ����, ���ڿ� �����ֱ� 
	// ex) vn -1.000 1.000 1.000 --> ���� ���� �и��ϱ� 
	vector<float> my_strtok_f(char* str, char* delimeter) {
		vector <float> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : ���ڿ��� ���ڷ� 
			v.push_back(atof(tok));
			tok = strtok_s(NULL, delimeter, &context);
		}
		// �ϳ��ϳ� �ɰ��� ���Ϳ��� �־ ���� ���� 
		return v;
	}

	// string ��
	vector<string> my_strtok_s(char* str, char* delimeter) {
		vector <string> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : ���ڿ��� ���ڷ� 
			v.push_back(tok);
			tok = strtok_s(context, delimeter, &context);
		}
		// �ϳ��ϳ� �ɰ��� ���Ϳ��� �־ ���� ���� 
		return v;
	}


	// int ��
	vector<int> my_strtok_i(char* str, char* delimeter) {
		vector <int> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : ���ڿ��� ���ڷ� 
			v.push_back(atof(tok));
			tok = strtok_s(context, delimeter, &context);
		}
		// �ϳ��ϳ� �ɰ��� ���Ϳ��� �־ ���� ���� 
		return v;
	}

	void loadObj(ifstream& fin) {
		string line;
		CObj obj_tmp;
		int cnt = 0; // ��� obj�� �ҷ��Դ°� 

		// ���� obj ������ ���� ���ͼ�
		// ���� ���, 2��° obj ����� ������ idx�� ���Ҷ� 
		// ����� 1��° vertex�ӿ��� �ұ��ϰ�
		// 65��°��� txt ���Ͽ� ����ȴ�
		// �ֳ��ϸ�, ���� obj�� vertex ��������
		// �����Ǿ�� �����̴� 
		int cnt_prev_vertex = 0;
		int cnt_prev_texture = 0;
		int cnt_prev_normal = 0;

		// �������� �д´� 
		while (getline(fin, line)) {
			int len = line.length();
			vector<float> vf;
			vector<string> s;
			vector<int> vi;
			CPoint3f p3;
			CPoint2f p2;
			CPoint3i p3i;
			// v����, vt����, vn����, f ���� �˾Ƴ��� �Ѵ�
			if (line[0] == 'o' && line[1] == ' ') {
				// ���ο� obj ������ ���� �� 
				// ex. o ť��_ť��.003 (�� o�� ���� ����)
				obj_tmp.name = line.substr(2, len - 2); // len-2 : �� �������� ���� --> ��2���� �����Ƿ� len - 2
				objs.push_back(obj_tmp);
				// ���ο� obj�� ���ö����� update 
				// ���� obj���� �������� � ���Դ���
				// texture ������ � ���Դ���
				// normal vector ������ � ���Դ��� 
				// �� ���� ������ �����ذ��� 
				if (cnt > 0) {
					cnt_prev_vertex += objs[cnt - 1].v.size();
					cnt_prev_texture += objs[cnt - 1].vt.size();
					cnt_prev_normal += objs[cnt - 1].vn.size();
				}
				cnt += 1;
			}
			if (line[0] == 'v' && line[1] == ' ') { // v �϶� 
				// ex) v -1.05 -0.98 1.005
				//(char*) ���ִ� ������ my_strtok_f �� ���������� �ޱ� ������ 
				// c_str : string�� const char ������ ��ȯ 
				vf = my_strtok_f((char*)line.substr(2, len - 2).c_str(), (char*)" ");
				p3.d = { vf[0], vf[1], vf[2] };
				// ���� obj�� vertex ������ �ִ´� 
				objs[cnt - 1].v.push_back(p3);
			}
			else if (line[0] == 'v' && line[1] == 't') { // vt �϶� 
				vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
				p2.d = { vf[0], vf[1] };
				objs[cnt - 1].vt.push_back(p2);
			}
			else if (line[0] == 'v' && line[1] == 'n') { // vn �϶� 
				vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
				p3.d = { vf[0], vf[1],vf[2] };
				objs[cnt - 1].vn.push_back(p3);
			}
			// f : ex) 1/1/1 ...
			else if (line[0] == 'f' && line[1] == ' ') {
				s = my_strtok_s((char*)line.substr(2, len - 2).c_str(), (char*)" ");
				// s : ex) 1/1/1
				int nVertexes = s.size();
				CFace face_tmp;
				for (int i = 0; i < nVertexes; i++) {
					vi = my_strtok_i((char*)s[i].c_str(), (char*)"/");
					p3i.d = {
						vi[0] - cnt_prev_vertex ,
						vi[1] - cnt_prev_texture ,
						vi[2] - cnt_prev_normal
					};
					face_tmp.v_pairs.push_back(p3i);
				}
				objs[cnt - 1].f.push_back(face_tmp);
			}
		}
	}
};