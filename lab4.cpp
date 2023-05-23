#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <iostream>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;
struct process
{
    char name[3];
    int start;
    int service;
    int finish;
    int waiting;
    queue<int> starts;
    int pr;
    int tr;
    queue<int> periods;
};

// function used for priority_queue to sort the priority_queue with the min service time first
struct getSmallestRem
{
    bool operator()(process const &p1, process const &p2)
    {
        //  if 2 process has the same service time the one who came first
        // sorted on the top
        if (p1.service == p2.service)
        {
            return p1.start > p2.start;
        }
        return p1.service > p2.service;
    }
};
// function used for priority_queue to sort the priority_queue with the min priority first
struct priority_fb
{
    bool operator()(process const &p1, process const &p2)
    {
        //  if 2 process has the same priorty time the one who came first
        // sorted on the top
        if (p1.pr == p2.pr)
        {
            return p1.start > p2.start;
        }
        return p1.pr > p2.pr;
    }
};
// function used for priority_queue to sort the priority_queue with the max priority first
struct aging
{
    bool operator()(process const &p1, process const &p2)
    {
        //  if 2 process has the same service time the one who came first
        // sorted on the top
       if (p1.pr == p2.pr)
        {
            if (p1.starts.empty() &&  p2.starts.empty() )
                return p1.start>p2.start;
            if (p1.starts.empty())
                return p1.start > (p2.starts.back()+p2.periods.front());
            if (p2.starts.empty())
                return p2.start > (p1.starts.back()+p1.periods.front());
            //if (!p1.starts.empty() && ! p2.starts.empty())
                return p1.starts.back()> p2.starts.back();
     //   printf("equal clash %s pr %d and %s pr %d\n",p1.name,p1.pr,p2.name,p2.pr);
        }
       // printf("clash %s pr %d and %s pr %d\n",p1.name,p1.pr,p2.name,p2.pr);
        return p1.pr < p2.pr;
    }
};
// function used for priority_queue to sort the priority_queue with the max Response Ratio Next ratio first
struct getSmallestRatio
{
    bool operator()(process const &p1, process const &p2)
    {
        //  if 2 process has the same service time the one who came first
        // sorted on the top
        if (float(p1.waiting + p1.service) / float(p1.service) == float(p2.waiting + p2.service) / float(p2.service))

        {
            return p1.start > p2.start;
        }
        return (float(p1.waiting + p1.service) / float(p1.service)) < (float(p2.waiting + p2.service) / float(p2.service));
    }
};

// functions used in our program
// ******************************

// for printing the header of the file
void printTitle(string line3);
// roundRobin algo
void RR(queue<process> q, char *des[], int proc, int outType, string line3, int processNo);
// FCFS trace
void FCFSa(queue<process> q, string line3);
// FCFS stats
void FCFSb(queue<process> q);
// Highest Response Ratio Next algorithm
void HRRN(queue<process> q, string line3, int outType);
// Highest Response Ratio Next trace
void HRRNA(int NoOfPro, process procDetails[], process listProc[], string line3);
// Highest Response Ratio Next stats
void HRRNB(int NoOfPro, process procDetails[]);
// Shortest remaining time
void SRT(int outType, string line3, queue<process> q);
// Shortest remaining time  trace
void SRTA(int NoOfPro, string line3, process listProc[], process procDetails[]);
// Shortest remaining time stats
void SRTB(int NoOfPro, process procDetails[]);
// Shortest process next
void SPN(int outType, string line3, queue<process> q);
// Shortest process next trace
void SPNA(int NoOfPro, process procDetails[], string line3, process listProc[]);
// Shortest process next stats
void SPNB(int NoOfPro, process procDetails[]);
// feedback algorithm
void FB(queue<process> q, char *des[], int proc, int outType, string line3, int processNo);
// feedback 2i algorithm
void FB2i(queue<process> q, char *des[], int proc, int outType, string line3, int processNo);
// aging algorithm
void Ag(queue<process> q, char *des[], int proc, int outType, string line3, int processNo);
// ************************************************************************************************

int main()
{
    // reading input from std using cin
    char buff[80];
    cin >> buff;
    // getting outputtype 1 for trace 0 for stats
    int outType = strcmp(buff, "trace") == 0 ? 1 : 0;
    // getting array of algorithms types
    cin >> buff;
    // separate the algorithms types and save the in array
    char *des[50];
    des[0] = strtok(buff, ",");
    int i = 0;
    while (des[i] != NULL)
    {
        i++;
        des[i] = strtok(NULL, ",");
    }
    int algoCount = i;
    char line3[20];
    // read the limit of processing time
    cin >> line3;
    // reading the number of processes
    int processNo;
    cin >> processNo;
    // reading the processes and store them in a queue of struct
    queue<struct process> q;
    char buffer[80];
    for (i = 0; i < processNo; i++)
    {
        // separate the start , service and name and store them in struct
        process x;
        cin >> buffer;
        strcpy(x.name, strtok(buffer, ","));
        x.start = stoi(strtok(NULL, ","));
        x.service = stoi(strtok(NULL, ","));
        // push the struct into the queue
        q.push(x);
    }

    queue<struct process> temp;
    // loop over the algorithms
    for (int proc = 0; proc < algoCount; proc++)
    {
        // convert the algorithm name from char to int and switch over it
        switch (int(des[proc][0]) - '0')
        {
        case 1:
            // FCFS algorithm
            if (outType == 1)
            {
                FCFSa(q, line3);
            }
            else
            {
                FCFSb(q);
            }
            break;
        case 2:
            // round robin algorithm
            RR(q, des, proc, outType, line3, processNo);
            break;
        case 3:
            // shortest process next
            SPN(outType, line3, q);
            break;

        case 4:
            // Shortest remaining time
            SRT(outType, line3, q);
            break;
        case 5:
            // Highest Response Ratio Next
            HRRN(q, line3, outType);
            break;
        case 6:
            // feedback
            FB(q, des, proc, outType, line3, processNo);
            break;
        case 7:
            //  feedback with 2i
            FB2i(q, des, proc, outType, line3, processNo);
            break;
        case 8:
            // agging
            Ag(q, des, proc, outType, line3, processNo);
            break;
        default:
            break;
        }
    }
    return 0;
}
// First come first serve
void FCFSa(queue<process> q, string line3)
{
    cout << "FCFS  ";
    // printing the header
    printTitle(line3);
    cout << "------------------------------------------------" << endl;
    // initialization
    int start = 0, end = 0, newStart = 0, pro = 0;
    queue<process> temp;
    int i;
    // getting values out of queue and push them in temp queue
    while (!q.empty())
    {
        process current = q.front();
        temp.push(q.front());
        q.pop();
        //  print name
        printf("%s     |", current.name);
        //  update the start time
        start = current.start;
        // store the processNo
        pro++;
        int time = current.service;
        // check if the process needs a newStart or not
        // it needs a newStart if another process was executing when it came so it must wait for the runnning to finish first
        if (start <= end && pro != 1)
        {
            newStart = end;
        }
        int s = start;
        //  looping over the processing time
        for (i = 0; i < stoi(line3); i++)
        {
            //  printing the first process
            if (pro == 1)
            {
                // if running now pring *
                if (start == i && time != 0)
                {
                    printf("*|");
                    time--;
                    start++;
                }
                // it will never wait so else it will print space
                else
                {
                    printf(" |");
                }
                //  update the end to be used as the start of the next process
                end = current.start + current.service;
            }
            //  printing the rest processes if it needed to start but there is another one running
            // so it will wait
            else if (i < end && start <= i)
            {

                printf(".|");
            }
            // when the running process finished it will enter and print *
            else if (newStart <= i && time != 0)
            {
                printf("*|");
                time--;
            }
            // when it finishes it will print space
            else
            {
                printf(" |");
            }
        }
        //  update the end to be used as a start for the next process
        end = newStart + current.service;
        printf(" \n");
    }
    printf("------------------------------------------------\n\n");
}

