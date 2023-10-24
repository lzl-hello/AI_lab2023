# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
"""
Produce the dataset
"""

import os
import mindspore as ms
# 导入mindspore中context模块，用于配置当前执行环境，包括执行模式等特性。
import mindspore.context as context
# c_transforms模块提供常用操作，包括OneHotOp和TypeCast
import mindspore.dataset.transforms as C
# vision.c_transforms模块是处理图像增强的高性能模块，用于数据增强图像数据改进训练模型。
import mindspore.dataset.vision as CV

# 设置MindSpore的执行模式和设备
context.set_context(mode=context.GRAPH_MODE, device_target='CPU')  # Ascend, CPU, GPU


#根据数据集存储地址，生成数据集
def create_dataset(data_dir, training=True, batch_size=32, resize=(32, 32),
                   rescale=1/(255*0.3081), shift=-0.1307/0.3081, buffer_size=64):
    #生成训练集和测试集的路径
    data_train = os.path.join(data_dir, 'train')  # train set
    data_test = os.path.join(data_dir, 'test')  # test set
    #利用MnistDataset方法读取mnist数据集，如果training是True则读取训练集
    ds = ms.dataset.MnistDataset(data_train if training else data_test)
    #map方法是非常有效的方法，可以整体对数据集进行处理，resize改变数据形状，rescale进行归一化，HWC2CHW改变图像通道
    ds = ds.map(input_columns=["image"], operations=[CV.Resize(resize), CV.Rescale(rescale, shift), CV.HWC2CHW()])
    #利用map方法改变数据集标签的数据类型
    ds = ds.map(input_columns=["label"], operations=C.TypeCast(ms.int32))
    # shuffle是打乱操作，同时设定了batchsize的大小，并将最后不足一个batch的数据抛弃
    ds = ds.shuffle(buffer_size=buffer_size).batch(batch_size, drop_remainder=True)
    return ds
