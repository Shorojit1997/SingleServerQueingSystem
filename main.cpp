#include<bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include<string>
using namespace std;

class CustomerDetails
{
public:
    int customarNumber;
    float a_tBefore;
    float arivalTime;
    float serviceStartTime;
    float serviceTime;
    float serviceEndTime;
    float watingTime;
    float c_time;
    float turnAroundTime;
};

class SingleServer
{

private:
    int numberOfCustomer;
    int multiplier;
    int increment;
    int mod;
    float averageUtilization;
    float averageDelay;
    float averageQueue;
    int maxTime;

    CustomerDetails *Cd;
    int *arr;
    vector<pair<pair<int,int>,int> > forPrint;


public:
    SingleServer(int NCustomer,int mul=(rand()%100),int inc=5,int mo=9)
    {
        numberOfCustomer=NCustomer;
        multiplier= mul;
        increment=inc;
        mod=mo;
    }
    int getArivalTime();
    int getServiceTime();
    void assignTime();
    void CalculateTime();
    void QueingTime();
    int numbering();
    void painting();
    void printTime();
    string to_string(int x);
};


void SingleServer::assignTime()
{
    Cd=new CustomerDetails[numberOfCustomer+5];
    int sum=0;
    for(int i=1; i<=numberOfCustomer; i++)
    {
        Cd[i].customarNumber=i;
        Cd[i].a_tBefore=getArivalTime();
        sum+=Cd[i].a_tBefore;
        Cd[i].arivalTime=sum;
        Cd[i].serviceTime=getServiceTime()+1;


        Cd[i].serviceStartTime=0;
        Cd[i].serviceEndTime=0;
        Cd[i].watingTime=0;
    }


    return;
}

void SingleServer::QueingTime()
{

    arr=new int[maxTime];
    for(int i=0; i<maxTime; i++)arr[i]=0;

    for(int i=1; i<=numberOfCustomer; i++)
    {
        for(int j=(int)Cd[i].arivalTime; j<=(int)Cd[i].serviceEndTime; j++)
        {
            arr[j]++;
        }
    }

    map<int,int> mp;
    for(int i=1; i<=maxTime; i++)
    {
        //  cout<<arr[i];
        if(arr[i]>0)
        {
            mp[arr[i]]++;
        }
    }
    for(int i=0; i<=numberOfCustomer; i++)
    {
        int cnt=0;
        for(int j=1; j<=maxTime; j++)
        {
            if(i==arr[j])
            {
                cnt++;
            }
            else
            {
                if(cnt)
                {
                    forPrint.push_back( { {j-cnt,j},i});
                }
                cnt=0;
            }
        }
    }
    sort(forPrint.begin(),forPrint.end());
    /*  for(int i=0; i<forPrint.size(); i++)
      {
          cout<<forPrint[i].first.first<<" "<<forPrint[i].first.second<<" "<<forPrint[i].second<<endl;
      }*/
    float total=0;
    for(int i=1; i<=numberOfCustomer; i++)
    {
        total+=(float)(i*mp[i]);
    }

    this->averageQueue=(total/numberOfCustomer);



    return;
}

void SingleServer::CalculateTime()
{
    float st_time=0;
    float totalUtlization=0;
    float totalDelay;

    for(int i=1; i<=numberOfCustomer; i++)
    {
        Cd[i].serviceStartTime=max(Cd[i].arivalTime,st_time);
        st_time=Cd[i].serviceStartTime+Cd[i].serviceTime;
        Cd[i].c_time=Cd[i].serviceEndTime=st_time;
        Cd[i].watingTime=Cd[i].serviceStartTime-Cd[i].arivalTime;
        Cd[i].turnAroundTime=Cd[i].serviceEndTime-Cd[i].arivalTime;


        totalUtlization+=Cd[i].serviceTime;
        totalDelay+=Cd[i].watingTime;
    }

    this->averageDelay=(totalDelay/numberOfCustomer);
    this->averageUtilization=(totalUtlization/numberOfCustomer);
    this->maxTime=(int)(Cd[numberOfCustomer].serviceEndTime+10);

    return;
}


void SingleServer::printTime()
{
    printf("\n\n Avarage Delay  of %d Customer  is                    : %.2f\n",numberOfCustomer,averageDelay);
    printf(" Avarage number of customer in queue for %d Customer  is  : %.2f\n",numberOfCustomer,averageQueue);
    printf(" Avarage Server Utilization  of %d Customer  is           : %.2f\n\n\n",numberOfCustomer,averageUtilization);



    cout<<"   AT  |  ST   |  SST  |  SET  |  WT   |  TAT\n";
    cout<<" -------------------------------------------------\n";
    for(int i=1; i<=numberOfCustomer; i++)
    {
        printf(" %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f\n",Cd[i].arivalTime,Cd[i].serviceTime,Cd[i].serviceStartTime,Cd[i].serviceEndTime,Cd[i].watingTime,Cd[i].turnAroundTime);
        cout<<" -------------------------------------------------\n";
    }

    return;
}


int SingleServer::getArivalTime()
{
    static int ariveddAt=0;
    ariveddAt=(multiplier*ariveddAt + increment)%mod;
    //ariveddAt=rand()%mod;
    return ariveddAt;
}

int SingleServer::getServiceTime()
{
    static int serviceAt=0;
    serviceAt=(multiplier*serviceAt + increment)%mod;
    //  serviceAt=rand()%mod;
    return serviceAt;
}

string SingleServer::to_string(int x)
{
    string ss="";
    while(x)
    {
        char c=(char)(x%10)+'0';
        ss=c+ss;
        x/=10;
    }
    return ss;
}


int  SingleServer::numbering()
{
    for(int i=0; i<=2*maxTime; i+=10)
    {
        int x=i*5;
        line(100+x,395,100+x,405);
        char ch[5];
        string ss=to_string(i);
        int j=0;
        for(j=0; j<ss.size(); j++)ch[j]=ss[j];
        ch[j]='\0';
        outtextxy(90+x, 410,ch);
    }
    for(int i=0; i<=numberOfCustomer; i+=1)
    {
        int x=i*50;
        line(95,400-x,105,400-x);
        char ch[5];
        string ss=to_string(i);
        int j=0;
        for(j=0; j<ss.size(); j++)ch[j]=ss[j];
        ch[j]='\0';
        outtextxy(90, 400-x,ch);
    }
    return 0;
}

void SingleServer::painting()
{

    for(int i=0; i<forPrint.size(); i+=1)
    {
        int cc=(i+5)%10;
        cc==0? ++cc:cc;
        setcolor(cc);
        settextstyle(10,0,10);
        int left=forPrint[i].first.first;
        int right=forPrint[i].first.second;
        int range=forPrint[i].second;
        range=range*50;
        left=left*5;
        right=right*5;
        setfillstyle(1,cc);
        rectangle(100+left,400-range,100+right,400);
        if(range>0)
            floodfill(101+left,401-range,cc);

    }
    return ;
}


void init(SingleServer ob)
{
    int gd = DETECT, gm;
    initwindow(800, 600);
    setfillstyle(HATCH_FILL,RED);

    line(30,400, 750, 400);
    line(100,0,100, 500);
    setcolor(WHITE);
    ob.numbering();
    ob.painting();
    return;
}

signed main()
{
    while(true)
    {
        printf("Number of Customer want to get service ? : ");
        int n;
        cin>>n;
        SingleServer ob(n);
        ob.assignTime();
        ob.CalculateTime();
        ob.QueingTime();
        ob.printTime();
        init(ob);

    }
    getch();
    return 0 ;
}
