#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

void signs(vector<string> & eq);
vector<string> split(string  eq);

class eqn
{
    map <string,float> eq;
    vector <string> vars;
public:
    eqn(){}
    eqn (string string_form)
    {
        //a constructor that binds the varaible to its coefficient in a map
        vector <string> terms;
        terms = split(string_form);
        signs(terms);
        for(int i = 0 ; i<terms.size() ; i++)
        {
            bool constant = 0;
            for(int j = 0 ; j<terms[i].length() ; j++)
            {
                constant = 0;
                if(terms[i][j] > '9' )
                //to know where the varariable name begins
                {
                    constant =1;
                    if(eq.find(terms[i].substr( j, terms[i].length()-j)) == eq.end())
                    {
                        eq[string(terms[i].substr( j, terms[i].length()-j))] = atof(terms[i].substr(0,j).c_str());
                    }
                    else
                    {
                        float holder =  atof(terms[i].substr(0,j).c_str());
                        eq[string(terms[i].substr( j, terms[i].length()-j))] +=  holder ;

                    }
                    break;

                }
            }
            if (constant == 0)
            {
                if(eq.find(string("zzz999")) == eq.end()) eq[string("zzz999")] = atof(terms[i].c_str());
                //to assure that the constant is the last thing in the map
                else
                {
                    eq[string("zzz999")] += atof(terms[i].c_str());
                }
            }

        }
    }
    ~ eqn(){}
    int num_vars()
    {
        return eq.size()-1;
    }
    float get_coef(string var)
    {
        if(eq.find(var) != eq.end())
        {
            if(var =="zzz999") return -eq[var];
            else return eq[var];
        }
        else return 0 ;
    }
    void set_coef(string var ,float value)
    {
        eq[var] = value;
    }
    vector<string> get_keys()
    {
        for(map <string,float>::iterator it = eq.begin(); it!= eq.end() ;it++)
        {
            vars.push_back(string(it->first));
        }
        return vars;
    }
    bool is_first_in_printing(string var)
    {
        bool ans=1;
        vector<string> keys = get_keys();
        for(int i=0 ; i<keys.size() ; i++)
        {
            if(keys[i] == var) break;
            else
            {
                if(get_coef(keys[i]) != 0) ans = 0;
            }
        }
        return ans;
    }
    void print()
    {
        bool first_term = 0;
        for(map <string,float>::iterator it = eq.begin(); it!= eq.end() ;it++)
        {
            if(it->second == 0 && it !=eq.end() && it->first != "zzz999" ) continue;

            else if(it->first == "zzz999")
            {
                if(it->second != 0) cout << '='<< -(it->second);
                else cout<<'='<< '0';
            }
            else if ((it->second)> 0 && !is_first_in_printing(it->first))
            {
                cout<<'+'<<it->second<<it->first;
            }

            else cout<<it->second<<it->first;
        }
        cout<<endl;
    }
    eqn add(eqn eq2)
    {
        eqn ans;
        vector <string> Vars = get_keys();
        for(int i = 0; i< Vars.size(); i++)
        {
            ans.set_coef(Vars[i], (get_coef(Vars[i]) + eq2.get_coef(Vars[i])));
        }
        Vars = eq2.get_keys();
        for(int i = 0; i< Vars.size(); i++)
        {
            ans.set_coef(Vars[i], (get_coef(Vars[i])+ eq2.get_coef(Vars[i])));
        }
        int cons = -(get_coef("zzz999")+ eq2.get_coef("zzz999"));
        ans.set_coef("zzz999", cons);
        return ans;
    }
    eqn subtract(eqn eq2)
    {
        eqn ans;
        vector <string> Vars = get_keys();
        for(int i = 0; i< Vars.size(); i++)
        {
            ans.set_coef(Vars[i], (get_coef(Vars[i]) - eq2.get_coef(Vars[i])));
        }
        Vars = eq2.get_keys();
        for(int i = 0; i< Vars.size(); i++)
        {
            ans.set_coef(Vars[i], (get_coef(Vars[i]) - eq2.get_coef(Vars[i])));
        }
        int cons = -(get_coef("zzz999") - eq2.get_coef("zzz999"));
        ans.set_coef("zzz999", cons);
        return ans;
    }
    eqn multiply(float num)
    {
        eqn ans;
        vector <string> Vars = get_keys();
        for(int i = 0; i< Vars.size(); i++)
        {
            ans.set_coef(Vars[i], (get_coef(Vars[i]) * num));
        }
        return ans;
    }
    eqn sep(string var)
    {
        eqn ans = multiply((-1)/get_coef(var));
        float cons = -1*get_coef("zzz999");
        ans.set_coef("zzz999", cons);
        return ans;
    }
    eqn substitute(string var, eqn eq)
    {
        eqn ans = eq.sep(var);
        ans = ans.multiply(get_coef(var));
        ans = add(ans);
        ans.set_coef(var, 0);
        return ans;
    }
    eqn operator+(eqn eq2)
    {
        return add(eq2);
    }
    eqn operator-(eqn eq2)
    {
        return subtract(eq2);
    }
    eqn operator*(float num)
    {
        return multiply(num);
    }
};

