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

	var N, M, w, b, g int
	fmt.Fscan(reader, &N, &M, &w, &b, &g)

	grid := make([]string, N)

	for i := 0; i < N; i++ {
		fmt.Fscan(reader, &grid[i])
	}

	total := N * M
	S := total
	T := total + 1

	mf := NewMaxFlow(total + 2)

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			id := i*M + j
			if grid[i][j] == 'B' {
				mf.AddEdge(S, id, 0)
				mf.AddEdge(id, T, w)
			} else {
				mf.AddEdge(S, id, b)
				mf.AddEdge(id, T, 0)
			}
		}
	}

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			u := i*M + j
			for d := 0; d < 4; d++ {
				ni, nj := i+dx[d], j+dy[d]
				if ni >= 0 && ni < N && nj >= 0 && nj < M {
					v := ni*M + nj
					mf.AddEdge(u, v, g)
				}
			}
		}
	}

	fmt.Println(mf.MaxFlow(S, T))
}
