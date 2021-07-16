# Bidirectional-Dijkstra
# Bidirectional-Dijkstra
In this fast moving world we want everything to be done within seconds or even milliseconds. We want to find the optimized solution for every single problem we encounter. So this is the optimized solution to normal dijkstra algorithim.

We know dijkstra expands in a circle so we want to go from S to T and radius of circle is 2r so area covewred will be pi*(2r)^2 == 4*pi*r^2 and on the other hand in case of bidirectional dijkstra we move from both sides like from S and also from T and and as we encounter a common node we stop, let the common node be U so from S to U it will be a circle of radius r and from T tu U it will be also r so area will sum up to pi*r^2 + pi*r^2 == 2*pi*r^2.<br />

![bidirectional_dijkstra](https://user-images.githubusercontent.com/42600243/125914023-d0b2188f-5def-4c95-9619-1140dd96d9a6.png)


So we can see that it is half than the the original dijkstra.
