import csv, sys

def read_file(filename):
	'''
	Reads the contents from `filename` and parses it into a graph based on the number of vertices
	'''
	# opening the file and using the csv parser to separate the numbers
	with open(filename, 'r') as csv_file:
		file_handle = csv.reader(csv_file)
		data = next(file_handle)

	# Making a blank (filled with zeros) graph using the number of verties
	graph = [[0 for i in range(int(data[0]))] for j in range(int(data[0]))]

	# Getting the data from the file and inserting it into the graph
	k = 0
	for i in range(0, int(data[0])):
		for j in range(0, int(data[0])):
			k += 1
			graph[i][j] = int(data[k])

	# Returning the number of vertices (the first number in `data`) and the graph we just made
	return int(data[0]),graph

def prims_algorithm(fname):
	'''
	Here we use the Prim's algorithm to find the minimum spanning tree
	'''

	# Getting the number of vertices and the graph from the input file
	number_of_vertices, graph = read_file(fname)

	print(f"{number_of_vertices} vertices found")

	selected_edges = [False] * number_of_vertices

	current_edge = 0

	sum_of_weights = 0

	selected_edges[0] = True

	# Main loop where we add vertices to the spanning tree till there is none left
	while (current_edge < number_of_vertices - 1):

		# Choosing a huge value for minimum so we can compare with other values
		minimum_weight = sys.maxsize
		p, q = 0, 0
		for i in range(number_of_vertices):
			if selected_edges[i]:
				for j in range(number_of_vertices):
					if ((not selected_edges[j]) and graph[i][j]):
						# If the weight of the edge is greater than the current
						# minimum then we add it to the selected edges
						if minimum_weight > graph[i][j]:
							minimum_weight = graph[i][j]
							p = i
							q = j
		print(f"Adding edge ({p}, {q}) with weight {graph[p][q]}.")
		sum_of_weights += graph[p][q]
		# Setting the edge to selected as true
		selected_edges[q] = True
		current_edge += 1

	print(f"\nTotal weight of spanning tree: {sum_of_weights}")


if __name__ == "__main__":
	if len(sys.argv) == 2:
		prims_algorithm(sys.argv[1])