#include <bits/stdc++.h>
using namespace std;

set<pair<double,double> > all;



int main()
{
    ios::sync_with_stdio(0);
    double n=0, x1 , y1 , x2 , y2 , x3 , y3,x4,y4 , bx , by ,xx[2],yy[2];
    while(cin >> x1) {
            //cout << x1 <<' ' << y1<< endl;
        cin >>y1 >> x2 >>y2 >> x3 >> y3 >>x4 >> y4;
        int k = 0,s = 1;
        all.insert({x1,y1});
        if(all.find({x2,y2})!= all.end()) {
            bx = x2;
            by = y2;
            all.erase({x2,y2});
        }
        else
            all.insert({x2,y2});
        if(all.find({x3,y3})!= all.end()) {
            bx = x3;
            by = y3;
            all.erase({x3,y3});
        }
        else
            all.insert({x3,y3});
        if(all.find({x4,y4})!= all.end()) {
            bx = x4;
            by = y4;
            all.erase({x4,y4});
        }
        else
            all.insert({x4,y4});
        //cout << all.size()<<endl;
        //cout << xx[0] << ' ' << xx[1] << ' ' << bx << endl;
        double x = all.begin()->first + (++all.begin())->first - bx;
        double y = all.begin()->second+(++all.begin())->second-by;
        //if(n>0) cout << endl;
        //cout << all.begin()->first << ' ' << (++all.begin())->first << endl;
        //cout << all.size();
        printf("%.3lf %.3lf\n",x,y);
        ++n;
        all.clear();
    }

    return 0;
}
