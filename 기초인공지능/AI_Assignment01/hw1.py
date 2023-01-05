############# Write Your Library Here ###########

from collections import deque
from queue import PriorityQueue

################################################


def search(maze, func):
    return {
        "bfs": bfs,
        "dfs":dfs,
        "astar": astar,
        "astar_four_circles": astar_four_circles,
        "astar_many_circles": astar_many_circles
    }.get(func)(maze)


def bfs(maze):
    """
    [Problem 01] 제시된 stage1 맵 세 가지를 BFS Algorithm을 통해 최단 경로를 return하시오.
    """
    ####################### Write Your Code Here ################################
    
    # path는 (x, y) 를 한 element로 갖는 list 이다.
    # path length 는 len(path)로 파악할 수 있다.
    start_point = maze.startPoint()
    queue = deque()
    visited_point = {start_point}
    #dict 형태로, position : position_before 형태를 저장한다.
    parent_node = {}
    queue.append(start_point)
    path = []
    
    # queue에 원소가 존재하면, loop를 반복한다.
    while queue:
        node = queue.popleft()
        if maze.isObjective(node[0], node[1]):
            # 현재 endpoint에 존재한다면, path을 구한다.
            path.append(node)
            while path[-1] != start_point:
                path.append(parent_node[path[-1]])
            
            path.reverse()
            
            return path
        for near_node in maze.neighborPoints(node[0], node[1]):
            if near_node not in visited_point:
                visited_point.add(near_node)
                queue.append(near_node)
                parent_node[near_node] = node
            
    
    ############################################################################


def dfs(maze):
    """
    [Problem 02] 제시된 stage1 맵 세 가지를 DFS Algorithm을 통해 최단 경로를 return하시오.
    """
    
    
    start_point = maze.startPoint()
    path = []
    visited_point = {start_point}
    #dict 형태로, position : position_before 형태를 저장한다.
    parent_node = {}
    ####################### Write Your Code Here ################################
    visited_point = {start_point}
    stack = [start_point]
    mazesize = maze.getDimensions()
    current_path = [0 for i in range(mazesize[0]*mazesize[1])]
    current_path[0] = start_point
    current_length = 1
    

    # backtracking 형태로 min path을 구하는 방법...
    """
    def recursive_dfs(maze, current_path, current_length, path):
        if maze.isObjective(current_path[current_length-1][0], current_path[current_length-1][1]):
            
            print(len(path))

            # 첫 번째로 발견한 path 인 경우
            if len(path) == 0:
                path = [(i[0], i[1]) for i in current_path[0:current_length]]
                #print(path, "is path")

            # 이후 발견한 path의 경우, size를 비교하여 저장한다.
            else:
                if current_length < len(path):
                    path = [(i[0], i[1]) for i in current_path[0:current_length]]
            
            #print(path)

        else:

            if current_length == 1:
                for near_node in maze.neighborPoints(current_path[current_length-1][0], current_path[current_length-1][1]):
                    current_path[current_length] = near_node
                    recursive_dfs(maze, current_path, current_length + 1, path)
        
            else:
                for near_node in maze.neighborPoints(current_path[current_length-1][0], current_path[current_length-1][1]):
                    # 이미 지난 node를 지나며 cycle 등이 생길 수 있는 문제를 방지하기 위해
                    if near_node not in current_path[0:current_length]:
                        current_path[current_length] = near_node
                        recursive_dfs(maze, current_path, current_length + 1, path)

    recursive_dfs(maze, current_path, current_length, path)
    """

    # iterative 한 형태로 구현

    # stack 에 원소가 존재한다면, 탐색을 계속한다.
    while stack:
        # path를 발견한다면, loop를 종료하며 return 한다.
        node = stack.pop()
        if maze.isObjective(node[0], node[1]):
            path.append(node)
            while path[-1] != start_point:
                path.append(parent_node[path[-1]])
            
            path.reverse()

            return path

        for near_node in maze.neighborPoints(node[0], node[1]):
            if near_node not in visited_point:
                visited_point.add(near_node)
                stack.append(near_node)
                parent_node[near_node] = node


    ############################################################################



