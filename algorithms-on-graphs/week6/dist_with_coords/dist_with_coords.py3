#!/usr/bin/python3

import sys
import queue
import math

class AStar:
    def __init__(self, n, adj, cost, x, y):
        # See the explanations of these fields in the starter for friend_suggestion        
        self.n = n
        self.adj = adj
        self.cost = cost
        self.inf = 10**18
        self.d = [[self.inf for i in range(n)],[self.inf for i in range(n)]]
        self.visited = [ [False for i in range(n)],[False for i in range(n)]]
        self.workset = []
        # Coordinates of the nodes
        self.x = x
        self.y = y
        self.best = self.inf
        self.f = 0
        self.t = 0

    # See the explanation of this method in the starter for friend_suggestion
    def clear(self):
        for v in self.workset:
            self.d[0][v] = self.inf
            self.d[1][v] = self.inf
            self.visited[0][v] = False
            self.visited[1][v] = False
        del self.workset[0:len(self.workset)]
        self.best = self.inf
    def pi_f(self,v):
        return int (math.sqrt( (self.x[v]-self.x[self.t])**2 + (self.y[v]-self.y[self.t])**2 ))
    def pi_r(self,v):
        return int (math.sqrt((self.x[v] - self.x[self.f]) ** 2 + (self.y[v] - self.y[self.f]) ** 2) )
    def potential(self,v,side):
        if side:
            return int ((self.pi_f(v)-self.pi_r(v)) / 2)
        return int(-(self.pi_f(v)-self.pi_r(v)) / 2)
    def real_dist(self,v,side):
        return self.d[side][v] - self.potential(v, side)
    # See the explanation of this method in the starter for friend_suggestion
    def visit(self, q, side, v, dist):
        if self.d[side][v] != dist:
            return
        if self.visited[side][v]:
            return

        for i in range(len(self.adj[side][v])) :
            nxt = self.adj[side][v][i]
            cst = self.cost[side][v][i] - self.potential(v,side) + self.potential(nxt,side)
            edge = self.cost[side][v][i]

            if self.d[side][nxt] > dist + cst :
                if self.d[side][nxt] == self.inf and self.d[not side][nxt] == self.inf :
                    self.workset.append(nxt)
                q[side].put((dist+cst,nxt))
                self.d[side][nxt] = dist + cst
                # print(self.real_dist(v,side) ," ", edge , " " , self.real_dist(nxt,not side) , " " , v)
                self.best = min(self.best,self.real_dist(v,side)+edge+self.real_dist(nxt,not side))
        self.visited[side][v] = True

    # Returns the distance from s to t in the graph
    def query(self, s, t):
        self.clear()
        q = [queue.PriorityQueue(),queue.PriorityQueue()]
        self.f = s
        self.t = t
        self.d[0][s] = self.potential(s,0)
        self.d[1][t] = self.potential(t,1)
        self.workset.append(s)
        self.workset.append(t)
        self.visit(q,0,s,self.potential(s,0))
        self.visit(q,1,t,self.potential(t,1))
        while (not q[0].empty()) or (not q[1].empty()):
            if not q[0].empty() :
                vc = q[0].get()
                if(self.visited[1][vc[1]]):
                    break
                self.visit(q,0,vc[1],vc[0])
            if not q[1].empty() :
                vc = q[1].get()
                if(self.visited[0][vc[1]]):
                    break
                self.visit(q,1,vc[1],vc[0])
        for x in self.workset:
            self.best = min(self.best,self.real_dist(x,0)+self.real_dist(x,1))

        if self.best != self.inf:
            return self.best

        return -1

def readl():
    return map(int, sys.stdin.readline().split())

if __name__ == '__main__':
    n,m = readl()
    x = [0 for _ in range(n)]
    y = [0 for _ in range(n)]
    adj = [[[] for _ in range(n)],[[] for _ in range(n)]]
    cost = [[[] for _ in range(n)],[[] for _ in range(n)]]
    for i in range(n):
        a, b = readl()
        x[i] = a
        y[i] = b
    for e in range(m):
        u,v,c = readl()
        adj[0][u-1].append(v-1)
        cost[0][u-1].append(c)
        adj[1][v-1].append(u-1)
        cost[1][v-1].append(c)
    t, = readl()
    astar = AStar(n, adj, cost, x, y)
    for i in range(t):
        s, t = readl()
        print(astar.query(s-1, t-1))
