#include <iostream>
using namespace std;


//Three students (a, b, c) are arriving in the mess at the same time. The id numbers of
//these students are 2132, 2102, 2453 and the food taken time from the mess table is 2, 4 and 8
//minutes. If the two students have same remaining time so it is broken by giving priority to the
//students with the lowest id number. Consider the longest remaining time first (LRTF) scheduling
//algorithm and calculate the average turnaround time and waiting time.

struct student{
	int id;
	int time_check;
	int complete_time_taken = 0;
	int burst_time;
};


//sorts as per burst time

void sortFnlrtf(student s[]){
    for(int i=1;i<3;i++){
        for(int j=0;j<3-i;j++){
            if(s[j].time_check < s[j+1].time_check){
                student temp = s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }
            else if(s[j].time_check == s[j+1].time_check){
                if(s[j].id > s[j+1].id){
                    student temp = s[j];
                    s[j]=s[j+1];
                    s[j+1]=temp;
                }
            }
        }
    }

}

bool notComplete(student s[]){
    for (int i=0;i<3;i++){
        if(s[i].time_check!=0){
            return true;
        }
    }
    return false;
}

void setCompleteTimer(student s[]){
    for (int i=0;i<3;i++){
            if(s[i].time_check!=0)
                s[i].complete_time_taken +=1;
    }

}

main(){
	student s[3];

	int i;
	for(i=0;i<3;i++){
        cout<<"Please input the id "<<i+1<<"\n";
		cin>>s[i].id;
		cout<<"How much time will you take in the mess\n";
		cin>>s[i].time_check;
		//Will input the burst time of each student.
		s[i].burst_time = s[i].time_check;

	}
	sortFnlrtf(s);
	//5 3 2
	//4 3 2
	//3 3 2


    while(notComplete(s)){
        // Keep doing your stuff
        cout<<s[0].id<<"\n";
        setCompleteTimer(s);
        s[0].time_check--;
        sortFnlrtf(s);
    }
    int sum = 0;
    int sum1 = 0;
    // Turn around time = Completion Time - Arrival Time
    // Waiting Time = Turn Around Time - Burst Time
    // Calculate average turn around time and waiting time
    for(int i=0;i<3;i++){
        cout<<s[i].id<<" : "<<s[i].complete_time_taken<<"\n";
        cout<<s[i].id<<" : "<<s[i].complete_time_taken - s[i].burst_time<<"\n";
        sum += s[i].complete_time_taken;
        sum1 += s[i].burst_time;
    }
cout<<"The average turnaround time is :"<<sum/3<<"\n";
    cout<<"The average waiting time is :"<<sum1/3<<"\n";

}
