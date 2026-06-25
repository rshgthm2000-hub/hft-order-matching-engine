# High-Frequency Trading (HFT) Order Matching Engine

## 📌 Overview

This project implements a trading simulation system in **C++** that models the mechanics of an exchange matching platform. The system is divided into three distinct execution modules (P1, P2, P3) to handle market data parsing, trader profiling, and a live order-matching engine. 

Designed using Standard Template Library (STL) vectors and custom sorting comparators, this engine demonstrates how financial systems evaluate price-time priority to clear trades.

---

## 🚀 Execution Modes & Features

The system operates in three distinct modes based on standard input (`P1`, `P2`, or `P3`):

### **Part 1 (P1): Ticker Analytics**
* **CSV Batch Ingestion:** Parses historical market orders from a flat CSV file.
* **Order Counting:** Groups inbound orders by `CompanyTicker`.
* **Output:** Sorts tickers alphabetically and prints the total number of orders (Buy + Sell) placed for each distinct security.

### **Part 2 (P2): Trader Risk/Exposure Profiling**
* **Trader-Centric Ledgers:** Repurposes the book structure to group data by `UserName` instead of the ticker.
* **Quantity Aggregation:** Calculates the total volume (quantity) of shares a specific trader has placed across all their orders.
* **Targeted Output:** Accepts a list of specific trader names from standard input and outputs their total combined order quantities.

### **Part 3 (P3): Live Order Matching Engine**
* **Standard Input Stream:** Reads a continuous stream of space-separated market orders (`TYPE USER TICKER QTY PRICE`).
* **Price-Time Priority (FIFO):** Enforces exchange-matching logic. Compatible orders are matched by the best price level first, and then by the chronological order arrival sequence.
* **Partial Order Management:** Tracks partial order fills, updating resting volumes and leaving remaining balances active in the queue.
* **Automated Clearing & Logging:** Triggers executions instantly when buy and sell thresholds cross, logging outputs to a specific formatted CSV file.

---

## 🔄 P3 Matching Strategy

The matching engine (Part 3) strictly tracks exchange-style double-auction execution patterns:
* **Buy Orders:** Sorted to match against the lowest available sell price sitting in the active Ask book.
* **Sell Orders:** Sorted to match against the highest available buy price sitting in the active Bid book.
* **Time Ties:** When multiple orders share identical price levels, the engine prioritizes the oldest order (tracked via a global incrementing order time variable).
* **Fractional Resolution:** Resolves quantity mismatches dynamically, deducting the traded amount and retaining the unexecuted residual balance in the vector.

---

## 🛠️ Technologies Used

* **Language:** C++
* **Paradigm:** Procedural & Object-Oriented Programming (OOP)
* **Standard Library:** Standard Template Library (STL)
* **File Handling:** `std::ifstream` and `std::ofstream` for data ingestion and transaction serialization.

---

## 📊 Data Structures

The engine maps algorithmic requirements using lightweight standard containers:

| Container / Algorithm | Technical Purpose |
| :--- | :--- |
| `std::vector<Book>` | Acts as the main dynamic registry for storing independent tickers (or traders in P2). Searched linearly via a custom `find_idx` function. |
| `std::vector<Order>` | Maintains the isolated `buy` and `sell` order layers inside each Book. |
| `std::sort()` | Used dynamically on-the-fly to enforce Price-Time priority right before evaluating potential matches. |

---

## 📂 I/O & Project Structure

The project relies on specific local directory paths for logging executed trades in **Part 3**:

* **Input (`P1` & `P2`):** Reads standard comma-separated lines.
* **Input (`P3`):** Reads space-separated lines from standard input.
* **Output (`P3`):** Writes executed trades to `./actual_output/Q1/CSV/CS24B009/[fileName]`

### Sample Output Log (`P3` Executed Trades)
```csv
Ticker,Seller,Buyer,Qty,Price,Time
INFY,Priya,Rajesh,60,2440.00,0

---

## 🧑‍💻 Author

**RISHI GOUTHAM (CS24B009)** *C++ | Systems Programming | Computer Science Student* > Developed as part of systems programming and data structures coursework modeling electronic market architectures.

---

## 📄 License

This project is created for educational and academic simulation purposes under the advanced data structures and software systems curriculum tracks.
