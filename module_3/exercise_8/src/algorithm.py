#!/usr/bin/env python3

import sys
import logging

log = logging.getLogger(__name__)

from math import inf


def warshall(adjlist):
    """
    Returns an NxN matrix that contains the result of running Warshall's
    algorithm.

    Pre: adjlist is not empty.
    """
    adjacency_matrix = adjlist.adjacency_matrix()
    num_nodes = len(adjacency_matrix)

    reachability = []
    for row in range(num_nodes):
        row_reachability = []
        for col in range(num_nodes):
            is_reachable = adjacency_matrix[row][col] != inf or row == col
            row_reachability.append(is_reachable)
        reachability.append(row_reachability)

    for intermediate in range(num_nodes):
        for source in range(num_nodes):
            for destination in range(num_nodes):
                current_reachability = reachability[source][destination]
                path_through_intermediate = (
                    reachability[source][intermediate]
                    and reachability[intermediate][destination]
                )
                reachability[source][destination] = (
                    current_reachability or path_through_intermediate
                )

    return reachability


def floyd(adjlist):
    """
    Returns an NxN matrix that contains the result of running Floyd's algorithm.

    Pre: adjlist is not empty.
    """
    adjacency_matrix = adjlist.adjacency_matrix()
    num_nodes = len(adjacency_matrix)

    distances = []
    for row in range(num_nodes):
        row_distances = []
        for col in range(num_nodes):
            if row != col:
                row_distances.append(adjacency_matrix[row][col])
            else:
                row_distances.append(0)
        distances.append(row_distances)

    for intermediate in range(num_nodes):
        for source in range(num_nodes):
            for destination in range(num_nodes):
                path_through_intermediate = (
                    distances[source][intermediate]
                    + distances[intermediate][destination]
                )
                if path_through_intermediate < distances[source][destination]:
                    distances[source][destination] = path_through_intermediate

    return distances


def dijkstra(adjlist, start_node):
    """
    Returns the result of running Dijkstra's algorithm as two N-length lists:
    1) distance d: here, d[i] contains the minimal cost to go from the node
    named `start_node` to the i:th node in the adjacency list.
    2) edges e: here, e[i] contains the node name that the i:th node's shortest
    path originated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: start_node is a member of adjlist.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 2
    b|* * 2
    c|* * *

    For start node "a", the expected output would then be:

    d: [ None, 1, 2]
    e: [ None, 'a', 'a' ]
    """
    nodes = adjlist.list_nodes()
    adjacency_matrix = adjlist.adjacency_matrix()
    num_nodes = len(nodes)

    start_index = nodes.index(start_node)

    distances = []
    for node_index in range(num_nodes):
        distances.append(inf)

    predecessors = []
    for node_index in range(num_nodes):
        predecessors.append(None)

    distances[start_index] = 0

    visited = []
    for node_index in range(num_nodes):
        visited.append(False)

    for i in range(num_nodes):
        minimum_distance = inf
        current_node = -1
        for node_index in range(num_nodes):
            if not visited[node_index] and distances[node_index] < minimum_distance:
                minimum_distance = distances[node_index]
                current_node = node_index

        if current_node == -1:
            break

        visited[current_node] = True

        for neighbor in range(num_nodes):
            if (
                not visited[neighbor]
                and adjacency_matrix[current_node][neighbor] != inf
            ):
                distance_through_current = (
                    distances[current_node] + adjacency_matrix[current_node][neighbor]
                )
                if distance_through_current < distances[neighbor]:
                    distances[neighbor] = distance_through_current
                    predecessors[neighbor] = nodes[current_node]

    distances[start_index] = None
    predecessors[start_index] = None

    return distances, predecessors


def prim(adjlist, start_node):
    """
    Returns the result of running Prim's algorithm as two N-length lists:
    1) lowcost l: here, l[i] contains the weight of the cheapest edge to connect
    the i:th node to the minimal spanning tree that started at `start_node`.
    2) closest c: here, c[i] contains the node name that the i:th node's
    cheapest edge orignated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: adjlist is setup as an undirected graph and start_node is a member.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 3
    b|1 * 1
    c|3 1 *

    For start node "a", the expected output would then be:

    l: [ None, 1, 1]
    c: [ None, 'a', 'b' ]
    """
    nodes = adjlist.list_nodes()
    adjacency_matrix = adjlist.adjacency_matrix()
    num_nodes = len(nodes)

    start_index = nodes.index(start_node)

    lowcost = []
    for node_index in range(num_nodes):
        lowcost.append(inf)

    closest = []
    for node_index in range(num_nodes):
        closest.append(None)

    lowcost[start_index] = 0

    in_spanning_tree = []
    for node_index in range(num_nodes):
        in_spanning_tree.append(False)

    in_spanning_tree[start_index] = True

    for node_index in range(num_nodes):
        if (
            node_index != start_index
            and adjacency_matrix[start_index][node_index] != inf
        ):
            lowcost[node_index] = adjacency_matrix[start_index][node_index]
            closest[node_index] = start_node

    for i in range(num_nodes - 1):
        minimum_cost = inf
        next_node = -1
        for node_index in range(num_nodes):
            if not in_spanning_tree[node_index] and lowcost[node_index] < minimum_cost:
                minimum_cost = lowcost[node_index]
                next_node = node_index

        if next_node == -1:
            break

        in_spanning_tree[next_node] = True

        for neighbor in range(num_nodes):
            if (
                not in_spanning_tree[neighbor]
                and adjacency_matrix[next_node][neighbor] != inf
            ):
                if adjacency_matrix[next_node][neighbor] < lowcost[neighbor]:
                    lowcost[neighbor] = adjacency_matrix[next_node][neighbor]
                    closest[neighbor] = nodes[next_node]

    lowcost[start_index] = None
    closest[start_index] = None

    return lowcost, closest


if __name__ == "__main__":
    logging.critical("module contains no main")
    sys.exit(1)
