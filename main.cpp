#include <iostream>
#include <fstream>
#define max 100
using namespace std;

ifstream f("/sudoku.txt");

//reading from the file
void read(int &n, int a[][max])
{
    f>>n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            f>>a[i][j];
    f.close();
}
//writing the solution
void write(int n, int a[][max])
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
        
    }
    cout << endl;
    
}

//method 1 - classic backtraking
bool foundSolution(int n, int a[][max])
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (a[i][j]==0)
                return false;
    
    for (int i=0; i<n; i++)
        for (int j=0; j<n-1; j++)
            for (int k=j+1; k<n; k++)
                if (a[i][j]==a[i][k] || a[j][i]==a[k][i])
                    return false;
    return true;
}

void solve(int n, int a[][max], int i, int j)
{
    int ok=0;
    for (int k = 1; k<=n; k++)
    {
        if (a[i][j]==0)
        {
            a[i][j]=k;
            ok=1;
            
        }

        write(n,a);
        if (foundSolution(n, a))
        write(n, a);
        else
            if (j<n && i <n)
            {
                if (j==n-1)
                    solve(n,a,i+1,0);
                else
                    solve(n, a, i, j+1);
            }
        if (ok)
        a[i][j]=0;
    }
    
}
//method 2 - killer sudoku
int sum(int n)
{
    int s=0;
    for (int i=1; i<=n; i++)
        s+=i;
    return s;
}


bool foundSolutionKiller(int n, int a[][max], int s)
{

    
    int sumL=0, sumC=0;
    for (int i=0; i<n; i++)
    {
        sumL=0;
        sumC=0;
        for (int j=0; j<n; j++)
        {
            sumL+=a[i][j];
            sumC+=a[j][i];
            
        }

        if (sumL!=s || sumC!=s)
            return false;
        
    }
    
    for (int i=0; i<n; i++)
        for (int j=0; j<n-1; j++)
            for (int k=j+1; k<n; k++)
                if (a[i][j]==a[i][k] || a[j][i]==a[k][i])
                    return false;
    
    return true;
}


void solveKiller(int n, int a[][max], int s,int i, int j)
{
    int ok=0;
    for (int k = 1; k<=n; k++)
    {
        if (a[i][j]==0)
        {
            a[i][j]=k;
            ok=1;
        }

        if (foundSolutionKiller(n, a, s))
        write(n, a);
        else
            if (j<n && i <n)
            {
                if (j==n-1)
                    solveKiller(n,a,s,i+1,0);
                else
                    solveKiller(n, a, s,i, j+1);
            }
        if (ok)
        a[i][j]=0;
    }
    
}

        
//both methods have similar performances, depending on the size of
//the table and case, for example on a 6x6 table, there are
//6^36 possible cases

int main()
{
    int choice;
    int size, table[max][max];
    read(size, table);
    write(size, table);
    cout << "What method do you want to use? Normal/Killer (1/2): ";
    cin >> choice;
    switch (choice) {
        case 1:
            solve(size, table, 0, 0);
            break;
        case 2:
            solveKiller(size, table, sum(size),0, 0);

        default:
            break;
    }
    
    
}