def manhattan_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def astar(maze):
    """
    [Problem 03] 제시된 stage1 맵 세가지를 A* Algorithm을 통해 최단경로를 return하시오.
    (Heuristic Function은 위에서 정의한 manhattan_dist function을 사용할 것.)
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################
    
    end_point = maze.circlePoints()[0]

    heuristic = manhattan_dist

    pqueue = PriorityQueue()

    #dict 형태로, position : position_before 형태를 저장한다.
    parent_node = {}
    #dict 형태로, value 를 저장한다.
    f_value = {}
    g_value = {}
    h_value = {}

    g_value[start_point] = 0
    h_value[start_point] = heuristic(start_point, end_point)
    f_value[start_point] = g_value[start_point] + h_value[start_point]

    pqueue.put((f_value[start_point], start_point))

    while pqueue.empty() != True:
        node = pqueue.get()[1]
        
        
        if maze.isObjective(node[0], node[1]):
            path.append(node)
            while path[-1] != start_point:
                path.append(parent_node[path[-1]])
            
            path.reverse()

            return path

        else:
            for near_node in maze.neighborPoints(node[0], node[1]):
                current_g_value = g_value[node] + 1
                current_h_value = heuristic(near_node, end_point)
                current_f_value = current_g_value + current_h_value

                if near_node not in f_value.keys():
                    f_value[near_node] = current_f_value
                    g_value[near_node] = current_g_value
                    h_value[near_node] = current_h_value
                    parent_node[near_node] = node
                    pqueue.put((current_f_value, near_node))
                
                elif current_f_value < f_value[near_node]:
                    f_value[near_node] = current_f_value
                    g_value[near_node] = current_g_value
                    h_value[near_node] = current_h_value
                    parent_node[near_node] = node
                    pqueue.put((current_f_value, near_node))


    ############################################################################



def stage2_heuristic(current_pos, destinations, dest_arrived):

    #  현재 위치에서 가장 가까운 목적지로 manhattan_dist 을 heuristic으로 이용한다.
    dest_left = [destinations[i] for i in range(4) if dest_arrived[i] == 0]
    
    if dest_left == []:
        return 0
    
    x1_diff = [abs(i[0] - current_pos[0]) for i in dest_left]
    x2_diff = [abs(i[1] - current_pos[1]) for i in dest_left]
    manhattan_value = min(x1_diff) + min(x2_diff)

    return manhattan_value

def astar_four_circles(maze):
    """
    [Problem 04] 제시된 stage2 맵 세 가지를 A* Algorithm을 통해 최단경로를 return하시오.
    (Heuristic Function은 직접 정의할것)
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################

    # 필요한 것 : 
    
    pqueue = PriorityQueue()

    # 각 destination은 [1, 0, 1, 1] 와 같이 방문을 기준으로 적용된다.
    destinations = maze.circlePoints()

    heuristic = stage2_heuristic
    
    
    # visited_node, visited_destination pair(set) 을 저장할 수 있는 visited
    f_value = {}
    g_value = {}
    h_value = {}

    # path을 저장하기 위한 parent_node 또한 dict 로 저장
    parent_node = {}

    path_save = []


    g_value[(start_point, (0, 0, 0, 0))] = 0
    h_value[(start_point, (0, 0, 0, 0))] = heuristic(start_point, destinations, (0, 0, 0, 0))
    f_value[(start_point, (0, 0, 0, 0))] = g_value[(start_point, (0, 0, 0, 0))] + h_value[(start_point, (0, 0, 0, 0))]

    pqueue.put((f_value[(start_point, (0, 0, 0, 0))], (0, 0, 0, 0), start_point))
    
    while pqueue.empty() != True:
        

        dest_arrived, node = pqueue.get()[1:]

        
        # 모든 destination을 확인한 경우,
        if all(dest_arrived):
            path_save.append((node, dest_arrived))
            while path_save[-1][0] != start_point or path_save[-1][1] != (0, 0, 0, 0):
                path_save.append(parent_node[path_save[-1]])
            
            path = [i[0] for i in path_save]
            
            path.reverse()

            return path

        else:
            #print(parent_node)

            for near_node in maze.neighborPoints(node[0], node[1]):
                new_dest = list(dest_arrived)
                for i in range(4):
                    if near_node == destinations[i]:
                        new_dest[i] = 1
                new_dest = tuple(new_dest)
                
                current_g_value = g_value[(node, dest_arrived)] + 1
                current_h_value = heuristic(near_node, destinations, new_dest)
                current_f_value = current_g_value + current_h_value

                if (near_node, new_dest) not in f_value.keys() or current_f_value < f_value[(near_node, new_dest)]:
                
                    f_value[(near_node, new_dest)] = current_f_value
                    g_value[(near_node, new_dest)] = current_g_value
                    h_value[(near_node, new_dest)] = current_h_value

                    # near_node 가 destination 중 하나인 경우
                    if new_dest != dest_arrived:
                        
                        parent_node[(near_node, new_dest)] = (node, dest_arrived)
                        pqueue.put((current_f_value, new_dest, near_node))
                    else:
                        parent_node[(near_node, dest_arrived)] = (node, dest_arrived)
                        pqueue.put((current_f_value, dest_arrived, near_node))








    ############################################################################