// First come first serve stats
void FCFSb(queue<process> q)
{
    cout << "FCFS\n";
    process pr[q.size()];
    int i = 0;
    queue<process> temp;
    //  poping the queue into a list
    while (!q.empty())
    {
        pr[i] = q.front();
        temp.push(q.front());
        q.pop();
        i++;
    }
    // printing the name of the process
    cout << "Process    |";
    for (i = 0; i < temp.size(); i++)
    {
        printf("%3s  |", pr[i].name);
    }
    // print the arrival
    cout << "\nArrival    |";
    for (i = 0; i < temp.size(); i++)
    {
        printf("%3d  |", pr[i].start);
    }
    //  print the service time
    cout << "\nService    |";
    for (i = 0; i < temp.size(); i++)
    {
        printf("%3d  |", pr[i].service);
    }
    cout << " Mean|" << endl;
    cout << "Finish     |";
    int prevFinish = 0, currentFinish = 0;
    int finish[temp.size()];
    //  printing the finish time
    for (i = 0; i < temp.size(); i++)
    {
        //  first process finish time is the start time + service time
        if (i == 0)
        {
            currentFinish = pr[i].start + pr[i].service;
        }
        // if it came while another process is running it will be the prevFinish + service
        else if (pr[i].start < prevFinish)
        {
            currentFinish = prevFinish + pr[i].service;
        }
        //  else it will be its start+service
        else
        {
            currentFinish = pr[i].start + pr[i].service;
        }
        // printing finish time
        printf("%3d  |", currentFinish);
        finish[i] = currentFinish;
        prevFinish = currentFinish;
    }
    cout << "-----|" << endl;
    cout << "Turnaround |";
    int turnAround[q.size()];
    float sum = 0;
    // printing turnAround finish-start time
    for (i = 0; i < temp.size(); i++)
    {
        turnAround[i] = finish[i] - pr[i].start;
        sum += turnAround[i];
        printf("%3d  |", turnAround[i]);
    }
    //  printing the mean
    printf("%5.2f|", sum / float(temp.size()));
    // printing the normTurn
    cout << "\nNormTurn   |";
    float NormTurn = 0.0;
    sum = 0;
    for (i = 0; i < temp.size(); i++)
    {
        NormTurn = float(turnAround[i]) / float(pr[i].service);
        sum += NormTurn;
        // if(turnAround[i]<10)printf(" ");
        printf("%5.2f|", NormTurn);
    }
    // getting the mean
    printf("%5.2f|\n\n", sum / temp.size());
}
// Shortest process next
void SPN(int outType, string line3, queue<process> q)
{
    // initializations
    priority_queue<struct process, vector<struct process>, getSmallestRem> prQueue;
    int NoOfPro = q.size();
    struct process procDetails[NoOfPro];
    int i = 0;
    process listProc[stoi(line3)];
    // putting the queue into a list
    while (!q.empty())
    {
        procDetails[i] = q.front();
        i++;
        q.pop();
    }
    int k;
    int kp = 0;
    int temp = 0;

    //  looping over the processinng time
    for (i = 0; i < stoi(line3); i++)
    {
        k = 0;
        // loooping over the number of processses
        while (k < NoOfPro)
        {
            // if process satrt time came push it into the priority queue
            if (procDetails[k].start == i)
            {
                prQueue.push(procDetails[k]);
            }
            k++;
        }
        // getting the shortest process time and assign its end and pop it out of priority queue
        //  save its value in a list of process
        if (temp == 0 && prQueue.size() != 0)
        {
            listProc[kp] = prQueue.top();
            listProc[kp].finish = i + prQueue.top().service;
            listProc[kp].start = i;
            kp++;
            temp = prQueue.top().service - 1;
            prQueue.pop();
        }
        // there is a running process so dec the service time (temp)
        else
        {
            temp = temp - 1;
        }
        if (prQueue.size() == 0 && temp < 0)
        {
            temp = 0;
        }
    }
    //  rearrange the listof process to ease the printig process
    k = 0;
    while (k < NoOfPro)
    {
        int ih = 0;
        while (ih < NoOfPro)
        {
            if (strcmp(listProc[ih].name, procDetails[k].name) == 0)
            {
                procDetails[k].finish = listProc[ih].finish;
                break;
            }
            ih++;
        }
        k++;
    }
    //  it needed trace
    if (outType == 1)
    {
        SPNA(NoOfPro, procDetails, line3, listProc);
    }
    //  if needed stats
    if (outType == 0)
    {
        SPNB(NoOfPro, procDetails);
    }
}
// shortest process next trace
void SPNA(int NoOfPro, process procDetails[], string line3, process listProc[])
{
    cout << "SPN   ";
    // printing the header title
    printTitle(line3);
    cout << "------------------------------------------------" << endl;
    process current;
    int k = 0;
    int ih, i;
    //  looping over the number of processes
    while (k < NoOfPro)
    {
        printf("%s     |", procDetails[k].name);
        ih = 0;
        //  finding the right element from the array which has the same name
        //  to print with the same order
        while (ih < NoOfPro)
        {
            if (strcmp(listProc[ih].name, procDetails[k].name) == 0)
            {
                current = listProc[ih];
            }
            ih++;
        }
        procDetails[k].finish = current.finish;
        for (i = 0; i < stoi(line3); i++)
        {
            // if process is waiting print
            if (i >= procDetails[k].start && i < current.start)
            {
                printf(".|");
            }
            //  if running print *
            else if (i >= current.start && i < current.finish)
            {
                printf("*|");
            }
            // else space
            else
                printf(" |");
        }
        printf(" \n");
        k++;
    }
    cout << "------------------------------------------------\n"
         << endl;
}

