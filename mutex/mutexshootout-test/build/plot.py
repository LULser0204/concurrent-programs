#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import os

def collect(binary, thread_count, mutex_type):
    cmd = f"./{binary} {thread_count} {mutex_type}"
    print(f"Running command: {cmd}")
    output = os.popen(cmd).read()
    print(f"Output: {output}")  
    
    try:
        values = [int(value.strip()) for value in output.split(', ') if value.strip()]
    except ValueError:
        values = []
    return values

def run_tests(binary, thread_count, mutex_types):
    results = {}
    for mutex_type in mutex_types:
        print(f"Testing {mutex_type}...")
        times = collect(binary, thread_count, mutex_type)
        if times:
            results[mutex_type] = np.array(times)
    return results

def plot_results(results):
    plt.figure(figsize=(12, 6))
    for mutex_type, times in results.items():
        if times.size > 0:
            x = np.arange(len(times))
            plt.scatter(x, times, label=mutex_type)
    
    plt.legend()
    plt.ylabel('Latency (ns)')
    plt.xlabel('The i-th Experiment')
    plt.title('Mutex Performance Comparison')
    plt.show()

if __name__ == "__main__":
    binary = "MutexShootout" 
    thread_count = 4  
    mutex_types = ["std", "boost", "pthread"]  
    
    results = run_tests(binary, thread_count, mutex_types)
    plot_results(results)

