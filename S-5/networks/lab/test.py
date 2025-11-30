def max_reward(A, B, C):

    from collections import defaultdict

    graph = defaultdict(list)
    for u, v, reward in C:
        graph[u].append((v, reward))

    memo = {}

    def dfs(current_place, rewards_used):
        if (current_place, tuple(rewards_used.items())) in memo:
            return memo[(current_place, tuple(rewards_used.items()))]

        max_reward_from_here = 0

        for next_place, base_reward in graph[current_place]:
            road_key = (current_place, next_place)
            if road_key not in rewards_used:
                rewards_used[road_key] = 0

            j = rewards_used[road_key] + 1
            reward = max(0, base_reward - (j * (j - 1) // 2))

            if reward > 0:
                rewards_used[road_key] += 1
                reward_accumulated = reward + dfs(next_place, rewards_used)
                rewards_used[road_key] -= 1

                max_reward_from_here = max(max_reward_from_here, reward_accumulated)

        memo[(current_place, tuple(rewards_used.items()))] = max_reward_from_here
        return max_reward_from_here

    # Start DFS from place B with no roads used
    return dfs(B, defaultdict(int))

import sys
input = sys.stdin.readline

############ ---- Input Functions ---- ############
def inp():
    return(int(input()))
def inlt():
    return(list(map(int,input().split())))
def insr():
    s = input()
    return(list(s[:len(s) - 1]))
def invr():
    return(map(int,input().split()))
a = inp()
b = inp()
n = inp()
c = []
for i in range(n):
    x, y, z = inlt()
    c.append([x, y, z])
print(max_reward(a, b, c))