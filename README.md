
# CNN-layer-onlycpp

only using vector, iofstream lib


https://github.com/user-attachments/assets/bfcac4c6-f056-47aa-aa8c-09154ffc547b


- [homemade header](https://github.com/sungjoonyoung/CNN-layer-onlycpp/tree/main/000.equipment_header)
  - Linear Algebra
    - inner product
    - coordinate
    - auto coordinate for NN (insert Bias Unit automatically)
    - exponential
    - convolution (3d, 2d + stride)
  - Activation function
    - sigmoid
    - ReLU
    - derivative
  - String (for data pasing)
    - string "x,xx,x" -> vector{x,xx,x}
    - vector{xx,xxx,x} -> "xx,xxx,x"
    - node vector reader
    - filter reader (3d, 2d)
  

- (ing) [XO-judge](https://github.com/sungjoonyoung/CNN-layer-onlycpp/tree/main/100.NN_XO_judge)
  - dataset
    - X
    - O
    - BMP -> txt
  - layer
    - for Node Vectors
    - for Convolution Matrix
  - main
  - traning main
