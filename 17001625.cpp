#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include <sstream>  
#include <math.h>  
  

using namespace std;

	static const int size=1010;
	
		struct node{
			string index;
			int val;
		};

class subject{
	
	private:
		static int k;
		struct node *dataarray[size];
	public:
		subject(); //dynamocly allocate the array
		char grade(int i); // return the grade
		void grade();// Display The number of A,B,C,D,F,s..
		friend void subjectreport(subject &sub1);
		friend void datawrite(subject &sub1);
		friend void subjectdetails(subject &sub1);
		friend void studentdetails(subject &sub1);
		~subject(); // delete the allocated array
};


subject::subject(){
			string s1,s2;
			int i=0;
			ifstream file("subjdata.txt");
			while(!file.eof()){
					file>>s1>>s2;
					dataarray[i] = new node;
					dataarray[i]->index=s1;
					stringstream sso;
					sso<<s2;
					sso>>dataarray[i]->val;
				//	cout<<dataarray[i]->index<<"   "<<dataarray[i]->val<<endl;
					i++;							
			}
			k=i;
			file.close();
		}

subject::~subject(){
	for(int i=0;i<k;i++){
		delete dataarray[i];
	}
}


int subject::k=0;


char subject::grade(int x){
	if(x>=70){
		return 'A';
	}
	else if(x>=55){
		return 'B';
	}
	else if(x>=40){
		return 'C';
	}
	else if(x>=30){
		return 'D';
	}else{
		return 'F';
	}
	return 'O';
}



void studentdetails(subject &sub1){
	string tag1,subj;
	
	int y,year;
	int total=0,count=0;
	float avg=0;    // 
	cout<<"Enter the student Index :";
	cin>>tag1;
	stringstream sso;
	sso<<tag1;
	sso>>year;
	cout<<endl<<"Acadamic Year = "<<year/1000000+2000<<"    Index = "<<tag1<<endl;
	cout<<endl<<"Subject Code"<<"\t"<<"Marks"<<"\t"<<"Grade"<<endl;
	for(int i=0;i<sub1.k;i++){
		if(sub1.dataarray[i]->index.length()==7){
			subj=sub1.dataarray[i]->index;	
		}
		y=sub1.dataarray[i]->val;
		if(sub1.dataarray[i]->index==tag1){
			cout<<subj<<"\t\t"<<sub1.dataarray[i]->val<<"\t"<<sub1.grade(y)<<endl;
			total=total+y;
			count=count+1;
			subj="";
		}	
	}
		
		if(count>0){
			cout<<endl<<"Number of Subjects faced  : "<<count<<endl;
			cout<<"Marks Average             : "<<(float)total/count<<endl;
		}else{
			cout<<"Not in the file "<<endl;	
		}
}


void subjectdetails(subject &sub1){
			string tag,tag2;
			cout<<"Enter the subject code here : ";
			cin>>tag2;
			int x=-1,y,rate=0;
			for(int i=0;i<sub1.k;i++){
				tag=sub1.dataarray[i]->index;
				if((tag.length()==7)&&(tag==tag2)){
					x=sub1.dataarray[i]->val;
					cout<<tag<<"\t Number of students "<<x<<endl;
					for(int j=i+1;j<=i+x;j++){
						y=sub1.dataarray[j]->val;
						cout<<sub1.dataarray[j]->index<<"\t"<<y<<"\t"<<sub1.grade(y)<<endl;	
					}
					break;				
					}			
				}
					
					if(x<0){
						cout<<"Not in the file "<<endl;
					}
}

