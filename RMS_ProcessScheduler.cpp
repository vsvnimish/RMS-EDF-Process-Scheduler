#include<iostream>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
bool isdeadlinemissed(long long ,fstream &co);//this function will return true if process deadline is going to miss if we run that 
//else it will return false
bool can_prempt_and_deadline(long long x,long long y,fstream &co);// if process x can prempt process y and process x should not
//miss deadline then only this function will return true else it will return false 
void setup_process(long long );//this function will take process to its next period
long long preempt(long long x,fstream &co);//this function will check whether any process can prempt process x or not,if some process
// can prempt process x then this function will return index of that process else it will return -1 
long long process_selector(fstream &co);//if some process are ready to execute then this function will select higher priority process among them
//and that selected process should not miss deadline then only that process will be selected else it will look for another process
//and if no process are ready to execute then it will select process which is available earlier than other processes
//and if all process has reached there occurence limit then this function will return -1;

struct process{
	long long id;//process id will be stored
	double remaining_time;//at any point of time this will store remaining execution time of process
	double processing_time;//it will store execution time of process
	double available_time;//it will store the time at when the process is ready to execute
	double deadline_time;//it will store the deadline time of process
	double period;//it will store period of process
	long long occur;//it will store the total number of times the process has executed
	long long repeat;//this will store the number which tells that how many times that process has to execute
	long long dead;//if process misses its deadline then it will be intialized to 1 to indicate us 
	double waiting_time;//this will keep track of waiting time of process
	long long suc;//this will keep track of number of times that a particular process has finished its execution sucessfully
};
process *p;
double timer=0;
long long n;
//NOTE : the array which is used for storing process will be sorted based on their priority in our main function
long long process_selector(fstream &co){
    long long i=0,minindex;
	double min;
    for(i=0;i<n;i++){//we will return index of high priority process which satisfies below condition
   	 if(p[i].occur!=-1&&timer>=p[i].available_time&&isdeadlinemissed(i,co)!=true){//the conditions are the process should not execeed
   	 //its occurence limit and it should be ready and its deadline should not be missed
   	       return i;
     }
    }//if none of process satisifies above conditions then we need to execute below procedure
    for(i=0;i<n;i++){
     if((p[i].occur)!=-1){//this is for getting index of process which does not reached its occurence limit 
     		 break;
	 } 
    }
    if(i==n){//if all process has reached its occurence limit then return -1
       return -1; 
    }
    //at this point of time no process are ready to execute so we will select process which is available before other process
    minindex=i; 
    min=p[i].available_time;
    while(i<n){
   	  if(min>p[i].available_time&&p[i].occur!=-1){
   	  	   min=p[i].available_time;
   	  	   minindex=i;
	  }	
     i++;		 
    }//minindex will be index of process which available before other process
    return minindex;
}
long long preempt(long long x,fstream &co){
     long long i,minindex;
     double min,temptimer=timer,currenttimer;
     for(i=0;i<x;i++){//we want one index of process to intilaize minindex which satisfies below conditions 
     	if(p[i].occur!=-1&&can_prempt_and_deadline(i,x,co)){//conditions are the process should not exceed its occurence limit
     	 //and the process whose index is i should be able to prempt process whose index is x and process of index i should not
     	 //miss its deadline 
     	 break;   
		}      	
	 }
     if(i==x){//all process which is having higher priority than x has reached there occurence limit or they may not be able to
        //prempt x
      	timer=timer+p[x].remaining_time;//update timer to time at which process of index x has completed its execution
        return -1;//returing -1 because no premption is happening 
     } 
     minindex=i; 
     min=p[i].available_time;
     while(i<x){
   	  if(min>p[i].available_time&&p[i].occur!=-1&&can_prempt_and_deadline(i,x,co)){
   	  	   min=p[i].available_time;
   	  	   minindex=i;
      }	
      i++;		 
     }//minindex will contain index of process which is able to prempt and process which is available before others and process 
	 //which has not execeeded its occurence limit 
     temptimer=timer;
     timer=p[minindex].available_time;//updated timer to time at which process of minindex is ready
     temptimer=timer-temptimer;//temptimer will store the amount of time process of index x has executed
     p[x].remaining_time=p[x].remaining_time-temptimer;//change reamining time of process of index x
     return minindex;
}
bool can_prempt_and_deadline(long long x,long long y,fstream &co){
     double temptimer=timer,temp;
     if(timer+p[y].remaining_time>p[x].available_time){//here process of index x can prempt process of index y 
         timer=p[x].available_time;//updated timer to time at when process of index x is ready
         if(!isdeadlinemissed(x,co)){//if deadline for process of index x is not going to miss then this condition will become true
         	  timer=temptimer;//update timer to previous timer
	          return true;
	     }
     }
     timer=temptimer;//update timer to previous timer
     return false;//in other cases this will return false
}
bool isdeadlinemissed(long long x,fstream &co){
	if(timer+p[x].remaining_time>p[x].deadline_time){//the process deadline is going to miss
		p[x].waiting_time+=p[x].period;//as process missess deadline add its period to present waiting time
		p[x].dead++;//counter to keep track of number of deadlines missed for a process
		co<<"Process P"<<p[x].id<<" missed its deadline at time "<<timer<<"\n";
		setup_process(x);//taking process to its next period
	    return true;
    }
    return false;	       
}
bool compare(process a,process b){
	if(a.period!=b.period)
	      return !(a.period>b.period);//process having lower period will have higher priority
    return !(a.id>b.id);//if periods are same then give higher priority to process whose id is less	
}
void setup_process(long long x){
	p[x].available_time=p[x].deadline_time;//update available time
	p[x].deadline_time=p[x].available_time+p[x].period;////update deadline time
	p[x].remaining_time=p[x].processing_time;////update remaining time
	if(p[x].occur==p[x].repeat-1)
		p[x].occur=-1;//then this is an indicator to tell that process has reached its occurence limit
	else	 
	    p[x].occur++;//if process not reached its limit then we need to increment its occurence
}
int main(){
   ifstream ci("inp-params.txt");
   fstream co;
   co.open("RMS-Log.txt",ios::out);
   ofstream cu("RM-Stats.txt");
   long long i=0,a,b,c,x,pid,j,m;
   timer=0;
   double f=0,ch,current_timer,kl;
   ci>>n;
   p=(process*)malloc(sizeof(process)*n);
   for(i=0;i<n;i++){
      ci>>p[i].id;
      p[i].occur=0;
      p[i].available_time=0;
      ci>>p[i].processing_time;
      p[i].remaining_time=p[i].processing_time;
      ci>>p[i].period;
      ci>>p[i].repeat;
      if(p[i].repeat<=0||p[i].processing_time>p[i].period)
             p[i].occur=-1;//indicator to tell that this process cannot execute 
      p[i].deadline_time=p[i].period;
      //p[i].org=i+1;//store orginal index of process
      p[i].dead=0;
      p[i].waiting_time=0;
      if(p[i].processing_time>p[i].period){
         p[i].dead=p[i].repeat;
         p[i].waiting_time=p[i].repeat*p[i].period;//because processing time is greater than period every time it will miss 
         //deadline so we are calculating waiting time here
      }
      p[i].suc=0;
   }
   for(i=0;i<n;i++)
       co<<"Process P"<<p[i].id<<": processing time="<<p[i].processing_time<<"; deadline:"<<p[i].deadline_time<<"; period:"<<p[i].period<<" joined the system at time 0\n";
   sort(p,p+n,compare);//sort the process based on their priority
   x=process_selector(co);
   co<<"Process P"<<p[x].id<<" starts execution at "<<timer<<"\n";
   while(x!=-1){
	  pid=preempt(x,co);//after premption timer will be updated 
	  for(j=0;j<n;j++){//after updation of timer every process deadline will be checked
	  	if(timer>p[j].deadline_time&&p[j].occur!=-1){//if deadline missess
            co<<"Process P"<<p[x].id<<" missed its deadline at time "<<timer<<"\n";
	  		p[j].waiting_time+=p[j].period;//as process missess deadline add its period to present waiting time
	  		p[j].dead++;//counter to keep track of number of deadlines missed for a process
	  		setup_process(j);//take the process to its next period
		}
	  }	///allprocess whose deadline are missed at present timer will be updated
	  if(pid==-1){////no premption will happen
		 p[x].waiting_time+=timer-(p[x].available_time)-p[x].processing_time;
		 co<<"Process P"<<p[x].id<<" finishes execution at "<<timer<<"\n";
		 p[x].suc++;//increment it beacuse process has finished successfully
		 setup_process(x);//take the process to its next period
		 x=process_selector(co);//select another process
		 if(x==-1)//if all process has reached its occurence limit then process_selector will return -1
		     break;	 		   
		 if(timer<p[x].available_time&&timer!=0){
		 	timer=p[x].available_time;//update timer to time at which process is available
		 	co<<"CPU is idle till time "<<timer<<"\n";
		 }        
		 if(p[x].remaining_time==p[x].processing_time)
		    co<<"Process P"<<p[x].id<<" starts execution at "<<timer<<"\n";		     
		 else//if reamining and processing time are not same means that proces has executed some part before
		    co<<"Process P"<<p[x].id<<" resumes execution at "<<timer<<"\n"; 
      }
	  else{//premption will happen 
		 co<<"Process P"<<p[x].id<<" is preempted by Process P"<<p[pid].id<<" at time "<<timer<<". Remaining processing time:"<<p[x].remaining_time<<"\n";
		 co<<"Process P"<<p[pid].id<<" starts execution at "<<timer<<"\n";	    
		 x=pid;//pid prempts x so next process to execute should be pid
	  }
   }
   long long sum=0;
   double wait=0.0;
   long long total_process=0,temp=0;
   for(i=0;i<n;i++){
      sum+=p[i].dead;//sum is the total number of process that missed their deadlines
      wait+=double(p[i].waiting_time)/double(p[i].repeat);
      total_process+=p[i].repeat;
      temp+=p[i].suc;
   }
   wait=wait/n;
   cu<<"Number of processes that came into the system: "<<total_process<<"\n";
   cu<<"Number of processes that successfully completed: "<<temp<<"\n";
   cu<<"Number of processes that missed their deadlines: "<<sum<<" \n";
   cu<<"Average waiting time for each process: "<<wait<<" Milliseconds\n";
   return 0;
}
 
