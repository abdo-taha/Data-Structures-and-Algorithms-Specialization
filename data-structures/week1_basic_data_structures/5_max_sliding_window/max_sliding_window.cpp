#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::max;

class StackWithMax {
    vector<int> stack;
    vector<int> maximum;


  public:
    StackWithMax(){
        maximum.push_back(-1);
    }
    void Push(int value) {
        stack.push_back(value);
        maximum.push_back( std::max(maximum[maximum.size()-1] , value ) );

    }
    int top(){
        return stack[stack.size()-1 ];
    }
    void Pop() {
        assert(stack.size());
        stack.pop_back();
        maximum.pop_back();
    }

    int Max() const {

        return maximum[maximum.size()-1];
    }
    bool empty(){
        return Max() == -1;
    }
};

class queueWithMax{
    StackWithMax input , output;
public:
    void enqueue(int x){
        input.Push(x);
    }
    int deque(){
        if(output.empty()){
            while(!input.empty()){
                output.Push(input.top() );
                input.Pop();
            }
        }
        int x = output.top();
        output.Pop();
        return x;
    }
    int Max(){
        return max(input.Max(),output.Max());
    }

};

void max_sliding_window_naive(vector<int> const & A, int w) {
    queueWithMax q;
    for(int i = 0; i < w-1;++i){
        q.enqueue(A[i]);
    }
    for(int i = w -1; i< A.size() ; ++i){
        q.enqueue(A[i]);
        cout << q.Max() << " ";
        q.deque();
    }


    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
