#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//.obj 파일 해석하기 (.txt )

//o. ~ : object 의 이름
//v  ~ : vertex의 x,y,z 좌표
//vt ~ : texture vector
//vn ~ : normal vector(법선 벡터)
//f ~  : 각 면
//	이어져있는점/texture/normal vector

using namespace std;

// 2개의 점을 가지는 class ( ex. x,y )
class CPoint2f {
public:
	vector <float> d{ 0,0 };
};

// 3개의 점을 가지는 class
class CPoint3f {
public:
	vector <float> d{ 0,0,0 };
};

// 정수형 
class CPoint3i {
public:
	vector <int> d{ 0,0,0 };
};

// 3개,혹은 4개의 점이 하나의 면을 구성
class CFace {
	// f ~: 각 면
	//	이어져있는점 / texture / normal vector
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

// Model : 여러개의 obj
class CModel {
public:
	vector <CObj> objs;

	// 하나의 str 로부터, 여러개의 delimeter(기준점)
	// 을 가지고,
	// 그, 문자에 따라서, 문자열 나눠주기 
	// ex) vn -1.000 1.000 1.000 --> 공백 단위 분리하기 
	vector<float> my_strtok_f(char* str, char* delimeter) {
		vector <float> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : 문자열을 숫자로 
			v.push_back(atof(tok));
			tok = strtok_s(NULL, delimeter, &context);
		}
		// 하나하나 쪼개서 벡터에다 넣어서 벡터 리턴 
		return v;
	}

	// string 형
	vector<string> my_strtok_s(char* str, char* delimeter) {
		vector <string> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : 문자열을 숫자로 
			v.push_back(tok);
			tok = strtok_s(context, delimeter, &context);
		}
		// 하나하나 쪼개서 벡터에다 넣어서 벡터 리턴 
		return v;
	}


	// int 형
	vector<int> my_strtok_i(char* str, char* delimeter) {
		vector <int> v;
		char* context;
		char* tok = strtok_s(str, delimeter, &context);
		while (tok != NULL) {
			// atof : 문자열을 숫자로 
			v.push_back(atof(tok));
			tok = strtok_s(context, delimeter, &context);
		}
		// 하나하나 쪼개서 벡터에다 넣어서 벡터 리턴 
		return v;
	}

	void loadObj(ifstream& fin) {
		string line;
		CObj obj_tmp;
		int cnt = 0; // 몇개의 obj를 불러왔는가 

		// 이전 obj 까지의 누적 벡터수
		// 예를 들어, 2번째 obj 면들의 각각의 idx를 구할때 
		// 사실은 1번째 vertex임에도 불구하고
		// 65번째라고 txt 파일에 저장된다
		// 왜냐하면, 이전 obj의 vertex 개수들이
		// 누적되어가기 때문이다 
		int cnt_prev_vertex = 0;
		int cnt_prev_texture = 0;
		int cnt_prev_normal = 0;

		// 한줄한줄 읽는다 
		while (getline(fin, line)) {
			int len = line.length();
			vector<float> vf;
			vector<string> s;
			vector<int> vi;
			CPoint3f p3;
			CPoint2f p2;
			CPoint3i p3i;
			// v인지, vt인지, vn인지, f 인지 알아내야 한다
			if (line[0] == 'o' && line[1] == ' ') {
				// 새로운 obj 정보가 들어온 것 
				// ex. o 큐브_큐브.003 (앞 o와 공백 제거)
				obj_tmp.name = line.substr(2, len - 2); // len-2 : 총 가져오는 길이 --> 앞2개가 빠지므로 len - 2
				objs.push_back(obj_tmp);
				// 새로운 obj가 나올때마다 update 
				// 이전 obj까지 점개수가 몇개 나왔는지
				// texture 개수가 몇개 나왔는지
				// normal vector 개수가 몇개 나왔는지 
				// 에 대한 정보를 저장해간다 
				if (cnt > 0) {
					cnt_prev_vertex += objs[cnt - 1].v.size();
					cnt_prev_texture += objs[cnt - 1].vt.size();
					cnt_prev_normal += objs[cnt - 1].vn.size();
				}
				cnt += 1;
			}
			if (line[0] == 'v' && line[1] == ' ') { // v 일때 
				// ex) v -1.05 -0.98 1.005
				//(char*) 해주는 이유는 my_strtok_f 가 포인터형을 받기 때문에 
				// c_str : string을 const char 형으로 변환 
				vf = my_strtok_f((char*)line.substr(2, len - 2).c_str(), (char*)" ");
				p3.d = { vf[0], vf[1], vf[2] };
				// 현재 obj의 vertex 정보에 넣는다 
				objs[cnt - 1].v.push_back(p3);
			}
			else if (line[0] == 'v' && line[1] == 't') { // vt 일때 
				vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
				p2.d = { vf[0], vf[1] };
				objs[cnt - 1].vt.push_back(p2);
			}
			else if (line[0] == 'v' && line[1] == 'n') { // vn 일때 
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