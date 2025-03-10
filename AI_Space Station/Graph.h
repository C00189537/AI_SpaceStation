#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <list>

class Node
{
public:

	Node(int xholder, int yholder, bool solidholder) 
	{
		x = xholder;
		y = yholder;
		solid = solidholder;
	};
	~Node() {};

	int x;
	int y;
	int weight;
	int heuristic;
	Node * previous;
	bool marked = false;
	bool solid = false;

	std::vector<Node*> arc;

};

class Graph
{
public:
	Graph(){}
	~Graph(){}

	void AddNode(int x, int y, bool solid)
	{
		m_graph.push_back(new Node(x,y,solid));
	}

	void GenerateGraph()
	{
		int width = 0;
		int height = 0;
		for (int i = 0; i < m_graph.size(); i++)
		{
			m_graph.at(i)->arc.clear();
			if (m_graph.at(i)->x > width)
			{
				width = m_graph.at(i)->x;
			}
			if (m_graph.at(i)->y > height)
			{
				height = m_graph.at(i)->y;
			}
		}

		for (int i = 0; i <= width; i++)
		{
			for (int j = 0; j <= height; j++)
			{
				Node * holder = GetNode(i, j);
				if (!holder->solid)
				{
					if (holder->x - 1 >= 0 && !GetNode(i - 1, j)->solid)
					{
						holder->arc.push_back(GetNode(i - 1, j));
					}
					if (holder->y - 1 >= 0 && !GetNode(i, j - 1)->solid)
					{
						holder->arc.push_back(GetNode(i, j - 1));
					}
					if (holder->x + 1 < width && !GetNode(i + 1, j)->solid)
					{
						holder->arc.push_back(GetNode(i + 1, j));
					}
					if (holder->y + 1 < height && !GetNode(i, j + 1)->solid)
					{
						holder->arc.push_back(GetNode(i, j + 1));
					}
				}
			}
		}

	}

	Node* GetNode(int x, int y)
	{
		for (int i = 0; i < m_graph.size(); i++)
		{
			if (m_graph.at(i)->x == x && m_graph.at(i)->y == y)
			{
				return m_graph.at(i);
				break;
			}
		}
		return 0;
	}

	std::vector<Node> Path(int x, int y, int x2, int y2)//X + Y = Starting position, X2+Y2 = End position
	{
		std::priority_queue<Node *, std::vector<Node*>, SearchCostComparer> pq;

		bool complete = false;

		int width = 0;
		int height = 0;
		for (int i = 0; i < m_graph.size(); i++)
		{
			if (m_graph.at(i)->x > width)
			{
				width = m_graph.at(i)->x;
			}
			if (m_graph.at(i)->y > height)
			{
				height = m_graph.at(i)->y;
			}
		}

		int * pTemp;

		Node* start = GetNode(x, y);
		Node* dest = GetNode(x2, y2);

		for (int i = 0; i < m_graph.size(); i++)
		{
			m_graph.at(i)->marked = false;
			m_graph.at(i)->weight = 9999999;
			m_graph.at(i)->heuristic = sqrt(((dest->x - m_graph.at(i)->x)*(dest->x - m_graph.at(i)->x)) + ((dest->y - m_graph.at(i)->y)*(dest->y - m_graph.at(i)->y)));
			m_graph.at(i)->previous = NULL;
		}

		dest->weight = 0;

		pq.push(dest);
		dest->marked = true;

		while (pq.size() != 0 && pq.top() != start && !complete)
		{
			std::list<Node*> neighbours;

			for (int j = 0; j < pq.top()->arc.size(); j++)
			{
				neighbours.push_back(pq.top()->arc.at(j));
			}

			int sizeholder = neighbours.size();

			while (neighbours.size() != 0 && !complete)
			{
				if (neighbours.front() != pq.top())
				{
					int distC = 1 + pq.top()->weight;
					if (distC < neighbours.front()->weight)
					{
						neighbours.front()->weight = distC;
						neighbours.front()->previous = pq.top();
					}
					if (!neighbours.front()->marked)
					{
						pq.push(neighbours.front());
						neighbours.front()->marked = true;
					}
				}

				neighbours.pop_front();
			}
			pq.pop();
		}

		std::vector<Node> holder;

		holder.push_back(*start);

		std::cout << "Path is (" << holder.back().x << "," << holder.back().y << ")";

		while (holder.back().previous != NULL)
		{
			holder.push_back(*holder.back().previous);
			std::cout << ", (" << holder.back().x << "," << holder.back().y << ")";
		}

		std::cout << "" << std::endl;

		return holder;

	}

private:

	class SearchCostComparer {
	public:
		bool operator()(Node * n1, Node * n2) {
			int p1 = n1->weight;
			int p2 = n2->weight;
			return p1 + n1->heuristic > p2 + n2->heuristic;
		}
	};

	std::vector<Node*> m_graph;

};
#endif