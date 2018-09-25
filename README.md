# OS_assignment #

1.   [Homework 1](#hw1)
2.   [Homework 2](#hw2)
3.   [Homework 3](#hw3)

<h2 id="hw1">Homework 1</h2>

- **fork()**

  費氏數列（Fibonacci sequence）是將已知數列前兩項相加成為新項的數列，即 0, 1, 1, 2, 3, 5, 8, …

  > fib[0] = 0 <br>
  > fib[1] = 1 <br>
  > fib[n] = fib[n - 1] +fib[n - 2]

  此程式旨在使用 system call `fork()` 將數列生成於 child process，由使用者在 command line 輸入數列大小，例如輸入 5，輸出 0 1 1 2 3 5。
同時，使用 `wait()` 讓 parent process 等待 child process 完成任務後才允許程式結束。

- **Shared Memory**

  使用 shared-memory 為 child process 和 parent process 建立共用的記憶體區段，讓 child process 生成費氏數列後，可直接由parent process 取用並輸出。
  
  在此程式中，定義了一個名為 shared_data 的 struct，其內容如下：
  
      #define MAX_SEQUENCE 10
      
      typedef struct{
        long fib_sequence[MAX_SEQUENCE];
        int sequence_size;
      }shared_data;

  讓 parent process 依序進行以下任務：
  1.	從 command line 接收參數，並確保該參數為正數且不大於 MAX_SEQUENCE。
  2.	生成一個 shared-memory segment。
  3.	將 shared-memory segment attach 到該記憶體空間。
  4.	將 command line 的參數存至 sequence_size。
  5.	使用 `fork()` 產生 child process，並利用 `wait()` 等待 child process 完成任務。
  6.	輸出 shared-memory segment 內的費氏數列。
  7.	detech 及 remove shared-memory segment。
  
  因為 child process 由 parent process 複製而來，shared-memory segment 同樣會附著於 child process 上。child process 產生費氏數列後，detach 掉 shared-memory segment，parent process 仍可取用到費氏數列。<br>
  此應用方式須小心同步（synchronization）的問題。在此程式中，因 parent process 利用 wait() 等待 child process 直到完成任務，故能保持同步。

<h2 id="hw2">Homework 2</h2>

- **Multithread - 1**

  費氏數列（Fibonacci sequence）是將已知數列前兩項相加成為新項的數列，即 0, 1, 1, 2, 3, 5, 8, …

  > fib[0] = 0 <br>
  > fib[1] = 1 <br>
  > fib[n] = fib[n - 1] +fib[n - 2]

  此程式在接收使用者在 command line 所輸入的數列長度後，用 1 條獨立的 child thread 生成數列，最後由 parent thread 輸出結果。
  
- **Multithread - 2**
  
  執行期間透過 multithread 的技術，用 3 條相互獨立的 worker thread 分別執行作業，並把值存在 global 變數。<>
  任務完成後，由 parent thread 輸出結果。
  
<h2 id="hw3">Homework 3</h2>

- **Mutual Exclusion (Mutex)**

  此程式為運用蒙地卡羅方法（Monte Carlo Method）估算圓周率 pi 值。

  先使用多條 threads 亂數產生點，並判斷該點是否落在有效區塊內，然後以 global 變數儲存有效落點的累積個數。最後在 parent thread 計算出估計的 pi 值。<br>
  過程中，以 mutual exclusion(mutex) lock 防止不同的 thread 更新 global 變數時可能產生的 race condition 問題。