vector <vector<float>> crammer(vector<eqn> eqns);
eqn operator* (float num ,eqn eqn);
vector<string> all_vars(vector <eqn> eqns);
vector <vector<float>> crammer_coef(vector<eqn> eqns,string var);
void print_matrix(vector <vector <float>> matrix);
float determinant(vector <vector<float>> matrix);
vector <vector<float>>sub_matrix(vector <vector<float>> matrix , int column);
void solve(vector <eqn>eqns);
void operator<< (ostream &o , eqn  eq);
void column(vector <eqn> eqns , string var);
vector<string> complex_input(string operation);
void input(string operation, vector <eqn> eqns);

int main()
{
    string temp,operation;
    int n;
    cout<<"Enter the number of equations: ";
    cin>>n;
    cout<<"Enter the equations \n";
    vector<eqn> eqns;
    for(int i = 0; i<n ; i++)
    {
        cin>>temp;
        eqns.push_back(eqn(temp));
    }
    cin.ignore();
    while(true)
    {
        cout<<"Enter the operation you want"<<endl;
        getline( cin , operation);
        if(operation == "quit") break;
        else input(operation,eqns);
    }
}

void input(string operation, vector <eqn> eqns)

{
    if(operation == "num_vars") cout<<all_vars(eqns).size()<<endl;
    else if(operation == "D") print_matrix(crammer(eqns));
    else if(operation == "D_value") cout<<determinant(crammer(eqns))<<endl;
    else if(operation == "solve")  solve(eqns);
    else if(operation[0] == 'D' && operation.length() > 1) print_matrix(crammer_coef(eqns, operation.substr(2)));
    vector <string> Input = complex_input(operation);
    if(Input[0] == "equation") cout<<eqns[stoi(Input[1])-1];
    else if(Input[0] == "column") column(eqns, Input[1]);
    else if(Input[0] == "add") cout<<(eqns[stoi(Input[1])-1] + eqns[stoi(Input[2])-1]);
    else if(Input[0] == "subtract")  cout<<eqns[stoi(Input[1])-1] - eqns[stoi(Input[2])-1];
    else if(Input[0] == "substitute") cout<<eqns[stoi(Input[2])-1].substitute(Input[1], eqns[stoi(Input[3])-1]);
}
void column(vector <eqn> eqns , string var)
{
    for(int i = 0 ; i < eqns.size() ; i++)
    {
        cout<<eqns[i].get_coef(var)<<endl;
    }
}
void solve(vector <eqn>eqns)
{
    vector<string> vars = all_vars(eqns);
    if (vars.size() > eqns.size())
    {
        cout<<"No Solution"<<endl;
    }
    else
    {
        float Crammer = determinant(crammer(eqns));
        if (Crammer == 0) cout<<"No Solution"<<endl;
        else
        {
            for(int i = 0; i< vars.size() ; i++)
            {
                cout<<vars[i]<<'='<<determinant(crammer_coef(eqns , vars[i]))/Crammer<<endl;
            }
        }
    }
}
vector <vector<float>>sub_matrix(vector <vector<float>> matrix , int column)
{
    vector <vector<float>> sub_mat;
    vector<float> temp;
    for(int i = 1 ; i<matrix.size(); i++)
    {
        temp.clear();
        for(int k=0 ; k<matrix.size(); k++)
        {
            if(k != column)  temp.push_back(matrix[i][k]);
        }
        sub_mat.push_back(temp);
    }
    return sub_mat;
}
float determinant(vector <vector<float>> matrix)
{
    int n = matrix.size();
    vector <vector<float>> sub_mat;
    float ans = 0 ;
    if (n==2)
    {
        return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
    }
    if (n==1) return matrix[0][0];
    else
    {
        for(int i = 0 ; i< n ; i++)
        {
            sub_mat = sub_matrix(matrix , i);
            if(i%2 == 0)  {ans += (matrix[0][i])*determinant(sub_mat);}
            else  {ans -= (matrix[0][i])*determinant(sub_mat);}
        }
        return ans;
    }
}
vector <vector<float>> crammer(vector<eqn> eqns)
{
    vector <string> vars = all_vars(eqns);
    vector <vector<float>> matrix;
    vector <float> temp;
    for(int i = 0 ; i<eqns.size(); i++)
    {
        temp.clear();
        matrix.push_back(temp);
        for(int k=0 ; k<vars.size(); k++)
        {
            matrix[i].push_back(eqns[i].get_coef(vars[k]));
        }
    }
    return matrix;
}
void print_matrix(vector <vector <float>> matrix)
{
    for(int i = 0 ; i<matrix.size(); i++)
    {
        for(int k=0 ; k<matrix[i].size(); k++)
        {
            cout<<matrix[i][k]<<"\t";
        }
        cout<<endl;
    }
}
vector <vector<float>> crammer_coef(vector<eqn> eqns, string var)
{
    vector <string> vars = all_vars(eqns);
    vars[find(vars.begin() , vars.end(), var)- vars.begin()] = "zzz999";
    vector <vector<float>> matrix;
    vector <float> temp;
    for(int i = 0 ; i<eqns.size(); i++)
    {
        temp.clear();
        matrix.push_back(temp);
        for(int k=0 ; k<vars.size(); k++)
        {
            matrix[i].push_back(eqns[i].get_coef(vars[k]));
        }
    }
    return matrix;
}
vector<string> split(string  eq)
{
    //split every term and form a vector of the terms
    string temp;
    int holder= 0;
    vector <string> contents;
    for(int i =0 ; i<eq.length(); i++)
    {
        if(eq[i] == '+'||eq[i] == '-'||eq[i] == '=')
        {
            temp = eq.substr(holder,(i-holder));
            contents.push_back(temp);
            holder = i;
            if( eq[i] == '=' && eq[i+1] == '-') i++;
        }
    }
    temp = eq.substr(holder,(eq.length()-holder));
    contents.push_back(temp);
    return contents;
}
void signs(vector<string> & eq)
{
    //set a proper sign to every term
    int eq_sign =100000;
    for(int i = 0 ; i<eq.size() ; i++)
    {
        if(eq[i][0] == '=')
        {
            eq_sign = i;
            eq[i].erase(0,1);
            if(eq[i][0] == '-')
            {
                eq[i].erase(0,1);
            }
            else
            {
                eq[i] = "-" + eq[i];
            }
        }
        if(eq[i][0] > '9') eq[i] = "1" + eq[i]; //if the user's input was x1 --for example--
        if(eq[i].length() >1)
        {
            if(eq[i][0] == '+' && eq[i][1] > '9')  eq[i].insert(1, "1");
            if(eq[i][0] == '-' && eq[i][1] > '9')  eq[i].insert(1, "1");
        }
        if(i> eq_sign)
        {
        //inverse the +/- sign after equal sign
            if(eq[i][0] == '-')
            {
                eq[i].erase(0,1);
            }
            if(eq[i][0] == '+')
            {
                eq[i].erase(0,1);
                eq[i] = "-" + eq[i];
            }
        }
    }
}
eqn operator* (float num ,eqn eqn)
{
    return(eqn.multiply(num));
}
vector<string> all_vars(vector <eqn> eqns)
{
    vector<string> Vars,holder;
    for(int i = 0; i<eqns.size();i++)
    {
        holder = eqns[i].get_keys();
        Vars.insert(Vars.begin(),holder.begin(),holder.end()-1);
    }
    set<string> vars( Vars.begin() , Vars.end());
    Vars.assign(vars.begin(),vars.end());
    return Vars;
}
void operator<< (ostream &o , eqn  eq)
{
    return eq.print();
}
vector<string> complex_input(string operation)
{
    stringstream ss;
    string temp;
    vector <string> input;
    ss << operation ;
    while(ss>>temp)
    {
        input.push_back(temp);
    }
    return input;
}



