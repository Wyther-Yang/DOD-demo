# DOD-demo
These is a demo that used to compare the difference between DOD and OOD.  
  
  
        ++++++Section of OOD+++++  
        +-----------------------+  
        + 2560 cars in 144 frame +  
        real    0m0.027s  
        +-----------------------+  
        +-----------------------+  
        + 5120 cars in 144 frame +  
        real    0m0.042s  
        +-----------------------+  
        +-----------------------+  
        + 10240 cars in 144 frame +  
        real    0m0.080s  
        +-----------------------+  
        +-----------------------+  
        + 20480 cars in 144 frame +  
        real    0m0.163s  
        +-----------------------+  
        ++++++Section of DOD+++++  
        +-----------------------+  
        + 2560 cars in 144 frame +  
        real    0m0.018s  
        +-----------------------+  
        +-----------------------+  
        + 5120 cars in 144 frame +  
        real    0m0.041s  
        +-----------------------+  
        +-----------------------+  
        + 10240 cars in 144 frame +  
        real    0m0.070s  
        +-----------------------+  
        +-----------------------+  
        + 20480 cars in 144 frame +  
        real    0m0.098s  
        +-----------------------+  

Repeat 100 times, rough look:  

        little data:  
                DOD > OOD performancc;  
        medium:  
                DOD == OOD;  
        huge:  
                DOD >>>>>>>> OOD;  
  
Soon i well test Cache miss with Perf.  


emmm... this's all.


