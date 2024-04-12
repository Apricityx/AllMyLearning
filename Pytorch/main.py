import torch as th
import torch.nn as nn
from torch import tensor

loss = nn.MSELoss()

input = th.Tensor([2, 3, 4, 5])
target = th.Tensor([4, 5, 6, 7])
output = loss(input, target)

print(output)

tensor(4.)
