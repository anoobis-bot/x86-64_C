
### Correctness Check for C and x86-64
![image](https://github.com/anoobis-bot/x86-64_C/assets/99565376/9f867907-cdc1-4dea-a0eb-f997cc20c9cc)

***

### Comparative Average Execution Time in Debug Mode
| **Vector Size (n)** |  **C Average Execution Time**  | **x86-64 Average Execution Time** |
| :-----------------: |:------------------------------:| :-------------------------------: |
|    2<sup>20</sup>   |         0.0027 seconds         |           0.0005 seconds          |
|    2<sup>24</sup>   |         0.0528 seconds         |           0.0101 seconds          |
|    2<sup>29</sup>   |         1.9803 seconds         |           0.3247 seconds          |



### Comparative Average Execution Time in Release Mode
| **Vector Size (n)** |  **C Average Execution Time**  | **x86-64 Average Execution Time** |
| :-----------------: |:------------------------------:| :-------------------------------: |
|    2<sup>20</sup>   |         0.0006 seconds         |           0.0006 seconds          |
|    2<sup>24</sup>   |         0.0087 seconds         |           0.0103 seconds          |
|    2<sup>29</sup>   |         0.2932 seconds         |           0.3470 seconds          |

***

### Analysis of the performance of the kernels
<p align="justify"> In debug mode, x86-64 is consistently much faster than C as expected. However, when running the kernels in release mode and the vector size is not that big, x86-64 kernel is slightly slower or just as fast as C kernel, but as the vector increases it is evident x86-64 kernel is slower than C kernel in release mode. This could be because C kernel is optimized and x86-64 is unoptimized on release mode. In both modes, the difference in execution time widens exponentially as the vector size increases which is to be expected. </p>
