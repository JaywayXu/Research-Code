import numpy as np
from Draw import Draw

MaxIt = 1000
ro_np = np.empty((MaxIt))
for it in range(MaxIt):
    # Eq.(14.2)
    beta = 0.2 + (1.2 - 0.2) * pow((1 - pow((it / MaxIt), 3)), 2)
    # Eq.(14.1)
    alpha = abs(beta * np.sin((3 * np.pi / 2 + np.sin(3 * np.pi / 2 * beta))))
    ro_np[it] = alpha * (2 * np.random.rand() - 1)

print(ro_np.mean())
draw = Draw()
draw.drawPloterro([ro_np], ['ro'], 'ro', isSave=True,
                  isDrawSub=False, figName='./ro.png')
