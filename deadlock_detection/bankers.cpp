#include "iostream"
using namespace std;

int main(){
    int m,n;
    cout << "Enter the number of processes: ";
    cin>>n;
    cout<<"Enter total number of resources:";
    cin>>m;
    int maxNeed[n][m],allocated[n][m];
    int available[m],safeSeq[n],finished[n];

    for(int i = 0; i < n; i++) finished[i] = 0;
    
    cout<<"Enter total instances of each resources: "<<endl;
    for(int i=0;i<m;i++){
        cout<<"Enter resources"<<i+1<<":";
        cin>>available[i];
    }

    cout<<"Enter allocated and max need of each process:"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"Process "<<i<<endl;
        for(int j = 0; j < m; j++){
            cout<<"Enter allocated resource " << j+1 <<":";
            cin>>allocated[i][j];
            cout<<"Enter maximum needed resource "<<j+1<<":";
            cin>>maxNeed[i][j];
        }
        cout<<endl;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            available[i] -= allocated[j][i];
        }
    }

    int completed = 0,i = 0, j = 0;
    while(completed != n){
        bool isSafe = false;
        for (i = 0; i < n; i++) {
            if(finished[i]) continue;
            
            for(j = 0; j < m; j++)
                if(maxNeed[i][j] - allocated[i][j] > available[j])
                    break;  
            
            if(j == m){
                isSafe = true;
                for(int k = 0; k < m; k++) available[k] += allocated[i][k];
                safeSeq[completed++] = i+1;
                finished[i] = 1; 
            }
        }
        if(!isSafe){
            cout<<"The system is not Deadlock safe....!";
            return 0;
        }
    }
    cout<<"The system is in safe state..."<<endl;
    cout<<"Following is the safe sequence:"<<endl;
    cout<<safeSeq[0];
    for(int i = 1; i < n;i++){
        cout<<"->"<<safeSeq[i];
    }
    return 0;
}