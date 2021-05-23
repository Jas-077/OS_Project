#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int check(int t,int add)
{
    int initial_time=t-add;
    int final_time=t;
    if(initial_time%5==0)
    initial_time++;
    for(int i=initial_time;i<=final_time;i++)
    {
        if(i%5==0 && i!=0)
        {
        return 1;
        }
    }
    return 0;
}

int find_small(vector<int> indexes,int bt[],int x)
{
    int min=100000000;
    int min_index=-1;
    int  t;
    
    for(int i=0;i<indexes.size();i++)
    {
        t=indexes[i];
        if(bt[t]<min && t!=x)
        {
            min=bt[t];
            min_index=t;
        }
    }
    return min_index;
}

void remove_index(vector<int> &indexes,int rem)
{
    vector<int> indexes2;
    for(int i=0;i<indexes.size();i++)
    {
        
        if(indexes[i]!=rem)
        
        {
            
            indexes2.push_back(indexes[i]);}
    }
    indexes.clear();
    for(int i=0;i<indexes2.size();i++)
    {
        
        indexes.push_back(indexes2[i]);
    }
}

float avg (int a[], int l)
{
  float av = 0;
  for (int i = 0; i < l; i++)
    {
      av += a[i];
    }
  av = av / l;
  return av;
}

int main ()
{
    int l;
    cout<<"Enter the no of Processes\n";
    cin>>l;
    int p[l];
    int at[l];
    int bt[l];
    int tim;
    float alpha;
    for(int i=0;i<l;i++)
    {
        p[i]=i+1;
    }
    cout<<"\nEnter the Arrival Time of Processes\n";
    for(int i=0;i<l;i++)
    {
        cout<<"Enter Arrival time of "<<(i+1)<<" Process\n";
        cin>>at[i];
    }
  cout<<"\nEnter the Burst Time of Processes\n";
    for(int i=0;i<l;i++)
    {
        cout<<"Enter Burst time of "<<(i+1)<<" Process\n";
        cin>>bt[i];
    }
    cout<<"\nEnter initial Time Quantum\n";
    cin>>tim;
    cout<<"\nEnter value of Alpha\n";
    cin>>alpha;
  int total_bt = 0;
  
  int min;
  int index;
  
  int ct[l] = { 0 };
  int visited[l] = { 0 };
  int tat[l] = { 0 };
  int wt[l] = { 0 };
  int bt2[l] = { 0 };
  int new_element;
  for (int i = 0; i < l; i++)
    {
      total_bt += bt[i];
      bt2[i] = bt[i];
    }
  cout << "Proccess ID\t Arrival Time\t Burst Time\n";
  for (int i = 0; i < l; i++)
    {
      cout << "P" << (i + 1) << "\t\t " << at[i] << "\t\t " << bt[i];
      cout << endl;
    }
  vector < int >indexes;
  int j = 0;
  index = 0;
  for(int i=0;i<l;i++)
  {
      if(at[i]==0)
      indexes.push_back(i);
  }
  visited[index] = 1;
  int current_index=-1;
  int select_new=1;
  float vtq=(float)tim;
  int f=0;
  int first_it=1;
  while (j < total_bt)
    {
        f=0;
      if(first_it==1)
      {
      current_index =find_small(indexes,bt,current_index);
      first_it=0;
      }
      
      else if(select_new==1 && indexes.size()>1)
      current_index =find_small(indexes,bt,current_index);
      else if(indexes.size()<=1)
      current_index=indexes[0];
      remove_index(indexes,current_index);
      for (int i = 0; i < l; i++)
	{
	  if (at[i] <= (j + tim) && visited[i] == 0)
	    {
	      indexes.push_back(i);
	      visited[i] = 1;
	    }
	}
      if (bt[current_index] > tim)
	{
	  bt[current_index] -= tim;
	  j += tim;
	  f=check(j,tim);
	  indexes.push_back(current_index);
	  if(bt[current_index]>=floor(0.5*tim) && bt[current_index]<=ceil(1.5*tim))
	  {
	      select_new=0;
	  }
	  else
	  select_new=1;
	}
      else if (bt[current_index] != 0)
	{
	  j += bt[current_index];
	 f=check(j,bt[current_index]);
	  bt[current_index] = 0;
	  ct[current_index] = j;
	  select_new=1;
	  vtq=ceil(alpha*bt2[current_index])+ceil((1-alpha)*vtq);
	  
	}
	
	if(f==1)
	{
	tim=vtq;
	}
    }
    
    
  for (int i = 0; i < l; i++)
    {
      tat[i] = ct[i] - at[i];
      wt[i] = tat[i] - bt2[i];
    }
  cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
  for (int i = 0; i < l; i++)
    {
      cout << "P" << (i +
		      1) << "\t" << at[i] << "\t" << bt2[i] << "\t" << ct[i]
	<< "\t" << tat[i] << "\t" << wt[i] << "\t";
      cout << endl;
    }
  float through = (float) l / total_bt;
  cout<<endl;
  cout << "Total Execution Time: " << total_bt << endl;
  cout << "Average TAT: " << avg (tat, l) << endl;
  cout << "Average WT: " << avg (wt, l) << endl;
  cout << "Throughput: " << through << endl;
  return 0;
}
