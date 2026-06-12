# High-Frequency Trading (HFT) Order Matching Engine

## 📌 Overview

This project implements a low-latency trading simulation system in **C++** that models the core mechanics of a High-Frequency Trading (HFT) matching platform. The system processes rapid inbound market data, maintains independent limit order books across multiple stock tickers, executes trades using deterministic matching algorithms, and exports sequential transaction records.

Designed with data structure efficiency in mind, this engine demonstrates how financial systems utilize priority-based sorting to maximize transaction throughput.

---

## 🚀 Features

### 📊 Market Data Analytics
* **CSV Batch Ingestion:** Parses historical market orders from flat-file formats sequentially.
* **Ticker Analytics:** Generates real-time, ticker-wise order metrics and volume statistics.
* **Risk/Exposure Profiling:** Computes trader-level quantity exposure across multiple distinct securities simultaneously.

### ⚙️ Order Matching Engine
* **Price-Time Priority (FIFO):** Enforces exchange-matching logic where compatible orders are matched by the best price level first, and then by the chronological order arrival sequence.
* **Multi-Ticker Independent Books:** Dynamically scales independent buy/sell books per isolated equity ticker.
* **Partial Order Management:** Seamlessly tracks partial order fills, updating resting volumes and leaving remaining balances active in the queue.

### 📝 Trade Execution & Logging
* **Automated Clearing:** Triggers match executions the instant buy and sell thresholds cross.
* **Granular Records:** Captures transaction details including Ticker, Buyer ID, Seller ID, Traded Quantity, Execution Price, and Timestamp.
* **Persistent Auditing:** Exports finalized execution matrices into standard CSV format transaction logs.

---

## 🔄 System Workflow

```text
       Market Orders (Inbound Stream / CSV)
                        │
                        ▼
                Order Processing
                        │
                        ▼
             Order Book Management
         (Independent Ticker Ledgers)
                        │
                        ▼
                 Matching Engine
          (Price-Time Priority Evaluation)
                        │
                        ▼
                 Trade Execution
           (Instant Resolution & Fills)
                        │
                        ▼
                Transaction Logs
             (Output Audit Trail)
```

---

## 🎯 Matching Strategy

The engine strictly tracks exchange-style double-auction execution patterns:
* **Buy Orders:** Instantly matched against the lowest available sell price sitting in the active Ask book.
* **Sell Orders:** Instantly matched against the highest available buy price sitting in the active Bid book.
* **Time Ties:** When multiple orders share identical price levels, the matching loop prioritizes the oldest order in the queue.
* **Fractional Resolution:** Resolves quantity mismatches dynamically, maintaining the unexecuted residual balance in the book while closing the filled portion.

---

## 🛠️ Technologies Used

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (OOP)
* **Standard Library:** Standard Template Library (STL) Containers and Algorithms
* **I/O Engine:** Standard File I/O stream handling for transactional serialization

---

## 📊 Data Structures

The engine maps algorithmic requirements to highly optimized memory layouts to reduce matching overhead:

| Container | System Mapping | Technical Purpose |
| :--- | :--- | :--- |
| `std::vector` | `Order_Storage` | Provides cache-friendly sequential memory layout for linear ingestion. |
| `std::map` | `Ticker_&_Trader_Analytics` | Keeps balance maps sorted dynamically by unique alpha key identifiers. |
| `std::priority_queue` | `Order_Book_Depth` | Enforces max-heap and min-heap sorting for instant $O(1)$ access to best Bid/Ask layers. |

---

## 📈 Sample Execution

### Input (`market_orders.csv`)
```text
BUY Rajesh INFY 100 2450.00
SELL Priya INFY 60 2440.00
```

### Output (`executed_trades.csv`)
```text
Ticker,Seller,Buyer,Qty,Price,Time
INFY,Priya,Rajesh,60,2440.00,0
```

---

## 📂 Project Structure

```text
HFT-Order-Matching-Engine/
│
├── src/
│   └── main.cpp               # Core driver, CSV parser, and matching engine logic
│
├── data/
│   └── market_orders.csv      # Input dataset containing simulated market orders
│
├── output/
│   └── executed_trades.csv    # Generated transaction logs for cleared trades
│
└── README.md                  # Project documentation
```

---

## 🧑‍💻 Author

**RISHI GOUTHAM** C++ | Low-Latency Systems | Computer Science Student  

*Developed as part of systems programming and data structures coursework modeling high-throughput electronic market architectures.*

---

## 📄 License

This project is created for educational and academic simulation purposes under the advanced data structures and software systems curriculum tracks.
```
