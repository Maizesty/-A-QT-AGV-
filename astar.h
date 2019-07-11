#ifndef ASTAR_H
#define ASTAR_H
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include<algorithm>
#include <string.h>
using namespace std;

class Node
{   public:
    int x,y;
    int g; //起始点到当前点实际代价
    int h;//当前节点到目标节点最佳路径的估计代价
    int f;//估计值
    Node* father;
    Node()
    {
    this->father = NULL;
    }

    Node(int x,int y)
    {
        this->x = x;
        this->y = y ;
        this->g = 0;
        this->h = 0;
        this->f = 0;
        this->father = NULL;
    }
    Node(int x,int y,Node* father)
    {
        this->x = x;
        this->y = y ;
        this->g = 0;
        this->h = 0;
        this->f = 0;
        this->father = father;
    }
    void changepos(int _x,int _y);
};
class Astar{
    public:
        Astar()
        {
            startPos=new Node();
            endPos=new Node();
        }

        ~Astar();
        void search(Node* _startPos,Node* _endPos);
        void checkPoit(int x,int y,Node* father,int g);
        void NextStep(Node* currentPoint);
        int isContains(vector<Node*>* Nodelist ,int x,int y);
        void countGHF(Node* sNode,Node* eNode,int g);
        static bool compare(Node* n1,Node* n2);
        bool unWalk(int x,int y);
        vector<Node*> openList;
        vector<Node*> closeList;
        Node *startPos;
        Node *endPos;
        Node *way;
        static const int WeightW = 10;// 正方向消耗
        static const int WeightWH = 14;//打斜方向的消耗
        static const int row =31;
        static const int col =31;
        bool mode=true;
};

#endif // ASTAR_H
