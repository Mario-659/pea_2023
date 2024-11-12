import pandas as pd
import matplotlib.pyplot as plt

from io import StringIO
data = StringIO("""sample,density,algorithm,averageTimeInNanoseconds
4,100,BruteForce,1749
4,100,BranchAndBound,11467
4,100,Dynamic,1856
5,100,BruteForce,2024
5,100,BranchAndBound,30985
5,100,Dynamic,2438
6,100,BruteForce,3513
6,100,BranchAndBound,98968
6,100,Dynamic,4612
7,100,BruteForce,12406
7,100,BranchAndBound,349184
7,100,Dynamic,8490
8,100,BruteForce,83609
8,100,BranchAndBound,1194608
8,100,Dynamic,19860
9,100,BruteForce,859374
9,100,BranchAndBound,3094458
9,100,Dynamic,51391
10,100,BruteForce,7153273
10,100,BranchAndBound,8556569
10,100,Dynamic,119039
11,100,BruteForce,72318015
11,100,BranchAndBound,26882595
11,100,Dynamic,282624
12,100,BruteForce,857949696
12,100,BranchAndBound,78880414
12,100,Dynamic,665669
13,100,BruteForce,11187921510
13,100,BranchAndBound,199774650
13,100,Dynamic,1593230
""")
df = pd.read_csv(data)

plt.figure(figsize=(10, 6))

for algorithm in df['algorithm'].unique():
    subset = df[df['algorithm'] == algorithm]
    plt.plot(subset['sample'], subset['averageTimeInNanoseconds'], label=algorithm, marker='o', linestyle=':')

plt.yscale('log')
plt.xlabel('Sample Size')
plt.ylabel('Average Time (ns)')
plt.title('Algorithm Performance by Sample Size')
plt.legend()
plt.grid(True)
plt.show()