// shortest process next stats
void SPNB(int NoOfPro, process procDetails[])
{
    printf("SPN\n");
    int i;
    printf("Process    |");
    // printing process name
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3s  |", procDetails[i].name);
    }
    // printing process arrival
    printf("\nArrival    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].start);
    }
    // printing process service
    printf("\nService    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].service);
    }
    printf(" Mean|");
    // printing process finish
    printf("\nFinish     |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].finish);
    }
    printf("-----|");
    float sum = 0;
    //     printing process turnarround finish-start
    float turnAround[NoOfPro];
    printf("\nTurnaround |");
    for (i = 0; i < NoOfPro; i++)
    {
        turnAround[i] = procDetails[i].finish - procDetails[i].start;
        printf("%3d  |", procDetails[i].finish - procDetails[i].start);
        sum += turnAround[i];
    }
    // printing process normturn turnAround/service
    printf("%5.2f|", sum / float(NoOfPro));
    printf("\nNormTurn   |");
    sum = 0;
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%5.2f|", turnAround[i] / float(procDetails[i].service));
        sum += turnAround[i] / float(procDetails[i].service);
    }
    printf("%5.2f|\n\n", sum / float(NoOfPro));
}

// Shortest remaining time
void SRT(int outType, string line3, queue<process> q)
{
    //    initialization
    int i;
    priority_queue<struct process, vector<struct process>, getSmallestRem> prQueue;
    int NoOfPro = q.size();
    struct process procDetails[NoOfPro];
    i = 0;
    process listProc[stoi(line3)];
    //  getting the queue put in array
    while (!q.empty())
    {
        procDetails[i] = q.front();
        i++;
        q.pop();
    }
    int k;
    //  loop over the procssing time
    for (i = 0; i < stoi(line3); i++)
    {
        k = 0;
        // loop over the no of processes and if start arrives push in priority queue
        while (k < NoOfPro)
        {
            if (procDetails[k].start == i)
            {
                prQueue.push(procDetails[k]);
            }
            k++;
        }
        if (prQueue.size() != 0)
        {
            // save the top of the priority queue in array of processes
            listProc[i] = prQueue.top();
            process temp = prQueue.top();
            //  dec the service time
            temp.service = temp.service - 1;
            prQueue.pop();
            // if service time doesn't finish push it again in priorty queue
            if (temp.service != 0)
            {
                prQueue.push(temp);
            }
            else
            //  find the process in the array using the process name and assig finsh to it
            {
                k = 0;
                while (k < NoOfPro)
                {

                    if (strcmp(procDetails[k].name, temp.name) == 0)
                    {
                        procDetails[k].finish = i + 1;
                    }
                    k++;
                }
            }
        }
    }
    //  if trace
    if (outType == 1)
    {
        SRTA(NoOfPro, line3, listProc, procDetails);
    }
    // it stats
    if (outType == 0)
    {
        SRTB(NoOfPro, procDetails);
    }
}
// Shortest remaining time trace
void SRTA(int NoOfPro, string line3, process listProc[], process procDetails[])
{
    cout << "SRT   ";
    printTitle(line3);
    cout << "------------------------------------------------" << endl;
    int k = 0;
    int i;
    // printing the processes trace
    while (k < NoOfPro)
    {
        printf("%s     |", procDetails[k].name);
        for (i = 0; i < stoi(line3); i++)
        {
            // if waiting
            if (i >= procDetails[k].start && i < procDetails[k].finish && !strcmp(listProc[i].name, procDetails[k].name) == 0)
            {
                printf(".|");
            }
            // if running
            else if (strcmp(listProc[i].name, procDetails[k].name) == 0)
            {
                printf("*|");
            }
            else
                printf(" |");
        }
        printf(" \n");
        k++;
    }
    cout << "------------------------------------------------\n"
         << endl;
}
// Shortest remaining time stats
void SRTB(int NoOfPro, process procDetails[])
{
    printf("SRT\n");
    printf("Process    |");
    // printing name
    int i;
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3s  |", procDetails[i].name);
    }
    // printing Arrival

    printf("\nArrival    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].start);
    }
    //  printing service
    printf("\nService    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].service);
    }
    printf(" Mean|");
    //  printing finish

    printf("\nFinish     |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].finish);
    }
    printf("-----|");
    float sum = 0;
    float turnAround[NoOfPro];
    //  printing turnaround
    printf("\nTurnaround |");
    for (i = 0; i < NoOfPro; i++)
    {
        turnAround[i] = procDetails[i].finish - procDetails[i].start;
        printf("%3d  |", procDetails[i].finish - procDetails[i].start);
        sum += turnAround[i];
    }
    // mean
    printf("%5.2f|", sum / float(NoOfPro));
    //  printing nNormTurn
    printf("\nNormTurn   |");
    sum = 0;
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%5.2f|", turnAround[i] / float(procDetails[i].service));
        sum += turnAround[i] / float(procDetails[i].service);
    }
    // mean
    printf("%5.2f|\n\n", sum / float(NoOfPro));
}