def mst(dest_arrived, sorted_edge):
    sum_value = 0
    edge_count = 0
    edge_index = 0
    # 포함된 집합을 표현한 dest_dict 이다.
    dest_dict = {i:i for i in range(len(dest_arrived))}
    '''
    #priorityqueue에 edge를 대입한다.
    pqueue = PriorityQueue()
    for i in range(len(dest_arrived)):
        for j in range(len(dest_arrived)):
            if i < j and dest_arrived[i] == 0 and dest_arrived[j] == 0:
                pqueue.put((dest_to_dest[i][j], i, j))
    '''
    while edge_count < dest_arrived.count(0) - 1:
        #print(dest_dict)
        data = sorted_edge[edge_index]
        # node 를 이미 거친 경우,
        if dest_arrived[data[1]] == 1 or dest_arrived[data[2]] == 1:
            edge_index += 1
            continue

        # 두 edge 가 서로 다른 set을 연결하는 경우 (cycle 을 만들지 않는 경우와 동일하다.) 
        if dest_dict[data[1]] != dest_dict[data[2]]:
            save_set = min(dest_dict[data[1]], dest_dict[data[2]])
            change_set = max(dest_dict[data[1]], dest_dict[data[2]])
            
            sum_value += data[0]
            edge_count += 1
            
            for i in range(len(dest_arrived)):
                if dest_dict[i] == change_set:
                    dest_dict[i] = save_set
        
        edge_index += 1
    
    #print('done')
    #print(sum_value)
    return sum_value

def stage3_heuristic(current_pos, destinations, dest_arrived, sorted_edge):
    
    # 2 가지의 value 를 이용한다.

    # 첫 번째는 현재 위치에서 가장 가까운 목적지로 manhattan_dist
    # 두 번째는 MST value, 즉 모든 남은 목적지를 연결하기 위한 value 를 사용한다.
    # 구한 두 값을 더한 값을 stage3_heuristic value 로 설정한다.
    dest_left = [destinations[i] for i in range(len(destinations)) if dest_arrived[i] == 0]
    if dest_left == []:
        return 0

    x1_diff = [abs(i[0] - current_pos[0]) for i in dest_left]
    x2_diff = [abs(i[1] - current_pos[1]) for i in dest_left]

    manhattan_value = min(x1_diff) + min(x2_diff)

    mst_value = mst(dest_arrived, sorted_edge)

    return manhattan_value + mst_value


