import pandas
maze=pandas.DataFrame([[0 for i in range(8)] for i in range(8)])
maze.to_csv("map.csv",index=False,header=False)