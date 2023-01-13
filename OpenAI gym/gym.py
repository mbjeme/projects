import os
import openai
import gym
import time
import numpy as np
import matplotlib.pyplot as plt
import pygame

def eval_policy(qtable_, num_of_episodes_, max_steps_, env):
    rewards = []
    for episode in range(num_of_episodes_):
        print(episode)
        obs, info = env.reset()
        step = 0
        done = False
        total_rewards = 0
        for step in range(max_steps_):
            action = np.argmax(qtable_[obs,:])
            new_state, reward, done, truncated, info = env.step(action)
            total_rewards += reward
            if done:
                rewards.append(total_rewards)
                break
            obs = new_state
    #env.close()
    avg_reward = sum(rewards)/num_of_episodes_
    return avg_reward

def train_qtable(qtable, env, episodes, max_steps):

    rewards = []

    for episode in range(episodes):

        obs, info = env.reset()
        done = False
        step = 0

        print(f"Suoritetaan {episode}...")

        for move in range(max_steps):
            action = np.random.randint(0, 4)
            new_state, reward, done, truncated, info = env.step(action)
            qtable[obs, action] = reward + 0.9 * np.max(qtable[new_state])
            obs = new_state
            if done == True:
                break

        if episode % 10 == 0:
            avg_reward = eval_policy(qtable, 20, 100, env)
            print(f"Evaluation function value {avg_reward}")
            rewards.append(avg_reward)

    return qtable, rewards

def train_qtable_cpart(qtable, env, episodes, max_steps):
    rewards = []

    for episode in range(episodes):

        obs, info = env.reset()
        done = False
        step = 0

        print(f"Suoritetaan {episode}...")

        for move in range(max_steps):
            action = np.random.randint(0, 4)
            new_state, reward, done, truncated, info = env.step(action)
            qtable[obs, action] = qtable[obs, action] + \
                                  0.5*((reward + 0.9 *
                                        np.max(qtable[new_state])) -
                                       qtable[obs, action])
            obs = new_state
            if done == True:
                break

        if episode % 10 == 0:
            avg_reward = eval_policy(qtable, 20, 100, env)
            print(f"Evaluation function value {avg_reward}")
            rewards.append(avg_reward)

    return qtable, rewards

def run_a():
    # Creating the environment
    env = gym.make("FrozenLake-v1", is_slippery=False, render_mode="human")
    env.reset()
    env.render()

    # Defining the values.
    action_size = env.action_space.n
    print("Action size: ", action_size)
    state_size = env.observation_space.n
    print("State size: ", state_size)

    all_rewards = []

    for num in range(10):
        print(f"KOE NUMERO {num + 1}")
        reward_best = -1000
        all_episodes = 201
        max_steps = 100
        qtable = np.random.rand(state_size, action_size)

        trained_qtable, rewards = train_qtable(qtable, env, all_episodes,
                                               max_steps)

        print(qtable)
        print(rewards)

        all_rewards.append(rewards)

    x_axis = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
              150, 160, 170, 180, 190, 200]

    for value in range(10):
        plt.plot(x_axis, all_rewards[value])
    plt.title("Deterministic with deterministic update rule")
    plt.xlabel("Episodes")
    plt.ylabel("Average reward")
    plt.show()

def run_b():
    # Creating the environment
    env = gym.make("FrozenLake-v1", is_slippery=True, render_mode="human")
    env.reset()
    env.render()

    # Defining the values.
    action_size = env.action_space.n
    print("Action size: ", action_size)
    state_size = env.observation_space.n
    print("State size: ", state_size)

    all_rewards = []

    for num in range(10):
        print(f"KOE NUMERO {num+1}")
        reward_best = -1000
        all_episodes = 201
        max_steps = 100
        qtable = np.random.rand(state_size, action_size)

        trained_qtable, rewards = train_qtable(qtable, env, all_episodes,
                                               max_steps)

        print(qtable)
        print(rewards)

        all_rewards.append(rewards)

    x_axis = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
              150, 160, 170, 180, 190, 200]

    for value in range(4):
        plt.plot(x_axis, all_rewards[value])
    plt.title("Non-deterministic with deterministic update rule")
    plt.xlabel("Episodes")
    plt.ylabel("Average reward")
    plt.show()

def run_c():
    # Creating the environment
    env = gym.make("FrozenLake-v1", is_slippery=True, render_mode="human")
    env.reset()
    env.render()

    # Defining the values.
    action_size = env.action_space.n
    print("Action size: ", action_size)
    state_size = env.observation_space.n
    print("State size: ", state_size)

    all_rewards = []

    for num in range(10):
        print(f"KOE NUMERO {num + 1}")
        reward_best = -1000
        all_episodes = 201
        max_steps = 100
        qtable = np.random.rand(state_size, action_size)

        trained_qtable, rewards = train_qtable(qtable, env, all_episodes,
                                               max_steps)

        print(qtable)
        print(rewards)

        all_rewards.append(rewards)

    x_axis = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
              150, 160, 170, 180, 190, 200]

    for value in range(10):
        plt.plot(x_axis, all_rewards[value])
    plt.title("Non-deterministic with non-deterministic update rule")
    plt.xlabel("Episodes")
    plt.ylabel("Average reward")
    plt.show()

def main():
    run_a()
    run_b()
    run_c()

    print("After running the experiments with non-deterministic version (b),")
    print("we can see that compared to deterministic (a) the non-deterministic")
    print("version does not find one exact answer to get the reward. ")
    print("The graph shows a little impovement over time but there is more")
    print("variety of average rewards between diffent runs. ")

    print()

    print("When using the non-deterministic update rule, the graph")
    print("shows a little improvement over time but the average rewards")
    print("are smaller than without the update rule. Compared to the (b)")
    print("graph the variety of average rewards is less random.")





if __name__ == '__main__':
    main()
