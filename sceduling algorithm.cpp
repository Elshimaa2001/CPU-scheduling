#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#include <string.h>
#include <algorithm> 
#include <iomanip>
#include <queue> 
#include <cstring>
using namespace std;

//Helper function for printing stats
int countDigit(long long n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}
void SPN(string arrname[], int numberofprocesses, int arr_servicetime[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int time, int arr_starttime[], int arr_endtime[],string line1){
     
  //Array to store tracing
    char arr_print [numberofprocesses][time];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=' '; 
        }
    }
    if (line1.compare("trace")==0){
     
        
     cout << "SPN   ";
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       
       //Filling the trace array
       if (j1>9){j1=i1%10;}

      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }
 
    float avg_turnaround_time;
    float avg_waiting_time;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    int total_idle_time = 0;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    


    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != numberofprocesses) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < numberofprocesses; i++) {
            if(arr_arrivaltime[i] <= current_time && is_completed[i] == 0) {
                if(arr_servicetime[i] < mn) {
                    mn = arr_servicetime[i];
                    idx = i;
                }
                if(arr_servicetime[i] == mn) {
                    if(arr_arrivaltime[i] < arr_arrivaltime[idx]) {
                        mn = arr_servicetime[i];
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            //claculating turnaround time,starttime,endtime
            arr_starttime[idx] = current_time;
            arr_endtime[idx] = arr_starttime[idx] +  arr_servicetime[idx];
            arr_turnaroundtime[idx] = arr_endtime[idx]  - arr_arrivaltime[idx];
            arr_waittime[idx] = arr_turnaroundtime[idx] - arr_servicetime[idx];
           
            total_turnaround_time += arr_turnaroundtime[idx];
            total_waiting_time +=  arr_waittime[idx];
         
            total_idle_time += arr_starttime[idx] - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = arr_endtime[idx] ;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < numberofprocesses; i++) {
        min_arrival_time = min(min_arrival_time,arr_arrivaltime[i]);
        max_completion_time = max(max_completion_time,arr_endtime[i] );
    }

    avg_turnaround_time = (float) total_turnaround_time / numberofprocesses;
    avg_waiting_time = (float) total_waiting_time / numberofprocesses;
  
  
         //Printing the trace
    if(line1.compare("trace")==0){

    for (int j=0;j<numberofprocesses;j++){
         cout << arrname[j];
         cout << "     |";
        for(int i = arr_starttime[j]; i < arr_endtime[j]; i++){
                        arr_print[j][i]='*';

				}
        for(int i = arr_arrivaltime[j]; i < arr_starttime[j]; i++){
                        arr_print[j][i]='.';}
        
         for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
            cout << "|";
    }   
            cout << " \n";
    }
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";

    }



            //Printing the stats


    float nturnaround[numberofprocesses];
    for (int x=0;x<numberofprocesses;x++){
        nturnaround[x]= (float)arr_turnaroundtime[x]/(float)arr_servicetime[x];
    }

    if (line1.compare("stats")==0){
        cout << "SPN\n";
        cout << "Process    |";
        for (int m=0;m<numberofprocesses;m++){
            cout << "  ";
            cout << arrname[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_arrivaltime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_arrivaltime[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_servicetime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_servicetime[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_endtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_endtime[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_turnaroundtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+arr_turnaroundtime[m];
            cout << arr_turnaroundtime[m];
            cout << "  |";
        }
           if(countDigit(sum/numberofprocesses)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)sum/numberofprocesses);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<numberofprocesses;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/numberofprocesses)+2<4){
            cout << " ";
            }
         printf("%.2f",(float)nsum/numberofprocesses);
           
            cout << "|";
            cout << "\n";
            cout << "\n";
    }

}

void FCFS(string processes[], int n, int service[],int arrive[], int wait[],int turnaround[],int time, int start[], int end[], string l) {
  
  //Array to store tracing
    char arr_print [n][time];
    for (int i4=0;i4<n;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=' '; 
        }
    }
    if (l.compare("trace")==0){
       
        
     cout << "FCFS  ";
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       
       if (j1>9){j1=i1%10;}

      cout << j1;
      cout << " ";
       j1++;
        }
        cout << "\n";
        for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }




   


   int t[time];
  
    
    for(int j=0;j<n;j++){
        if(j==0){
            //Setting stats for first process
            start[0]=arrive[0];
            end[0]=arrive[0]+service[0];
            wait[0]=0;
            turnaround[0]=end[0]-arrive[0];
        }
        else {
            //Run the process that arrived after previous process ended
            if(arrive[j] > end[j-1] && j < n){
               
                start[j]=arrive[j];
                end[j]=arrive[j]+service[j];
                wait[j]=0;
                turnaround[j]=end[j]-arrive[j];
               
            }else{
                //Run the process that arrived before previous process ended after previous process ends
                start[j]=end[j-1];
                end[j]=start[j]+service[j];
                wait[j]=start[j]-arrive[j];
                turnaround[j]=end[j]-arrive[j];
               
            }

        }
        //print trace of processes
        if (l.compare("trace")==0){
        for(int i = start[j]; i < end[j]; i++){
                        arr_print[j][i]='*';

				}
        for(int i = arrive[j]; i < start[j]; i++){
                        arr_print[j][i]='.';

				}        
                 cout << processes[j];
        cout << "     |";
    
        for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
            cout << "|";
        }  
        cout << " ";  
        cout << "\n";

    

        }

    }

     if (l.compare("trace")==0){
        for(int i3=0;i3<48;i3++){
        cout << "-";
        }
        cout << "\n"; 
        cout << "\n";     
        }
    float nturnaround[n];
    for (int x=0;x<n;x++){
        //Calculate normalized turnaround
        nturnaround[x]= (float)turnaround[x]/(float)service[x];
    }

    //Printing stats
    if (l.compare("stats")==0){
        cout << "FCFS\n";
        cout << "Process    |";
        for (int m=0;m<n;m++){
            cout << "  ";
            cout << processes[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<n;m++){
           if (countDigit(arrive[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arrive[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<n;m++){
           if (countDigit(service[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << service[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<n;m++){
            if (countDigit(end[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << end[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        for (int m=0;m<n;m++){
            if (countDigit(turnaround[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+turnaround[m];
            cout << turnaround[m];
            cout << "  |";
        }
            if(countDigit(sum/n)+2<4){
            cout << " ";
            }
           printf("%.2f",(float)sum/n);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<n;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/n)+2<4){
            cout << " ";
            }
           printf("%.2f",(float)nsum/n);
            cout << "|\n";
            cout << "\n";
            
    }
		
}



void HRRN(string processes[], int n, int service[],int arrive[], int wait[],int turnaround[],int time, int start[], int end[], string l){
         
  //Array to store tracing
    char arr_print [n][time];
    for (int i4=0;i4<n;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=' '; 
        }
    }
    if (l.compare("trace")==0){  
     cout << "HRRN  ";
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }
   
   //Array to check for process completion
    int iscomplete[n];
    for (int i=0;i<n;i++){
        iscomplete[i]=0;
    }


    for (int t=0;t<time;){
        int highest=-1;
        double HRR=-1;
        for (int i=0;i<n;i++ ){
            //Calculate response ratio of newly arrived processes
            if (arrive[i]<=t && iscomplete[i]==0){
                float ratio= ((float)((t-arrive[i])+service[i])/service[i]);
                if(ratio>HRR){
                    HRR=ratio; //set highest ratio
                    highest=i;  //index of process with highest ratio
                }
            }
        }
        if(highest == -1) break; //finished
        
        //Calculate stats of processes
        start[highest]=t;
        end[highest]=start[highest]+service[highest];
        wait[highest]=start[highest]-arrive[highest];
        turnaround[highest]=end[highest]-arrive[highest];
        t=t+service[highest];
        iscomplete[highest]=1;
        
    }

    //Printing trace of processes
    if(l.compare("trace")==0){

    
    for (int j=0;j<n;j++){
         cout << processes[j];
         cout << "     |";
        for(int i = start[j]; i < end[j]; i++){
                        arr_print[j][i]='*';

				}
        for(int i = arrive[j]; i < start[j]; i++){
                        arr_print[j][i]='.';}
        
         for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
            cout << "|";
    }   
            cout << " \n";
    }
         
        for(int i3=0;i3<48;i3++){
        cout << "-";
        }
        
        cout << "\n";
        cout << "\n";
             
    
    }


    //Printing stats of processes
    float nturnaround[n];
    for (int x=0;x<n;x++){
        nturnaround[x]= (float)turnaround[x]/(float)service[x];
    }

   if (l.compare("stats")==0){
        cout << "HRRN\n";
        cout << "Process    |";
        for (int m=0;m<n;m++){
            cout << "  ";
            cout << processes[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<n;m++){
           if (countDigit(arrive[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arrive[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<n;m++){
           if (countDigit(service[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << service[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<n;m++){
            if (countDigit(end[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << end[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        for (int m=0;m<n;m++){
            if (countDigit(turnaround[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+turnaround[m];
            cout << turnaround[m];
            cout << "  |";
        }
            if(countDigit(sum/n)+2<4){
            cout << " ";
            }
             printf("%.2f",(float)sum/n);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<n;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/n)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)nsum/n);
            cout << "|";
            cout << "\n";
	cout << "\n";
    }
	

}

void RR(string arrname[], int numberofprocesses, int arr_servicetime[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int time, int arr_starttime[], int arr_endtime[],string line1,int quantum)
{       
     
  //Array to store tracing
     string arr_print [numberofprocesses][time];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=" |"; 
        }
    }

    if (line1.compare("trace")==0){  
     cout << "RR-" << quantum << "  " ;
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }
    
    int remain [numberofprocesses];
    int item;
    for(int i = 0; i < numberofprocesses; i++) {
        remain [i] = arr_servicetime[i];
    }
    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mm[100];
    memset(mm,0,sizeof(mm));
    mm[0] = 1;
    while(completed != numberofprocesses) {
        item = q.front();
        q.pop();
        if(remain [item] == arr_servicetime[item]) {
            //Setting start time of newly arriving processes
            arr_starttime[item] = max(current_time,arr_arrivaltime[item]);
            current_time = arr_starttime[item];
                if (remain[item]<quantum){

                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
              
            
        }
        //Filling the trace array
        if(remain [item]-quantum > 0) {
            
            if (remain[item]<quantum){

                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
            remain [item] -= quantum;   
            current_time += quantum;
        }
        else {
            if (remain[item]<quantum){

                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
                //Calculating stats after process finishes executing  

            current_time += remain [item];
            remain [item] = 0;
            completed++;
            arr_endtime[item] = current_time;
            arr_turnaroundtime[item] = arr_endtime[item] - arr_arrivaltime[item];
            arr_waittime[item] = arr_turnaroundtime[item] - arr_servicetime[item];
            
        }
        //Push all the processes that arrived while the previous process was running into the queue
        for(int i = 1; i < numberofprocesses; i++) {
            if(remain [i] > 0 && arr_arrivaltime[i] <= current_time && mm[i] == 0) {
                q.push(i);
                mm[i] = 1;
            }
        }
        if(remain [item] > 0) {
            q.push(item);
        }
        //If queue is empty push a process that hasn't finished
        if(q.empty()) {
            for(int i = 1; i < numberofprocesses; i++) {
                if(remain [i] > 0) {
                    q.push(i);
                    mm[i] = 1;
                    break;
                }
            }
        }
    }

     //Printing the trace
    if(line1.compare("trace")==0){    
        for (int j=0;j<numberofprocesses;j++){
            cout << arrname[j];
            cout << "     |";
            for(int i = arr_arrivaltime[j]; i < arr_endtime[j]; i++){
               if(arr_print[j][i].compare(" |")==0){
                    arr_print[j][i]=".|";  
               } 
				}

            for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
    }   
            cout << " \n";    
     }
     
     for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";
     }  

     //Printing the stats

    float nturnaround[numberofprocesses];
    for (int x=0;x<numberofprocesses;x++){
        nturnaround[x]= (float)arr_turnaroundtime[x]/(float)arr_servicetime[x];
    }
    if (line1.compare("stats")==0){
        cout << "RR-"<<quantum<<"\n";
        cout << "Process    |";
        for (int m=0;m<numberofprocesses;m++){
            cout << "  ";
            cout << arrname[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_arrivaltime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_arrivaltime[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_servicetime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_servicetime[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_endtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_endtime[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_turnaroundtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+arr_turnaroundtime[m];
            cout << arr_turnaroundtime[m];
            cout << "  |";
            
        }
            if(countDigit(sum/numberofprocesses)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)sum/numberofprocesses);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<numberofprocesses;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/numberofprocesses)+2<4){
            cout << " ";
            }
         printf("%.2f",(float)nsum/numberofprocesses);
           
            cout << "|";
           cout << "\n";
            cout << "\n";
            
    }


}




void SRT(string arrname[], int numberofprocesses, int arr_servicetime[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int time, int arr_starttime[], int arr_endtime[],string line1)
{       
     
  //Array to store tracing
    string arr_print [numberofprocesses][time];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=" |"; 
          
        }
    }

    if (line1.compare("trace")==0){  
     cout << "SRT   " ;
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }

    
    int remain[numberofprocesses];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));
    for(int i = 0; i < numberofprocesses; i++) {
        remain[i] = arr_servicetime[i];
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != numberofprocesses) {
        int item = -1;
        int min = 10000000;
        for(int i = 0; i < numberofprocesses; i++) {
            if(arr_arrivaltime[i] <= current_time && is_completed[i] == 0) {
                if(remain[i] < min) {
                    min = remain[i];
                    item = i;
                }
                if(remain[i] == min) {
                    if(arr_arrivaltime[i] < arr_arrivaltime[item]) {
                        min = remain[i];
                        item = i;
                    }
                }
            }
        }

        if(item != -1) {
            if(remain[item] == arr_servicetime[item]) {
                
                arr_starttime[item] = current_time;
            }
            arr_print[item][current_time]="*|";
            remain[item] -= 1;
            current_time++;
            prev = current_time;
            
            if(remain[item] == 0) {
                //calculating the turnaround time, starttime, and finish time
                arr_endtime[item] = current_time;
                arr_turnaroundtime[item] = arr_endtime[item] - arr_arrivaltime[item];
                arr_waittime[item] = arr_turnaroundtime[item] - arr_servicetime[item];
                is_completed[item] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

       //Printing the trace
  if(line1.compare("trace")==0){    
        for (int j=0;j<numberofprocesses;j++){
            cout << arrname[j];
            cout << "     |";

            for(int i = arr_arrivaltime[j]; i < arr_endtime[j]; i++){
               if(arr_print[j][i].compare(" |")==0){
                    arr_print[j][i]=".|";  
               } 
			}

            for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
    }   
            cout << " \n";              
           
     }
     
      for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";
     }
      //Printing the stats
    float nturnaround[numberofprocesses];
    for (int x=0;x<numberofprocesses;x++){
        nturnaround[x]= (float)arr_turnaroundtime[x]/(float)arr_servicetime[x];
    }
    if (line1.compare("stats")==0){
        cout << "SRT\n";
        cout << "Process    |";
        for (int m=0;m<numberofprocesses;m++){
            cout << "  ";
            cout << arrname[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_arrivaltime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_arrivaltime[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_servicetime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_servicetime[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_endtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_endtime[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_turnaroundtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+arr_turnaroundtime[m];
            cout << arr_turnaroundtime[m];
            cout << "  |";
            
        }
            if(countDigit(sum/numberofprocesses)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)sum/numberofprocesses);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<numberofprocesses;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/numberofprocesses)+2<4){
            cout << " ";
            }
         printf("%.2f",(float)nsum/numberofprocesses);
           
            cout << "|";
            cout << "\n";
            cout << "\n";
            
    }

   


}

void FB(string arrname[], int numberofprocesses, int arr_servicetime[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int time, int arr_starttime[], int arr_endtime[],string line1,int quantum)
{   


    //Array for tracing
     string arr_print [numberofprocesses][time];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=" |"; 
        }
    }

    if (line1.compare("trace")==0){  
     cout << "FB-1  ";
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }


    struct process{
        int id;
        int priority;
        int start;
    };

struct pri{
    bool operator()(process const &p1, process const &p2)
    {   //Organize priority queue according to highest priority
       if (p1.priority==p2.priority){
        return p1.start > p2.start;
       }
        return p1.priority < p2.priority;
    }
};

    priority_queue <struct process,vector<struct process>,pri> pq;
    struct process pp[numberofprocesses];
    for (int i=0;i<numberofprocesses;i++){
        //Initializing array of struct containing our processes
        pp[i].id=i;
        pp[i].priority=5;
        pp[i].start=arr_arrivaltime[i];
       
    }



    
    int remain [numberofprocesses];
    int item;
    for(int i = 0; i < numberofprocesses; i++) {
        remain [i] = arr_servicetime[i];
    }
    queue<int> q;
    int current_time = 0;
    //Insert first process into priority queue
    pq.push(pp[0]);
    int completed = 0;
    int mm[100];
    memset(mm,0,sizeof(mm));
    mm[0] = 1;


    while(completed != numberofprocesses) {
       
        process item2 = pq.top();
        item = item2.id;
        
        pq.pop();

        if(remain [item] == arr_servicetime[item]) {
            //Setting start time of newly arriving processes
            arr_starttime[item] = max(current_time,arr_arrivaltime[item]);
            current_time = arr_starttime[item];
                if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                    //Filling the trace array
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
                
            
        }
        if(remain [item]-quantum > 0) {
            
            if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
            }
                else{
                    //Filling the trace array
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }


            //Calculating remaining time for a process and the current time
            remain [item] -= quantum;    
            current_time += quantum;
            
        }
        else {
            if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                    //Filling the trace array
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }

             //Calculating stats after process finishes executing   
            current_time += remain [item];
            remain [item] = 0;
            completed++;
            arr_endtime[item] = current_time;
            arr_turnaroundtime[item] = arr_endtime[item] - arr_arrivaltime[item];
            arr_waittime[item] = arr_turnaroundtime[item] - arr_servicetime[item];
           
            
        }
        for(int i = 1; i < numberofprocesses; i++) {
        //Push all the processes that arrived while the previous process was running into the queue
            if(remain [i] > 0 && arr_arrivaltime[i] <= current_time && mm[i] == 0) {
                pq.push(pp[i]);
                mm[i] = 1;
            }
        }

        //Push current process into queue if it hasn't finished
        if(remain [item] > 0) {
           if (!pq.empty()){
                // Decrease priority of processes that reentered the ready queue
                pp[item].priority=item2.priority-1;
            }
            pq.push(pp[item]);
        }
        //If queue is empty push a process that hasn't finished
        if(pq.empty()) {
            for(int i = 1; i < numberofprocesses; i++) {
                if(remain [i] > 0) {
                    pq.push(pp[i]);
                    mm[i] = 1;
                    break;
                }
            }
        }

        
    }

    //Printing the trace
    if(line1.compare("trace")==0){    
        for (int j=0;j<numberofprocesses;j++){
            cout << arrname[j];
            cout << "     |";
            for(int i = arr_arrivaltime[j]; i < arr_endtime[j]; i++){
               if(arr_print[j][i].compare(" |")==0){
                    arr_print[j][i]=".|";  
               } 
				}

            for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
    }   
            cout << " \n";    
     }
     
     for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";
     }  


    //Printing the stats
    float nturnaround[numberofprocesses];
    for (int x=0;x<numberofprocesses;x++){
        nturnaround[x]= (float)arr_turnaroundtime[x]/(float)arr_servicetime[x];
    }
    if (line1.compare("stats")==0){
        cout << "FB-1\n";
        cout << "Process    |";
        for (int m=0;m<numberofprocesses;m++){
            cout << "  ";
            cout << arrname[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_arrivaltime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_arrivaltime[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_servicetime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_servicetime[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_endtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_endtime[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_turnaroundtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+arr_turnaroundtime[m];
            cout << arr_turnaroundtime[m];
            cout << "  |";
            
        }
            if(countDigit(sum/numberofprocesses)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)sum/numberofprocesses);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<numberofprocesses;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/numberofprocesses)+2<4){
            cout << " ";
            }
         printf("%.2f",(float)nsum/numberofprocesses);
           
            cout << "|";
            cout << "\n";
            cout << "\n";

    }


}

void FB2i(string arrname[], int numberofprocesses, int arr_servicetime[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int time, int arr_starttime[], int arr_endtime[],string line1)
{

    //Setting up trace array
     string arr_print [numberofprocesses][time];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<time;j4++ ){
            arr_print[i4][j4]=" |"; 
        }
    }

    if (line1.compare("trace")==0){  
     cout << "FB-2i ";
     int j1=0;
     for (size_t i1 = 0; i1 <= time; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    }


    struct process{
        int id;
        int priority;
        int start;
    };

struct pri{
    bool operator()(process const &p1, process const &p2)
    {   //Order priority queue according to process priorities
       if (p1.priority==p2.priority){
        return p1.start > p2.start;
       }
        return p1.priority < p2.priority;
    }
};

    priority_queue <struct process,vector<struct process>,pri> pq;
    struct process pp[numberofprocesses];
    for (int i=0;i<numberofprocesses;i++){
        //Initializing priorities of all processes
        pp[i].id=i;
        pp[i].priority=5;
        pp[i].start=arr_arrivaltime[i];
       
    }



    
    int remain [numberofprocesses];
    int item;
    for(int i = 0; i < numberofprocesses; i++) {
        remain [i] = arr_servicetime[i];
    }
    queue<int> q;
    int current_time = 0;

    //Insert first process into priority queue
    pq.push(pp[0]);
    int completed = 0;
    int mm[100];
    memset(mm,0,sizeof(mm));
    mm[0] = 1;
    int quantum;
    while(completed != numberofprocesses) {
       
        process item2 = pq.top();

       //Setting quantum of processes according to their priorities
        if (item2.priority==5){
            quantum=1;
        }
        else if (item2.priority==4){
            quantum=2;
        }
        else if (item2.priority==3){
            quantum=4;
        }
       else if (item2.priority==2){
            quantum=8;
        }
       else if (item2.priority==1){
            quantum=16;
        }
        else {
        quantum=16;
        }
        item = item2.id;
         
        
        pq.pop();

       
        if(remain [item] == arr_servicetime[item]) {
            //Setting start time of newly arriving processes
            arr_starttime[item] = max(current_time,arr_arrivaltime[item]);
            current_time = arr_starttime[item];
                if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                    //Filling the trace array
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
                
            
        }
        if(remain [item]-quantum > 0) {
            
            if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
            }
                else{
                  for (int p=0;p<quantum;p++){
                    //Filling the trace array
                    arr_print[item][current_time+p]="*|";
                    } 
                }


            //Calculating remaining time for a process and the current time
            remain [item] -= quantum;    
            current_time += quantum;
            
        }
        else {
            if (remain[item]<quantum){
                    //Filling the trace array
                    for (int p=0;p<remain[item];p++){

                    arr_print[item][current_time+p]="*|";
                    }
                }
                else{
                    //Filling the trace array
                  for (int p=0;p<quantum;p++){

                    arr_print[item][current_time+p]="*|";
                    } 
                }
            //Calculating stats after process finishes executing  

            current_time += remain [item];
            remain [item] = 0;
            completed++;
            arr_endtime[item] = current_time;
            arr_turnaroundtime[item] = arr_endtime[item] - arr_arrivaltime[item];
            arr_waittime[item] = arr_turnaroundtime[item] - arr_servicetime[item];
            
        }
        for(int i = 1; i < numberofprocesses; i++) {
            //Push all the processes that arrived while the previous process was running into the queue
            if(remain [i] > 0 && arr_arrivaltime[i] <= current_time && mm[i] == 0) {
                pq.push(pp[i]);
                mm[i] = 1;
            }
        }
        if(remain [item] > 0) {
           if (!pq.empty()){
            // Decrease priority of processes that reentered the ready queue
                pp[item].priority=item2.priority-1;
            }
            pq.push(pp[item]);
        }
        //If queue is empty push a process that hasn't finished
        if(pq.empty()) {
            for(int i = 1; i < numberofprocesses; i++) {
                if(remain [i] > 0) {
                    pq.push(pp[i]);
                    mm[i] = 1;
                    break;
                }
            }
        }


    }

     //Printing the trace
    if(line1.compare("trace")==0){    
        for (int j=0;j<numberofprocesses;j++){
            cout << arrname[j];
            cout << "     |";
            for(int i = arr_arrivaltime[j]; i < arr_endtime[j]; i++){
               if(arr_print[j][i].compare(" |")==0){
                    arr_print[j][i]=".|";  
               } 
				}

            for (int j4=0; j4<time;j4++ ){
            cout << arr_print[j][j4];
    }   
            cout << " \n";    
     }
     
     for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";
     }  

    //Printing the stats

    float nturnaround[numberofprocesses];
    for (int x=0;x<numberofprocesses;x++){
        nturnaround[x]= (float)arr_turnaroundtime[x]/(float)arr_servicetime[x];
    }
    if (line1.compare("stats")==0){
        cout << "FB-2i\n";
        cout << "Process    |";
        for (int m=0;m<numberofprocesses;m++){
            cout << "  ";
            cout << arrname[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Arrival    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_arrivaltime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_arrivaltime[m];
            cout << "  |";
        }
        cout << "\n";
        cout << "Service    |";
        for (int m=0;m<numberofprocesses;m++){
           if (countDigit(arr_servicetime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_servicetime[m];
            cout << "  |";
        }
        cout << " Mean|";
        cout << "\n";
        cout << "Finish     |";
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_endtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            cout << arr_endtime[m];
            cout << "  |";
        }
       cout << "-----|";
        cout << "\n";
        cout << "Turnaround |";
        float sum=0;
        
        for (int m=0;m<numberofprocesses;m++){
            if (countDigit(arr_turnaroundtime[m])>1){
                cout << " ";
            }
            else{
            cout << "  ";
            }
            sum=sum+arr_turnaroundtime[m];
            cout << arr_turnaroundtime[m];
            cout << "  |";
            
        }
            if(countDigit(sum/numberofprocesses)+2<4){
            cout << " ";
            }
            printf("%.2f",(float)sum/numberofprocesses);
            cout << "|";
            cout << "\n";
            cout << "NormTurn   |";
            float nsum=0;
            for (int m=0;m<numberofprocesses;m++){
            
                cout << " ";
            
            
            nsum=nsum+nturnaround[m];
            printf("%.2f",(float)nturnaround[m]);
            cout << "|";
        }
         if(countDigit(nsum/numberofprocesses)+2<4){
            cout << " ";
            }
         printf("%.2f",(float)nsum/numberofprocesses);
           
            cout << "|";
            cout << "\n";
            cout << "\n";

    }


}



void Aging(string arrname[], int numberofprocesses, int arr_periority[],int arr_arrivaltime[], int arr_waittime[],int arr_turnaroundtime[],int lastinstant, int arr_starttime[], int arr_endtime[],int quantum)
{

         
  //Array to store tracing

    string arr_print [numberofprocesses][lastinstant];
    for (int i4=0;i4<numberofprocesses;i4++){
        for (int j4=0; j4<lastinstant;j4++ ){
            arr_print[i4][j4]=" |"; 
        }
    }

    
     cout << "Aging ";
     int j1=0;
     for (size_t i1 = 0; i1 <= lastinstant; i1++){
       if (j1>9){j1=i1%10;}
      cout << j1;
      cout << " ";
       j1++;
    }
    cout << "\n";
    for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
    
    struct process{
        int id;
        int priority;
        int start;
        int end;
    };

    struct pri{
        bool operator()(process const &p1, process const &p2)
        {
       if (p1.priority==p2.priority){
        return p1.start > p2.start;
        }
        return p1.priority <p2.priority;
        }
    };

    priority_queue <struct process,vector<struct process>,pri> pq;
    struct process pp[numberofprocesses];
    struct process pp1[numberofprocesses];
    process item2 ;
    int item=-1;
    int current_time ;
    for (int i=0;i<numberofprocesses;i++){

        pp[i].id=i;
        pp[i].priority=arr_periority[i]+1;
        pp[i].start=arr_arrivaltime[i];
        pp[i].end;
    }
    pq.push(pp[0]);
    pp[0].start=arr_arrivaltime[0];


    for(int i=0;i<=lastinstant;i++) {
            current_time=i;
     
       
////////checking the quantum of the running proces, if completed block it and assign the earliest priority to it

           if (!pq.empty() &&quantum<=current_time-pp[item].start && item!=-1){
            
            pp[item].end = current_time;
            arr_turnaroundtime[item] = pp[item].end - pp[item].start;
            //cout<<arrname[item]<<pp[item].priority<<pp[item].start<<pp[item].end<<endl;
            for (int i=pp[item].start;i<pp[item].end;i++){
                arr_print[item][i]="*|";
            }
             pp[item].priority=arr_periority[item];
            pq.push(pp[item]);
           
            pp[item].priority=arr_periority[item];
           item=-1;
           pq.pop();
            }
          
            pp[item].priority=arr_periority[item];
            
       //Inserting new processes in the priority queue 
        for(int i = 0; i < numberofprocesses; i++) {
            if( arr_arrivaltime[i] <= current_time ) {
                pq.push(pp[i]);
                
            }
            
        }
          /////////////if no process is running run the highest priority
            if(!pq.empty() && item ==-1){
                item2=pq.top();
                 item = item2.id;
               
         
                 for(int i = 0; i < numberofprocesses; i++) {
                      if( pp[i].start <= current_time && pp[i].id!=item) {
                          pp[i].priority++;
            }}
              
                pp[item].start=current_time;    
                pp[item].priority=arr_periority[item];         
        }
        
         while (!pq.empty()) {
        pq.pop();
    }
            /////////////////////sort the priorty queue based on current priority
          for(int i=0; i<numberofprocesses;i++){
            if(pp[i].start<=current_time){
            pq.push(pp[i]);}

        }      
        }

            
        for (int j=0;j<numberofprocesses;j++){
            cout << arrname[j];
            cout << "     |";
            for(int i = arr_arrivaltime[j]; i < lastinstant; i++){
               if(arr_print[j][i].compare(" |")==0){
                    arr_print[j][i]=".|";  
               } 
				}

            for (int j4=0; j4<lastinstant;j4++ ){
            cout << arr_print[j][j4];
    }   
            cout << " \n";    
     }
     
     for(int i3=0;i3<48;i3++){
        cout << "-";
    }
   cout << "\n";
   cout << "\n";
      
}



int main()
{
	string line1;
    cin>>line1;

    string schedulingpolicies;
    cin>>schedulingpolicies;
    
    vector<string> s_schedulingpolicy;
    stringstream ss(schedulingpolicies);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        s_schedulingpolicy.push_back(substr);
    }
    string sarr_quantum[s_schedulingpolicy.size()];
    for(int i=0;i<s_schedulingpolicy.size() ;i++){
        sarr_quantum[i]={"0"};

    }
    vector < string > v;
    int index0=0;
    int m[s_schedulingpolicy.size()];
    for (int i = 0; i < s_schedulingpolicy.size(); i++) {
       if(s_schedulingpolicy[i].at(0) == '2' || s_schedulingpolicy[i].at(0) == '8' ){
                m[index0]=i;
                index0++;
               stringstream ss(s_schedulingpolicy[i]);
                while (ss.good()) {
                string substr;
                getline(ss, substr, '-');
                v.push_back(substr); 
            }
          }
    }
    for (size_t i = 0; i <index0; i++){
        
        s_schedulingpolicy[m[i]]=v[i*2];
        sarr_quantum[m[i]]=v[(i*2)+1];

       }
    
    int lastinstant;
    cin>>lastinstant;
    int numberofprocesses;
    cin>>numberofprocesses;
    string arr[numberofprocesses];
    for (int i = 0; i < numberofprocesses; i++) {
        cin >> arr[i];
    }
    string arrname[numberofprocesses];
    string sarr_arrivaltime[numberofprocesses];
    string sarr_servicetime[numberofprocesses];
    int index1=0;
	  int index2=0;
    int index3=0;
    vector < string > v1;
    for (int i = 0; i < numberofprocesses; i++) {
        stringstream ss(arr[i]);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v1.push_back(substr);
            }
            }
                  
    for (int i = 0; i < numberofprocesses*3; i++)
    {
        if( i%3 ==0){
            arrname[index1]=v1[i];
		      	index1++;
        }
        else if (i%3 ==1)
        {
            sarr_arrivaltime[index2]=v1[i];
			      index2++;
        }
        else{
            sarr_servicetime[index3]=v1[i];
            index3++;

        }

    }
     /*for (size_t i = 0; i < s_schedulingpolicy.size(); i++)
        cout << s_schedulingpolicy[i] << endl;  
    for (size_t i = 0; i < s_schedulingpolicy.size(); i++)
        cout << arr_quantum[i] << endl;           
    for (size_t i = 0; i <numberofprocesses; i++)
        cout << arrname[i] << endl;
    for (size_t i = 0; i < numberofprocesses; i++)
        cout << sarr_servicetime[i] << endl;
    for (size_t i = 0; i < numberofprocesses; i++)
        cout << sarr_arrivaltime[i]<< endl;*/
        int arr_waittime[numberofprocesses], 
    arr_starttime[numberofprocesses],
    arr_endtime[numberofprocesses],
    arr_turnaroundtime[numberofprocesses];

  int arr_arrivaltime[numberofprocesses];
    int arr_servicetime[numberofprocesses];
    int schedulingpolicy[s_schedulingpolicy.size()];
    int arr_quantum[s_schedulingpolicy.size()];
    for (size_t i = 0; i < numberofprocesses; i++)
       arr_arrivaltime[i]=stoi(sarr_arrivaltime[i]);
       for (size_t i = 0; i < numberofprocesses; i++)
       arr_servicetime[i]=stoi(sarr_servicetime[i]);
  for (size_t i = 0; i < s_schedulingpolicy.size(); i++)
       schedulingpolicy[i]=stoi(s_schedulingpolicy[i]);
    
    for (size_t i = 0; i < s_schedulingpolicy.size(); i++)
       arr_quantum[i]=stoi(sarr_quantum[i]);

  for(int i=0; i< s_schedulingpolicy.size();i++){
    switch (schedulingpolicy[i]) {
    case 1:
    FCFS(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime,line1);
    break;
    case 2:
    RR(arrname,  numberofprocesses,  arr_servicetime, arr_arrivaltime,  arr_waittime, arr_turnaroundtime, lastinstant,  arr_starttime, arr_endtime,line1,arr_quantum[i]);

    break;
    case 3:
    SPN(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime,line1);
    break;
    case 4:
    SRT(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime,line1);
    break;
    case 5:
    HRRN(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime,line1);
    break;
    case 6: FB(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime, line1,1);
    break;
    case 7:
    FB2i(arrname,numberofprocesses,arr_servicetime,arr_arrivaltime,arr_waittime,arr_turnaroundtime,lastinstant,arr_starttime,arr_endtime, line1);
    break;
    
    case 8:
    Aging(arrname,  numberofprocesses,  arr_servicetime, arr_arrivaltime,  arr_waittime, arr_turnaroundtime, lastinstant,  arr_starttime, arr_endtime,arr_quantum[i]);
    break;
    
}


  }      
 
}
