/*
Minimize Cashflow

Ritvik - 2020A7PS1723H
Ansh Gupta - 2020A7PS0259H
Ishaan Srivastava - 2020A7PS2071H
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int numberOfTransactions = 0;

/*  Function to calculate the maximum and the minimum value of the net difference 
    between the money taken and given by a Friend  */
pair<int, int> getMinMax(vector<int> &netDifference, int N) {
    int maxIndex = 0;
    int minIndex = 0;

    for(int i=1; i<N; i++) {
        if(netDifference[i] < netDifference[minIndex])
            minIndex = i;
        if(netDifference[i] > netDifference[maxIndex])
            maxIndex = i;
    }

    return {maxIndex, minIndex};
}

// Function to get the transactions needed for minimum cashflow
void minimizeCashFlow(vector<int> &netDifference, int N, vector< vector<int> > &graph, int value) {

    pair<int, int> max_min = getMinMax(netDifference, N);
    int maxValue = max_min.first, minValue = max_min.second;

    if(netDifference[maxValue] == 0 && netDifference[minValue] == 0)
        return;

    int transactionAmount = netDifference[maxValue] < -netDifference[minValue] ? netDifference[maxValue] : -netDifference[minValue];
    netDifference[maxValue] -= transactionAmount;
    netDifference[minValue] += transactionAmount;

    if(minValue == value || maxValue == value || value == -1)
        cout<<"F"<<minValue+1<<" pays "<<transactionAmount<<" to F"<<maxValue+1<<endl;
    else {
        graph[minValue][maxValue] += transactionAmount;
        numberOfTransactions--;
    }

    numberOfTransactions++;

    minimizeCashFlow(netDifference, N, graph, value);
}

// Function to get the net difference in the money given and taken calculated for every Friend 
void calculateNetDifference(vector< vector<int> > &graph, int N) {
    vector<int> netDifference(N, 0);

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) 
            netDifference[i] += (graph[j][i] - graph[i][j]);

    minimizeCashFlow(netDifference, N, graph, -1);
}

/*  Function to get the net difference of money given and taken for 
    every Friend that had a transaction with the person leaving  */
void calculateNetDifference(vector< vector<int> > &graph, int N, int value) {
    vector<int> netDifference(N, 0);
    int netAmount = 0;

    for(int i=0; i<N; i++) {
        netDifference[i] += (graph[value][i] - graph[i][value]);
        netAmount += netDifference[i];
        graph[value][i] = 0;
        graph[i][value] = 0;
    }

    netDifference[value] = -netAmount;
        
    minimizeCashFlow(netDifference, N, graph, value);
}

// Function to take input of the transactions from the user.
void getTransactions(vector< vector<int> > &graph, int numberFriends) {

    int n;
    cout<<"\nEnter number of transactions: ";
    cin>>n;

    int moneyFrom = 0, moneyTo = 0, amount = 0;

    for(int i=0; i<n; i++){
        cout<<"\nFor transaction "<<i+1<<": "<<endl;

        cout<<"Enter the Friend (numbered from 1 to "<<numberFriends<<") that gives money: ";
        cin>>moneyFrom;

        cout<<"Enter the Friend (numbered from 1 to "<<numberFriends<<") that takes money: ";
        cin>>moneyTo;

        cout<<"Enter the amount: ";
        cin>>amount;

        graph[moneyTo-1][moneyFrom-1] += amount;
    }
}

int main() {

    int n;
    cout<<"Enter number of friends: ";
    cin>>n;

    vector< vector<int> > graph(n , vector<int>(n, 0));

    getTransactions(graph, n);

    int choice = 0;
    cout<<"\nIs there any particular order in which any of the Friend are leaving? \n0 for no\n1 for yes"<<endl;
    cout<<"Please enter your choice: ";
    cin>>choice;

    cout<<endl;

    int m;

    string noTransaction = "There are no necessary transactions";

    // If the user selects to specify some priority for the settlement of transactions.
    if(choice == 1) {
        cout<<"\nEnter number of Friends leaving early: ";
        cin>>m;

        cout<<endl;

        vector<int> order(m);
        int input = 0;

        for(int i=0; i<m; i++) {
            // Inputs to be given in 1 Indexing
            cout<<"Enter the "<<i+1<<"-th person leaving: ";
            cin>>input;
            order[i] = input-1;
        } 

        for(int i=0; i<m; i++) {
            numberOfTransactions = 0;

            cout<<"\nDoing Settlements for F"<<order[i]+1<<endl;
            calculateNetDifference(graph, n, order[i]);
            
            if(numberOfTransactions == 0)
                cout<<noTransaction<<endl;
        }
    }

    numberOfTransactions = 0;

    // The final check for the Friends still present in the graph
    if(n != m) {
        cout<<"The Final Transactions between the Friends still having dues: "<<endl;
        calculateNetDifference(graph, n);

        if(numberOfTransactions == 0)
            cout<<noTransaction<<endl;
    }

    cout<<"\nThe above sequence of transactions is a way to minimize the cash flow between the n Friends.";
    
    return 0;
}