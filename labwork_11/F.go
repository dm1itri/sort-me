package main

import (
	"bufio"
	"fmt"
	"os"
)

type Edge struct {
	to, rev, capacity int
}

type MaxFlow struct {
	graph [][]Edge
	level []int
	iter  []int
}

func NewMaxFlow(n int) *MaxFlow {
	return &MaxFlow{
		graph: make([][]Edge, n),
		level: make([]int, n),
		iter:  make([]int, n),
	}
}

func (mf *MaxFlow) AddEdge(from, to, capacity int) {
	mf.graph[from] = append(mf.graph[from], Edge{to, len(mf.graph[to]), capacity})
	mf.graph[to] = append(mf.graph[to], Edge{from, len(mf.graph[from]) - 1, 0})
}

func (mf *MaxFlow) MaxFlow(from, to int) int {
	flow := 0
	for mf.bfs(from, to) {
		for i := range mf.iter {
			mf.iter[i] = 0
		}
		for f := mf.dfs(from, to, 1e9); f > 0; f = mf.dfs(from, to, 1e9) {
			flow += f
		}
	}
	return flow
}

func (mf *MaxFlow) bfs(from, to int) bool {
	for i := range mf.level {
		mf.level[i] = -1
	}
	queue := []int{from}
	mf.level[from] = 0

	for len(queue) > 0 {
		vertex := queue[0]
		queue = queue[1:]
		for _, e := range mf.graph[vertex] {
			if e.capacity > 0 && mf.level[e.to] < 0 {
				mf.level[e.to] = mf.level[vertex] + 1
				queue = append(queue, e.to)
			}
		}
	}
	return mf.level[to] >= 0
}

func (mf *MaxFlow) dfs(from, to, maxFlow int) int {
	if from == to {
		return maxFlow
	}
	for i := &mf.iter[from]; *i < len(mf.graph[from]); (*i)++ {
		e := &mf.graph[from][*i]
		if e.capacity > 0 && mf.level[from]+1 == mf.level[e.to] {
			if f := mf.dfs(e.to, to, min(maxFlow, e.capacity)); f > 0 {
				e.capacity -= f
				mf.graph[e.to][e.rev].capacity += f
				return f
			}
		}
	}
	return 0
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	var N, M, P int
	fmt.Fscan(reader, &N, &M, &P)

	V := make([]int, N)
	need := make([][]int, N)
	for i := 0; i < N; i++ {
		var K int
		fmt.Fscan(reader, &V[i], &K)
		need[i] = make([]int, K)
		for j := 0; j < K; j++ {
			fmt.Fscan(reader, &need[i][j])
			need[i][j]--
		}
	}

	C := make([]int, M)
	for j := 0; j < M; j++ {
		fmt.Fscan(reader, &C[j])
	}

	pairs := make([]struct{ a, b, d int }, P)
	for i := 0; i < P; i++ {
		fmt.Fscan(reader, &pairs[i].a, &pairs[i].b, &pairs[i].d)
		pairs[i].a--
		pairs[i].b--
	}

	S := N + P + M
	T := S + 1
	maxFlow := NewMaxFlow(T + 1)

	var sumPos int
	for i := 0; i < N; i++ {
		maxFlow.AddEdge(S, i, V[i])
		sumPos += V[i]
		for _, j := range need[i] {
			mnode := N + P + j
			maxFlow.AddEdge(i, mnode, 1e9)
		}
	}

	for k := 0; k < P; k++ {
		s := C[pairs[k].a] + C[pairs[k].b] - pairs[k].d
		if s > 0 {
			bnode := N + k
			maxFlow.AddEdge(S, bnode, s)
			sumPos += s
			maxFlow.AddEdge(bnode, N+P+pairs[k].a, 1e9)
			maxFlow.AddEdge(bnode, N+P+pairs[k].b, 1e9)
		}
	}

	for j := 0; j < M; j++ {
		maxFlow.AddEdge(N+P+j, T, C[j])
	}

	fmt.Println(sumPos - maxFlow.MaxFlow(S, T))
}