def astar_many_circles(maze):
    """
    [Problem 05] 제시된 stage3 맵 다섯 가지를 A* Algorithm을 통해 최단 경로를 return하시오.
    (Heuristic Function은 직접 정의 하고, minimum spanning tree를 활용하도록 한다.)
    """

    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################

    destinations = maze.circlePoints()
    dest_size = len(destinations)
    maze_size = maze.getDimensions()

    # 각 dest to dest 의 length 을 파악하기 위한 부분이다.
    sorted_edge = []
    
    for i in range(dest_size):
        for j in range(dest_size):
            
            if i == j:
                break
            
            start_point_in_bfs = destinations[j]
            queue = deque()
            visited_point = {start_point_in_bfs}
            #dict 형태로, position : position_before 형태를 저장한다.
            parent_node = {}
            queue.append(start_point_in_bfs)
            path_in_bfs = []
    
            # queue에 원소가 존재하면, loop를 반복한다.
            while queue:
                node = queue.popleft()
                if node == destinations[i]:
                # 현재 endpoint에 존재한다면, path을 구한다.
                    path_in_bfs.append(node)
                    while path_in_bfs[-1] != start_point_in_bfs:
                        path_in_bfs.append(parent_node[path_in_bfs[-1]])
        
                    sorted_edge.append((len(path_in_bfs), j, i))
                    break
                
                for near_node in maze.neighborPoints(node[0], node[1]):
                    if near_node not in visited_point:
                        visited_point.add(near_node)
                        queue.append(near_node)
                        parent_node[near_node] = node
            
            """
            # 동일하게 manhattan 형태로 구현한다.
            man_x1 = abs(destinations[i][0] - destinations[j][0])
            man_x2 = abs(destinations[i][1] - destinations[j][1])
            sorted_edge.append((man_x1 + man_x2, j, i))
            """

    sorted_edge.sort(key = lambda x : (x[0], x[1], x[2]))                


    # astar로 최한 거리를 구하는 과정, Stage2와 동일하며, 4가 아닌 dest_size로 처리한다.
    # 또한 heuristic 의 인자 또한 바꾸어 주어야 한다.
    pqueue = PriorityQueue()

    heuristic = stage3_heuristic
    
    
    # visited_node, visited_destination pair(set) 을 저장할 수 있는 visited
    f_value = {}
    g_value = {}
    h_value = {}

    # path을 저장하기 위한 parent_node 또한 dict 로 저장
    parent_node = {}

    path_save = []

    tuple_0 = [0 for i in range(dest_size)]
    tuple_0 = tuple(tuple_0)
    
    g_value[(start_point, tuple_0)] = 0
    h_value[(start_point, tuple_0)] = heuristic(start_point, destinations, tuple_0, sorted_edge)
    f_value[(start_point, tuple_0)] = g_value[(start_point, tuple_0)] + h_value[(start_point, tuple_0)]


    pqueue.put((f_value[(start_point, tuple_0)], tuple_0.count(0), tuple_0, start_point))
    
    while pqueue.empty() != True:
        
        val, count, dest_arrived, node = pqueue.get()[:]
        
        # 모든 destination을 확인한 경우,
        if all(dest_arrived):
            path_save.append((node, dest_arrived))
            while path_save[-1][0] != start_point or path_save[-1][1] != tuple_0:
                path_save.append(parent_node[path_save[-1]])
            
            path = [i[0] for i in path_save]
            path.reverse()

            return path


        else:
            #print(parent_node)

            for near_node in maze.neighborPoints(node[0], node[1]):

                # 다음 위치가 destinations 중 하나인 경우, dest_arrived[i] = 1 로 설정해 준다.
                new_dest = list(dest_arrived)
                for i in range(dest_size):
                    if near_node == destinations[i]:
                        new_dest[i] = 1
                new_dest = tuple(new_dest)

                current_g_value = g_value[(node, dest_arrived)] + 1
                current_h_value = heuristic(near_node, destinations, new_dest, sorted_edge)
                current_f_value = current_g_value + current_h_value


                if (near_node, new_dest) not in f_value.keys() or current_f_value < f_value[(near_node, new_dest)]:
                
                    f_value[(near_node, new_dest)] = current_f_value
                    g_value[(near_node, new_dest)] = current_g_value
                    h_value[(near_node, new_dest)] = current_h_value

                    # near_node 가 destinations 중 하나인 경우
                    if new_dest != dest_arrived:
                        
                        parent_node[(near_node, new_dest)] = (node, dest_arrived)
                        pqueue.put((current_f_value, new_dest.count(0), new_dest, near_node))
                    else:
                        parent_node[(near_node, dest_arrived)] = (node, dest_arrived)
                        pqueue.put((current_f_value, dest_arrived.count(0), dest_arrived, near_node))


    ############################################################################