void subjectreport(subject &sub1){
			string tag,tag2;
			cout<<"Enter the subject code here : ";
			cin>>tag2;
			int x,y,rate=0,total=0;
			int a=0,b=0,c=0,d=0,f=0;
			float mean=0;
			float var=0,sd=0;
			float p=0;
			for(int i=0;i<sub1.k;i++){
				tag=sub1.dataarray[i]->index;
				if((tag.length()==7)&&(tag==tag2)){
					x=sub1.dataarray[i]->val;
					cout<<"Course Id = \t\t\t"<<tag<<endl<<"Number of students enrolled :\t"<<x<<endl;
					
				
					
					for(int j=i+1;j<=i+x;j++){
						y=sub1.dataarray[j]->val;	
						total=total+y;
						mean=(float)total/x;
//						var=var+pow(y- mean, 2);
						if(y>=40){
							rate++;
						}
						if(y>=70){
							a=a+1;
								}
						else if(y>=55){
							b=b+1;
								}
						else if(y>=40){
							c=c+1;
							}
						else if(y>=30){
							d=d+1;
						}else{
							f=f+1;
						}	
					}
					
					for(int j=i+1;j<=i+x;j++){
						p=p+pow(sub1.dataarray[j]->val-mean,2);
					}
					
					var=p/x;
					
					sd=sqrt(var);
					cout<<"The pass rate is : \t\t"<<(float)rate/x*100<<"%"<<endl;
					cout<<"The fail rate is : \t\t"<<(1-((float)rate/x))*100<<"%"<<endl;
					cout<<"The average Mark : \t\t"<<mean<<endl;
					cout<<"The standered diviation : \t"<<setprecision(2)<<fixed<<sd<<endl;
					cout<<"Number of A s    :\t\t"<<a<<"   "<<(float)a/x*100<<"%"<<endl;
					cout<<"Number of B s    :\t\t"<<b<<"   "<<(float)b/x*100<<"%"<<endl;
					cout<<"Number of C s    :\t\t"<<c<<"   "<<(float)c/x*100<<"%"<<endl;
					cout<<"Number of D s    :\t\t"<<d<<"   "<<(float)d/x*100<<"%"<<endl;
					cout<<"Number of F s    :\t\t"<<f<<"   "<<(float)f/x*100<<"%"<<endl;
				}
				
			}
			if(total==0){
				cout<<"Not in the file "<<endl;	
			}		
}
void datawrite(subject &sub1){
			string tag;
			
			int x,y,rate=0,total=0;
			int a=0,b=0,c=0,d=0,f=0;
			float mean=0;
			float var=0,sd=0;
			for(int i=0;i<sub1.k;i++){
				tag=sub1.dataarray[i]->index;
				if((tag.length()==7)){
					x=sub1.dataarray[i]->val;
//					cout<<"Course Id = \t\t\t"<<tag<<endl<<"Number of students enrolled :\t"<<x<<endl;
					for(int j=i+1;j<=i+x;j++){
						y=sub1.dataarray[j]->val;	
						total=total+y;
						mean=(float)total/x;
						var=var+pow(y- mean, 2);
						if(y>=40){
							rate++;
						}
						if(y>=70){
							a=a+1;
								}
						else if(y>=55){
							b=b+1;
								}
						else if(y>=40){
							c=c+1;
							}
						else if(y>=30){
							d=d+1;
						}else{
							f=f+1;
						}	
					}
					sd=sqrt(var/x);
					ofstream outfile("summdata.txt",ios::out|ios::app);
					outfile<<tag<<" "<<x<<" "<<"A "<<setprecision(2)<<fixed<<(float)a/x*100<<"%"<<" B "<<setprecision(2)<<fixed<<(float)b/x*100<<"%"<<" C "<<setprecision(2)<<fixed<<(float)c/x*100<<"%"<<" D "<<setprecision(2)<<fixed<<(float)d/x*100<<"%"<<" E "<<setprecision(2)<<fixed<<(float)f/x*100<<"%"<<endl;
					outfile.close();
				}	
			}
			if(total==0){
				cout<<"Not in the file "<<endl;	
			}else{
				cout<<"Data stored"<<endl;
			}		
}


int main(){
	
		int x=1;
	
	subject b;
	
	while(x){
		
		cout<<"........................................."<<endl;
		cout<<"1. Display Subject"<<endl;
		cout<<"2. Display Student"<<endl;
		cout<<"3. Display Subject Summary"<<endl;
		cout<<"4. Save Summaries"<<endl;
		cout<<"5. Exit Program"<<endl;
		cout<<"........................................."<<endl;
		cout<<"Select option :       ";
		
		cin>>x;
	
	switch(x){
		
		case 1: 
					subjectdetails(b);
					system("pause");
					break;
		case 2: 
					studentdetails(b);
					system("pause");
					break;
		case 3: 
					subjectreport(b);
					system("pause");
					break;
		case 4: 
					datawrite(b);
					system("pause");
					break;
		case 5: 
					b.~subject();
					x=0;
					break;			
		
		default: 					
					cout<<"Invalid option"<<endl ;
					break;
		}
	}

	
	return 0;
}