//  highest ratio response next
void HRRN(queue<process> q, string line3, int outType)
{
    //   initialization
    priority_queue<struct process, vector<struct process>, getSmallestRatio> prQueue;
    queue<struct process> tempQueue;
    int NoOfPro = q.size();
    struct process procDetails[NoOfPro];
    int i;
    i = 0; //  initio

    //  pop the queue into an array
    process listProc[stoi(line3)];
    while (!q.empty())
    {
        procDetails[i] = q.front();
        procDetails[i].waiting = 0;
        i++;
        q.pop();
    }

    int k;
    int kp = 0;
    int temp = 0;
    // loop over the processing time
    for (i = 0; i < stoi(line3); i++)
    {
        k = 0;
        //  loop over the no of processes
        while (k < NoOfPro)
        {
            // if start arrives then push process in priority queue
            if (procDetails[k].start == i)
            {
                prQueue.push(procDetails[k]);
            }
            k++;
        }
        // assign finish to each process if the running is finished
        if (temp == 0 && prQueue.size() != 0)
        {
            listProc[kp] = prQueue.top();
            listProc[kp].finish = i + prQueue.top().service;
            listProc[kp].start = i;
            kp++;
            temp = prQueue.top().service - 1;
            prQueue.pop();
        }
        // if any process is running dec the temp
        //  and increase the waiting of all prcesses and push them back to priorty queue
        else
        {
            temp = temp - 1;
            while (prQueue.size() != 0)
            {
                process current = prQueue.top();
                current.waiting++;
                tempQueue.push(current);
                prQueue.pop();
            }
            while (!tempQueue.empty())
            {
                prQueue.push(tempQueue.front());
                tempQueue.pop();
            }
        }
        // if priority queu is empty assign temp to 0to be able to add to queue
        if (prQueue.size() == 0 && temp < 0)
        {
            temp = 0;
        }
    }
    k = 0;
    // arrange the processes to add finish
    while (k < NoOfPro)
    {
        int ih = 0;
        while (ih < NoOfPro)
        {
            if (strcmp(listProc[ih].name, procDetails[k].name) == 0)
            {
                procDetails[k].finish = listProc[ih].finish;
                break;
            }
            ih++;
        }
        k++;
    }
    //  if trace
    if (outType == 1)
    {
        HRRNA(NoOfPro, procDetails, listProc, line3);
    }
    //  if stats
    if (outType == 0)
    {
        HRRNB(NoOfPro, procDetails);
    }
}
//  highest ratio response next trace
void HRRNA(int NoOfPro, process procDetails[], process listProc[], string line3)
{
    cout << "HRRN  ";
    printTitle(line3);
    cout << "------------------------------------------------" << endl;
    process current;
    int k = 0;
    int ih;
    // printing the processes
    while (k < NoOfPro)
    {
        printf("%s     |", procDetails[k].name);
        ih = 0;
        while (ih < NoOfPro)
        {
            if (strcmp(listProc[ih].name, procDetails[k].name) == 0)
            {
                current = listProc[ih];
            }
            ih++;
        }
        procDetails[k].finish = current.finish;
        int i;
        // looping over the procesor time
        for (i = 0; i < stoi(line3); i++)
        {
            // waiting
            if (i >= procDetails[k].start && i < current.start)
            {
                printf(".|");
            }
            // running
            else if (i >= current.start && i < current.finish)
            {
                printf("*|");
            }
            else
                printf(" |");
        }
        printf(" \n");
        k++;
    }
    cout << "------------------------------------------------\n"
         << endl;
}
// highest ratio response next stats
void HRRNB(int NoOfPro, process procDetails[])
{
    printf("HRRN\n");
    printf("Process    |");
    //  printing process name
    int i;
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3s  |", procDetails[i].name);
    }
    //  printing arrival
    printf("\nArrival    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].start);
    }
    // printing service
    printf("\nService    |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].service);
    }
    printf(" Mean|");
    //  printing finish
    printf("\nFinish     |");
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%3d  |", procDetails[i].finish);
    }
    printf("-----|");
    float sum = 0;
    float turnAround[NoOfPro];
    //  printing tirnaround
    printf("\nTurnaround |");
    for (i = 0; i < NoOfPro; i++)
    {
        turnAround[i] = procDetails[i].finish - procDetails[i].start;
        printf("%3d  |", procDetails[i].finish - procDetails[i].start);
        sum += turnAround[i];
    }
    printf("%5.2f|", sum / float(NoOfPro));
    //  printing normturn
    printf("\nNormTurn   |");
    sum = 0;
    for (i = 0; i < NoOfPro; i++)
    {
        printf("%5.2f|", turnAround[i] / float(procDetails[i].service));
        sum += turnAround[i] / float(procDetails[i].service);
    }
    printf("%5.2f|\n\n", sum / float(NoOfPro));
}
// printing header
void printTitle(string line3)
{
    int title = 0;
    for (int k = 0; k <= stoi(line3); k++)
    {
        printf("%d ", title);
        title++;
        if (title > 9)
            title = 0;
    }
    printf("\n");
}
// Round Robin with quantum Q
void RR(queue<process> q, char *des[], int proc, int outType, string line3, int processNo)
{
    // strtok to the input quntum
    strtok(des[proc], "-");
    int period = stoi(strtok(NULL, ","));
    int time = 1;
    queue<struct process> qq;
    queue<struct process> done;
    queue<struct process> temp1;
    queue<struct process> temp2;

    // take a copy from thr original data to be printed
    while (!q.empty())
    {
        temp1.push(q.front());
        temp2.push(q.front());
        q.pop();
    }
    while (!temp2.empty())
    {
        q.push(temp2.front());
        temp2.pop();
    }

    // loop to catch the first process for the exection
    while (qq.empty())
    {
        process current;
        current = q.front();
        q.pop();
        // pop the first element of the queue and check if it is time to start
        if (current.start + 1 <= time)
        {
            // set the first time of the process for running
            current.starts.push(time);
            // if the serving time of the process > quantum time
            // then increment the time with the quantum value
            // otherwise increament the time with the serving time of the process
            if (current.service >= period)
            {
                time = time + period;
                current.service = current.service - period;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            // loop on the original process to check if there is a process need to start and join the ready queue
            for (int a = current.starts.front(); a < time + 1; a++)
            {
                for (int b = 0; b < q.size(); b++)
                {
                    process old = q.front();
                    q.pop();
                    if (old.start + 1 <= a)
                    {
                        qq.push(old);
                    }

                    else
                    {
                        q.push(old);
                    }
                }
            }
            // push the process back in the ready queue if there is a remaining service time
            if (current.service)
            {
                qq.push(current);
            }
            // otherwise push the process in the done queue to be ready for printing
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }

        // push the process back to the original queue if it still early for it to be ready
        else
        {
            q.push(current);
        }
    }

    while (!qq.empty())
    {

        process current = qq.front();
        qq.pop();
        // pop the first element of the queue and check if it is time to start
        if (current.start + 1 <= time)
        {
            // set the first time of the process for running
            current.starts.push(time);
            // if the serving time of the process > quantum time
            // then increment the time with the quantum value
            // otherwise increament the time with the serving time of the process
            if (current.service >= period)
            {

                time = time + period;
                current.service = current.service - period;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            // loop on the original process to check if there is a process need to start and join the ready queue
            for (int a = current.starts.front(); a < time + 1; a++)
            {
                for (int b = 0; b < q.size(); b++)
                {
                    process old = q.front();
                    q.pop();
                    if (old.start + 1 == a)
                    {
                        qq.push(old);
                    }
                    else
                    {
                        q.push(old);
                    }
                }
            }
            // push the process back in the ready queue if there is a remaining service time
            if (current.service)
            {
                qq.push(current);
            }
            // otherwise push the process in the done queue to be ready for printing
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }
    }

    // add the modified data to the processes in the original copy of the queue
    while (!temp1.empty())
    {
        process t = temp1.front();
        temp1.pop();
        while (1)
        {
            process d = done.front();
            done.pop();
            if (!strcmp(t.name, d.name))
            {
                d.service = t.service;
                q.push(d);
                break;
            }
            else
                done.push(d);
        }
    }

    // choose the type of printing trace or state
    if (outType)
    {
        // print trace format
        // print the titles
        printf("RR-%d  ", period);
        printTitle(line3);
        cout << "------------------------------------------------" << endl;
        // loop on each process on the queue
        while (!q.empty())
        {
            process current = q.front();
            q.pop();
            printf("%s     |", current.name);
            int i = 1;
            // loop on the total time given
            while (i <= stoi(line3))
            {
                // start printing if we reach the start time of the process
                if (current.start + 1 <= i && current.service > 0)
                {
                    if (i == current.starts.front())
                    {
                        // start printing from the start values stored in the starts queue
                        // print * on the quantum period or on the remaining services time (choonse the smallest)
                        if (current.service < period)
                        {
                            for (int y = 0; y < current.service; y++)
                            {
                                printf("*|");
                                i++;
                                current.starts.pop();
                            }
                            current.service = 0;
                        }
                        else
                        {
                            for (int y = 0; y < period; y++)
                            {
                                printf("*|");
                                i++;
                            }
                            current.starts.pop();
                            current.service = current.service - period;
                        }
                    }
                    // print . in the waiting times of the process
                    else
                    {
                        printf(".|");
                        i++;
                    }
                }
                // print an empty pipe if the process didn't start yet or if it is ended
                else
                {
                    printf(" |");
                    i++;
                }
            }
            printf(" \n");
        }
        printf("------------------------------------------------\n\n");
    }
    else
    {
        // print state format
        // print the titles
        queue<struct process> backup;
        printf("RR-%d", period);
        printf("\n");
        printf("Process    |");
        process current;
        // print the processes' names
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            printf("%3s  |", current.name);
            backup.push(current);
        }
        printf("\n");
        printf("Arrival    |");
        // print arrival time of the processes
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.start);
            q.push(current);
        }
        printf("\n");
        printf("Service    |");
        // print service time of the processes
        while (!q.empty())
        {
            current = q.front();
            q.pop();

            printf("%3d  |", current.service);
            backup.push(current);
        }
        printf(" Mean|");
        printf("\n");
        printf("Finish     |");
        // print finish time of the processes
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.finish);
            q.push(current);
        }
        printf("-----|");
        printf("\n");
        printf("Turnaround |");
        // print turnaround time of the processes
        float tr_mean = 0;
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            current.tr = current.finish - current.start;
            tr_mean = tr_mean + current.tr;

            printf("%3d  |", current.tr);
            backup.push(current);
        }
        // calculate the tr mean value and print it
        tr_mean = tr_mean / processNo;
        printf("%5.2f|", tr_mean);
        printf("\n");

        printf("NormTurn   |");
        float nr_mean = 0;
        float nr = 0;
        // print Normturn time of the processes
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();
            nr = current.tr * 1.0 / current.service;
            nr_mean = nr_mean + nr;
            printf("%5.2f|", nr);
            q.push(current);
        }
        // calculate the normtr mean value and print it
        nr_mean = nr_mean / processNo;
        printf("%5.2f|", nr_mean);
        printf("\n\n");
    }
}

