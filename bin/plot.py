#!/usr/bin/env python3

import glob
import pandas as pd

data = []
for file in glob.glob("*.freq", ):
    data.append(file)

legend = []
for i, f in enumerate(data):
  df = pd.read_csv(f)
  ts = int(df.columns[0])
  legend.append(f.split('.')[0] + ' - cpu=' + f.split('.')[1])

  df.index = pd.RangeIndex(start=ts, stop=ts + df.shape[0])

  if i == 0:
    result = df.copy()
  else:
    result = pd.concat([result, df], axis=1, sort=False)

ax = result.plot()

ax.axes.xaxis.set_visible(False)
ax.set_ylabel("Current frequency of the CPU")
ax.legend(legend, loc='lower right')

ax.get_figure().savefig('plot.pdf') 