/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-08-07 18:03:56
* @Modified time: 2020-08-07 18:15:42
* @Content:  简单工厂模式
*            书上并没有对这种模式进行具体的分析，只是大概给出利用面对对象编程的思想
*            简单工厂由是三部分组成，工厂类角色、抽象产品类角色、具体产品类角色
*            工厂类在客户端的直接调用下创建产品对象
*            抽象产品角色是所创建的对象的父类，具有相同的特点
*            具体产品角色，简单工程模式所创建的任何对象都是这个角色的实例
*/


#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

//using namespace std;

#include<iostream>
#include<thread>
#include<string>

using namespace std;

// 基类
class Oper{
protected:
    double num1=0, num2=0;

public:
    friend class Interactive;
    Oper(double _num1, double _num2) : num1(_num1), num2(_num2) {}
    Oper() {}
    virtual double Getresult()=0;
};

// +
class OperAdd:public Oper{
public:
    OperAdd(double _num1, double _num2) : Oper(_num1, _num2) {}
    double Getresult(){
        return num1 + num2;
    }
};

// -
class OperMinus:public Oper{
public:
    OperMinus(double _num1, double _num2) : Oper(_num1, _num2) {}
    double Getresult(){
        return num1 - num2;
    }
};

// *
class OperAcc:public Oper{
public:
    OperAcc(double _num1, double _num2) : Oper(_num1, _num2) {}
    double Getresult(){
        return num1 * num2;
    }
};

// /
class OperDiv:public Oper{
public:
    OperDiv(double _num1, double _num2) : Oper(_num1, _num2) {}
    double Getresult(){
        if(abs(num2-0)<1e-9) throw "Division by zero condition!";
        return num1 / num2;
    }
};


class Interactive{
    double numA, numB;
    string opstr;
public:
    Interactive(double _numA, double _numB, string _opstr) : \
        numA(_numA), numB(_numB), opstr(_opstr) {}
    double Calculate(){
        Oper* oopp;
        if(opstr=="+") oopp = new OperAdd(numA, numB);
        if(opstr=="-") oopp = new OperMinus(numA, numB);
        if(opstr=="*") oopp = new OperAcc(numA, numB);
        if(opstr=="/") oopp = new OperDiv(numA, numB);
        return oopp->Getresult();
    }
};

int main(){
    Interactive op1(2.5, 0, "/");
    try{
        double x = op1.Calculate();
        cout << x << endl;
    }
    catch(const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}

