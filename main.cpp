#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;


class Person
{
private:
    int code;
    string name;
    int age;
    int status;
public:
    Person(){}

    void setCode(int code)
    {
        this->code = code;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    int getCode()
    {
        return this->code;
    }

    void setStatus(int status)
    {
        this->status = status;
    }

    int getStatus()
    {
        return this->status;
    }

    string getName()
    {
        return this->name;
    }

    int getAge()
    {
        return this->age;
    }
};


class SimpleGraph : public Person
{
    int row, col;
    int personCode = 0;
    Person** person;
    int* vDegree;
    int vAmmount;
    bool iEulerian;

//    /// somatoria de todos os graus do grafo todo
//    int vertexDegreeSum()
//    {
//        int sum = 0;
//        for (int x=0; x<row; x++)
//            sum+= this->vDegree[x];
//
//        return sum;
//    }
//
//    /// retorna a quantidade de arrestas no grafo
//    int getEdgeAmmount()
//    {
//        return vertexDegreeSum()/2;
//    }
//
//    /// retorna todas as adjecencias possiveis em um grafo
//    int getAllPossiblesEdge(int diferenceLogicNumber)
//    {
//        if (diferenceLogicNumber > 0)
//        {
//            return diferenceLogicNumber + (getAllPossiblesEdge(diferenceLogicNumber-1));
//        }
//        return diferenceLogicNumber;
//    }
//
public:
    SimpleGraph(int row, int col)
    {
        this->row = row;
        this->col = col;
        this->vAmmount = 0;
        this->personCode = 0;
        this->vDegree = new int[this->row];
        this->person = new Person*[this->row];
        for (int x = 0; x<row; x++)
             this->person[x] = new Person[this->col];
    }

    void setPerson(string name, int age)
    {
        if (personCode < this->row)
        {
            this->vDegree[personCode] = 0;
            this->person[personCode][0].setCode(personCode);
            this->person[personCode][0].setName(name);
            this->person[personCode][0].setAge(age);
            this->personCode++;
        }
        else
            cout << "Limite maximo" << endl;
    }


    int getRow()
    {
        return this->row;
    }

    int assoc(string name)
    {
        for (int x = 0; x<this->row; x++)
        {
            if (this->person[x][0].getName() == name)
                return this->person[x][0].getCode();
        }
        return -1;
    }

    bool comfirmedFriendship(string yourName, string friendName)
    {
        for (int x = 1; x < this->row; x++)
        {
            if (this->person[assoc(friendName)][x].getName() == yourName)
                return true;
        }
        return false;
    }

    void addFriend(string yourName, string friendName)
    {
        this->person[assoc(yourName)][0].setStatus(1);

        if (assoc(friendName) == 0)
            this->person[assoc(yourName)][assoc(friendName)+1].setName(friendName);
        else
            this->person[assoc(yourName)][assoc(friendName)].setName(friendName);

        if (comfirmedFriendship(yourName,friendName))
            this->person[assoc(yourName)][0].setStatus(2);
    }

    void displayFriends(string yourName)
    {
        for (int x=1; x<this->row; x++)
        {
           if (this->person[assoc(yourName)][x].getName() != "")
           {
                cout << this->person[assoc(yourName)][x].getName() << " ";
                    if (!comfirmedFriendship(yourName,this->person[assoc(yourName)][x].getName()))
                        cout << "(Solicitacao de amizade pendente!)";
                    else cout << "Amigos";
                cout << endl;
           }

        }
    }

    void getInfoAccount(string yourName)
    {
        if (assoc(yourName) != -1)
        {
            cout << "Nome: " << this->person[assoc(yourName)][0].getName() << endl;
            cout << "Idade: " << this->person[assoc(yourName)][0].getAge() << endl << endl;
            cout << "Lista de amizades" << endl;
            displayFriends(yourName);
        }
        else cout << "Conta invalida" << endl;
    }

//
//    /// número de vértices do grafo;
//    int vertexAmmount()
//    {
//        return this->vAmmount;
//    }
//
//    /// o grau de cada vertice
//    int vertexDegree(int vertex)
//    {
//        return vertex > 0 && vertex <= this->row ? this->vDegree[vertex-1] : -1;
//    }
//
//    void printVertex()
//    {
//        for (int x=0; x<row; x++)
//            cout << this->vDegree[x] << endl;
//    }
//
//    /// se um grafo é regular ou não
//    bool isRegular()
//    {
//        int x=0;
//        while (x < this->vAmmount-1)
//        {
//            if(this->vDegree[x] != this->vDegree[x+1]) return false;
//            x++;
//        }
//        return true;
//    }
//    /// o grau do grafo
//
//    /// se é ou não euliriano
//    bool isEulerian()
//    {
//        return this->iEulerian;
//    }
//    /// se tem loops
//
//    /// dados dois vertices dizer se é ou nao adjacente
//    bool isAdjacent(int vertex1, int vertex2)
//    {
//        return this->matrix[vertex1-1][vertex2-1];
//    }
//
//    /// se é completo
//    bool isComplete()
//    {
//       if (getAllPossiblesEdge(vertexAmmount()-1) == getEdgeAmmount())
//        return true;
//       return false;
//    }
//
    void print()
    {
        cout << "\n\nRelatorio geral da rede social" << endl;
        for(int x = 0; x<this->row; x++)
        {
            for(int y = 0; y<this->col; y++)
            {
                if (this->person[x][y].getName() != "")
                {
                    cout <<  this->person[x][y].getName() << " | ";
                }
            }
            cout << "\n";
        }
    }
};

int main()
{
    SimpleGraph grafo(30,30);

    ifstream file;
    string name;

    file.open("accounts.txt");
    int row = 0;
    while (file >> name && row < grafo.getRow())
    {
        grafo.setPerson(name, 40);
        row++;
    }

    grafo.addFriend("Kaila", "Elle");
    grafo.addFriend("Kaila", "Lang");
    grafo.addFriend("Lang", "Akira");
    grafo.addFriend("Lang", "Kaila");

    grafo.addFriend("Simmons", "Leandro");
    grafo.addFriend("Bradley", "Kallie");
    grafo.addFriend("Bradley", "Villa");
    grafo.addFriend("Bradley", "Gomez");


    grafo.getInfoAccount("Lang");

    grafo.print();




//    grafo.print();




}
