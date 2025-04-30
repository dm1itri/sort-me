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
	var n int
	fmt.Fscan(reader, &n)

	wins := make([]int, n)
	remain := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &wins[i])
	}
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &remain[i])
	}

	games := make([][]int, n)
	for i := 0; i < n; i++ {
		games[i] = make([]int, n)
	}

	totalGames := 0
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			fmt.Fscan(reader, &games[i][j])
			if i < j {
				totalGames += games[i][j]
			}
		}
	}

	maxWins := wins[0] + remain[0]
	for i := 1; i < n; i++ {
		if wins[i] > maxWins {
			fmt.Println("NO")
			return
		}
	}

	gameNodeStart := 1
	teamNodeStart := gameNodeStart + n*n
	sink := teamNodeStart + n

	mf := NewMaxFlow(sink + 1)

	totalFlowNeeded := 0
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			gameCount := games[i][j]
			if gameCount == 0 {
				continue
			}

			gameNode := gameNodeStart + i*n + j
			mf.AddEdge(0, gameNode, gameCount)
			mf.AddEdge(gameNode, teamNodeStart+i, gameCount)
			mf.AddEdge(gameNode, teamNodeStart+j, gameCount)
			totalFlowNeeded += gameCount
		}
	}

	for i := 1; i < n; i++ {
		maxExtra := maxWins - wins[i]
		mf.AddEdge(teamNodeStart+i, sink, maxExtra)
	}

	mf.AddEdge(teamNodeStart, sink, 1e9)

	if mf.MaxFlow(0, sink) == totalFlowNeeded {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
