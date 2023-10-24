# 导入mindspore中context模块，用于配置当前执行环境，包括执行模式等特性。
import mindspore.context as context
from mindspore import nn

from mindspore.nn.probability.distribution import Normal

# 设置MindSpore的执行模式和设备
context.set_context(mode=context.GRAPH_MODE, device_target='CPU')  # Ascend, CPU, GPU


#定义模型结构，MindSpore中的模型时通过construct定义模型结构，在__init__中初始化各层的对象
class LeNet5(nn.Cell):
    def __init__(self, num_class=10, num_channel=1):
        super(LeNet5, self).__init__()
#定义卷积层，ReLU激活函数，平坦层和全连接层
        #conv2d的输入通道为1维，输出为6维，卷积核尺寸为5*5，步长为1，不适用padding
        self.conv1 = nn.Conv2d(num_channel, 6, 5, pad_mode='valid')
        self.conv2 = nn.Conv2d(6, 16, 5, pad_mode='valid')
        self.fc1 = nn.Dense(16 * 5 * 5, 120, weight_init=Normal(0.02))
        self.fc2 = nn.Dense(120, 84, weight_init=Normal(0.02))
        self.fc3 = nn.Dense(84, num_class, weight_init=Normal(0.02))
        self.relu = nn.ReLU()
        self.max_pool2d = nn.MaxPool2d(kernel_size=2, stride=2)
        self.flatten = nn.Flatten()
    #构建Lenet5架构，x代表网络的输入
    def construct(self, x):
        x = self.max_pool2d(self.relu(self.conv1(x)))
        x = self.max_pool2d(self.relu(self.conv2(x)))
        x = self.flatten(x)
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.fc3(x)
        return x