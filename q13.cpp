/*Ques. 13. Write a program for multilevel queue scheduling algorithm. There must be three
/queues generated. There must be specific range of priority associated with every queue. Now
prompt the user to enter number of processes along with their priority and burst time. Each
process must occupy the respective queue with specific priority range according to its priority.
Apply Round robin algorithm with quantum time 4 on queue with highest priority range. Apply
priority scheduling algorithm on the queue with medium range of priority and First come first
serve algorithm on the queue with lowest range of priority. Each and every queue should get a
quantum time of 10 seconds. Cpu will keep on shifting between queues after every 10
seconds i.e. to apply round robin algorithm OF 10 seconds on over all structure.
Calculate Waiting time and turnaround time for every process. The input for number of
processes should be given by the user.
*/

//ALGORITHM
    //Initiate 3 queues and associate specific range of priority with every queue
    //Enter number of processes along with their priority and burst time.
    //Each process should occupy respective queue
    //Apply Round Robin Algorithm (q=4) with highest priority range
    //Apply Priority Scheduling Algorithm on medium priority range
    //First Come First Serve on lowest priority range
    //Each queue will only get 10 seconds
    //Round Robin on overall structure

    //q1 : p1,p2,p3  |RR(4)    |
    //q2 : p4,p5,p6  |PS    ---| Round Robin (10)
    //q3 : p7,p8,p9  |FCFS     |

#include <iostream>
using namespace std;

struct process{
    int priority;
    int burst_time;
    bool executed = False;
};

struct queues{
    int priority_start;
    int priority_end;
    int length = 0;
    process *p;
    bool executed = False;
};

void notComplete(queues q[]){
        for(int i=0;i<3;i++){
            for(int j=0;j<q[i].length;j++){
                if(q[i].p[j].burst_time != 0){
                    return true;
                }
            }
        }
        return false;
}
/*
void shuffleQueuesOrder(queues q[]){
    queues temp;
    for(int i=0;i<2;i++){
        temp = q[i];
        q[i] = q[i+1];
        q[i+1] = temp;
    }
}
*/
void processNotComplete(queues q[]){
    if(q.p[0].burst_time != 0){
        return true;
    }
    return false;
}

void sort_rr(process *temp){

}



main(){

    //Initializing 3 queues
    queues q[3];
    q[0].priority_start = 1;
    q[0].priority_end = 3;
    q[1].priority_start = 4;
    q[1].priority_end = 6;
    q[2].priority_start = 7;
    q[2].priority_end = 9;

    int no_of_processes,priority_of_process,burst_time_of_process;
    //Prompt User for entering Processes and assigning it to respective queues.
    cout<<"Enter the number of processes\n";
    cin>>no_of_processes;
    process p1[no_of_processes];

    for(int i=0;i<no_of_processes;i++){
        cout<<"Enter the priority of the process\n";
        cin>>priority_of_process;
        cout<<"Enter the burst time of the process\n";
        cin>>burst_time_of_process;
        p1[i].priority = priority_of_process;
        p1[i].burst_time = burst_time_of_process;
        for(int j=0;j<3;j++){
        if(q[j].priority_start<=priority_of_process && priority_of_process<=q[j].priority_end){
            q[j].length++;
        }
        }
    }

    for(int i =0;i<3;i++){
        int len = q[i].length;
        q[i].p = new process[len];
    }


    int a=0;
    int b=0;
    int c=0;

    for(int i =0;i<3;i++){
        for(int j=0;j<no_of_processes;j++){
            if((q[i].priority_start<=p1[j].priority) && (p1[j].priority<=q[i].priority_end)){
                if(i==0){
                    q[i].p[a++] = p1[j];

                    }
                else if(i==1){
                    q[i].p[b++] = p1[j];
                    }
                else{
                    q[i].p[c++] = p1[j];
                    }
            }
        }
    }

    a--;b--;c--;
    for(int i=0;i<3;i++){
        cout<<"Queue "<<i+1<<" : \t";
        for(int j=0;j<q[i].length;j++){
            cout<<q[i].p[j].priority<<"->";
        }
        cout<<"NULL\n";
    }


    //While RR on multiple queues is not complete, keep on repeating

    //sort_rr(q[0].p);
    //sort_ps(q[1].p);
    //sort_fcfs(q[2].p);

    int timer = 0;
    int l =0;
    while(notComplete(q)){

        if(timer == 10){
            l+=1;
            if(l>=3){
                l=l%3;
            }
        }

        //Process lth queue if its already not executed
        //If its executed change the value of l
        if(q[l].executed == true){
            l+=1;
            if(l>=3){
                l=l%3;
            }
            continue;
        }

        //Finally you now have a queue which is not completely executed
        //Process the incomplete processes over it

        if(l==0){
            //Round Robin Algorithm for q=4
            int rr_timer = 4;
            while(processNotComplete(q[0])){
                while(rr_timer!=0 || timer!= 10 || processNotComplete(q)){
                    q[0].p[0].burst_time--;
                    rr_timer--;
                    timer++;
                    }
                if(timer==10){
                    break;
                }
                if(rr_timer!=0){

                    //Process is complete
                    //Mark it unsortable
                    q[0].p[0].executed = true;
                    //Now sort for remaining processes
                    sort_rr(q[0].p);
                    //Take other process from the queue
                    //Sorting is done on the basis of priority
                    // and if the process is executed simply put it in the end
                    // and somehow don't involve it in sorting
                    // check if every process is executed mark queue executed.
                }
                else if(rr_timer==0 && processNotComplete(q)){
                 sort_rr(q[0].p);

                }
            }
        }

        else if(l==1){
            //Priority Scheduling

        }
        else{
            //FCFS
        }
    }
}