// Feedback with priority 2^i
void FB2i(queue<process> q, char *des[], int proc, int outType, string line3, int processNo)

{
    queue<struct process> done;
    queue<struct process> temp1;
    queue<struct process> temp2;
    priority_queue<struct process, vector<struct process>, priority_fb> temp3;
    int time = 1;

    // take a copy of the original queue
    while (!q.empty())
    {
        q.front().pr = 0;
        temp1.push(q.front());
        temp2.push(q.front());
        q.pop();
    }
    while (!temp2.empty())
    {
        q.push(temp2.front());
        temp2.pop();
    }

    // loop till catching the first process to start
    while (temp3.empty())
    {
        process current;
        current = q.front();
        q.pop();
        // if it is time for the process to start
        if (current.start + 1 <= time)
        {
            // set the quantum of the process as 2 power its priority
            int x = int(pow(2 * 1.0, current.pr * 1.0));
            // push the start time of the process
            current.starts.push(time);
            // push the quntum period of this run of the process
            current.periods.push(x);
            // increament the time by the quantum period if it > the service time
            // otherwise increament the the time by the service time and set the service time = 0
            if (current.service >= x)
            {
                time = time + x;
                current.service = current.service - x;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            // loop on the origina queue to check if there is a process need to start and enter the ready queue
            for (int a = current.starts.front(); a < time + 1; a++)
            {
                for (int b = 0; b < q.size(); b++)
                {
                    process old = q.front();
                    q.pop();
                    if (old.start + 1 <= time)
                    {
                        // if a new process enter the ready queue increament the priority of the processes if any in the ready queue by 1
                        if (temp3.size() == 1)
                        {
                            process inc = temp3.top();
                            temp3.pop();
                            inc.pr++;
                            temp3.push(inc);
                            old.pr++;
                        }
                        else if (!temp3.empty())
                        {
                            old.pr++;
                        }
                        temp3.push(old);
                    }
                    else
                    {
                        q.push(old);
                    }
                }
            }
            // push the process back to the ready queue with high priority value if there are remaining service time and there is other processes waiting in the ready queue
            // don't icreament the priority if it is the only process in the ready queue
            if (current.service)
            {
                if (temp3.size() == 1)
                {

                    process inc = temp3.top();
                    temp3.pop();
                    inc.pr++;
                    temp3.push(inc);
                    current.pr++;
                }
                else if (!temp3.empty())
                {
                    current.pr++;
                }
                temp3.push(current);
            }
            // push the process in the done queue if the process ended to be printed
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }
        else
        {
            q.push(current);
        }
    }
    while (!temp3.empty())
    {
        int b = 0;
        // loop on the origina queue to check if there is a process need to start and enter the ready queue
        while (b < q.size())
        {
            b++;
            process old = q.front();
            q.pop();
            // if it is time for the process to start
            if (old.start + 1 <= time)
            {
                b = 0;
                // set the quantum of the process as 2 power its priority
                int x = int(pow(2 * 1.0, old.pr * 1.0));
                // push the start time of the process
                old.starts.push(time);
                // push the quntum period of this run of the process
                old.periods.push(x);
                // increament the time by the quantum period if it > the service time
                // otherwise increament the the time by the service time and set the service time = 0
                if (old.service >= x)
                {
                    time = time + x;
                    old.service = old.service - x;
                }
                else
                {
                    time = time + old.service;
                    old.service = 0;
                }
                if (old.service)
                {
                    // push the process back to the ready queue with high priority value if there are remaining service time and there is other processes waiting in the ready queue
                    // don't icreament the priority if it is the only process in the ready queue
                    if (temp3.size() == 1)
                    {
                        if (temp3.top().pr > old.pr)
                        {
                            old.pr++;
                        }
                        else
                        {
                            process inc = temp3.top();
                            temp3.pop();
                            inc.pr++;
                            temp3.push(inc);
                            old.pr++;
                        }
                    }
                    else if (!temp3.empty())
                    {
                        old.pr++;
                    }
                    temp3.push(old);
                }
                // push the process in the done queue if the process ended to be printed
                else
                {
                    old.finish = time - 1;
                    done.push(old);
                }
            }
            else
                q.push(old);
        }

        process current = temp3.top();
        temp3.pop();
        // if it is time for the process to start
        if (current.start + 1 <= time)
        {
            // push the start time of the process
            current.starts.push(time);
            // set the quantum of the process as 2 power its priority
            int x = int(pow(2 * 1.0, current.pr * 1.0));
            // push the quntum period of this run of the process
            current.periods.push(x);
            // increament the time by the quantum period if it > the service time
            // otherwise increament the the time by the service time and set the service time = 0
            if (current.service >= x)
            {
                time = time + x;
                current.service = current.service - x;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            if (current.service)
            {
                // push the process back to the ready queue with high priority value if there are remaining service time and there is other processes waiting in the ready queue
                // don't icreament the priority if it is the only process in the ready queue
                if (!temp3.empty())
                {
                    current.pr++;
                }
                temp3.push(current);
            }
            // push the process in the done queue if the process ended to be printed
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }
    }
    // add the modified data to the processes in the original copy of the queue
    while (!temp1.empty())
    {
        process t = temp1.front();
        temp1.pop();
        while (1)
        {
            process d = done.front();
            done.pop();
            if (!strcmp(t.name, d.name))
            {
                d.service = t.service;
                q.push(d);
                break;
            }
            else
                done.push(d);
        }
    }

    // choose the type of printing trace or state
    if (outType)
    {
        // choose the trace format
        // print the titles
        printf("FB-2i ");
        printTitle(line3);
        cout << "------------------------------------------------" << endl;
        // loop on all processes in the original queue
        while (!q.empty())
        {
            process current = q.front();
            q.pop();
            printf("%s     |", current.name);
            int i = 1;
            // loop on the time interval
            while (i <= stoi(line3))
            {
                // start printing if we reach the start of the process

                if (current.start + 1 <= i && current.service > 0)
                {
                    if (i == current.starts.front())
                    {
                        int period = current.periods.front();
                        current.periods.pop();
                        // print * starting from the start values stored in the starts queue till the end of the serving time or the end of the quantum period
                        if (current.service < period)
                        {
                            for (int y = 0; y < current.service; y++)
                            {
                                printf("*|");
                                i++;
                                current.starts.pop();
                            }
                            current.service = 0;
                        }
                        else
                        {
                            for (int y = 0; y < period; y++)
                            {
                                printf("*|");
                                i++;
                            }
                            current.starts.pop();
                            current.service = current.service - period;
                            period++;
                        }
                    }
                    // print . in the waiting time of the process
                    else
                    {
                        printf(".|");
                        i++;
                    }
                }
                // print an empty pipe if the process didn'y start yet or the process is finished
                else
                {
                    printf(" |");
                    i++;
                }
            }
            printf(" \n");
        }
        printf("------------------------------------------------\n\n");
    }

    else
    {
        // choose the state format
        // print the title

        queue<struct process> backup;
        printf("FB-%di", 2);
        printf("\n");
        printf("Process    |");
        process current;
        // print the names of the processes
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            printf("%3s  |", current.name);
            backup.push(current);
        }
        printf("\n");
        // print the arrival time of the processes
        printf("Arrival    |");
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.start);
            q.push(current);
        }
        printf("\n");
        // print the service time of the processes
        printf("Service    |");
        while (!q.empty())
        {
            current = q.front();
            q.pop();

            printf("%3d  |", current.service);
            backup.push(current);
        }
        printf(" Mean|");
        printf("\n");
        // print the finish time of the processes
        printf("Finish     |");
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.finish);
            q.push(current);
        }
        printf("-----|");
        printf("\n");
        // print the turnaround of the processes
        printf("Turnaround |");
        float tr_mean = 0;
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            current.tr = current.finish - current.start;
            tr_mean = tr_mean + current.tr;

            printf("%3d  |", current.tr);
            backup.push(current);
        }
        // calculate the mean tr and print it
        tr_mean = tr_mean / processNo;
        printf("%5.2f|", tr_mean);
        printf("\n");

        // print the norm tr of the processes
        printf("NormTurn   |");
        float nr_mean = 0;
        float nr = 0;
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();
            nr = current.tr * 1.0 / current.service;
            nr_mean = nr_mean + nr;
            printf("%5.2f|", nr);
            q.push(current);
        }
        // calculate the mean norm tr and print it
        nr_mean = nr_mean / processNo;
        printf("%5.2f|", nr_mean);
        printf("\n\n");
    }
}

