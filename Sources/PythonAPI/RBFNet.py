import torch
import numpy as np


class RBFLayer(torch.nn.Module):
    def __init__(self, in_features, out_features, centers=None):
        super(RBFLayer, self).__init__()
        self.in_features = in_features
        self.out_features = out_features
        self.centers = torch.nn.Parameter(torch.Tensor(out_features, in_features))
        self.log_beta = torch.nn.Parameter(torch.Tensor(out_features))
        self.reset_parameters(centers)

    def reset_parameters(self, centers):
        if centers is not None:
            self.centers.data = centers
        else:
            torch.nn.init.kaiming_uniform_(self.centers, a=5)
        torch.nn.init.constant_(self.log_beta, 0)

    # 用模型预测x值
    def forward(self, x):
        size = (x.size(0), self.out_features, self.in_features)
        x = x.unsqueeze(1).expand(size)
        c = self.centers.unsqueeze(0).expand(size)
        beta = torch.exp(-self.log_beta).unsqueeze(0).expand(size[:2])
        return beta * torch.norm(x - c, dim=2)


class RBFNetwork(torch.nn.Module):
    def __init__(self, in_features, hidden_features, out_features, centers=None, *args, **kwargs):
        super(RBFNetwork, self).__init__()
        self.rbf = RBFLayer(in_features, hidden_features, centers)
        self.linear = torch.nn.Linear(hidden_features, out_features)

    def forward(self, x):
        x = self.rbf(x)
        x = torch.exp(-x)
        x = self.linear(x)
        return x


x_train = torch.randn(100, 2)
y_train = torch.sin(x_train[:, 0]) + torch.cos(x_train[:, 1])

rbfModel = RBFNetwork(1, 10, 1)

criterion = torch.nn.MSELoss()
optimizer = torch.optim.Adam(rbfModel.parameters(), lr=0.01)

for epoch in range(1000):
    optimizer.zero_grad()
    y_pred = rbfModel(x_train)
    loss = criterion(y_pred, y_train.unsqueeze(-1))
    loss.backward()
    optimizer.step()
    if epoch % 100 == 0:
        print(f'Epoch {epoch}, Loss: {loss.item()}')

print('====== Finish Train ======')
