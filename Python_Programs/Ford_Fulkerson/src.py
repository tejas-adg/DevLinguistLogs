import csv, sys

def read_file(filename):
	'''
	Reads the contents from `filename` and   it into a graph based on the number of vertices
	'''
	# opening the file and using the csv parser to separate the numbers
	with open(filename, 'r') as csv_file:
		file_handle = csv.reader(csv_file)
		data = next(file_handle)

	# Making a blank (filled with zeros) graph using the number of verties
	graph = [[0 for i in range(int(data[0]))] for j in range(int(data[0]))]

	# Getting the data from the file and inserting it into the graph
	k = 0

	# from 0 to end
	for i in range(0, int(data[0])):
		for j in range(0, int(data[0])):
			k += 1
			graph[i][j] = int(data[k])

	# Returning the number of vertices (the first number in `data`) and the graph we just made
	return int(data[0]),graph

class ford_fulkerson:

	def __init__(directed, graph):
		directed.graph = graph
		directed.number_of_rows = len(graph)

	# Using BFS as a searching algorithm
	def breadth_first_search(directed, s, t, parent):
		selected_edges = [False] * (directed.number_of_rows)
		FIFO_list = []

		FIFO_list.append(s)
		selected_edges[s] = True

		while FIFO_list:
			u = FIFO_list.pop(0)
			for ind, val in enumerate(directed.graph[u]):
				if selected_edges[ind] == False and val > 0:
					FIFO_list.append(ind)
					selected_edges[ind] = True
					parent[ind] = u

		return True if selected_edges[t] else False

	# Applying fordfulkerson algorithm
	def run(directed, source, sink):
		papa = [-1] * (directed.number_of_rows)
		total_flow = 0

		while directed.breadth_first_search(source, sink, papa):   
			# assuming the max bottleneck first
			bottleneck_capacity = float("Inf")
			temporary_list, temp_sink = [], sink
			temporary_list.append(sink)
			while(temp_sink != source):
				bottleneck_capacity = min(bottleneck_capacity, directed.graph[papa[temp_sink]][temp_sink])
				temp_sink = papa[temp_sink]
				temporary_list.append(temp_sink)
			temporary_list.reverse() 
			directed.print_path(bottleneck_capacity, temporary_list)

			# Adding the path flows
			total_flow += bottleneck_capacity

			# Updating the residual values of edges
			directed.update(source, sink, papa, bottleneck_capacity)

		return total_flow

	def update(directed, source, sink, papa, bottleneck_capacity):
		temp_sink = sink
		while (temp_sink != source):
			temp2 = papa[temp_sink]
			directed.graph[temp2][temp_sink] -= bottleneck_capacity
			directed.graph[temp_sink][temp2] += bottleneck_capacity
			temp_sink = papa[temp_sink]

	def print_path(self, bottleneck_capacity, temporary_list):
		print(f"Augmenting Path found: {' '.join([str(i) for i in temporary_list])} with flow: {bottleneck_capacity}")

if __name__ == "__main__":
	if len(sys.argv) == 2:
		sink, graph = read_file(sys.argv[1])
		g = ford_fulkerson(graph)
		source = 0
		sink -= 1
		print(f"\nTotal flow: {g.run(source, sink)}")