// Feedback with default priority 1
void FB(queue<process> q, char *des[], int proc, int outType, string line3, int processNo)
{
    int period = 1;
    queue<struct process> done;
    queue<struct process> temp1;
    queue<struct process> temp2;
    priority_queue<struct process, vector<struct process>, priority_fb> temp3;
    int time = 1;
    // take a copy of the original queue
    while (!q.empty())
    {
        q.front().pr = 0;
        temp1.push(q.front());
        temp2.push(q.front());
        q.pop();
    }
    while (!temp2.empty())
    {
        q.push(temp2.front());
        temp2.pop();
    }

    // loop to catch the first process to be ready
    while (temp3.empty())
    {
        process current;
        current = q.front();
        q.pop();
        // if it is time to start a process
        if (current.start + 1 <= time)
        {
            // put the time to starts queue of the process
            current.starts.push(time);
            // increament the time by the quantum period if the serving time > the quantum period
            // otherwise icreament the time by the service time
            if (current.service >= period)
            {
                time = time + period;
                current.service = current.service - period;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            // loop inside the quantum period to check if there is a process need to join the ready queue
            for (int a = current.starts.front(); a < time + 1; a++)
            {
                for (int b = 0; b < q.size(); b++)
                {
                    process old = q.front();
                    q.pop();
                    if (old.start + 1 <= time)
                    {
                        // if the ready queue is not empty increament the priorities of the processes in the queus
                        // otherwise insert the process without priority increament
                        if (temp3.size() == 1)
                        {

                            process inc = temp3.top();
                            temp3.pop();
                            inc.pr++;
                            temp3.push(inc);
                            old.pr++;
                        }
                        else if (!temp3.empty())
                        {
                            old.pr++;
                        }
                        temp3.push(old);
                    }
                    else
                    {
                        q.push(old);
                    }
                }
            }
            // push the process back to the ready queue if it has remaining service time
            // otherwise push it in done queue to be printed
            if (current.service)
            {
                if (temp3.size() == 1)
                {

                    process inc = temp3.top();
                    temp3.pop();
                    inc.pr++;
                    temp3.push(inc);
                    current.pr++;
                }
                else if (!temp3.empty())
                {
                    current.pr++;
                }
                temp3.push(current);
            }
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }
        else
        {
            q.push(current);
        }
    }
    // loop till all processes finish their serving time
    while (!temp3.empty())
    {
        // check if there is a process from the original queue want to join the ready queue
        for (int b = 0; b < q.size(); b++)
        {
            process old = q.front();
            q.pop();
            // if it is time to start a process
            if (old.start + 1 <= time)
            {
                // put the current time to the starts queue of the process
                b = 0;
                old.starts.push(time);
                // increament the time by the quantum period if it is < the service time
                // otherwise increament the time by the service time
                if (old.service >= period)
                {
                    time = time + period;
                    old.service = old.service - period;
                }
                else
                {
                    time = time + old.service;
                    old.service = 0;
                }
                // push the process back to the ready queue if it has remaining time
                // otherwise push it in the done queue to be printed
                if (old.service)
                {
                    // check if there is another processes in the queue increament the process priority
                    // otherwise push it without increament
                    if (temp3.size() == 1)
                    {
                        if (temp3.top().pr > old.pr)
                        {
                            old.pr++;
                        }
                        else
                        {
                            process inc = temp3.top();
                            temp3.pop();
                            inc.pr++;
                            temp3.push(inc);
                            old.pr++;
                        }
                    }
                    else if (!temp3.empty())
                    {
                        old.pr++;
                    }
                    temp3.push(old);
                }
                else
                {
                    old.finish = time - 1;
                    done.push(old);
                }
            }
            else
                q.push(old);
        }
        process current = temp3.top();
        temp3.pop();
        // if it is time to start a process
        if (current.start + 1 <= time)
        {
            // push the current time to the starts queue of the process
            current.starts.push(time);
            // increament the time by the quantum period if it is < service time
            // otherwise increament the time by the serving time of the process
            if (current.service >= period)
            {
                time = time + period;
                current.service = current.service - period;
            }
            else
            {
                time = time + current.service;
                current.service = 0;
            }
            // push the process back to the ready queue if it has remaining service time
            // otherwise push it in the done queue to be printed
            if (current.service)
            {
                // if the queue has another ready processes increament the priority of the process before pushing it
                // otherwise don't increament the priority
                if (!temp3.empty())
                {
                    current.pr++;
                }
                temp3.push(current);
            }
            else
            {
                current.finish = time - 1;
                done.push(current);
            }
        }
    }
    // add the modified data to the processes in the original copy of the queue
    while (!temp1.empty())
    {
        process t = temp1.front();
        temp1.pop();
        while (1)
        {
            process d = done.front();
            done.pop();
            if (!strcmp(t.name, d.name))
            {
                d.service = t.service;
                q.push(d);
                break;
            }
            else
                done.push(d);
        }
    }
    // choose the type of the output format
    if (outType)
    {
        // choose the trace format
        // print the titles

        printf("FB-%d  ", period);
        printTitle(line3);
        cout << "------------------------------------------------" << endl;

        while (!q.empty())
        {
            process current = q.front();
            q.pop();
            printf("%s     |", current.name);
            int i = 1;
            // loop on the time input
            while (i <= stoi(line3))
            {
                // if we reach the time of the process start
                if (current.start + 1 <= i && current.service > 0)
                {
                    // print * from the start values stored in the starts queue till the quantum period or the serving time of the process
                    if (i == current.starts.front())
                    {
                        if (current.service < period)
                        {
                            for (int y = 0; y < current.service; y++)
                            {
                                printf("*|");
                                i++;
                                current.starts.pop();
                            }
                            current.service = 0;
                        }
                        else
                        {
                            for (int y = 0; y < period; y++)
                            {
                                printf("*|");
                                i++;
                            }
                            current.starts.pop();
                            current.service = current.service - period;
                        }
                    }
                    // print . in the waiting intervals
                    else
                    {
                        printf(".|");
                        i++;
                    }
                }
                // print empty pipes if the process ended or before the start of the process
                else
                {
                    printf(" |");
                    i++;
                }
            }
            printf(" \n");
        }
        printf("------------------------------------------------\n\n");
    }

    else
    {
        // choose the state format
        // print titles

        queue<struct process> backup;
        printf("FB-%d", period);
        printf("\n");
        // print the names of processes
        printf("Process    |");
        process current;
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            printf("%3s  |", current.name);
            backup.push(current);
        }
        printf("\n");
        // print the arrival times of processes
        printf("Arrival    |");
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.start);
            q.push(current);
        }
        printf("\n");
        // print the service times of processes
        printf("Service    |");
        while (!q.empty())
        {
            current = q.front();
            q.pop();

            printf("%3d  |", current.service);
            backup.push(current);
        }
        printf(" Mean|");
        printf("\n");
        // print the finish times of processes
        printf("Finish     |");
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();

            printf("%3d  |", current.finish);
            q.push(current);
        }
        printf("-----|");
        printf("\n");
        // print the tr around times of processes
        printf("Turnaround |");
        float tr_mean = 0;
        while (!q.empty())
        {
            current = q.front();
            q.pop();
            current.tr = current.finish - current.start;
            tr_mean = tr_mean + current.tr;

            printf("%3d  |", current.tr);
            backup.push(current);
        }
        // calculate the mean tr around value then print it
        tr_mean = tr_mean / processNo;
        printf("%5.2f|", tr_mean);
        printf("\n");
        // print the norm tr times of processes
        printf("NormTurn   |");
        float nr_mean = 0;
        float nr = 0;
        while (!backup.empty())
        {
            current = backup.front();
            backup.pop();
            nr = current.tr * 1.0 / current.service;
            nr_mean = nr_mean + nr;
            printf("%5.2f|", nr);
            q.push(current);
        }
        // calculate the mean norm tr time and print it
        nr_mean = nr_mean / processNo;
        printf("%5.2f|", nr_mean);
        printf("\n\n");
    }
}

