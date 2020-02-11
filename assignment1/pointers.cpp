// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

#define MAX 0x7FFFFFFF

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;
    // Sequence of user input -> store in fields of `student`
	std::string charactersFilename(argv[1]);
	std::string charactersFilename2(argv[2]);

  	std::string line;
  	std::ifstream myfile ( charactersFilename );
  	if (!myfile.is_open()){ std::cout << "Unable to open file"; }

	std::ofstream ofs;
	ofs.open( charactersFilename2 , std::ofstream::out | std::ofstream::trunc);

	char c = '1';
	double *d_num;
	double zero = 0.0;
	student.grades = &zero;
	char ch;
	int i;

	char id[10], f_name[20], l_name[20], num[10];
	char cset[] = "1234567890";
	while( getline (myfile,line) )
	{

		switch(c)
		{
			case '1' :
				if (ofs.is_open()){ ofs << "Please enter the student's id number: "; }
			
				strcpy(id, line.c_str());
			
				if( std::strlen(id) < 10 && atof(id)>0.0 ){ student.id = atoi(id); c = '2'; }
				else{ ofs << "Sorry, I cannot understand your answer" << std::endl; }
			break;
			case '2' :
				if (ofs.is_open()){ ofs << "Please enter the student's first name: "; }

				strcpy(f_name, line.c_str());

				if( std::count(line.begin(), line.end(), ' ') > 0){
					ofs << "Sorry, I cannot understand your answer" << std::endl;
					c = '2';
				}else{
					student.f_name = f_name;
					c = '3';
				}
			break;
			case '3' :
				if (ofs.is_open()){ ofs << "Please enter the student's last name: "; }

				strcpy(l_name, line.c_str());

				//line = &student.f_name[0] + line;

				/*for(i=0; i<line.length(); i++){
					if( line[i]&0x80 ){
						ofs << "Sorry, I cannot understand your answer" << std::endl;
						c = '2';
					}
				}*/
				if( (std::count(line.begin(), line.end(), ' ') > 0 || line.length() > 127) ){
					ofs << "Sorry, I cannot understand your answer" << std::endl;
					c = '2';
				}else{
					student.l_name = l_name;
					c = '4';
				}
			break;
			case '4' :
				if (ofs.is_open()){ ofs << "Please enter how many assignments were graded: "; }
			 	strcpy(num, line.c_str());
				
				if( !(line.size() == strspn(num, cset)) ){
					ofs << "Sorry, I cannot understand your answer" << std::endl;
					c = '4';
				}else{
					student.n_assignments = atoi(&line[0]);

					if( student.n_assignments < MAX && student.n_assignments < 1 ){
						ofs << "Sorry, I cannot understand your answer" << std::endl;
						c = '4';
					}else{
						ofs << "\n";
						c = '5';
						i = 0 ;
					}
				}
			break;
			case '5' :
				if (ofs.is_open()){ ofs << "Please enter grade for assignment " << i <<": "; }
				char grade[10];
				strcpy(grade, line.c_str());
				
				std::string fs = &grade[0];
				std::string tstr = fs.substr( fs.find(".")+1 );
				
				if( atof(grade) >=1000.0 || atof(grade) < 0.0 || tstr.length()>6 ){
					ofs << "Sorry, I cannot understand your answer" << std::endl;
					c = '5';
				}else{
					
					double temp = atof(&line[0]);
					d_num = &temp;
					*student.grades = *student.grades + *d_num;
					++i;
				}
		}
	}
    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`
	double avg;
	calculateStudentAverage(&student, &avg);

	if (ofs.is_open()){ 
		ofs << "\nStudent: "<<student.f_name<<" "<<student.l_name<<" ["<<student.id<<"]\n";
		ofs << "  Average grade: "<< avg <<"\n";
	}
	ofs.close();
	myfile.close();
    return 0;
}

void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
	*avg = *((Student*)object)->grades / ((Student*)object)->n_assignments;
	*avg = ((float)((int)(*avg * 10 + .5))) / 10;
}
