#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

struct pos
{
    int x;
    int y;
};

class node
{
public:
    int current;
    bool possibleValue[10];
    int num_possible;
    bool evaluatedValue[10];

    node()
    {
        this->current = 0;
        this->num_possible = 0;

        for (int i = 0; i < 10; ++i) {
            this->possibleValue[i] = false;
            this->evaluatedValue[i] = false;
        }


    }

    void operator=(node temp)
    {
        this->current = temp.current;
        this->num_possible = temp.num_possible;
        for (int i = 0; i < 10; ++i) {
            this->possibleValue[i] = temp.possibleValue[i];
            this->evaluatedValue[i] = temp.evaluatedValue[i];
        }
    }
};

class Sudoko
{
public:
    node input[9][9];
    node temp[9][9];

    ifstream input_file;
    ofstream output_file;

    ////////////////////////////////////////

    Sudoko()
    {
        input_file.open("in2.txt");
        output_file.open("output.txt");
    }

    bool read()
    {
        int t;
        for (int i = 0; i < 9 ; ++i) {
            for (int j = 0; j < 9; ++j) {
                input_file >> t;
                if(t == 0)
                {
                    input[i][j].current = t;
                    for (int k = 1; k < 10; ++k) {
                        input[i][j].num_possible = 9;
                        input[i][j].possibleValue[k] = true;
                    }

                }
                else if( t == -1)
                    return false;
                else
                    input[i][j].current = t;
            }
        }
        return true;
    }

    void initialize_input()
    {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {

                if( input[i][j].current != 0)
                {
                    int index = input[i][j].current;

                    for (int k = 0; k < 9; ++k) {

                        if (input[i][k].possibleValue[index])
                        {
                            input[i][k].possibleValue[index] = false;
                            input[i][k].num_possible--;
                        }
                        if (input[k][j].possibleValue[index])
                        {
                            input[k][j].possibleValue[index] = false;
                            input[k][j].num_possible--;
                        }

                    }

                    for (int k = (i-(i%3)) ; k < ((i-(i%3))+3) ; ++k) {
                        for (int l = (j-(j%3)) ; l < ((j-(j%3))+3) ; ++l) {

                            if (input[k][l].possibleValue[index])
                            {
                                input[k][l].possibleValue[index]=false;
                                input[k][l].num_possible--;
                            }
                        }
                    }
                }
            }

        }
    }

    void copy_input()
    {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                temp[i][j] = input[i][j];
            }
        }
    }

    bool Do (pos p, stack<pos> *s)
    {
        if(temp[p.x][p.y].num_possible == 0)
            return false;

        int i=1;
        pos t;

        for (i; i < 10; i++)
        {
            if (temp[p.x][p.y].possibleValue[i])
                break;
        }

        temp[p.x][p.y].possibleValue[i] = false;
        temp[p.x][p.y].evaluatedValue[i] = true;
        temp[p.x][p.y].num_possible--;
        temp[p.x][p.y].current = i;

        int index = i;

        for (int k = 0; k < 9; ++k) {

            if (temp[p.x][k].possibleValue[index])
            {
                temp[p.x][k].possibleValue[index] = false;
                temp[p.x][k].num_possible--;
                t.x=p.x;
                t.y=k;
                s->push(t);
            }
            if (temp[k][p.y].possibleValue[index])
            {
                temp[k][p.y].possibleValue[index] = false;
                temp[k][p.y].num_possible--;
                t.x=k;
                t.y=p.y;
                s->push(t);
            }
        }
        for (int k = (p.x-(p.x%3)) ; k < ((p.x-(p.x%3))+3) ; ++k) {
            for (int l = (p.y-(p.y%3)) ; l < ((p.y-(p.y%3))+3) ; ++l) {

                if (temp[k][l].possibleValue[index])
                {
                    temp[k][l].possibleValue[index]=false;
                    temp[k][l].num_possible--;
                    t.x=k;
                    t.y=l;
                    s->push(t);
                }
            }
        }


        return true;
    }

    void unDo ( pos p , stack<pos> *s)
    {
        pos t;
        int c = temp[p.x][p.y].current;
        temp[p.x][p.y].current = 0;
        while ( !(s->empty()) )
        {
            t = s->top();
            temp[t.x][t.y].possibleValue[c] = true;
            temp[t.x][t.y].num_possible++;
            s->pop();
        }
    }

    bool LCV_DO( pos p , stack<pos> *s)
    {
        if(temp[p.x][p.y].num_possible == 0)
            return false;

        node nt;
        pos t;
        nt = temp[p.x][p.y];


        int size_min = 82;
        int index_min = 10;

        while (Do(p,s))
        {
            if(s->size() < size_min)
            {
                size_min = s->size();
                index_min = temp[p.x][p.y].current;
            }
            unDo(p,s);
        }

        temp[p.x][p.y] = nt;

        temp[p.x][p.y].possibleValue[index_min] = false;
        temp[p.x][p.y].evaluatedValue[index_min] = true;
        temp[p.x][p.y].num_possible--;
        temp[p.x][p.y].current = index_min;

        int index = index_min;

        for (int k = 0; k < 9; ++k) {

            if (temp[p.x][k].possibleValue[index])
            {
                temp[p.x][k].possibleValue[index] = false;
                temp[p.x][k].num_possible--;
                t.x=p.x;
                t.y=k;
                s->push(t);
            }
            if (temp[k][p.y].possibleValue[index])
            {
                temp[k][p.y].possibleValue[index] = false;
                temp[k][p.y].num_possible--;
                t.x=k;
                t.y=p.y;
                s->push(t);
            }
        }
        for (int k = (p.x-(p.x%3)) ; k < ((p.x-(p.x%3))+3) ; ++k) {
            for (int l = (p.y-(p.y%3)) ; l < ((p.y-(p.y%3))+3) ; ++l) {

                if (temp[k][l].possibleValue[index])
                {
                    temp[k][l].possibleValue[index]=false;
                    temp[k][l].num_possible--;
                    t.x=k;
                    t.y=l;
                    s->push(t);
                }
            }
        }

        return true;

    }

    pos MRV_Selection()
    {
        pos t;
        t.x=-1;
        t.y=-1;

        int min = 10;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if( (temp[i][j].num_possible < min) && (temp[i][j].current == 0) )
                {
                    min = temp[i][j].num_possible;
                    t.x = i;
                    t.y = j;
                }
            }
        }

        return t;
    }

    bool ForwardChecking()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if( (temp[i][j].num_possible==0) && (temp[i][j].current==0) )
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool solve()
    {
        pos pt;

        pt = MRV_Selection();
        if(pt.x == -1)
            return true;

        node nt;
        stack<pos> s;
        nt = temp[pt.x][pt.y];
        while ( LCV_DO(pt,&s) )
        {
            if( ForwardChecking() )
            {
                if( solve() )
                    return true;
            }
            unDo(pt,&s);
        }

        temp[pt.x][pt.y] = nt;
        return false;
    }

    void Print()
    {
        for (int i = 0; i < 9; i++)
        {
            if(i%3==0)
                output_file<<endl;
            for (int j = 0; j < 9; j++)
            {
                if(j%3==0)
                    output_file<<" ";
                output_file<<temp[i][j].current<<" ";
            }
            output_file<<endl;
        }

        output_file<<endl;
        output_file<<"#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#"<<endl<<endl;
    }

};



int main()
{

    Sudoko s;

    while(s.read())
    {
        s.initialize_input();
        s.copy_input();
        s.solve();
        s.Print();
    }

}