// Aging
void Ag(queue<process> q, char *des[], int proc, int outType, string line3, int processNo)
{
    {
        // strtok to get the quantum period
        strtok(des[proc], "-");
        int period = stoi(strtok(NULL, ","));
        queue<struct process> done;
        queue<struct process> temp1;
        process tempoo;
        priority_queue<struct process, vector<struct process>, aging> temp3;
        priority_queue<struct process, vector<struct process>, aging> temp2;
        int time = 0;
        // take a copy of the original queue
        while (!q.empty())
        {
            q.front().pr = q.front().service + 1;
            q.front().periods.push(period);
            temp1.push(q.front());
            temp2.push(q.front());
            q.pop();
        }
        while (!temp2.empty())
        {
            q.push(temp2.top());
            temp2.pop();
        }

        // loop till we catch the start of process
        while (temp3.empty() && time <= stoi(line3))
        {
            time++;
            process current;
            for (int l = 0; l < q.size(); l++)
            {
            current = q.front();
            q.pop();
            // if it is time to start a process
                if (current.start + 1 <= time)
                {
                    current.starts.push(time);
                    time = time + period;
                    // loop to check if there is a process from the original queue needs to join the ready state
                //    printf("initially, MY NAME IS %s\n", current.name);
                    current.pr = current.service + 1;
                    temp3.push(current);
                }
                else
                {
                    q.push(current);
                }
            }
        }
        // loop inside the time input
        while (!temp3.empty() && time <= stoi(line3))
        {
            // check if there is a process from the original queue needs to join the ready state
            for (int b = 0; b < q.size(); b++)
            {
                process old = q.front();
                q.pop();
                if (old.start + 1 <= time)
                {
                   // printf("arrived, MY NAME IS %s\n", old.name);
                    temp3.push(old);
                }
                else
                    q.push(old);
            }
            // start of execution
            process current = temp3.top();
            temp3.pop();
            // if it is time to start a process
            if (current.start + 1 <= time)
            {
                // put the current time to the time queue of the process
             //   printf("exe, MY NAME IS %s\n",current.name);
                current.starts.push(time);
                // increament the current time with the quantum period
                time = time + period;
                // if the ready queue isn't empty increament the priority of all processes inside it
                while (!temp3.empty())
                {
                    tempoo = temp3.top();
                    temp3.pop();
                    tempoo.pr++;
                    done.push(tempoo);
                }
                // restore the ready queue
                while (!done.empty())
                {
                    temp3.push(done.front());
                    done.pop();
                }
                // reset the priority of the current process to its initial value
                current.pr = current.service;
                // printf("MY NAME IS %s\n",current.name);
                temp3.push(current);
            }
            else
            {
                // printf("MY NAME IS %s\n",current.name);
                temp3.push(current);
            }
        }
        // add the modified data to the processes in the original copy of the queue
        while (!temp3.empty())
        {
            done.push(temp3.top());
            temp3.pop();
        }

        while (!temp1.empty())
        {
            process t = temp1.front();
            temp1.pop();
            while (1)
            {
                process d = done.front();
                done.pop();
                if (!strcmp(t.name, d.name))
                {
                    d.service = t.service;
                    q.push(d);
                    break;
                }
                else
                    done.push(d);
            }
        }
        // print titles
        printf("Aging ");
        printTitle(line3);
        cout << "------------------------------------------------" << endl;
        // loop on all processes
        while (!q.empty())
        {
            process current = q.front();
            q.pop();
            printf("%s     |", current.name);
            int i = 1;
            // loop on the time input
            while (i <= stoi(line3))
            {
                // if we reach the start of a process
                if (current.start + 1 <= i)
                {
                    // print * from the start values in the starts queue of the process till the end of the quantum period
                    if (i == current.starts.front())
                    {
                        for (int y = 0; y < period && i <= stoi(line3); y++)
                        {
                            printf("*|");
                            i++;
                        }
                        current.starts.pop();
                    }
                    // print . on the waiting time
                    else
                    {
                        printf(".|");
                        i++;
                    }
                }
                // print empty pipes before the start of the process
                else
                {
                    printf(" |");
                    i++;
                }
            }
            printf(" \n");
        }
        printf("------------------------------------------------\n\n");
    }
}